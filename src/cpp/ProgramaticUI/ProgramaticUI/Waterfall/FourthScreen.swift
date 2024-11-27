//
//  FourthScreen.swift
//  ProgramaticUI
//
//  Created by Michael DeLeo on 1/14/19.
//  Copyright © 2019 Michael DeLeo. All rights reserved.
//

import UIKit
import Foundation
import Photos

private let reuseIdentifier = "Cell"


//TODO: Have first photo be a blank photo
class FourthScreen: UIViewController, PageViewDelegate, UINavigationControllerDelegate {
    
    func deleteImage(index: IndexPath) {
        pages.remove(at: index.row)
        collectionView.reloadData()
        print("delete")
    }
    
    
    var collectionView: UICollectionView!
    var pages: [PageCell]!
    var done: UIButton!

    override func viewDidLoad() {
        super.viewDidLoad()
        
        self.view.backgroundColor = .black
        self.navigationItem.title = "Photos"
        let rightBarButton = UIBarButtonItem(barButtonSystemItem: .add, target: self, action: #selector(addButtonTapped))
        self.navigationItem.rightBarButtonItem = rightBarButton
        
        setupCollectionView()
        setupButton()
        
    
        //collectionView.setGradientBackground(colorOne: .red, colorTwo: .white)

        // Uncomment the following line to preserve selection between presentations
        // self.clearsSelectionOnViewWillAppear = false

        // Register cell classes
        //self.collectionView!.register(UICollectionViewCell.self, forCellWithReuseIdentifier: reuseIdentifier)

        // Do any additional setup after loading the view.
    }
    
    @objc func addButtonTapped(){
        print("add photo")
        let vc = UIImagePickerController();
        //Assign the delegate
        vc.delegate = self
        //Allow editing of the object
        vc.allowsEditing = true;
        
        //Check if the device can take pictures
        if UIImagePickerController.isSourceTypeAvailable(.camera){
            print("Camera is Available\n");
            //Assign object's source as the camera
            vc.sourceType = .photoLibrary;
            //vc.sourceType = UIImagePickerController.SourceType.camera;
        }
        else{
            print("Camera is not Available\n")
            //Assign object's source as the photo library
            vc.sourceType = .photoLibrary;
        }
        self.present(vc, animated: true, completion: nil);
    }
    
    @objc func doneButtonTapped(){
        print("Upload photos")
        let fifthScreen = FifthScreen()
        fifthScreen.pages = pages
        navigationController?.pushViewController(fifthScreen, animated: false)
    }
    
    func setupButton(){
        done = UIButton()
        done.setTitle("DONE", for: .normal)
        done.backgroundColor = .green
        done.setTitleColor(.black, for: .normal)
        done.addTarget(self, action: #selector(doneButtonTapped), for: .touchUpInside)
        
        view.addSubview(done)
        
        setupButtonConstraints()
    }
    
    func setupButtonConstraints(){
        done.translatesAutoresizingMaskIntoConstraints = false
        done.topAnchor.constraint(equalTo: view.safeAreaLayoutGuide.topAnchor, constant: 550).isActive = true
        done.bottomAnchor.constraint(equalTo: view.safeAreaLayoutGuide.bottomAnchor, constant: -10).isActive = true
        done.rightAnchor.constraint(equalTo: view.safeAreaLayoutGuide.rightAnchor, constant: -10).isActive = true
        done.leftAnchor.constraint(equalTo: view.safeAreaLayoutGuide.leftAnchor, constant: 10).isActive = true
    }
    
    func setupCollectionView(){
        let pagec1 = PageCell()
        pages = [pagec1]
        
        //Establish the layout
        let layout = UICollectionViewFlowLayout()
        layout.sectionInset = UIEdgeInsets(top: 0, left: 0, bottom: 0, right: 0)
        layout.minimumInteritemSpacing = 0
        layout.minimumLineSpacing = 0
        //Initialize the collection view
        collectionView = UICollectionView(frame: CGRect.zero, collectionViewLayout: layout)
        //register the first cell
        collectionView.register(PageCell.self, forCellWithReuseIdentifier: reuseIdentifier)
        
        collectionView.delegate = self
        collectionView.dataSource = self
        
        collectionView.backgroundColor = .white
        view.addSubview(collectionView)
        
        setupCollectionViewConstraints()
        
        collectionView.reloadData()
    }
    
    func setupCollectionViewConstraints(){
        collectionView.translatesAutoresizingMaskIntoConstraints = false
        collectionView.topAnchor.constraint(equalTo: view.safeAreaLayoutGuide.topAnchor, constant: 10).isActive = true
        collectionView.bottomAnchor.constraint(equalTo: view.safeAreaLayoutGuide.bottomAnchor, constant: -50).isActive = true
        collectionView.rightAnchor.constraint(equalTo: view.safeAreaLayoutGuide.rightAnchor, constant: -10).isActive = true
        collectionView.leftAnchor.constraint(equalTo: view.safeAreaLayoutGuide.leftAnchor, constant: 10).isActive = true
    }
    
    @objc func moveCell(){
        print("Tapped")
        
        //collectionView.beginInteractiveMovementForItem(at:)
    }
    
    func showPage(indexPath: IndexPath){
        print("showPage")
        let pageview = PageView()
        pageview.delegate = self
        pageview.imageView.image = pages[indexPath.row].imageView.image
        pageview.index = indexPath
        self.navigationController?.pushViewController(pageview, animated: true)
    
    }
    
    
    //func collectionView

    /*
    // MARK: - Navigation

    // In a storyboard-based application, you will often want to do a little preparation before navigation
    override func prepare(for segue: UIStoryboardSegue, sender: Any?) {
        // Get the new view controller using [segue destinationViewController].
        // Pass the selected object to the new view controller.
    }
    */



}

extension FourthScreen: UICollectionViewDelegate, UICollectionViewDataSource, UICollectionViewDelegateFlowLayout{
    // MARK: UICollectionViewDataSource
    
    /*func numberOfSections(in collectionView: UICollectionView) -> Int {
        // #warning Incomplete implementation, return the number of sections
        return 1
    }*/
    
    
    func collectionView(_ collectionView: UICollectionView,
                                 didSelectItemAt indexPath: IndexPath) {
        // here you know which item is selected by accessing indexPath.item property, for example:
        let selectedImage = pages[indexPath.row]
        showPage(indexPath: indexPath)
        
    }
    
    
    //Use for size
    func collectionView(_ collectionView: UICollectionView, layout collectionViewLayout: UICollectionViewLayout, sizeForItemAt indexPath: IndexPath) -> CGSize {
        return CGSize(width: view.bounds.width/2-10, height: view.bounds.height/2)
        //return CGSize(width: 100, height: 100)
    }
    
    //Use for interspacing
    func collectionView(_ collectionView: UICollectionView,
                        layout collectionViewLayout: UICollectionViewLayout,
                        minimumInteritemSpacingForSectionAt section: Int) -> CGFloat {
        return 0
    }
    
    func collectionView(_ collectionView: UICollectionView, layout
        collectionViewLayout: UICollectionViewLayout,
                        minimumLineSpacingForSectionAt section: Int) -> CGFloat {
        return 0
    }
    
    func collectionView(_ collectionView: UICollectionView, numberOfItemsInSection section: Int) -> Int {
        print("returned views")
        // #warning Incomplete implementation, return the number of items
        return pages.count
    }
    
    func collectionView(_ collectionView: UICollectionView, cellForItemAt indexPath: IndexPath) -> UICollectionViewCell {
        
        
        let cell = collectionView.dequeueReusableCell(withReuseIdentifier: reuseIdentifier, for: indexPath) as! PageCell
        
        cell.imageView.image = pages[indexPath.row].imageView.image
        
        //configure cell to be rearranged after a long touch
        //let gesture = UILongPressGestureRecognizer(target: self, action: #selector(showPage))
        //gesture.minimumPressDuration = 1
        
        //cell.addGestureRecognizer(gesture)
        
        //let gesture2 = UITapGestureRecognizer(target: self, action: #selector(showPage))
        //cell.addGestureRecognizer(gesture2)
        
        // Configure the cell
        
        return cell
    }
    
    // MARK: UICollectionViewDelegate
    
    
     // Uncomment this method to specify if the specified item should be highlighted during tracking
     func collectionView(_ collectionView: UICollectionView, shouldHighlightItemAt indexPath: IndexPath) -> Bool {
     return true
     }
    
    
    /*
     // Uncomment this method to specify if the specified item should be selected
     override func collectionView(_ collectionView: UICollectionView, shouldSelectItemAt indexPath: IndexPath) -> Bool {
     return true
     }
     */
    
    /*
     // Uncomment these methods to specify if an action menu should be displayed for the specified item, and react to actions performed on the item
     override func collectionView(_ collectionView: UICollectionView, shouldShowMenuForItemAt indexPath: IndexPath) -> Bool {
     return false
     }
     
     override func collectionView(_ collectionView: UICollectionView, canPerformAction action: Selector, forItemAt indexPath: IndexPath, withSender sender: Any?) -> Bool {
     return false
     }
     
     override func collectionView(_ collectionView: UICollectionView, performAction action: Selector, forItemAt indexPath: IndexPath, withSender sender: Any?) {
     
     }
     */
}


extension FourthScreen: UIImagePickerControllerDelegate{
    
    func imagePickerController(_ picker: UIImagePickerController, didFinishPickingMediaWithInfo info: [UIImagePickerController.InfoKey : Any]){
        
        let newPage = PageCell()
        
        // Local variable inserted by Swift 4.2 migrator.
        let infof = convertFromUIImagePickerControllerInfoKeyDictionary(info)
        
        //let Cell: CollectionViewCell = CollectionViewCell();
        
        picker.dismiss(animated: true, completion: nil);
        
        
        if var pickedImage = infof[convertFromUIImagePickerControllerInfoKey(UIImagePickerController.InfoKey.originalImage)] as? UIImage{
            if let imageURL = info[UIImagePickerController.InfoKey.referenceURL] as? URL {
                let result = PHAsset.fetchAssets(withALAssetURLs: [imageURL], options: nil)
                let asset = result.firstObject
                print("FileName:")
                print(asset?.value(forKey: "filename"))
                newPage.fileName = asset?.value(forKey: "filename") as! String
                //pickedImage(named: asset?.value(forKey: "filename"))
                newPage.imageView.image = pickedImage
                
                pages.append(newPage)
                collectionView.reloadData()
            }
            
        }
        
    }
    
    // Helper function inserted by Swift 4.2 migrator.
    fileprivate func convertFromUIImagePickerControllerInfoKeyDictionary(_ input: [UIImagePickerController.InfoKey: Any]) -> [String: Any] {
        return Dictionary(uniqueKeysWithValues: input.map {key, value in (key.rawValue, value)})
    }
    
    // Helper function inserted by Swift 4.2 migrator.
    fileprivate func convertFromUIImagePickerControllerInfoKey(_ input: UIImagePickerController.InfoKey) -> String {
        return input.rawValue
    }
}
