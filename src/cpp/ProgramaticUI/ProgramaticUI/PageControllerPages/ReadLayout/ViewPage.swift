//
//  ViewPage1.swift
//  ProgramaticUI
//
//  Created by Michael DeLeo on 1/13/19.
//  Copyright © 2019 Michael DeLeo. All rights reserved.
//

import UIKit

class ViewPage: UIViewController {
    
    var content: UITextView = {
        let temp = UITextView()
        temp.text = "Yes; As sparrows eagles, or the hare the lion. If I say sooth, I must report they were As cannons overcharged with double cracks, so they Doubly redoubled strokes upon the foe: Except they meant to bathe in reeking wounds, Or memorise another Golgotha, I cannot tell. But I am faint, my gashes cry for help.Yes; As sparrows eagles, or the hare the lion. If I say sooth, I must report they were As cannons overcharged with double cracks, so they Doubly redoubled strokes upon the foe: Except they meant to bathe in reeking wounds, Or memorise another Golgotha, I cannot tell. But I am faint, my gashes cry for help.Yes; As sparrows eagles, or the hare the lion. If I say sooth, I must report they were As cannons overcharged with double cracks, so they Doubly redoubled strokes upon the foe: Except they meant to bathe in reeking wounds, Or memorise another Golgotha, I cannot tell. But I am faint, my gashes cry for help.Yes; As sparrows eagles, or the hare the lion. If I say sooth, I must report they were As cannons overcharged with double cracks, so they Doubly redoubled strokes upon the foe: Except they meant to bathe in reeking wounds, Or memorise another Golgotha, I cannot tell. But I am faint, my gashes cry for help.Yes; As sparrows eagles, or the hare the lion. If I say sooth, I must report they were As cannons overcharged with double cracks, so they Doubly redoubled strokes upon the foe: Except they meant to bathe in reeking wounds, Or memorise another Golgotha, I cannot tell. But I am faint, my gashes cry for help."
        return temp
        
    }()
    
   /* var scrollView: UIScrollView!
    var topLabel: UILabel = {
        let label = UILabel()
        label.text = "Yes; As sparrows eagles, or the hare the lion. If I say sooth, I must report they were As cannons overcharged with double cracks, so they Doubly redoubled strokes upon the foe: Except they meant to bathe in reeking wounds, Or memorise another Golgotha, I cannot tell. But I am faint, my gashes cry for help.Yes; As sparrows eagles, or the hare the lion. If I say sooth, I must report they were As cannons overcharged with double cracks, so they Doubly redoubled strokes upon the foe: Except they meant to bathe in reeking wounds, Or memorise another Golgotha, I cannot tell. But I am faint, my gashes cry for help.Yes; As sparrows eagles, or the hare the lion. If I say sooth, I must report they were As cannons overcharged with double cracks, so they Doubly redoubled strokes upon the foe: Except they meant to bathe in reeking wounds, Or memorise another Golgotha, I cannot tell. But I am faint, my gashes cry for help.Yes; As sparrows eagles, or the hare the lion. If I say sooth, I must report they were As cannons overcharged with double cracks, so they Doubly redoubled strokes upon the foe: Except they meant to bathe in reeking wounds, Or memorise another Golgotha, I cannot tell. But I am faint, my gashes cry for help.Yes; As sparrows eagles, or the hare the lion. If I say sooth, I must report they were As cannons overcharged with double cracks, so they Doubly redoubled strokes upon the foe: Except they meant to bathe in reeking wounds, Or memorise another Golgotha, I cannot tell. But I am faint, my gashes cry for help."
        label.backgroundColor = .green
        label.translatesAutoresizingMaskIntoConstraints = false
        label.numberOfLines = 0
        label.sizeToFit()
        //label.preferredmax
        return label
    }()
*/
    override func viewDidLoad() {
        super.viewDidLoad()
        self.view.setGradientBackground(colorOne: .white, colorTwo: .black)

        setupText()
        //setupScrollView()
        // Do any additional setup after loading the view.
    }
    
    
    func setupText(){
        content.font = UIFont.systemFont(ofSize: 20)
        content.isScrollEnabled = true
        content.isEditable = false
        content.translatesAutoresizingMaskIntoConstraints = false
        content.backgroundColor = .gray
        view.addSubview(content)
        setupTextConstraints()
        //topLabel.text = "hello\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\nworld"
    }
    
    func setupTextConstraints(){
        content.topAnchor.constraint(equalTo: view.safeAreaLayoutGuide.topAnchor,constant: 0).isActive = true
        content.rightAnchor.constraint(equalTo: view.safeAreaLayoutGuide.rightAnchor,constant: 0).isActive = true
        content.leftAnchor.constraint(equalTo: view.safeAreaLayoutGuide.leftAnchor,constant: 0).isActive = true
        content.bottomAnchor.constraint(equalTo: view.safeAreaLayoutGuide.bottomAnchor,constant: 0).isActive = true
    }
    
    /*
    func setupScrollView(){
        
        let screensize: CGRect = UIScreen.main.bounds
        let screenWidth = screensize.width
        let screenHeight = screensize.height
        scrollView = UIScrollView(frame: CGRect(x: 0, y: 120, width: screenWidth, height: screenHeight))
        scrollView.backgroundColor = UIColor.gray
        
        scrollView.addSubview(topLabel)
        
        
        setupLabelConstraint()
        

        //scrollView.autoresizingMask = UIView.AutoresizingMask(rawValue: UIView.AutoresizingMask.flexibleWidth.rawValue | UIView.AutoresizingMask.flexibleHeight.rawValue)
        
        scrollView.contentSize = CGSize(width: screenWidth, height: 2000)
        view.addSubview(scrollView)
    }
    
    func setupLabelConstraint(){
        NSLayoutConstraint(item: topLabel, attribute: .leading, relatedBy: .equal, toItem: scrollView, attribute: .leadingMargin, multiplier: 1, constant: 10).isActive = true
        NSLayoutConstraint(item: topLabel, attribute: .width, relatedBy: .equal, toItem: nil, attribute: .notAnAttribute, multiplier: 1, constant: 350).isActive = true
        NSLayoutConstraint(item: topLabel, attribute: .top, relatedBy: .equal, toItem: scrollView, attribute: .topMargin, multiplier: 1, constant: 10).isActive = true
        NSLayoutConstraint(item: topLabel, attribute: .height, relatedBy: .equal, toItem: nil, attribute: .notAnAttribute, multiplier: 1, constant: 100).isActive = true
    }
    */
    /*
    // MARK: - Navigation

    // In a storyboard-based application, you will often want to do a little preparation before navigation
    override func prepare(for segue: UIStoryboardSegue, sender: Any?) {
        // Get the new view controller using segue.destination.
        // Pass the selected object to the new view controller.
    }
    */

}
