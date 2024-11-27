//
//  CheckerViewController.swift
//  BookReader
//
//  Created by Michael DeLeo on 12/30/18.
//  Copyright © 2018 Michael DeLeo. All rights reserved.
//

import Foundation
import UIKit

class CheckerViewController: UIViewController{
    var Text:Queue<String> = Queue();
    
    @IBOutlet var label:UILabel!;
    
    override func viewDidLoad() {
        super.viewDidLoad()
        self.label.text = "Hello";
    }
    
    override func viewDidAppear(_ animated: Bool) {
        while (Text.size == 0){}
        print(Text.items[0])
        self.label.text = Text.items[0]
        //self.label.text = Text.items[0]
    }
    
    override func prepare(for segue: UIStoryboardSegue, sender: Any?) {
        //If the destination is the table of text, then assign the converted text to the new data variable
        if segue.destination is TextTableViewController{
            let vc = segue.destination as? TextTableViewController
            vc?.new_data = Text.items[0];
        }
    }
    
    @IBAction func Redo(_ sender: UIButton){
        print("Redo the pictures\n")
        performSegue(withIdentifier: "check_to_pic", sender: self);
    }
    
    @IBAction func Continue(_ sender: UIButton){
        print("Continuing\n");
        performSegue(withIdentifier: "check_to_table", sender: self);
    }
}
