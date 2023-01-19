from flask import Flask
from flask import request
from flask import render_template

app=Flask(__name__)

@app.route('/login', methods=['POST','GET'])
def login():
    error =  None
    if request.method == 'POST':
        if valid_login(request.form['username'],
                       request.form['password']):
            return log_the_user_in(request.form['username'])
        else:
            error = 'Invalid username/password'
    #the code below is executed if the request method
    #was GET or the credentials were invalid
    return render_template('login.html', error=error)
# i dont know what is wrong with the input...i dont know where the input comes from
