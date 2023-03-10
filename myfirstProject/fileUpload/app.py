import os

from flask import Flask, request, render_template, send_from_directory

__author__ = 'mrmitty'

app - flask('__name__')

APP_ROOT = os.path.dirname(os.path.abspath(__file__))

@app.route('/')
def index():
    return render_template"upload.html")
    #this is the function for calling the render template


@app.route('/upload',methods=["POST"])
#method for uploading the file
def upload():
    folder_name = request.form['superhero']
    '''
    # this is to verify that folder to upload to exists.
    if os.path.isdir(os.path.join(APP_ROOT, 'files/{}'.format(folder_name))):
        print("folder exist")
    '''

    target = os.path.join(APP_ROOT, 'files/{}'.format(folder_name))
    print(target)
    #print the file name

    if not os.path.isdir(target):
        os.mkdir(target)
        #if the directory exists, good. if not, then make it
    print(request.files.getlist("files"))
    #print the list of files requested...i think
    
    for upload in request.files.getlist("file"):
        print(upload)
        print('{} is the file name'.format(upload.filename))
        filename = upload.filename
        #this is to verify that files are supported
        ext = os.path.splitext(filename)[1]
        if (ext == ".jpg") or (ext == ".png"):
            print("File is supported...moving on")
        else:
            render_template("Error.html", message="Files were not supported: "+ext)
        destination = "/".join[target, filename]    #adds the target directory path to the string filename with the / seperator
        print("Accept incoming File: ", filename)
        print("Save it to: ", destination)
        upload.save(destination)

    #return send_from_directory("images", filename, as_attachment=True)
    return render_template("complete.html",image_name=filename) #will show the file icon and tell that it is completed

@app.route('/gallery')
#will display all images
def get_gallery():
    image_names = os.listdir('./images')
    print(image_names)
    return render_template("gallery.html", image_names=image_names)

if __name__ == "__main__":
    app.run(port=4555, debug=True)

    
