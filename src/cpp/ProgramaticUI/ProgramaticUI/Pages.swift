//
//  Pages.swift
//  ProgramaticUI
//
//  Created by Michael DeLeo on 1/12/19.
//  Copyright © 2019 Michael DeLeo. All rights reserved.
//

import Foundation

class Chapter{
    
    private var pages:[String]
    private let FileName: String
    
    init(pages: [String], name: String){
        self.pages = pages
        FileName = name
    }
    
    init(){
        pages = []
        FileName = "temp"
    }
    
    func size() -> Int{
        return pages.count;
    }
    
    func page(index: Int) -> String{
        return pages[index]
    }
    
    func appendPage(page: String){
        pages.append(page)
    }
    
    func changePage(page: String, index: Int){
        pages[index] = page
    }
    
    func name() -> String{
        return FileName
    }
}
