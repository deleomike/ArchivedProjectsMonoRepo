//
//  PageView.swift
//  ProgramaticUI
//
//  Created by Michael DeLeo on 1/14/19.
//  Copyright © 2019 Michael DeLeo. All rights reserved.
//

import UIKit

protocol PageViewDelegate{
    func deleteImage(index: IndexPath);
}

class PageView: UIViewController {
    
    var delegate:PageViewDelegate?

    let imageView: UIImageView = {
        let image = UIImageView()
        image.image = UIImage(named: "family")
        return image
    }()
    
    var index: IndexPath = {
        var indexpath = IndexPath()
        return indexpath
    }()
    
    override func viewDidLoad() {
        super.viewDidLoad()
        
        
        let rightBarButton = UIBarButtonItem(barButtonSystemItem: .trash, target: self, action: #selector(trashButtonTapped))
        self.navigationItem.rightBarButtonItem = rightBarButton
        
        self.view.addSubview(imageView)
        
        imageView.translatesAutoresizingMaskIntoConstraints = false
        imageView.topAnchor.constraint(equalTo: view.safeAreaLayoutGuide.topAnchor, constant: 0).isActive = true
        imageView.bottomAnchor.constraint(equalTo: view.safeAreaLayoutGuide.bottomAnchor, constant: 0).isActive = true
        imageView.rightAnchor.constraint(equalTo: view.safeAreaLayoutGuide.rightAnchor, constant: 0).isActive = true
        imageView.leftAnchor.constraint(equalTo: view.safeAreaLayoutGuide.leftAnchor, constant: 0).isActive = true
        
        // Do any additional setup after loading the view.
    }
    
    @objc func trashButtonTapped(){
        self.delegate?.deleteImage(index: index);
        navigationController?.popViewController(animated: true)
        //navigationController?
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
