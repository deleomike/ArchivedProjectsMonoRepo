//
//  UIView+Extension.swift
//  ProgramaticUI
//
//  Created by Michael DeLeo on 1/12/19.
//  Copyright © 2019 Michael DeLeo. All rights reserved.
//

import Foundation
import UIKit

extension UIView{
    
    func setGradientBackground(colorOne: UIColor, colorTwo: UIColor){
        
        //create gradient object
        let gradientLayer = CAGradientLayer()
        //keep the gradient layer in the bounds of the frame (object)
        gradientLayer.frame = bounds;
        //layer takes an arry of colors...can be more than two
        gradientLayer.colors = [colorOne.cgColor,colorTwo.cgColor]
        //where the gradient begins
        gradientLayer.locations = [0.0, 1.0]
        //where the gradient ends...they blend in the middle
        gradientLayer.startPoint = CGPoint(x: 1.0, y: 1.0)
        gradientLayer.endPoint = CGPoint(x: 0.0, y: 0.0)
        
        //first layer inserted
        layer.insertSublayer(gradientLayer, at: 0)
    }
}
