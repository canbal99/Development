//
//  NSArrayManipulator.swift
//  DataStructures
//
//  Created by Ellen Shapiro on 8/3/14.
//  Copyright (c) 2014 Ray Wenderlich Tutorial Team. All rights reserved.
//

import Foundation

class NSArrayManipulator: ArrayManipulator {
  var numberArray = NSMutableArray()
  
  
  func arrayHasObjects() -> Bool {
    if (numberArray.count == 0) {
      return false
    } else {
      return true
    }
  }
  
  func setupWithObjectCount(_ count: Int) -> TimeInterval {
    return Profiler.runClosureForTime() {
      for i in 0 ..< count {
        self.numberArray.add(i)
      }
    }
  }
  
  fileprivate func nextElement() -> Int {
    return numberArray.count + 1
  }
  
  //MARK: Add/Insert
  
  func insertNewObjectAtBeginning() -> TimeInterval {
    let next = nextElement()
    
    let time = Profiler.runClosureForTime() {
      self.numberArray.insert(next, at: 0)
    }

    self.numberArray.remove(next)
    return time
  }
  
  func insertNewObjectInMiddle() -> TimeInterval {
    let next = nextElement()
    let half = Int(ceil(Float(numberArray.count) / Float(2)))
   
    let time = Profiler.runClosureForTime() {
      self.numberArray.insert(next, at: half)
    }
    
    self.numberArray.remove(next)
    
    return time
  }
  
  func addNewObjectAtEnd() -> TimeInterval {
    let next = nextElement()
    
    let time = Profiler.runClosureForTime() {
      self.numberArray.add(next)
    }
    
    self.numberArray.remove(next)
    
    return time
  }
  
  //MARK: Removal
  
  func removeFirstObject() -> TimeInterval {
    let first = numberArray[0] as! Int
    let time = Profiler.runClosureForTime() {
      self.numberArray.removeObject(at: 0)
    }
    
    self.numberArray.insert(first, at: 0)
    
    return time
  }
  
  func removeMiddleObject() -> TimeInterval {
    let half = Int(ceil(Float(numberArray.count) / Float(2)))
    let originalMiddle = numberArray[half] as! Int
    
    let time = Profiler.runClosureForTime() {
      self.numberArray.removeObject(at: half)
    }
  
    self.numberArray.insert(originalMiddle, at: half)

    return time
  }
  
  func removeLastObject() -> TimeInterval {
    let originalLast = numberArray.lastObject as! Int
    
    let time = Profiler.runClosureForTime() {
      self.numberArray.removeLastObject()
    }
    
    numberArray.add(originalLast)
    
    return time
  }
  
  //MARK: Lookup 
  
  func lookupByIndex() -> TimeInterval {
    let elements = UInt32(numberArray.count)
    let randomIndex = Int(arc4random_uniform(elements))

    let time = Profiler.runClosureForTime() {
      let _ = self.numberArray.object(at: randomIndex) as! Int
    }
    
    return time
  }
  
  func lookupByObject() -> TimeInterval {
    //Add a known object at a random index.
    let next = nextElement()
    let elements = UInt32(numberArray.count)
    let randomIndex = Int(arc4random_uniform(elements))
    numberArray.insert(next, at: randomIndex)
    
    let time = Profiler.runClosureForTime() {
      let _ = self.numberArray.index(of: next)
    }
    
    return time
  }
    
}
