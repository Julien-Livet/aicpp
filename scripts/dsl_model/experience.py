class Experience:
    def __init__(
        self,
        workerId,
        inputs,
        outputs,
        masks,
        prog_graphs,
        cost_tensors,
        target_program,
        subtarget_program,
        generated_program,
        alpha,
        use_semantic,
        model_version,
    ):
        self.workerId = workerId
        self.inputs = inputs.detach().cpu()
        self.outputs = outputs.detach().cpu()
        self.masks = masks.detach().cpu()
        self.prog_graphs = prog_graphs
        self.cost_tensors = [
            c.detach().cpu()
            for c in cost_tensors
        ]
        self.target_program = target_program
        self.subtarget_program = subtarget_program
        self.generated_program = generated_program
        self.alpha = float(alpha)
        self.use_semantic = bool(use_semantic)
        self.model_version = int(model_version)
