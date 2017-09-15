//
//  NSDictionaryManipulator.swift
//  DataStructures
//
//  Created by Ellen Shapiro on 8/3/14.
//  Copyright (c) 2014 Ray Wenderlich Tutorial Team. All rights reserved.
//

import Foundation

class NSDictionaryManipulator: DictionaryManipulator {
  var intDictionary = NSMutableDictionary()
  
  func dictHasEntries() -> Bool {
    if (intDictionary.count == 0) {
      return false
    } else {
      return true
    }
  }
  
  //MARK: Setup
  
  func setupWithEntryCount(_ count: Int) -> TimeInterval {
    return Profiler.runClosureForTime() {
      for i in 0 ..< count {
        self.intDictionary.setObject(i, forKey: i as NSCopying)
      }
    }
  }
  
  fileprivate func nextElement() -> Int {
    return self.intDictionary.count + 1
  }
  
  //MARK: Adding entries
  
  func addEntries(_ count: Int) -> TimeInterval {
    var dictionary = [Int: Int]()
    let next = nextElement()
    for i in 0 ..< count {
      let plusI = next + i
      dictionary[plusI] = plusI
    }
    
    let time = Profiler.runClosureForTime() {
      self.intDictionary.addEntries(from: dictionary)
    }
    
    //Restore to original state
    let keys = Array(dictionary.keys)
    self.intDictionary.removeObjects(forKeys: keys)
    
    return time
  }
  
  func add1Entry() -> TimeInterval {
    return addEntries(1)
  }
  
  func add5Entries() -> TimeInterval {
    return addEntries(5)
  }
      
  func add10Entries() -> TimeInterval {
    return addEntries(10)
  }
  
  //MARK: Removing entries
  
  func removeEntries(_ count: Int) -> TimeInterval {
    var dictionary = [Int: Int]()
    let next = nextElement()
    for i in 0 ..< count {
      let plusI = next + i
      dictionary[plusI] = plusI
    }
    
    self.intDictionary.addEntries(from: dictionary)
    
    //Restore to original state
    let keys = Array(dictionary.keys)
    
    
    return Profiler.runClosureForTime() {
      self.intDictionary.removeObjects(forKeys: keys)
    }
  }

  func remove1Entry() -> TimeInterval {
    return removeEntries(1)
  }
      
  func remove5Entries() -> TimeInterval {
    return removeEntries(5)
  }
      
  func remove10Entries() -> TimeInterval {
    return removeEntries(10)
  }
  
  //MARK: Looking up entries
  
  func lookupEntries(_ count: Int) -> TimeInterval {
    var dictionary = [Int: Int]()
    let next = nextElement()
    for i in 0 ..< count {
      let plusI = next + i
      dictionary[plusI] = plusI
    }
    
    self.intDictionary.addEntries(from: dictionary)
    
    let keys = Array(dictionary.keys)
    
    let time = Profiler.runClosureForTime() {
      for key in keys {
        self.intDictionary.object(forKey: key)
      }
    }
    
    //Restore to original state
    self.intDictionary.removeObjects(forKeys: keys)
    return time
  }
  
  func lookup1EntryTime() -> TimeInterval {
    return lookupEntries(1)
  }
      
  func lookup10EntriesTime() -> TimeInterval {
    return lookupEntries(10)
  }
}
