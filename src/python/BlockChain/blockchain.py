from hashlib import sha256
# from .app import peers
import json
import time


class Block:

    def __init__(self, ID, transactions, timestamp, previous_hash):
        """
        Constructor for the Block class
        :param ID: Unique ID of the block
        :param transaction: Transactions of the block
        :param timestamp: Time the block was created
        :param previous_hash: Hash of the previous block
        """

        #Initializable
        self.ID = ID
        self.transactions = transactions
        self.timestamp = timestamp
        self.previous_hash = previous_hash

        #Preset
        self.nonce = 0

        return    

    def compute_hash(self):
        """
        Precondition: Nothing
        Postcondition: Hash string
        Summary: Returns the hash of the block instance by first converting it into JSON string.
        """

        #flattened block
        block_string = json.dumps(self.__dict__, sort_keys=True)

        #encode and return
        return sha256(block_string.encode()).hexdigest()

class BlockChain:

    #Difficulty of proof of work algorithm
    difficulty = 2

    def __init__(self):
        """
        Constructor for block chain class
        """

        #list of unconfirmed transactions
        self.unconfirmed_transactions = []

        #list of blocks... the chain
        self.chain = []

        #instantiate the first block
        self.create_genesis_block()

    def create_genesis_block(self):
        """
        Precondition: Nothing
        Postcondition: Nothing
        Summary: Creates the initial block and assigns it to
            the beginning of the chain
        """

        #create the first block, with some default params
        genesis_block = Block(0, [], time.time(), "0")

        genesis_block.hash = genesis_block.compute_hash()

        self.chain = [genesis_block]

        return

    def proof_of_work(self, block):
        """
        Precondition: Block
        Postcondition: The computed hash
        Summary: This operation computes different values of the nonce to
            get a hash that satisfies the difficulty criteria
        """

        block.nonce = 0

        computed_hash = block.compute_hash()
        while not computed_hash.startswith('0' * self.difficulty):
            block.nonce += 1
            computed_hash = block.compute_hash()

        return computed_hash

    def add_block(self, block, proof):
        """
        Precondition: Block object, and computed hash for proof of validity
        Postcondition: False if invalid, True if valid
        Summary: Checks if the block is valid, and if so add it to the chain
        """

        #Get hash of the last block in the chain
        previous_hash = self.last_block.hash

        #Check if the block has a valid connection to the last block
        if previous_hash != block.previous_hash:
            return False

        #Check if the block's proof is valid
        if not self.is_valid_proof(block, proof):
            return False

        #Assign the hash
        block.hash = proof
        #Append the block
        self.chain.append(block)
        return True

        

        return

    def is_valid_proof(self, block, block_hash):
        """
        Precondition: Block object, proof of work hash
        Postcondition: False if hash is invalid, True if hash is valid
        Summary: Does a check of the hash content
        """

        return (block_hash.startswith('0' * self.difficulty) and 
                block_hash == block.compute_hash())

        return True

    def add_new_transaction(self, transaction):
        """
        Precondition: Transaction string
        Postcondition: Nothing
        Summary: Save the unconfirmed transaction
        """
        self.unconfirmed_transactions.append(transaction)

    def mine(self):
        """
        Precondition: Nothing
        Postcondition: Block ID
        Summary: Interface to add pending transactions to a blockchain
        """

        #No more pending transactions left
        if not self.unconfirmed_transactions:
            return False

        last_block = self.last_block

        new_block = Block(ID=last_block.ID + 1,
                        transactions=self.unconfirmed_transactions,
                        timestamp=time.time(),
                        previous_hash=last_block.hash)

        proof = self.proof_of_work(new_block)
        #add the block
        self.add_block(new_block, proof)
        #clear the transactions
        self.unconfirmed_transactions = []
        return new_block.ID

    def check_chain_validity(cls, chain):
        """
        Precondition:
        Postcondition:
        Summary: A Helper method to check if the entire blockchain is valid
        """

        result = True
        previous_hash = "0"

        #iterate through every block
        for block in chain:
            block_hash = block.hash
            #remove hash field to recompute the hash again
            delattr(block, "hash")

            if not cls.is_valid_proof(block, block.hash) or \
                    previous_hash != block.previous_hash:
                result = False
                break
            
            block.hash = previous_hash = block_hash

            return result





    @property
    def last_block(self):
        """
        A pythonic way to retrieve the last block
        """

        return self.chain[-1]