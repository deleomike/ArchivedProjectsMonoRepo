//
//  ViewController.swift
//  BookReader
//
//  Created by Michael DeLeo on 12/25/18.
//  Copyright © 2018 Michael DeLeo. All rights reserved.
//

import UIKit
import Photos

class ViewController: UIViewController {

    override func viewDidLoad() {
        super.viewDidLoad()

        // Do any additional setup after loading the view, typically from a nib.
        //view.backgroundColor = .white;
    }
    
    //IBACTION is the statement to indicate a buttion action. It connects code to a trigger event
    //Precondition:
    //Postcondition:
    //Summary:
    @IBAction func next_page(_ sender: UIButton){
        //the current page is main, no bundle
        //let storyboard = UIStoryboard(name: "main",bundle: nil);
        //Change view controller page to take picture
        //let controller = storyboard.instantiateViewController(withIdentifier: "Take_Picture");
        //change page
        //self.present(controller,animated:true,completion: nil);
        if (sender.tag == 0){
            //take pictures
            performSegue(withIdentifier: "main_to_pic", sender: self);
                        
            //change page to show the pictures taken
            
            print("\nPicture Taken\n");
        }
        else{
            //goes to the the read page where all the audio is
            performSegue(withIdentifier: "main_to_table", sender: self);
        }

    }

}

