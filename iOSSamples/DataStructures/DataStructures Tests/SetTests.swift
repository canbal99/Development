//
//  SetTests.swift
//  DataStructures
//
//  Created by Ellen Shapiro on 8/3/14.
//  Copyright (c) 2014 Ray Wenderlich Tutorial Team. All rights reserved.
//

import UIKit
import XCTest

class SetTests: PerformanceTestingCase {
    
    let count = 5000
    
    //MARK: Creation

    fileprivate func createSet(_ manipulator: SetManipulator) {
        self.measure { () -> Void in
            let time = manipulator.setupWithObjectCount(self.count)
            self.times.append(time)
        }
    }
    
//    func testCreatingNSSet() {
//        performFunctionInBackgroundThenLog("NSSet Create") {
//            self.createSet(NSSetManipulator())
//        }
//    }
//    
//    func testCreatingSwiftSet() {
//        performFunctionInBackgroundThenLog("Swift Set Create") {
//            self.createSet(SwiftSetManipulator())
//        }
//    }
    
    //MARK: Add one 
    
    func addOneObject(_ manipulator: SetManipulator) {
        manipulator.setupWithObjectCount(count)
        self.measure() {
            let time = manipulator.add1Object()
            self.times.append(time)
        }
    }
    
    func testAdding1ObjectToNSSet() {
        performFunctionInBackgroundThenLog("NSSet add one object") {
            self.addOneObject(NSSetManipulator())
        }
    }
    
    func testAdding1ObjectToSwiftSet() {
        performFunctionInBackgroundThenLog("Swift Set add one object") {
            self.addOneObject(SwiftSetManipulator())
        }
    }
    
    //MARK: Add 5
    
    func addFiveObjects(_ manipulator: SetManipulator) {
        manipulator.setupWithObjectCount(count)
        self.measure() {
            let time = manipulator.add5Objects()
            self.times.append(time)
        }
    }
    
    func testAdding5ObjectsToNSSet() {
        performFunctionInBackgroundThenLog("NSSet add five objects") {
            self.addFiveObjects(NSSetManipulator())
        }
    }
    
    func testAdding5ObjectsToSwiftSet() {
        performFunctionInBackgroundThenLog("Swift Set add five objects") {
            self.addFiveObjects(SwiftSetManipulator())
        }
    }
    
    //MARK: Add 10
    
    func addTenObjects(_ manipulator: SetManipulator) {
        self.measure() {
            let time = manipulator.add10Objects()
            self.times.append(time)
        }
    }
    
    func testAdding10ObjectsToNSSet() {
        performFunctionInBackgroundThenLog("NSSet add ten objects") {
            self.addTenObjects(NSSetManipulator())
        }
    }
    
    func testAdding10ObjectsToSwiftSet() {
        performFunctionInBackgroundThenLog("Swift Set add ten objects") {
            self.addTenObjects(SwiftSetManipulator())
        }
    }
    
    //MARK: Remove One
    
    func removeOneObject(_ manipulator: SetManipulator) {
        self.measure() {
            let time = manipulator.remove1Object()
            self.times.append(time)
        }
    }
    
    func testRemoving1ObjectFromNSSet() {
        performFunctionInBackgroundThenLog("NSSet remove one object") {
            self.removeOneObject(NSSetManipulator())
        }
    }
    
    func testRemoving1ObjectFromSwiftSet() {
        performFunctionInBackgroundThenLog("Swift Set remove one object") {
            self.removeOneObject(SwiftSetManipulator())
        }
    }
    
    //MARK: Remove 5
    
    func remove5Objects(_ manipulator: SetManipulator) {
        self.measure() {
            let time = manipulator.remove5Objects()
            self.times.append(time)
        }
    }
    
    func testRemoving5ObjectsFromNSSet() {
        performFunctionInBackgroundThenLog("NSSet remove five objects") {
            self.remove5Objects(NSSetManipulator())
        }
    }
    
    func testRemoving5ObjectsFromSwiftSet() {
        performFunctionInBackgroundThenLog("Swift Set remove five objects") {
            self.remove5Objects(SwiftSetManipulator())
        }
    }
    
    //MARK: Remove 10
    
    func remove10Objects(_ manipulator: SetManipulator) {
        self.measure() {
            let time = manipulator.remove10Objects()
            self.times.append(time)
        }
    }
    
    func testRemoving10ObjectsFromNSSet() {
        performFunctionInBackgroundThenLog("NSSet remove ten objects") {
            self.remove10Objects(NSSetManipulator())
        }
    }
    
    func testRemoving10ObjectsFromSwiftSSet() {
        performFunctionInBackgroundThenLog("Swift Set remove ten objects") {
            self.remove10Objects(SwiftSetManipulator())
        }
    }
    
    //MARK: Lookup 1
    
    func lookup1Object(_ manipulator: SetManipulator) {
        self.measure() {
            let time = manipulator.lookup1Object()
            self.times.append(time)
        }

    }
    
    func testLookup1ObjectInNSSet() {
        performFunctionInBackgroundThenLog("NSSet lookup one object") {
            self.lookup1Object(NSSetManipulator())
        }
    }
    
    func testLookup1ObjectInSwiftSet() {
        performFunctionInBackgroundThenLog("Swift set lookup one object") {
            self.lookup1Object(SwiftSetManipulator())
        }
    }
    
    //MARK: Lookup 10
    
    func lookup10Objects(_ manipulator: SetManipulator) {
        self.measure() {
            let time = manipulator.lookup10Objects()
            self.times.append(time)
        }
    }
    
    func testLookup10ObjectsInNSSet() {
        performFunctionInBackgroundThenLog("NSSet lookup 10 objects") {
            self.lookup10Objects(NSSetManipulator())
        }
    }
    
    func testLookup10ObjectsInSwiftSet() {
        performFunctionInBackgroundThenLog("Swift Set lookup 10 objects") {
            self.lookup10Objects(SwiftSetManipulator())
        }
    }
}
