from flask import Flask, request, make_response

app=Flask(__name__)

@app.route('/')
def index():
    username = request.cookies.get('username')
    # use cookies.get(key) instead of cookies[key] to not get a
    # KeyError if the cookie is missing.

    resp = make_response(render_template())
    resp.set_cookie('username','the username')
    return resp
#doesnt work at the moment
