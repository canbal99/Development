//
//  DictionaryTests.swift
//  DataStructures
//
//  Created by Ellen Shapiro on 8/3/14.
//  Copyright (c) 2014 Ray Wenderlich Tutorial Team. All rights reserved.
//

import UIKit
import XCTest

class DictionaryTests: PerformanceTestingCase {
    let count = 1000
    
    func createDictionary(_ manipulator: DictionaryManipulator) {
        self.measure() {
            let time = manipulator.setupWithEntryCount(self.count)
            self.times.append(time)
        }
    }
    
    func testCreatingNSDictionary() {
        performFunctionInBackgroundThenLog("NSDictionary Create") {
            self.createDictionary(NSDictionaryManipulator())
        }
    }
    
    func testCreatingSwiftDictionary() {
        performFunctionInBackgroundThenLog("Swift Dictionary Create") {
            self.createDictionary(SwiftDictionaryManipulator())
        }
    }
    
    //MARK: Add one
    
    func addOneEntry(_ manipulator: DictionaryManipulator) {
        manipulator.setupWithEntryCount(count)
        self.measure() {
            let time = manipulator.add1Entry()
            self.times.append(time)
        }
    }
    
    func testAdding1NSDictionary() {
        performFunctionInBackgroundThenLog("NSDictionary add one entry") {
            self.addOneEntry(NSDictionaryManipulator())
        }
    }
    
    func testAdding1SwiftDictionary() {
        performFunctionInBackgroundThenLog("Swift dictionary add one entry") {
            self.addOneEntry(SwiftDictionaryManipulator())
        }
    }
    
    //MARK: Add 5

    func addFiveEntries(_ manipulator: DictionaryManipulator) {
        manipulator.setupWithEntryCount(count)
        measure() {
            let time = manipulator.add5Entries()
            self.times.append(time)
        }
    }
    
    func testAdding5NSDictionaries() {
        performFunctionInBackgroundThenLog("NSDictionary Add five entries") {
            self.addFiveEntries(NSDictionaryManipulator())
        }
    }
    
    func testAdding5SwiftDictionaries() {
        performFunctionInBackgroundThenLog("Swift Dictionary Add five entries") {
            self.addFiveEntries(SwiftDictionaryManipulator())
        }
    }
    
    //MARK: Add 10

    func addTenEntries(_ manipulator: DictionaryManipulator) {
        manipulator.setupWithEntryCount(count)
        measure() {
            let time = manipulator.add10Entries()
            self.times.append(time)
        }
    }
    
    func testAdding10NSDictionaries() {
        performFunctionInBackgroundThenLog("NSDictionary Add ten entries") {
            self.addTenEntries(NSDictionaryManipulator())
        }
    }
    
    func testAdding10SwiftDictionaries() {
        performFunctionInBackgroundThenLog("Swift Dictionary Add ten entries") {
            self.addTenEntries(SwiftDictionaryManipulator())
        }
    }

    //MARK: Remove 1
    
    func removeOneEntry(_ manipulator: DictionaryManipulator) {
        manipulator.setupWithEntryCount(count)
        measure() {
            let time = manipulator.remove1Entry()
            self.times.append(time)
        }
    }
    
    func testRemoving1NSDictionary() {
        performFunctionInBackgroundThenLog("NSDictionary remove one item") {
            self.removeOneEntry(NSDictionaryManipulator())
        }
    }
    
    func testRemoving1SwiftDictionary() {
        performFunctionInBackgroundThenLog("Swift Dictionary remove one item") {
            self.removeOneEntry(SwiftDictionaryManipulator())
        }
    }

    //MARK: Remove 5
    
    func removeFiveEntries(_ manipulator: DictionaryManipulator) {
        manipulator.setupWithEntryCount(count)
        self.measure() {
            let time = manipulator.remove5Entries()
            self.times.append(time)
        }
    }
    
    func testRemoving5NSDictionaries() {
        performFunctionInBackgroundThenLog("NSDictionary remove five items") {
            self.removeFiveEntries(NSDictionaryManipulator())
        }
    }
    
    func testRemoving5SwiftDictionaries() {
        performFunctionInBackgroundThenLog("Swift Dictionary remove five items") {
            self.removeFiveEntries(SwiftDictionaryManipulator())
        }
    }

    //MARK: Remove 10
    
    func removeTenEntries(_ manipulator: DictionaryManipulator) {
        manipulator.setupWithEntryCount(count)
        measure() {
            let time = manipulator.remove10Entries()
            self.times.append(time)
        }
    }
    
    func testRemoving10EntriesNSDictionary() {
        performFunctionInBackgroundThenLog("NSDictionary remove ten items") {
            self.removeTenEntries(NSDictionaryManipulator())
        }
    }
    
    func testRemoving10EntriesSwiftDictionary() {
        performFunctionInBackgroundThenLog("Swift Dictionary remove ten items") {
            self.removeTenEntries(SwiftDictionaryManipulator())
        }
    }

    // MARK: Lookup 1
    
    func lookupOneEntry(_ manipulator: DictionaryManipulator) {
        manipulator.setupWithEntryCount(count)
        measure() {
            let time = manipulator.lookup1EntryTime()
            self.times.append(time)
        }
    }
    
    func testLookup1EntryNSDictionary() {
        performFunctionInBackgroundThenLog("NSDictionary lookup one item") {
            self.lookupOneEntry(NSDictionaryManipulator())
        }
    }
    
    func testLookup1EntrySwiftDictionary() {
        performFunctionInBackgroundThenLog("Swift Dictionary lookup one item") {
            self.lookupOneEntry(SwiftDictionaryManipulator())
        }
    }

    // MARK: Lookup 10
    
    func lookupTenEntries(_ manipulator: DictionaryManipulator) {
        manipulator.setupWithEntryCount(count)
        measure() {
            let time = manipulator.lookup10EntriesTime()
            self.times.append(time)
        }
    }
    
    func testLookup10EntriesNSDictionary() {
        performFunctionInBackgroundThenLog("NSDictionary lookup 10 items") {
            self.lookupTenEntries(NSDictionaryManipulator())
        }
    }
    
    func testLookup10EntriesSwiftDictionary() {
        performFunctionInBackgroundThenLog("Swift Dictionary lookup 10 items") {
            self.lookupTenEntries(SwiftDictionaryManipulator())
        }
    }
}
