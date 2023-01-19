from flask import Flask
app = Flask(__name__)

@app.route('/projects/')
def projects():
    #this includes typing in '/projects' and '/projects/'
    #will force the URL to endpoint '/projects/'
    #likened to a folder in a system (i.e. continues searc with extra /)
    return 'The Project Page'

@app.route('/about')
def about():
    #endpoint only works with '/about'
    #likened to a file in a system (i.e. is the endpoint)
    return 'The About Page'
