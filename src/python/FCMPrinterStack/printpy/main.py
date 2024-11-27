from typing import Union
from fastapi import FastAPI

import cups

conn = cups.Connection()

app = FastAPI()


@app.get("/")
def read_root():
    return {"Hello": "World"}


@app.get("/items/{item_id}")
def read_item(item_id: int, q: Union[str, None] = None):
    return {"item_id": item_id, "q": q}


@app.get("/printers")
def get_printer():
    return conn.getPrinters()


@app.get("/printers/{printer}")
def start_job(printer: str):
    printers = conn.getPrinters()

    if printer not in printers:
        return {"status": f"Printer {printer} does not exist"}
    else:
        return {"printer": printer, "status": "Starting Job"}