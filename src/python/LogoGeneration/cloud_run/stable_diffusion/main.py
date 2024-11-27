# make sure you're logged in with `huggingface-cli login`
from torch import autocast
from diffusers import StableDiffusionPipeline
from fastapi import FastAPI

from settings import DEVICE
from request_schemas import GenerateRequest

app = FastAPI()


pipe = StableDiffusionPipeline.from_pretrained(
    "CompVis/stable-diffusion-v1-4", 
    use_auth_token=True
).to(DEVICE)

pipe.enable_attention_slicing()
def dummy(images, **kwargs):
    return images, False
pipe.safety_checker = dummy

prompt = "a photo of an astronaut riding a horse on mars"
if DEVICE != "mps":
    with autocast(DEVICE):
        _ = pipe(prompt, num_inference_steps=1)
        image = pipe(prompt)["sample"][0]  
else:
    _ = pipe(prompt, num_inference_steps=1)
    images = pipe(prompt)["sample"] 

    for idx, image in enumerate(images): 

        image.save(f"astronaut_rides_horse_{idx}.png")


@app.get("/")
async def root():
    return {"message": "Hello World"}

@app.post("/generate")
async def generate(request: GenerateRequest):

    pipe = StableDiffusionPipeline.from_pretrained(
        "CompVis/stable-diffusion-v1-4", 
        use_auth_token=True
    ).to(DEVICE)

    prompt = "a photo of an astronaut riding a horse on mars"
    with autocast(DEVICE):
        image = pipe(prompt)["sample"][0]  
        
    image.save("astronaut_rides_horse.png")