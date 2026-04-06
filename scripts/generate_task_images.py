import base64
import io
from io import BytesIO
import json
import os
from PIL import Image
import sys
import view_task

def generate(folder: str):
    assert(folder in ("training", "evaluation"))

    files = os.listdir(f"../ARC-AGI-2/data/{folder}")

    for file in files:
        with open(f"../ARC-AGI-2/data/{folder}/{file}", "r") as f:
            data = json.loads(f.read())

        buffer = io.BytesIO()
        view_task.show("Train", data["train"], buffer)
        buffer.seek(0)
        image_base64 = base64.b64encode(buffer.read()).decode("utf-8")
        image_data = base64.b64decode(image_base64)
        image = Image.open(BytesIO(image_data))
        pngFile = file.replace(".json", ".png")
        image.save(f"data/{folder}/{pngFile}", 'PNG')

if (__name__ == "__main__"):
    generate(sys.argv[-1])
