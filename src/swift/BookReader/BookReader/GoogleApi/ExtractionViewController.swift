//
//  AudioController.swift
//  BookReader
//
//  Created by Michael DeLeo on 12/28/18.
//  Copyright © 2018 Michael DeLeo. All rights reserved.
//

import Foundation
import UIKit



//look into batch requests for google (up to 16 photos per request)

class GoogleOCR: UIViewController {
    @IBOutlet var progress: UIProgressView!
    private let apiKEY = "AIzaSyCVL1twNLQ3LNF6JVycY7UEWf9J2VGZGGs";
    private var apiURL: URL {
        return URL(string: "https://vision.googleapis.com/v1/images:annotate?key=\(apiKEY)")!
    }
    private let bucketURL = "https://www.googleapis.com/upload/storage/v1/b/bookreader/o?uploadType=media&name=/"
    private var AUTH = "ya29.GluLBl0_VVPpIPrJ1nyQLuZmeBRVMdnfvBkWTrufXj_kdfXuR2kYZ7JGZsfqTKBfpnib6uPk-GbrkWGeatijotysG6AxqpN9NsJZbKkJ7AkIvaMYbt_UYxjnUaY1";
    

    private func goDeeper(_ dict: [String: Any], key: String) -> [String: Any]{
        for (key, value) in dict {
            print(key)
            // access all key / value pairs in dictionary
        }
        
        let array = dict[key] as? [Any]
        let dict2 = array?[0] as? [String: Any]
        return dict2!
    }
    
    private func updateProgress(){
        progress.progress = progress.progress + 0.2
        return;
    }
    
    private func uploadToBucket(image: UIImage, imageName: String) -> String{
        var url: URL {
            return URL(string: bucketURL + imageName)!
        }
        
        var value:String = "error";
        
        var request = URLRequest(url: url);
        request.httpMethod = "POST"
        request.setValue("Bearer \(AUTH)", forHTTPHeaderField: "Authorization");
        
        //Check which image type the image is
        let imageType = String(imageName.suffix(3))
        if (imageType == "PNG" || imageType == "png"){
            request.httpBody = image.pngData();
        }
        else if(imageType == "JPG" || imageType == "jpg" || imageType == "JPEG" || imageType == "jpeg"){
            request.httpBody = image.jpegData(compressionQuality: 0.75);   //highest quality
        }
        else{
            request.httpBody = image.jpegData(compressionQuality: 0.75)
        }
        print(request)
        let task = URLSession.shared.dataTask(with: request) { (data, response, error) in
            if error != nil{
                print(error)
            }
            else{
                if let usableData = data{
                    do{
                        //find the link to retrieve the image
                        let json = try JSONSerialization.jsonObject(with: usableData, options: [])
                        print(json);
                        let dict = json as? [String: Any]
                        if (dict!["mediaLink"] as! String != nil){
                            value = dict!["mediaLink"] as! String
                            print("--\(imageName) Upload Success --")
                           
                                //self.callGoogleVisionAPI()
                        }
                        else{
                            print("--\(imageName) Upload Failure")
                        }
                        
                        //DispatchQueue.main.sync{
                        //    UIApplication.shared.isNetworkActivityIndicatorVisible = false
                        //}
                        

                    } catch let error as NSError{
                        print(error)
                    }
                }
            }
        }
        task.resume()
        
        return value;
    }
    
