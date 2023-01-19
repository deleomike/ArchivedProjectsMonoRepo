from flask import Flask
from flask import request
#from werkzueg.utilis import secure_filename

app=Flask(__name__)

@app.route('/upload', methods=['GET', 'POST'])
def upload_file():
    if request.method == 'POST':
        f = request.files['the_file']
        f.save('/var/www/uploads/uploaded_file.txt')
        #f.save('/var/www/uploads/' + secure_filename(f.filename))

        #NEVER trust the filename value, if you have to access it use the secure_filename
        #function from Werkzeug

#remember, set the enctype="multipart/form-data" on the HTML form, or files will not be transmitted    
