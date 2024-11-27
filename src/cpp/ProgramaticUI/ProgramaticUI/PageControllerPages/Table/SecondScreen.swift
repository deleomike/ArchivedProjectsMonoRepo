//
//  SecondScreen.swift
//  ProgramaticUI
//
//  Created by Michael DeLeo on 1/12/19.
//  Copyright © 2019 Michael DeLeo. All rights reserved.
//

import UIKit

class SecondScreen: UIViewController {

    let tableView: UITableView = UITableView()
    //let add: UIBarButtonItem = UIBarButtonItem()
    
    var chapters:[String] = ["First File", "Second File"]  //list of chapter titles for the table

    override func viewDidLoad() {
        super.viewDidLoad()
        navigationItem.title = "Chapters"
        setupTable()
        tableView.tableFooterView = UIView(frame: CGRect.zero)
        let rightBarButton = UIBarButtonItem(barButtonSystemItem: .add, target: self, action: #selector(addButtonTapped))
        self.navigationItem.rightBarButtonItem = rightBarButton
        tableView.register(ChapterCell.self, forCellReuseIdentifier: "cellId")
        view.backgroundColor = .gray
        

        // Do any additional setup after loading the view.
    }
    
    func setupTable(){
        //set the data source as this controller
        tableView.dataSource = self
        //set the delegate as this controller
        tableView.delegate = self
        tableView.backgroundColor = .white
        
        //add the table view
        view.addSubview(tableView)
        
        setupTableConstraints()
        
        tableView.reloadData()
    }
    
    func setupTableConstraints(){
        
        tableView.translatesAutoresizingMaskIntoConstraints = false
        //Set the constraint of the leading anchor to the leading anchor with 20 spacing
        tableView.leadingAnchor.constraint(equalTo: view.leadingAnchor, constant: 20).isActive = true
        //Set the constraint of the right side fo the button
        tableView.rightAnchor.constraint(equalTo: view.safeAreaLayoutGuide.rightAnchor, constant: -20).isActive = true
        //set the constraint of the height
        //table.heightAnchor.constraint(equalToConstant: 300).isActive = true
        
        tableView.topAnchor.constraint(equalTo: view.safeAreaLayoutGuide.topAnchor, constant: 10).isActive = true
        
        tableView.bottomAnchor.constraint(equalTo: view.safeAreaLayoutGuide.bottomAnchor, constant: -10).isActive = true
    }
    
    func addNewChapter(chap: Chapter){
        //append title of the chapter
        chapters.append(chap.name())
        
        //index path is basically the row of the table
        //selects first section of last row
        let indexPath = IndexPath(row: chapters.count - 1, section: 0)
        
        //begin editing of table
        tableView.beginUpdates()
        //insert one row
        tableView.insertRows(at: [indexPath], with: .automatic)
        //end the updates
        tableView.endUpdates()
        
    }
    
    /*
    //setup function for the ui button
    func setupAddButton(){
        //set background color of button to white
        add.target = self;
        add.action = #selector(addButtonTapped)
        add.style = .plain
        //add button to the subview before the view appears
        view.addSubview(add)
        
        //ui doesnt know where the button is yet
        //IMPORTANT to add the constraints to the subview before it is added to the view
        //because otherwise it wont make sense to the phone
        //setAddButtonConstraints()
        //Now it does
    }*/
    
    @objc func addButtonTapped(){
        //let temp: Chapter = Chapter(pages:[],name: "hello")
        //temp.appendPage(page: "Hello world")
        //addNewChapter(chap: temp)
        let fourthScreen = FourthScreen()
        self.navigationController?.pushViewController(fourthScreen, animated: true)
    }
    /*
    func setAddButtonConstraints(){
        //use auto layout
        nextButton.translatesAutoresizingMaskIntoConstraints = false
        //Set the constraint of the leading anchor to the leading anchor with 20 spacing
        nextButton.leadingAnchor.constraint(equalTo: view.leadingAnchor, constant: 20).isActive = true
        //Set the constraint of the right side fo the button
        nextButton.trailingAnchor.constraint(equalTo: view.trailingAnchor, constant: 20).isActive = true
        //set the constraint of the height
        nextButton.heightAnchor.constraint(equalToConstant: 50).isActive = true
        //set the button the center of the screen
        nextButton.centerYAnchor.constraint(equalTo: view.centerYAnchor).isActive = true
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

extension SecondScreen: UITableViewDelegate, UITableViewDataSource{
    func tableView(_ tableView: UITableView, numberOfRowsInSection section: Int) -> Int {
        return chapters.count
    }
    
    func tableView(_ tableView: UITableView, cellForRowAt indexPath: IndexPath) -> UITableViewCell {
        let chapterTitle = chapters[indexPath.row]
        
        let cell = tableView.dequeueReusableCell(withIdentifier: "cellId") as! ChapterCell
        cell.title.text = chapterTitle
        
        return cell
    }
    
    func tableView(_ tableView: UITableView, canEditRowAt indexPath: IndexPath) -> Bool {
        return true
    }
    
    
    func tableView(_ tableView: UITableView, commit editingStyle: UITableViewCell.EditingStyle, forRowAt indexPath: IndexPath) {
        
        if editingStyle == .delete {
            chapters.remove(at: indexPath.row)
            
            tableView.beginUpdates()
            tableView.deleteRows(at: [indexPath], with: .automatic)
            tableView.endUpdates()
        }
    }
    
    func tableView(_ tableView: UITableView, didSelectRowAt indexPath: IndexPath) {
        print("section: \(indexPath.section)")
        print("row: \(indexPath.row)")
        
        let controller = ThirdScreen()
        navigationController?.pushViewController(controller, animated: true)
        //TODO
        //Send data to next view controller to read
        
    }
    
    
}
