//
//  PageCell.swift
//  ProgramaticUI
//
//  Created by Michael DeLeo on 1/14/19.
//  Copyright © 2019 Michael DeLeo. All rights reserved.
//

import Foundation
import UIKit

class PageCell : UICollectionViewCell{
    
    override var isSelected: Bool{
        didSet{
            if self.isSelected
            {
                print("selected")
                self.select = true
                //self.transform = CGAffineTransform(a: f, b: <#T##CGFloat#>, c: <#T##CGFloat#>, d: <#T##CGFloat#>, tx: <#T##CGFloat#>, ty: <#T##CGFloat#>)
                self.transform = CGAffineTransform(scaleX: 1.1, y: 1.1)
                self.contentView.backgroundColor = UIColor.red
                //self.tickImageView.isHidden = false
            }
            else
            {
                self.select = false
                self.transform = CGAffineTransform.identity
                self.contentView.backgroundColor = UIColor.gray
                //self.tickImageView.isHidden = true
            }
        }
    }
    
    override init(frame: CGRect){
        super.init(frame: frame)
        setupViews()
    }
    
    /*
    let cellLabel: UILabel = {
        let cell = UILabel()
        cell.text = "Hello World"
        return cell
    }()
    */
    
    var select: Bool = false
    
    var fileName: String = {
        var file = String()
        file = "";
        return file
    }()
    
    var imageView: UIImageView = {
        let image = UIImageView()
        image.image = UIImage(named: "pic")
        return image
    }()
    func setupViews(){
        addSubview(imageView)
        setupConstraints()
    }
    
    func setupConstraints(){
        imageView.translatesAutoresizingMaskIntoConstraints = false
        imageView.topAnchor.constraint(equalTo: safeAreaLayoutGuide.topAnchor, constant: 0).isActive = true
        imageView.bottomAnchor.constraint(equalTo: safeAreaLayoutGuide.bottomAnchor, constant: 0).isActive = true
        imageView.rightAnchor.constraint(equalTo: safeAreaLayoutGuide.rightAnchor, constant: 0).isActive = true
        imageView.leftAnchor.constraint(equalTo: safeAreaLayoutGuide.leftAnchor, constant: 0).isActive = true
    }
    
    required init?(coder aDecoder: NSCoder) {
        fatalError("init(coder:) has not been implemented")
    }
}
