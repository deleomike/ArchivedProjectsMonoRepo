from flask import Flask
from flask import request
#by default, a route only answers to 'GET' requests
#use the methods parameter of .route to use different HTTP methods
app=Flask(__name__)

@app.route('/login', methods=['GET','POST'])
def login():
    if request.method == 'POST':
        return do_the_login()
    else:
        return show_the_login_form()

#still not quite sure what the methods

#STATIC Files
    #in development, make a folder static and store static files there
    #access with url_for('static, filename='name.css')
