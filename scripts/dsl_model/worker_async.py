from dsl_rl import VOCAB
import math
from . import utils
import pandas as pd
import torch

class Worker:
    def __init__(self, engine):
        self.j = None
        self.engine = engine

    def prepare_experience(self):
        prog_graphs: list = []
        cost_tensors: list = []
        grid_tensors: list = []

        for program, df, outputs in self.candidates:
            g = utils.build_prog_graph(program, VOCAB, "cuda")
            prog_graphs.append(g.cpu())

            c = utils.dataframe_to_cost_tensor(df)
            cost_tensors.append(c.cpu())

            t = utils.grids_to_tensors(outputs)
            grid_tensors.append(t.cpu())

        return prog_graphs, cost_tensors, grid_tensors

    def init(self, device: str, j: int) -> bool:
        self.j = j
        self.targetProgram = self.engine.program(j)
        self.trajectory = self.engine.trajectory(j)
        self.grids = self.engine.grids(j)

        try:
            self.outputs = self.engine.outputs(j)
        except RuntimeError:
            self.j = None

            return False

        pairs = list(zip(self.grids, self.outputs))
        inputs, outputs, masks = utils.arc_pairs_to_tensors(pairs)
        self.inputs = inputs.to(device)
        self.outputs = outputs.to(device)
        self.masks = masks.to(device)
        self.costs = list(reversed(self.trajectory))
        self.costs = sorted(self.costs, key = lambda x: (-x[0], len(x[1])))

        try:
            self.candidates: list = [("I", pd.DataFrame(self.engine.dfIdentity(j), columns = utils.scoreColumns), self.grids)] * utils.M
        except RuntimeError:
            self.candidates: list = [("I", pd.DataFrame([math.inf] * len(utils.scoreColumns), columns = utils.scoreColumns), self.grids)] * utils.M

        self.computeGraphs: bool = True
        self.temperature: float = utils.minTemperature
        self.testedPrograms = set()
        self.alpha: float = 1.0
        self.programCount: int = 1
        self.best_seen_cost = self.candidates[-1][1].sum(axis = 0, skipna = False)["Total cost"]
        self.iters_since_improvement = 0
        self.program = None
        self.cost = None
        self.df = None
        self.use_semantic = None
        self.count: int = 0
        self.prog_graphs = None
        self.cost_tensors = None
        self.subtargetProgram = None
        self.programOutputs = None
        self.outputTensors = None

        return True

    def process(self, model, device: str) -> bool:
        if (self.j == None):
            return False

        if (not self.candidates[-1][1].sum(axis = 0, skipna = False)["Total cost"]):
            return False

        if (not len(self.costs)):
            return False
        
        self.current_best = self.candidates[-1][1].sum(axis = 0, skipna = False)["Total cost"]

        if (self.current_best < self.best_seen_cost):
            self.best_seen_cost = self.current_best
        else:
            self.iters_since_improvement += 1

        if (self.count >= utils.MAX_ITERATIONS_PER_TARGET or self.iters_since_improvement >= utils.PLATEAU_PATIENCE):
            return False

        if (self.computeGraphs):
            self.prog_graphs, self.cost_tensors, self.grid_tensors = self.prepare_experience()

            self.computeGraphs = False

            model.eval()

            with torch.no_grad():
                self.z_context = model.encode_context(
                    self.inputs.to(device),
                    self.outputs.to(device),
                    self.masks.to(device),
                    [g.to(device) for g in self.prog_graphs],
                    [c.to(device) for c in self.cost_tensors],
                    [t.to(device) for t in self.grid_tensors],
                )

        torch.cuda.empty_cache()

        self.subtargetProgram = self.costs[0][1]

        self.program = utils.generate_one_cached(
            model,
            VOCAB,
            self.z_context,
            self.engine,
            temperature=self.temperature,
            device=device,
            max_depth=utils.programDepth(self.subtargetProgram) if self.costs else 0,
        )

        if (not self.program):
            self.cost = math.inf
        else:
            try:
                self.df = pd.DataFrame(self.engine.dfConnectionBuilder(self.j), columns = utils.scoreColumns)
                self.cost = self.df["Total cost"].sum(skipna = False)
                self.programOutputs = self.engine.dfConnectionBuilderOutputs(self.grids)

                if (any(not utils.is_valid_arc_grid(g) for g in self.programOutputs)):
                    self.program = None
            except RuntimeError:
                self.cost = math.inf

        if (not self.program or math.isinf(self.cost)):
            self.temperature = min(utils.maxTemperature, self.temperature * 1.05)
            self.alpha = min(1.0, self.alpha * 1.5)
            self.use_semantic = False
        elif (self.cost <= self.costs[0][0]):
            self.temperature = max(utils.minTemperature, self.temperature * 0.95)
            self.alpha = max(utils.minAlpha, self.alpha * 0.9)
            self.use_semantic = True
        else:
            self.temperature = min(utils.maxTemperature, self.temperature * 1.05)
            self.alpha = min(1.0, self.alpha * 1.5)
            self.use_semantic = False
            
        if (self.program):
            if (self.cost < self.candidates[0][1].sum(axis = 0, skipna = False)["Total cost"]
                and not self.program in [c[0] for c in self.candidates]):
                self.computeGraphs = True
                self.iters_since_improvement = 0

                self.candidates.pop(0)
                self.candidates.append((self.program, self.df, self.programOutputs))
                self.candidates = sorted(self.candidates, key = lambda x: (tuple(-x[1].sum(axis = 0, skipna = False)), -len(x[0]), x[0]))

                while (len(self.costs) and self.cost <= self.costs[0][0]):
                    self.costs.pop(0)
            elif (not math.isinf(self.cost) and not self.program in self.testedPrograms):
                self.iters_since_improvement = 0 #TODO: to remove?

            if (not self.program in self.testedPrograms):
                self.testedPrograms.add(self.program)

        self.count += 1

        return True
