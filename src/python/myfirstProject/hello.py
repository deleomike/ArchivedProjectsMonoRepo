from flask import Flask
app = Flask(__name__)

#first version
#@app.route('/')
#def hello():
#    return 'Hello, World!'

#this route shows immediately "hello, world"

#second version

@app.route('/')
def index():
    return 'Index Page'


@app.route('/hello')
def hello():
    return 'Hello, World!'

#so if you go to this site. you will see "index page". then if you add to the url '/hello' it takes you to Hello World
#the route parameter is essentially the url
