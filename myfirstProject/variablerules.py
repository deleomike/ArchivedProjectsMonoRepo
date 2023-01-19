from flask import Flask
app = Flask(__name__)

@app.route('/user/<username>')  #<> indicates a variable input
def show_user_profile(username):
    #show the user profile, typed in by user, for that profile
    return 'User %s' % username

@app.route('/post/<int:post_id>') #<int:arg> indicates the variable must be an int
# show the post with the given id, the id is an integer
def show_pot(post_id):
    return 'Post %d' % post_id

@app.route('/path/<path:subpath>')
# show the subpath after /path/
def show_subpath(subpath):
    return 'Subpath %s' % subpath
#nothing is initially shown. user must indicate the route as an extension
