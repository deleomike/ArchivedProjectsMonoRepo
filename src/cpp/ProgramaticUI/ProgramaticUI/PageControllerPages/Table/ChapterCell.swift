//
//  ChapterCell.swift
//  ProgramaticUI
//
//  Created by Michael DeLeo on 1/12/19.
//  Copyright © 2019 Michael DeLeo. All rights reserved.
//

import UIKit

class ChapterCell: UITableViewCell {
    
    var title: UILabel = UILabel()
    var read: UIButton = UIButton()
    
    override init(style: UITableViewCell.CellStyle, reuseIdentifier: String?){
        super.init(style: style,reuseIdentifier: reuseIdentifier)
        
        setupEverything()
        
        setupViews()
        
    }
    
    required init?(coder aDecoder: NSCoder) {
        fatalError("init(coder:) has not been implemented")
    }
    
    override func awakeFromNib() {
        super.awakeFromNib()
        title.text = "Hello"
    }

    override func setSelected(_ selected: Bool, animated: Bool) {
        super.setSelected(selected, animated: animated)

        // Configure the view for the selected state
    }
    
    func setupEverything(){
        let label = UILabel()
        label.text = "HelloWorld"
        label.translatesAutoresizingMaskIntoConstraints = false
        label.font = label.font.withSize(20)
        title = label
    }
    
    func setupViews(){
        addSubview(title)
        title.setGradientBackground(colorOne: .blue, colorTwo: .red)
        addConstraints(NSLayoutConstraint.constraints(withVisualFormat: "H:|[v0]|", options: NSLayoutConstraint.FormatOptions(), metrics: nil, views: ["v0":title]))
        addConstraints(NSLayoutConstraint.constraints(withVisualFormat: "V:|[v0]|", options: NSLayoutConstraint.FormatOptions(), metrics: nil, views: ["v0":title]))
        //title.topAnchor.constraint(equalTo: safeAreaLayoutGuide.topAnchor,constant: 0).isActive = true
    }
    
    /*
    
    func setupCell(){
        self.backgroundColor = .gray
        
        self.addSubview(title)
        
        setupTextConstraints()
    }
    
    func setupTextConstraints(){
        //use auto layout
        title.translatesAutoresizingMaskIntoConstraints = false
        //Set the constraint of the leading anchor to the leading anchor with 20 spacing
        title.leadingAnchor.constraint(equalTo: self.leadingAnchor, constant: 20).isActive = true
        //Set the constraint of the right side fo the button
        title.trailingAnchor.constraint(equalTo: self.trailingAnchor, constant: 20).isActive = true
        //set the constraint of the height
        title.heightAnchor.constraint(equalToConstant: 50).isActive = true
        //set the button the center of the screen
        title.centerYAnchor.constraint(equalTo: self.centerYAnchor).isActive = true
    }*/

}
