//
//  FifthScreen.swift
//  ProgramaticUI
//
//  Created by Michael DeLeo on 1/16/19.
//  Copyright © 2019 Michael DeLeo. All rights reserved.
//

//Loading Screen

import UIKit
import Foundation

class FifthScreen: UIViewController {
    
    
    let shapeLayer = CAShapeLayer()
    let trackLayer = CAShapeLayer()
    let begin = CATextLayer()
    var pages: [PageCell] = []
    var pagesText: [String] = []
    var links: [String] = []
    
    var animationStart: CGFloat!
    var animationIncrement: CGFloat!
    
    let requestThread = DispatchGroup()
    var sem = DispatchSemaphore(value: 0)
    
    
    private let apiKEY = "AIzaSyCVL1twNLQ3LNF6JVycY7UEWf9J2VGZGGs";
    private var apiURL: String!
    private var bucketURL = "https://www.googleapis.com/upload/storage/v1/b/bookreader/o?uploadType=media&name=/";
    private let AUTH = "ya29.GluaBvfZrZ2tIKVHTJCqtNT93XOGYSX8Ir6YWA2X5BYB2hjo_rj-BNwTBCSUD4klPRfCOGr_HC8dFsdqTB5L349uljp3pErOgbIbfxEo0EcM-6XPdckuNTdqc5x_";

    override func viewDidLoad() {
        super.viewDidLoad()
        apiURL = "https://vision.googleapis.com/v1/images:annotate?key=\(apiKEY)"
        
        animationStart = 0
        animationIncrement = CGFloat(1)/CGFloat(2*pages.count)
        
        print("received \(pages.count) pages")
    
        setupLoader()
        
        setupText()
        
        //doUrls()

        // Do any additional setup after loading the view.
    }
    
    @objc func shapeTapped(){
        begin.alignmentMode = .center
        var percent: CGFloat = (animationStart*10000)
        percent = percent.rounded()
        begin.string = String("\(percent/100)%")
        doUrls()
    }
    
    func incrementAnimation(){
        
        navigationItem.hidesBackButton = true
        navigationController?.navigationBar.isHidden = true
        
        print("animating")
        
        //initialize animation to go till end of circle
        let basicAnimation = CABasicAnimation(keyPath: "strokeEnd")
        
        //basicAnimation.toValue = 1
        print(animationIncrement)
        print(animationStart)
        //duration of animation is 2 seconds
        //var v: CGFloat = 1/4
        basicAnimation.fromValue = animationStart
        basicAnimation.byValue = animationIncrement
        basicAnimation.isAdditive = true
        basicAnimation.isCumulative = true
        animationStart += animationIncrement
        //basicAnimation.
        //basicAnimation.duration = 2
        basicAnimation.fillMode = CAMediaTimingFillMode.forwards
        //Does not let the animation reset
        basicAnimation.isRemovedOnCompletion = false
        
        
        
        shapeLayer.add(basicAnimation, forKey: "basic")
        

        begin.alignmentMode = .center
        var percent: CGFloat = (animationStart*10000)
        percent = percent.rounded()
        begin.string = String("\(percent/100)%")
        
        //doUrls()
        
        
    }
    
