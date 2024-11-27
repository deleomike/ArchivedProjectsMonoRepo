from pydantic import BaseModel

class GenerateRequest(BaseModel):
    prompt: str
    bucket_uri: str