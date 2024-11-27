//
//  CollectionView.swift
//  BookReader
//
//  Created by Michael DeLeo on 12/28/18.
//  Copyright © 2018 Michael DeLeo. All rights reserved.
//

import Foundation
import UIKit

class CollectionViewCell: UICollectionViewCell{
    @IBOutlet var Image: UIImageView!
    @IBOutlet var Label: UILabel!
    
    func Update(image: UIImage, title: String){
        Image.image = image;
        Label.text = title;
    }
}