    //completion: @escaping (OCRResult?)
    private func callGoogleVisionAPI(url: String) -> Void {
        
        var url = apiURL
        var request = URLRequest(url: url);
        request.httpMethod = "POST";
        request.setValue("X-IOS-Bundle-Identifier", forHTTPHeaderField: "Content-Type")
        //Create single json request
        let json: [String: Any] = ["requests":[["image":["source": ["imageUri": "https://storage.googleapis.com/bookreader/IMG_8344.jpg"]],"features":[["type": "TEXT_DETECTION"]]]]]
        //let json: [String: Any] = ["requests":[["image":["source": ["gcsImageUri": "gcs://bookreader/IMG_8344.jpg"]],"features":[["type": "TEXT_DETECTION"]]]]]
        //serialize the json
        let jsonRequest = try? JSONSerialization.data(withJSONObject: json);
        //print(jsonRequest);
        //print(json);
        request.httpBody = jsonRequest;
        //fetching the data from the url
        let task = URLSession.shared.dataTask(with: request) { (data, response, error) in
            if error != nil {
                print(error)
            } else {
                if let usableData = data {
                    do{
                        let json = try JSONSerialization.jsonObject(with: usableData, options: [])
                        if let dictionary = json as? [String: Any]{
                            let result = self.goDeeper(self.goDeeper(dictionary,key: "responses"),key: "textAnnotations")
                            
                            self.updateProgress()
                            //print(result["description"])
                            self.converted.enqueue(result["description"] as! String)
                            //print(self.converted.items[0])
                            print("Conversion is Done\n");
                            //self.performSegue(withIdentifier: "extract_to_check", sender: self);
                            
                        }
                        
                    } catch let error as NSError{
                        print(error)
                    }
                    
                }
            }
        }
        
        task.resume()
    }
    /*
    private func base64EncodeImage(_ image: UIImage) -> String?{
        //Convert image png to NSDATA format
        let imageData:NSData = image.pngData()! as NSData
        //convert NSData to a base64 encoded string of the image
        return imageData.base64EncodedString(options: .lineLength64Characters)
        //image.cgImage?.base64EncodedString(options: .endLineWithCarriageReturn)
    }*/
    
    var images:Queue<UIImage> = Queue();
    var names:Queue<String> = Queue();
    var converted:Queue<String> = Queue();
    var links:Queue<String> = Queue();
    
    override func prepare(for segue: UIStoryboardSegue, sender: Any?) {
        if segue.destination is CheckerViewController{
            let vc = segue.destination as? CheckerViewController;
            vc?.Text = converted;
        }
    }
    
    override func viewDidAppear(_ animated: Bool) {
        
        progress.progress = 0.5;
        
        var opQ: OperationQueue = OperationQueue();
 
        
        for i in 0..<images.size{
            opQ.addOperation {
                self.links.enqueue(self.uploadToBucket(image: self.images.items[i], imageName: self.names.items[i]));
            }
        }
        while(opQ.operationCount != 0){}
        sleep(3)
        print("Done Waiting \(links.items[0])")
        for i in 0..<links.size{
            opQ.addOperation {
                self.callGoogleVisionAPI(url: self.links.items[i])
            }
        }
        
        while(true){
            
        }
        //let imageName = names.items[0]
        //let image = images.items[0]
        
        //callGoogleVisionAPI()
        /*
        //TODO: Convert all pictures to one string of text
        //var url = URL(string: "http://jsonplaceholder.typicode.com/users/1")!
        //Request body
        var url = apiURL
        var request = URLRequest(url: url);
         request.httpMethod = "POST";
         request.setValue("X-IOS-Bundle-Identifier", forHTTPHeaderField: "Content-Type")
         //Create single json request
        let json: [String: Any] = ["requests":[["image":["source": ["imageUri": "https://storage.googleapis.com/bookreader/IMG_8344.jpg"]],"features":[["type": "TEXT_DETECTION"]]]]]
         //let json: [String: Any] = ["requests":[["image":["source": ["gcsImageUri": "gcs://bookreader/IMG_8344.jpg"]],"features":[["type": "TEXT_DETECTION"]]]]]
         //serialize the json
         let jsonRequest = try? JSONSerialization.data(withJSONObject: json);
         //print(jsonRequest);
         //print(json);
         request.httpBody = jsonRequest;
        //fetching the data from the url
        let task = URLSession.shared.dataTask(with: request) { (data, response, error) in
            if error != nil {
                print(error)
            } else {
                if let usableData = data {
                    do{
                        let json = try JSONSerialization.jsonObject(with: usableData, options: [])
                        if let dictionary = json as? [String: Any]{
                            let result = self.goDeeper(self.goDeeper(dictionary,key: "responses"),key: "textAnnotations")
                            
                            //print(result["description"])
                            self.converted.enqueue(result["description"] as! String)
                            print(self.converted.items[0])
                            print("Conversion is Done\n");
                            self.performSegue(withIdentifier: "extract_to_check", sender: self);
                            
                        }
                        
                    } catch let error as NSError{
                        print(error)
                    }
                    
                }
            }
        }
        
        task.resume()
        */
        /*
        print(self.converted.size);
        print(self.images.size);
            if (self.converted.size == self.images.size){
                self.performSegue(withIdentifier: "extract_to_check", sender: self);
                
            }*/
        //TODO: Update the progress bar

        
    }
    


}
