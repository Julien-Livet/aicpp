from dsl_rl import VOCAB
import math
import pandas as pd
import torch
import torch.nn.functional as F
from . import utils

class Worker:
    def __init__(self):
        self.j = None

    def init(self, engine, device: str, j: int) -> bool:
        self.j = j
        self.targetProgram = engine.program(j)
        self.trajectory = engine.trajectory(j)
        self.grids = engine.grids(j)

        try:
            self.outputs = engine.outputs(j)
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
            self.candidates: list = [("I", pd.DataFrame(engine.dfIdentity(j), columns = utils.scoreColumns))] * utils.M
        except RuntimeError:
            self.candidates: list = [("I", pd.DataFrame([math.inf] * len(utils.scoreColumns), columns = utils.scoreColumns))] * utils.M

        self.computeGraphs: bool = True
        self.temperature: float = utils.minTemperature
        self.testedPrograms = set()
        self.alpha: float = 1.0
        self.programCount: int = 1
        self.best_seen_cost = self.candidates[-1][1].sum(axis=0, skipna=False)["Total cost"]
        self.iters_since_improvement = 0
        self.program = None
        self.cost = None
        self.df = None
        self.count: int = 0
        
        return True

    def process(self, device: str, engine, model) -> bool:
        if (self.j == None):
            return True

        if (not self.candidates[-1][1].sum(axis = 0, skipna = False)["Total cost"]):
            return True

        if (not len(self.costs)):
            return True
        
        self.current_best = self.candidates[-1][1].sum(axis=0, skipna=False)["Total cost"]

        if (self.current_best < self.best_seen_cost):
            self.best_seen_cost = self.current_best
        else:
            self.iters_since_improvement += 1

        if (self.count > utils.MAX_ITERATIONS_PER_TARGET or self.iters_since_improvement > utils.PLATEAU_PATIENCE):
            return True

        if (self.computeGraphs):
            prog_graphs: list  = []
            cost_tensors: list = []

            for program, df in self.candidates:
                g = utils.build_prog_graph(program, VOCAB, device)
                prog_graphs.append(g)
                cost_tensors.append(utils.dataframe_to_cost_tensor(df).to(device))

            self.computeGraphs = False

            model.eval()

            with torch.no_grad():
                self.z_context = model.encode_context(
                    self.inputs, self.outputs, self.masks,
                    prog_graphs, cost_tensors
                )   # [1, D]

        self.program = utils.generate_one(
            model, VOCAB, self.z_context, engine,
            temperature = self.temperature,
            device = device,
            max_depth = utils.programDepth(self.costs[0][1]),
        )

        if (not self.program):
            self.cost = math.inf
        else:
            try:
                self.df = pd.DataFrame(engine.dfConnectionBuilder(self.j), columns = utils.scoreColumns)
                self.cost = self.df["Total cost"].sum(skipna = False)
            except RuntimeError:
                self.cost = math.inf

        return False

    def update(self, device: str, model, L_tokens, modelFilename: str):
        if (not self.program or math.isinf(self.cost)):
            L_total = L_tokens

            self.temperature = min(utils.maxTemperature, self.temperature * 1.05)
            self.alpha = min(1.0, self.alpha * 1.5)
        else:
            if (self.cost <= self.costs[0][0]):
                gen_ids = utils.encode_program_tokens(self.program, VOCAB).to(device)
                gen_input, gen_target = gen_ids[:-1], gen_ids[1:]

                logits_self = model.decoder(gen_input.unsqueeze(0), self.z_context)
                L_semantic = F.cross_entropy(
                    logits_self.reshape(-1, logits_self.size(-1)),
                    gen_target.reshape(-1)
                )

                self.temperature = max(utils.minTemperature, self.temperature * 0.95)
                self.alpha = max(utils.minAlpha, self.alpha * 0.9)
            else:
                L_semantic = L_tokens

                self.temperature = min(utils.maxTemperature, self.temperature * 1.05)
                self.alpha = min(1.0, self.alpha * 1.5)

            L_total = self.alpha * L_tokens + (1.0 - self.alpha) * L_semantic

        if (self.program):
            if (self.cost < self.candidates[0][1].sum(axis = 0, skipna = False)["Total cost"]
                and not self.program in [c[0] for c in self.candidates]):
                torch.save({
                    "model_state": model.state_dict(),
                    "d_model"    : model.decoder.d_model,
                    "vocab_size" : model.decoder.vocab_size,
                }, modelFilename)

                self.computeGraphs = True
                self.iters_since_improvement = 0

                self.candidates.pop(0)
                self.candidates.append((self.program, self.df))
                self.candidates = sorted(self.candidates, key = lambda x: (tuple(-x[1].sum(axis = 0, skipna = False)), -len(x[0]), x[0]))

                while (len(self.costs) and self.cost <= self.costs[0][0]):
                    self.costs.pop(0)
            elif (not math.isinf(self.cost) and not self.program in self.testedPrograms):
                self.iters_since_improvement = 0 #TODO: to remove?

            if (not self.program in self.testedPrograms):
                self.testedPrograms.add(self.program)

        self.count += 1

        return L_total
