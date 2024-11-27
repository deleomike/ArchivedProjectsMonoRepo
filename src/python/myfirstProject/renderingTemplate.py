from flask import render_template
from flask import Flask
app=Flask(__name__)

@app.route('/hello/')
@app.route('/hello/<name>')
def hello(name=None):
    return render_template('hello.html', name = name)
#finds the HTML template file that matches 'hello.html'
#uses the variable as an input

#this is a module, so the template is in a templates folder
