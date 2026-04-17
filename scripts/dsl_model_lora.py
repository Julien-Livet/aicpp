import torch
from datasets import load_dataset
from transformers import AutoTokenizer, AutoModelForCausalLM
from peft import LoraConfig, get_peft_model
from trl import SFTTrainer
from transformers import TrainingArguments

# =========================
# CONFIG
# =========================

model_name = "Qwen/Qwen2.5-Coder-7B-Instruct"

# =========================
# LOAD TOKENIZER & MODEL
# =========================

tokenizer = AutoTokenizer.from_pretrained(model_name)

model = AutoModelForCausalLM.from_pretrained(
    model_name,
    load_in_4bit=True,
    device_map="auto",
    torch_dtype=torch.float16
)

# =========================
# LORA CONFIG
# =========================

lora_config = LoraConfig(
    r=16,
    lora_alpha=32,
    target_modules=["q_proj", "v_proj"],
    lora_dropout=0.05,
    bias="none",
    task_type="CAUSAL_LM"
)

model = get_peft_model(model, lora_config)

# =========================
# DATASET
# =========================

def format_example(example):
    return {
        "text": f"""Solve the following ARC task using the DSL.

{example["input"]}

### Solution:
{example["output"]}
"""
    }

dataset = load_dataset("json", data_files="dsl_dataset.json")

dataset = dataset.map(format_example)

# =========================
# TRAINING ARGS
# =========================

training_args = TrainingArguments(
    output_dir="./dsl_model",
    per_device_train_batch_size=2,
    gradient_accumulation_steps=4,
    num_train_epochs=3,
    learning_rate=2e-4,
    logging_steps=10,
    save_steps=500,
    fp16=True,
    optim="paged_adamw_8bit"
)

# =========================
# TRAINER
# =========================

trainer = SFTTrainer(
    model=model,
    train_dataset=dataset["train"],
    dataset_text_field="text",
    tokenizer=tokenizer,
    args=training_args
)

# =========================
# TRAIN
# =========================

trainer.train()

# =========================
# SAVE
# =========================

model.save_pretrained("./dsl_model_lora")
tokenizer.save_pretrained("./dsl_model_lora")