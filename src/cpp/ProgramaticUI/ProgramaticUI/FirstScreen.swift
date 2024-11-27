//
//  FirstScreen.swift
//  ProgramaticUI
//
//  Created by Michael DeLeo on 1/11/19.
//  Copyright © 2019 Michael DeLeo. All rights reserved.
//

import UIKit

class FirstScreen: UIViewController {
    
    //instance of button
    let nextButton = UIButton()
    var foreground = CAShapeLayer()

    override func viewDidLoad() {
        super.viewDidLoad()
        setupNextButton()
        view.backgroundColor = .white
        //view.setGradientBackground(colorOne: .white, colorTwo: .blue)
        setupShape()

        // Do any additional setup after loading the view.
    }
    
    func setupShape(){
        var path = UIBezierPath()
        
        
        let center = view.center
        let circularPath = UIBezierPath(arcCenter: center, radius: 100, startAngle: -CGFloat.pi/2, endAngle: 2*CGFloat.pi - CGFloat.pi/2, clockwise: true)
        
        path.append(circularPath)
        foreground.path = path.cgPath
        foreground.strokeColor = UIColor.red.cgColor
        //sets the width of the stroke
        foreground.lineWidth = 10
        //shapeLayer.fillColor = UIColor.clear.cgColor
        foreground.strokeEnd = 1
        //Rounds the edgs
        foreground.lineCap = CAShapeLayerLineCap.round
        
        
        view.layer.addSublayer(foreground)
    }
    
    //setup function for the ui button
    func setupNextButton(){
        //set background color of button to white
        nextButton.backgroundColor = .white
        //set color of title, control state normal
        nextButton.setTitleColor(.blue, for: .normal)
        //set the title of the button
        nextButton.setTitle("LET'S BEGIN", for: .normal)
        
        //for this window, choose the selector nextButtontapped to be called when the button is touched up inside
        nextButton.addTarget(self, action: #selector(nextButtonTapped), for: .touchUpInside)
        
        //add button to the subview before the view appears
        view.addSubview(nextButton)
        
        //ui doesnt know where the button is yet
        //IMPORTANT to add the constraints to the subview before it is added to the view
        //because otherwise it wont make sense to the phone
        setNextButtonConstraints()
        //Now it does
    }
    
    @objc func nextButtonTapped(){
        //setup the next screen
        let nextScreen = SecondScreen()
        //push controller onto the stack
        navigationController?.pushViewController(nextScreen, animated: true)
    }
    
    func setNextButtonConstraints(){
        //use auto layout
        nextButton.translatesAutoresizingMaskIntoConstraints = false
        //Set the constraint of the leading anchor to the leading anchor with 20 spacing
        nextButton.leadingAnchor.constraint(equalTo: view.leadingAnchor, constant: 20).isActive = true
        //Set the constraint of the right side fo the button
        nextButton.rightAnchor.constraint(equalTo: view.safeAreaLayoutGuide.rightAnchor, constant: -20).isActive = true
        //set the constraint of the height
        nextButton.heightAnchor.constraint(equalToConstant: 50).isActive = true
        //set the button the center of the screen
        nextButton.centerYAnchor.constraint(equalTo: view.centerYAnchor).isActive = true
    }
    

    /*
    // MARK: - Navigation

    // In a storyboard-based application, you will often want to do a little preparation before navigation
    override func prepare(for segue: UIStoryboardSegue, sender: Any?) {
        // Get the new view controller using segue.destination.
        // Pass the selected object to the new view controller.
    }
    */

}
