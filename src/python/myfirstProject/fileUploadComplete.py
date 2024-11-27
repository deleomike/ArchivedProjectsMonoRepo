#INTRODUCTION
#1. A <form> tag is marked with enctype=multipart/form-dat and
#an <input type=file> is placed in that form
#2. The application accesses the file from th efiles dictionary on the request object
#3. Use the save() method of the file to save the file permanently somewhere
#on the filesystem

#there are bugs that i do not understand in here, but this is supposedly the complete upload prog

import os
from flask import Flask, flash, request, redirect, url_for, send_from_directory
from werkzeug.utils import secure_filename

UPLOAD_FOLDER = '/Users/michaeldeleo/myfirstProject/upload/' #the location of the uploaded file(s)
ALLOWED_EXTENSIONS = set(['txt', 'pdf', 'png', 'jpg', 'jpeg', 'gif'])
#set of allowed file extensions

app=Flask(__name__)
app.config['UPLOAD_FOLDER']=UPLOAD_FOLDER

##################################
#functions

def allowed_file(filename):
    return '.' in filename and \
           filename.rsplit('.',1)[1].lower() in ALLOWED_EXTENSIONS
            #rsplit() will return a list of words in the string, seperated by the delimiter
            #in this case the delimiter is '.'

            #"in" with a string followed by a string will act like REGEX by returning true
            #if the previous is included in the latter

@app.route('/', methods=['GET', 'POST'])
def upload_file():
    if request.method == 'POST':
        #check if the post request has the file part
        if 'file' not in request.files: #not a valid file
            flash('No file part')
            return redirect(request.url)
            
        file = request.files['file']
        #if user does not select file, browser also submits
        #empty part without filename
        if file.filename == '': #no file
            flash('No selected file')
            return redirect(request.url)
        if file and allowed_file(file.filename):    #if true, then it is a good file and will be uploaded
            filename = secure_filename(file.filename)
            file.save(os.path.join(app.config['UPLOAD_FOLDER'],filename))
            return redirect(url_for('uploaded_file', filename=filename))
        return '''
    <!doctype html>
    <title>Upload new File</title>
    <h1>Upload new File</h1>
    <form method=post enctype=multipart/form-data>
      <input type=file name=file>
      <input type=submit value=Upload>
    </form>
        '''
        

@app.route('/uploads/<filename>')
def uploaded_file(filename):
    return send_from_directory(app.config['UPLOAD_FOLDER'],filename)

