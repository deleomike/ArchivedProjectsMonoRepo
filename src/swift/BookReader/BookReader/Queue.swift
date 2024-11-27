//
//  Queue.swift
//  BookReader
//
//  Created by Michael DeLeo on 12/28/18.
//  Copyright © 2018 Michael DeLeo. All rights reserved.
//

import Foundation

//Queue with any type data

struct Queue<T>{
    
    var items:[T] = [];
    var size = 0
    
    //Precondition: Any value of any type
    //Postcondition: nothing
    //Summary: Adds an element to the end of the array
    mutating func enqueue(_ a: T){
        items.append(a);
        size = size + 1;
    }
    
    //Precondition: Nothing
    //Postcondition: Nothing
    //Summary: Removes first element
    mutating func dequeue(){
        if (size == 0){
            print("Queue is already empty\n");
        }
        else{
            items.remove(at: 0);
            size = size - 1;
        }
        return;
    }
    
    //Precondition: Nothing
    //Postcondition: Last element of items
    //Summary: Returns last element of items
    func back() -> T{
        return items[size-1];
    }
}
