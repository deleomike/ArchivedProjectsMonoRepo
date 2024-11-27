//
//  ReadController.swift
//  BookReader
//
//  Created by Michael DeLeo on 12/28/18.
//  Copyright © 2018 Michael DeLeo. All rights reserved.
//
//Summary: The purpose of this file is to import the text that has been saved into the memory, and to play it to the user
//All text is displayed in a label inside of a scroller

//IDEA For later...highlight which sentence is being spoken. code for it is below in comments

import Foundation
import UIKit
import AVFoundation

class Read: UIViewController{
    
    //Consider using google text to speech
    
    
    var text:String = "";
    
    @IBOutlet var label: UILabel!
    
    override func viewDidAppear(_ animated: Bool) {
        //Initialize the sentences queue
        text_to_audio();

    }
    
    override func viewDidLoad(){
        super.viewDidLoad()

        
        let label = UILabel()
        label.textAlignment = .natural
        self.label.text = text;
        
    }

    func text_to_audio(){
        //synth holds the reference for AVSpeechSynthesizer
        let synth = AVSpeechSynthesizer();
        
        //Holds the variable of the string to convert to speech
        let myUtterance = AVSpeechUtterance(string: text);
        synth.speak(myUtterance);

    }

}

/*class Read: UIViewController{
 var text:String = "";
 var sentences:Queue<String> = Queue();
 
 
 var lastPosition = 0;
 @IBOutlet var stackView: UIStackView!
 @IBOutlet var label: UILabel!
 
 override func viewDidAppear(_ animated: Bool) {
 //Initialize the sentences queue
 text_to_audio();
 
 }
 
 override func viewDidLoad(){
 super.viewDidLoad()
 let arr = text.characters.split{$0 == "."}.map(String.init)
 sentences.items = arr;
 sentences.size = arr.capacity;
 for i in 0..<sentences.size{
 print("\(sentences.items[i])\n");
 }
 let stackView = UIStackView();
 stackView.axis = .horizontal
 stackView.alignment = .fill // .leading
 stackView.distribution = .fill
 
 //let label = UILabel()
 //self.label.text = "Hello";
 //stackView.addArrangedSubview(label);
 /*
 let tap = UIGestureRecognizer(target: self, action: #selector(tapped))
 view.addGestureRecognizer(tap);
 
 createViews();*/
 
 }
 
 @IBAction func dosomething(_ sender: UIButton){
 let lab = UILabel(frame: CGRect(x: 0, y: 0, width: 200, height: 21))
 lab.center = CGPoint(x: 50, y: lastPosition);
 lastPosition = lastPosition + 50;
 lab.textAlignment = .center
 lab.text = "I'm a test label";
 self.stackView.addSubview(lab)
 }
 /*
 
 func createViews(){
 stackView = UIStackView(frame: .zero);
 stackView.translatesAutoresizingMaskIntoConstraints = false
 stackView.axis = .vertical
 stackView.alignment = .top
 view.addSubview(stackView)
 
 NSLayoutConstraint.activate([stackView.leftAnchor.constraint(equalTo: view.leftAnchor),
 stackView.rightAnchor.constraint(equalTo: view.rightAnchor),
 stackView.topAnchor.constraint(equalTo: view.topAnchor)])
 }
 
 @objc func tapped(){
 let label = UILabel(frame: .zero)
 label.translatesAutoresizingMaskIntoConstraints = false
 label.textColor = UIColor.black
 label.text = "Hi I am label\(lastLabelCount)"
 stackView.addArrangedSubview(label)
 }*/
 func text_to_audio(){
 //synth holds the reference for AVSpeechSynthesizer
 let synth = AVSpeechSynthesizer();
 
 //Holds the variable of the string to convert to speech
 for i in 0..<sentences.size{
 var myUtterance = AVSpeechUtterance(string: sentences.items[i]);
 synth.speak(myUtterance);
 }
 
 }
 
 
 /*(void) setup {
 
 //View 1
 UIView *view1 = [[UIView alloc] init];
 view1.backgroundColor = [UIColor blueColor];
 [view1.heightAnchor constraintEqualToConstant:100].active = true;
 [view1.widthAnchor constraintEqualToConstant:120].active = true;
 
 
 //View 2
 UIView *view2 = [[UIView alloc] init];
 view2.backgroundColor = [UIColor greenColor];
 [view2.heightAnchor constraintEqualToConstant:100].active = true;
 [view2.widthAnchor constraintEqualToConstant:70].active = true;
 
 //View 3
 UIView *view3 = [[UIView alloc] init];
 view3.backgroundColor = [UIColor magentaColor];
 [view3.heightAnchor constraintEqualToConstant:100].active = true;
 [view3.widthAnchor constraintEqualToConstant:180].active = true;
 
 //Stack View
 UIStackView *stackView = [[UIStackView alloc] init];
 
 stackView.axis = UILayoutConstraintAxisVertical;
 stackView.distribution = UIStackViewDistributionEqualSpacing;
 stackView.alignment = UIStackViewAlignmentCenter;
 stackView.spacing = 30;
 
 
 [stackView addArrangedSubview:view1];
 [stackView addArrangedSubview:view2];
 [stackView addArrangedSubview:view3];
 
 stackView.translatesAutoresizingMaskIntoConstraints = false;
 [self.view addSubview:stackView];
 
 
 //Layout for Stack View
 [stackView.centerXAnchor constraintEqualToAnchor:self.view.centerXAnchor].active = true;
 [stackView.centerYAnchor constraintEqualToAnchor:self.view.centerYAnchor].active = true;
 }*/
 }
*/
