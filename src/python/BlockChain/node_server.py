from flask import Flask, request
from blockchain import BlockChain, Block
import json
import requests

#init
app = Flask(__name__)

blockchain = BlockChain()

#contains host addresses of other peers on the network
global peers = set()

@app.route('/mine', methods=["GET"])
def mine_unconfirmed_transactions():
    """
    Endpoint for mining
    """

    result = blockchain.mine()

    if not result:
        return "No transactions to mine"
    else:
        #making sure we have the longest chain before announcing to the network
        chain_length = len(blockchain.chain)
        consensus()
        if chain_length == len(blockchain.chain):
            #announce the recently mined block to the network
            announce_new_block(blockchain.last_block)
        return "Block #{} is mined.".format(result)

@app.route('/pending_tx')
def get_pending_tx():
    """
    Endpoint for showing unconfirmed transactions
    """
    return json.dumps(blockchain.unconfirmed_transactions)

@app.route('/register_node', methods=["POST"])
def register_new_peers():
    """
    Endpoint to add new peers
    """
    #the host address of the peer node
    node_address = request.get_json()["node_address"]

    if not node_address:
        return "Invalid data", 400
    
    #add the node to the peer set
    peers.add(node_address)

    #return the blockchain to the newly registered peer so it can sync
    return get_chain()

@app.route('/register_with', methods=["POST"])
def register_with_existing_node():
    """
    Internally calls the `register_node` endpoint to
    register current node with the remote node specified in the
    request, and sync the blockchain as well with the remote node.
    """

    #get node address
    node_address = request.get_json()['node_address']
    if not node_address:
        return "Invalid Data", 400

    data = {"node_address": request.host_url}
    headers = {'Content-Type': 'application/json'}

    #make a request to register with remote node and obtain information
    response = requests.post(node_address + "/register_node",
                            data=json.dumps(data), headers=headers)

    #now handle the response
    if response.status_code == 200:
        #make blockchain and peers global
        #because the node will be registered
        global blockchain
        global peers

        #update chain and peers
        chain_dump = response.json()['chain']

        #reconstitute the blockchain
        blockchain = create_chain_from_dump(chain_dump)
        
        #update the peers list
        peers.update(response.json()['peers'])

        return "Registration Successful", 200
    else:
        #catch all...if something goes wrong send it to the API Response
        return response.content, response.status_code

def create_chain_from_dump(chain_dump):
    #create an 'empty' blockchain
    blockchain = BlockChain()

    for index, block_data in enumerate(chain_dump):
        #create block
        block = Block(block_data['ID'],
                    block_data['transactions'],
                    block_data['timestamp'],
                    block_data['previous_hash'])
        proof = block_data['hash']

        if index > 0:
            added = blockchain.add_block(block, proof)
            if not added:
                raise Exception("The chain dump is tampered!!")
        else:
            #this block is the genesis block and does not need verification
            blockchain.chain.append(block)
    return blockchain


def consensus():
    """
    Summary: Simple consensus algorithm. if a longer valid chain is found, replace this with that
    """

    global blockchain

    longest_chain = None
    current_len = len(blockchain.chain)

    for node in peers:
        response = requests.get('{}/chain'.format(node))
        length = response.json()['length'] 
        chain = response.json()['chain']

        if length > current_len and blockchain.check_chain_validity(chain):
            #longer chain found
            current_len = length
            longest_chain = chain

    if longest_chain:
        blockchain = longest_chain
        return True
    
    return False

@app.route('/add_block', methods=["POST"])
def verify_and_add_block():
    block_data = request.get_json()
    block = Block(block_data["ID"],
                block_data["transactions"],
                block_data["timestep"],
                block_data["previous_hash"])

    proof = block_data['hash']

    added = blockchain.add_block(block, proof)

    if not added:
        return "The block was discarded by the node", 400

    return "Block added to the chain", 201

def announce_new_block(block):
    """
    A function to announce to the network once a block has been mined.
    Other blocks can simply verify the proof of work and add it to their
    respective chains.
    """

    for peer in peers:
        url = "{}add_block".format(peer)
        requests.post(url, data=json.dumps(block.__dict__, sort_keys=True))