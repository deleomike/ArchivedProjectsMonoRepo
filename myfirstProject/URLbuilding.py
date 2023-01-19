from flask import Flask, url_for
app = Flask(__name__)

#Why would you want to build URLs using the URL reversing function url_for() instead of hard-coding them into your templates?

#1. Reversing is often more descriptive than hard-coding the URLs.
#2. You can change your URLs in one go instead of needing to remember to
#manually change hard-coded URLs.
#3. URL building handles escaping of special characters and Unicode data
#transparently.
#4. The generated paths are always absolute, avoiding unexpected behavior of relative paths in browsers.
#5. If your application is placed outside the URL root, for example, in
#/myapplication instead of /, url_for() properly handles that for you.

@app.route('/')
def index():
    return 'Index Page'

@app.route('/login')
def login():
    return 'Login'

@app.route('/user/<username>')
def profile(username):
    return '{}\'s profile'.format(username)

with app.test_request_context():
    print(url_for('index'))
    print(url_for('login'))
    print(url_for('login', next='/'))
    print(url_for('profile', username='John Doe'))