    func setupLoader(){
        
        setupTrackLayer()
        
        let center = view.center
        let circularPath = UIBezierPath(arcCenter: center, radius: 100, startAngle: -CGFloat.pi/2, endAngle: 2*CGFloat.pi - CGFloat.pi/2, clockwise: true)
        
        //add circle to shape layer
        shapeLayer.path = circularPath.cgPath
        
        //Makes the outer stroke color red
        shapeLayer.strokeColor = UIColor.red.cgColor
        //sets the width of the stroke
        shapeLayer.lineWidth = 10
        //shapeLayer.fillColor = UIColor.clear.cgColor
        shapeLayer.strokeEnd = 0
        //Rounds the edgs
        shapeLayer.lineCap = CAShapeLayerLineCap.round
        
        
        view.layer.addSublayer(shapeLayer)
        
        view.addGestureRecognizer(UITapGestureRecognizer(target:self, action: #selector(shapeTapped)))
    }
    
    func setupTrackLayer(){
        let center = view.center
        let circularPath = UIBezierPath(arcCenter: center, radius: 110, startAngle: -CGFloat.pi/2, endAngle: 2*CGFloat.pi - CGFloat.pi/2, clockwise: true)
        
        //circularPath.append(UIBezierPath(arcCenter: center, radius: sin(circularPath.currentPoint).cgPoint, startAngle: -CGFloat.pi/2, endAngle:  2*CGFloat.pi - CGFloat.pi/2, clockwise: true))
        
        //circularPath.current
        
        //print(sin(Double.pi))
        //add circle to shape layer
        trackLayer.path = circularPath.cgPath
        
        //Makes the outer stroke color red
        trackLayer.strokeColor = UIColor.gray.cgColor
        //sets the width of the stroke
        trackLayer.lineWidth = 30
        //shapeLayer.fillColor = UIColor.clear.cgColor
        //trackLayer.strokeEnd = 0
        //Rounds the edgs
        trackLayer.lineCap = CAShapeLayerLineCap.round
        
        let pulseAnimation = CABasicAnimation(keyPath: "lineWidth")
        pulseAnimation.toValue = 50
        pulseAnimation.fromValue = 30
        pulseAnimation.autoreverses = true
        pulseAnimation.repeatCount = .infinity
        pulseAnimation.duration = 1
        pulseAnimation.fillMode =  CAMediaTimingFillMode.forwards
        pulseAnimation.isRemovedOnCompletion = false
        trackLayer.add(pulseAnimation, forKey: "pulse")
        
        
        view.layer.addSublayer(trackLayer)
    }
    
    func setupText(){
        begin.string = "TAP TO BEGIN\nCONVERSION"
        begin.fontSize = 18
        begin.frame = CGRect(origin: view.center, size: CGSize.init(width: 123, height: 50))
        //begin.numberOfLines = 2
        begin.position = view.center
        
        view.layer.addSublayer(begin)
        
        //setupTextConstraints()
        
    }
    
    func doUrls(){
        
        print("dispatching \(2*pages.count) URLs")
        
        let bucketGroup = DispatchQueue(label: "bucketGroup", qos: .userInitiated)
        let visionGroup = DispatchQueue(label: "visionGroup", qos: .utility, attributes: .initiallyInactive)
        
        
        
        let notify = DispatchWorkItem{
            print("ready")
            visionGroup.activate()
        }
        
        //sendBucketSettingsRequest()
        
        //sem.wait()
        //print("settings are set")
        
        
        bucketGroup.sync {
            for i in 0..<pages.count{
                print("bucket upload: \(i)")
                //let requestThread = DispatchGroup()
                sendBucketRequest(url: bucketURL, index: i)
                
                //requestThread.
                //requestThread.wait()
                //requestThread.leave()
                
                
                //DispatchQueue.main.async {
                //Do UI Stuff
                //}
            }
            
        }
        for _ in 0..<pages.count{
            sem.wait()
            print("incremented")
            incrementAnimation()
        }
        //requestThread.wait()
        notify.perform()
        //requestThread.wait()
        
        
        //while (lock == 0){}
        //Notice how when it is async, it is not executing serially
        visionGroup.sync {
            for i in 0..<pages.count{
                print("vision upload: \(i)")
                sendVisionRequest(url: apiURL,index: i)
            }
        }
        
        for _ in 0..<pages.count{
            sem.wait()
            incrementAnimation()
        }
        
        for i in 100..<110 {
            print("Ⓜ️", i)
        }
        
        let sixthScreen = SixthScreen()
        
        navigationController?.pushViewController(sixthScreen, animated: true)
        
        /*
         
        var fulfilledUrls: Array<URL> = []
        
        let group = DispatchGroup();
        
        print("Setting Bucket to Public")
        /*sendRequest(address: URL(string: "https://www.googleapis.com/storage/v1/b/bookreader/iam")!, index: pages.count, ID: "Settings", headerField: "Bearer \(AUTH)", headerValue: "Authorization", whenFinished: {
            () in
            group.leave()
            })
        */
        
        group.wait()
        
        print("Uploading to Bucket")
        for i in 0..<pages.count{
            print("picture \(i+1) / \(pages.count)")
            group.enter()
            let url: URL = URL(string: bucketURL + pages[i].fileName)!
            
            sendRequest(address: url ,index: i, ID: "Bucket", headerField: "Bearer \(AUTH)" ,headerValue: "Authorization",whenFinished: {
                () in
                fulfilledUrls.append(URL(string: self.bucketURL + self.pages[i].fileName)!)
                group.leave()
                //self.shapeTapped()
                })
        }
        
        for i in links{
            print(i)
        }
        
        group.wait()
        
        print("Contacting Google API")
        var index = 1
        for url in urls{
            print("url \(index) / \(urls.count) - \(pages[index-1].fileName) - \(url)")
            group.enter()
            sendRequest(address: url, index: 0,ID: "Vision",headerField: "X-IOS-Bundle-Identifier",headerValue: "Content-Type", whenFinished: {
                () in
                fulfilledUrls.append(url)
                group.leave()
                //self.shapeTapped()
            })
            index += 1
        }
        
        group.wait()
        print("finished dispatching")
        */
    }
    /*
    func sendBucketSettingsRequest(){
        
        requestThread.enter()
        
        let url = URL(string: "https://www.googleapis.com/storage/v1/b/bookreader/iam")!
        
        var request = URLRequest(url: url)
        
        let json = ["bindings":[["role": "roles/storage.objectViewer","members":["allUsers"]]]]
        let jsonRequest = try? JSONSerialization.data(withJSONObject: json);
        request.httpBody = jsonRequest;
        request.httpMethod = "PUT"
        request.setValue("Bearer \(AUTH)", forHTTPHeaderField: "Authorization")
        
        let task = URLSession.shared.dataTask(with: request, completionHandler: {(data, response, error) in
            do{
                if let usableData = data{
                    let resJson = try JSONSerialization.jsonObject(with: usableData, options: [])
                    print(resJson)
                }
            }catch let error as NSError{
                print(error)
            }
            self.requestThread.leave()
            self.sem.signal()
        })
        task.resume()
    }*/
    
    func sendBucketRequest(url: String, index: Int){
        
        //add to request thread
        requestThread.enter()
        
        //address of the bucket
        let address = URL(string: url)!
        
        //start setting up the request
        var request = URLRequest(url: address)
        request.httpMethod = "POST"
        request.setValue("Bearer \(AUTH)", forHTTPHeaderField: "Authorization")
        
        var json: [String: Any];
        
        //Setup body of http request...convert image to image data for upload
        ////////////////////////////////////////////////////////////////////////////////////
        let imageName = pages[index].fileName
        let image = pages[index].imageView.image!
        
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
        ////////////////////////////////////////////////////////////////////////////////////
        
        let task = URLSession.shared.dataTask(with: request, completionHandler: {(data, response, error) in
            
            do{
                if let usableData = data{
                    
                    let resJson = try JSONSerialization.jsonObject(with: usableData, options: [])
                    //Test to see what is inside the json
                    if let dict = resJson as? [String: Any]{
                        if let test = dict["mediaLink"]{
                            print(resJson);
                            var value = dict["mediaLink"] as! String
                            print("--\(imageName) Upload Success --")
                            self.links.append(value)
                            //self.callGoogleVisionAPI()
                            //leave request thread, and increment semaphore
                            self.requestThread.leave()
                            self.sem.signal()
                        }
                        else if let test = dict["error"] as? [String: Any]{
                            let err = test["code"]!
                            let message = test["message"]!
                            print("Error \(err) \(String(describing: message))")
                        }
                        else{
                            print("--\(imageName) Upload Total Failure")
                        }
                    }
                }

            }catch let error as NSError{
                print(error)
            }
        })
        task.resume()
    }
    
    func sendVisionRequest(url: String, index: Int){
        
        requestThread.enter()
        
        let address = URL(string: url)!
        
        //create the request object
        var request = URLRequest(url: address)
        request.httpMethod = "POST"
        request.setValue("X-IOS-Bundle-Identifier", forHTTPHeaderField: "Content-Type")

        
        var json: [String: Any];
        /*else if ID == "Settings"{
            json = ["bindings":[["role": "roles/storage.objectViewer","members":["allUsers"]]]]
            let jsonRequest = try? JSONSerialization.data(withJSONObject: json);
            request.httpBody = jsonRequest;
        }*/
        //upload for google text detection
        
        json = try ["requests":[["image":["source": ["imageUri": self.links[index]]],"features":[["type": "TEXT_DETECTION"]]]]]
        let jsonRequest = try? JSONSerialization.data(withJSONObject: json);
        request.httpBody = jsonRequest;
        
        
        print(request)
        
        let task = URLSession.shared.dataTask(with: request, completionHandler: {(data, response, error) -> Void in
            
            //parse the json
            do{
                //try to get the data
                if let usableData = data{
                    //get the json
                    let resJson = try JSONSerialization.jsonObject(with: usableData, options: [])
                    //uploading to google
                    //convert to dictionary
                    if var dictionary = resJson as? [String: Any]{
                        print(resJson)
                        //get the first array
                        var result = dictionary["responses"] as? [Any]
                        //get the first nested dictionary
                        dictionary = (result![0] as? [String: Any])!
                        //get the second array
                        
                        //this is where the message will be revealed as an error or not
                        if let textAnnotations = try dictionary["textAnnotations"] as? [Any]{
                            //Now get the text
                            dictionary = (result![0] as? [String: Any])!
                            
                            print(dictionary["description"] as! String)
                            //append
                            self.pagesText.append(dictionary["description"] as! String)
                            //print(self.converted.items[0])
                            //self.performSegue(withIdentifier: "extract_to_check", sender: self);
                        }else if let textAnnotations = try dictionary["error"] as? [Any] {
                            print(textAnnotations)
                            self.pagesText.append("error")
                        }
                        else{
                            //no content
                            print("There is no content")
                            self.pagesText.append("There is no content")
                        }

 
                        self.requestThread.leave()
                        self.sem.signal()
                        
                    }
                    
                }
                else{
                    print("data isnt usable")
                }

                
            } catch let error as NSError{
                print(error)
            }

        })
        task.resume()
        
    }
    
    
    /*
    
    func sendRequest(url: String, whenFinished: () -> Void){
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
        
    }*/
    

    /*
    // MARK: - Navigation

    // In a storyboard-based application, you will often want to do a little preparation before navigation
    override func prepare(for segue: UIStoryboardSegue, sender: Any?) {
        // Get the new view controller using segue.destination.
        // Pass the selected object to the new view controller.
    }
    */

}
