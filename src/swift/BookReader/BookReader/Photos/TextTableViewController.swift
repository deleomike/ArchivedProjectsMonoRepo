//
//  TextTableViewController.swift
//  BookReader
//
//  Created by Michael DeLeo on 12/30/18.
//  Copyright © 2018 Michael DeLeo. All rights reserved.
//
//Summary: The purpose of this file is to import all text files, and then display them in a UIStackView
//The user can then click on one, and this will bring up the read page. This also takes in new data, and can append a new file and a new part to the stack view

import Foundation
import UIKit

class TextTableViewController: UIViewController{
    var new_data:String = "";
    var clips:Queue<String> = Queue();
    
    override func prepare(for segue: UIStoryboardSegue, sender: Any?) {
        if segue.destination is Read{
            let vc = segue.destination as? Read
            vc?.text = new_data;
        }
    }
    
    override func viewDidLoad(){
        //TODO: Import and update the data
        if new_data == ""{
            //Do nothing
        }
        else{
            //APPEND to table
        }
    }
    
    override func viewDidAppear(_ animated: Bool) {
        performSegue(withIdentifier: "table_to_read", sender: self);
    }
}
