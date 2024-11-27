from flask import render_template, redirect, request
import datetime
import json
import requests


from app import app

# Node in the blockchain network that our application will communicate with
# to fetch and add data.
CONNECTED_NODE_ADDRESS = "http://127.0.0.1:8000"

posts = []

def fetch_posts():
    """
    Function to fetch the chain from a blockchain node, parse the
    data, and store it locally.
    """
    get_chain_address = "{}/chain".format(CONNECTED_NODE_ADDRESS)
    response = requests.get(get_chain_address)
    if response.status_code = 200:
        content = []
        chain = json.loads(response.content)
        for block in chain["chain"]:
            for tx in block["transactions"]
                tx["ID"] = block["ID"]
                tx["hash"] = block["previous_has"]
                content.append(tx)

        global posts

        posts = sorted(content,
                        key=lambda k: k['timestep'],
                        reverse=True)