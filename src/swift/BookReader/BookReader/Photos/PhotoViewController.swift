//
//  Picture_Management.swift
//  BookReader
//
//  Created by Michael DeLeo on 12/27/18.
//  Copyright © 2018 Michael DeLeo. All rights reserved.
//

import Foundation
import UIKit
import Photos

//USE PHOTO FRAMEWORK

class PhotoViewController: UIViewController, UIImagePickerControllerDelegate, UINavigationControllerDelegate, UICollectionViewDelegate, UICollectionViewDataSource, UICollectionViewDelegateFlowLayout{
    
    //queue for objects of photo controller
    var images:Queue<UIImage> = Queue();
    var names:Queue<String> = Queue();
    
    @IBOutlet var imageView: UIImageView!
    
    //Collection View instance
    @IBOutlet var Collection: UICollectionView!
    override func prepare(for segue: UIStoryboardSegue, sender: Any?) {
    //override func prepare(for segue: UIStoryboardSegue, sender: Any?){
        if segue.destination is GoogleOCR{
            let vc = segue.destination as? GoogleOCR
            vc?.images = images;
            vc?.names = names;
        }
    }
    
    /////////////////////////////////
    /////////////////////////////////
    //UICollectionViewDataSource Required functions
    func collectionView(_ collectionView: UICollectionView, numberOfItemsInSection section: Int) -> Int{
        return 0;
    }
    func collectionView(_ collectionView: UICollectionView, cellForItemAt indexPath: IndexPath) -> UICollectionViewCell{
        let cell = UICollectionViewCell();
        return cell;
    }
    /////////////////////////////////
    /////////////////////////////////
    
    
    /////////////////////////////////
    /////////////////////////////////
    //UIImagePickerController Delegate functions
    func imagePickerController(_ picker: UIImagePickerController, didFinishPickingMediaWithInfo info: [UIImagePickerController.InfoKey : Any]){
        // Local variable inserted by Swift 4.2 migrator.
        let infof = convertFromUIImagePickerControllerInfoKeyDictionary(info)

        //let Cell: CollectionViewCell = CollectionViewCell();
        
        picker.dismiss(animated: true, completion: nil);
        

        if var pickedImage = infof[convertFromUIImagePickerControllerInfoKey(UIImagePickerController.InfoKey.originalImage)] as? UIImage{
            if let imageURL = info[UIImagePickerController.InfoKey.referenceURL] as? URL {
                let result = PHAsset.fetchAssets(withALAssetURLs: [imageURL], options: nil)
                let asset = result.firstObject
                print("FileName:")
                print(asset?.value(forKey: "filename"))
                names.enqueue(asset?.value(forKey: "filename") as! String)
                //pickedImage(named: asset?.value(forKey: "filename"))
                images.enqueue(pickedImage);
                //Cell.Image.image = pickedImage;
                imageView.image = pickedImage;
                
            }

        }

    }
    /////////////////////////////////
    /////////////////////////////////

    
    /////////////////////////////////
    //Precondition: UIButton tag
    //Postcondition: Nothing
    //Summary: Triggered when next picture button is pushed. gets the image from camera or library
    /////////////////////////////////
    @IBAction func TakePicture(_ sender: UIButton){
        let vc = UIImagePickerController();
        //Assign the delegate
        vc.delegate = self;
        //Allow editing of the object
        vc.allowsEditing = true;
        
        //Check if the device can take pictures
        if UIImagePickerController.isSourceTypeAvailable(.camera){
            print("Camera is Available\n");
            //Assign object's source as the camera
            vc.sourceType = .photoLibrary;
            //vc.sourceType = UIImagePickerController.SourceType.camera;
        }
        else{
            print("Camera is not Available\n")
            //Assign object's source as the photo library
            vc.sourceType = .photoLibrary;
        }
        self.present(vc, animated: true, completion: nil);
        
        print(images.size);

    }
    
    @IBAction func Done(_ sender: UIButton) {
        print("Done\n");
        performSegue(withIdentifier: "pic_to_extract", sender: self);
    }
}


// Helper function inserted by Swift 4.2 migrator.
fileprivate func convertFromUIImagePickerControllerInfoKeyDictionary(_ input: [UIImagePickerController.InfoKey: Any]) -> [String: Any] {
	return Dictionary(uniqueKeysWithValues: input.map {key, value in (key.rawValue, value)})
}

// Helper function inserted by Swift 4.2 migrator.
fileprivate func convertFromUIImagePickerControllerInfoKey(_ input: UIImagePickerController.InfoKey) -> String {
	return input.rawValue
}
