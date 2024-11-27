//
//  ThirdScreen.swift
//  ProgramaticUI
//
//  Created by Michael DeLeo on 1/12/19.
//  Copyright © 2019 Michael DeLeo. All rights reserved.
//

import UIKit

class ThirdScreen: UIPageViewController, UIPageViewControllerDataSource, UIPageViewControllerDelegate {
    
    var pages = [UIViewController]()
    let pageControl = UIPageControl()

    

    override func viewDidLoad() {
        super.viewDidLoad()
        self.navigationItem.title = "Page \(pageControl.currentPage + 2)"
        let rightBarButton = UIBarButtonItem(barButtonSystemItem: .play, target: self, action: #selector(readText))
        self.navigationItem.rightBarButtonItem = rightBarButton
        
        setupPageController()
        // Do any additional setup after loading the view.
    }
    
    @objc func readText(){
        //STUB FOR TEXT READING CODE
        
        print("Code Read")
        turnPageAndRead()
        //Turn to the next page and read
    }
    
    
    func turnPageAndRead(){
        //TODO
        if (pageControl.currentPage + 1) == pages.count{
            //Last page
            print("Last Page")
            
        }
        else{
            setViewControllers([pages[pageControl.currentPage + 1]], direction: .forward, animated: true, completion: nil)
            //advance page and read
            pageControl.currentPage = pageControl.currentPage + 1
            self.navigationItem.title = "Page \(pageControl.currentPage + 1)"
            
            readText()
        }
    }

    func setupPageController(){
        //set the datasource and the delegate for the page controller
        self.delegate = self
        self.dataSource = self
        
        //start at the first page
        let initialpage = 0
        
        //initialize the page's view controllers
        let page1 = ViewPage()
        let page2 = ViewPage()
        let page3 = ViewPage()
        
        page2.content.text = "hello"
        
        
        //append the pages to the array
        self.pages.append(page1)
        self.pages.append(page2)
        self.pages.append(page3)
        
        
        //setup the first view controller to be seen
        setViewControllers([pages[initialpage]], direction: .forward, animated: true, completion: nil)
        
        //PageControl
        self.pageControl.frame = CGRect()
        //color of the dot that indicates current page
        self.pageControl.currentPageIndicatorTintColor = UIColor.black
        //color of dots that are not the current page
        self.pageControl.pageIndicatorTintColor = UIColor.lightGray
        //set the number of pages
        self.pageControl.numberOfPages = self.pages.count
        //set the current page
        self.pageControl.currentPage = initialpage
        //add the page controller the sub view
        self.view.addSubview(self.pageControl)
        
        
        
        //now that the page controller is added to the subview, do constraints
        setupPageControllerConstraints()
    }
    
    func setupPageControllerConstraints(){
        self.pageControl.translatesAutoresizingMaskIntoConstraints = false
        self.pageControl.bottomAnchor.constraint(equalTo: self.view.bottomAnchor, constant: -5).isActive = true
        self.pageControl.widthAnchor.constraint(equalTo: self.view.widthAnchor, constant: -20).isActive = true
        self.pageControl.heightAnchor.constraint(equalToConstant: 20).isActive = true
        self.pageControl.centerXAnchor.constraint(equalTo: self.view.centerXAnchor).isActive = true
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

extension ThirdScreen{
    
    func pageViewController(_ pageViewController: UIPageViewController, viewControllerBefore viewController: UIViewController) -> UIViewController? {
        
        print("left")
        
        //try to get the index of the view controller being accessed
        if let viewControllerIndex = self.pages.index(of: viewController){
            //if the view controller is the first...then wrap around to the end
            if viewControllerIndex == 0{
                self.navigationItem.title = "Page \(pages.count)"
                //return last view controller
                return self.pages.last
            }
                //if the view controller is not the first, then just return the previous view controller
            else{
                self.navigationItem.title = "Page \(viewControllerIndex)"
                return self.pages[viewControllerIndex - 1]
            }
        }
        
        print("Error in Page Controller")
        //getting the index did not work
        return nil
    }
    
    func pageViewController(_ pageViewController: UIPageViewController, viewControllerAfter viewController: UIViewController) -> UIViewController? {
        
        print("right")
        
        //Try to get the index of the view controller
        if let viewControllerIndex = self.pages.index(of: viewController){
            //if the view controller is the last, then return the first
            if viewController == self.pages.last{
                self.navigationItem.title = "Page \(1)"
                return self.pages[0]
            }
            else{
                self.navigationItem.title = "Page \(viewControllerIndex + 2)"
                return self.pages[viewControllerIndex + 1]
            }
        }
        return nil
    }
    
    func pageViewController(_ pageViewController: UIPageViewController, didFinishAnimating finished: Bool, previousViewControllers: [UIViewController], transitionCompleted completed: Bool){
        
        //get the array of view controllers
        if let viewControllers = pageViewController.viewControllers{
            //get the index of the first one
            if let viewControllerIndex = self.pages.index(of: viewControllers[0]){
                //set as the current page
                self.pageControl.currentPage = viewControllerIndex
            }
        }
    }
    
    /*func application(_ application: UIApplication, didFinishLaunchingWithOptions launchOptions: [UIApplication.LaunchOptionsKey: Any]?) -> Bool {
        
        self.window = UIWindow(frame: UIScreen.main.bounds)
        if let window = self.window
    }*/
}
