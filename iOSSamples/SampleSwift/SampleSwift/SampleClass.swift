//
//  SampleClass.swift
//  SampleSwift
//
//  Created by Can Canbolat on 04.09.17.
//  Copyright © 2017 Can Canbolat. All rights reserved.
//

import Foundation

typealias CanINT32 = Int32

struct Vector2D {
    var x = 0.0, y = 0.0
}

// left + right
extension Vector2D {
    static func + (left: Vector2D, right: Vector2D) -> Vector2D {
        return Vector2D(x: left.x + right.x, y: left.y + right.y)
    }
}

// -vector
extension Vector2D {
    static prefix func - (vector: Vector2D) -> Vector2D {
        return Vector2D(x: -vector.x, y: -vector.y)
    }
}

// left += right
extension Vector2D {
    static func += (left: inout Vector2D, right: Vector2D) {
        left = left + right
    }
}

// left == right OR left != right
extension Vector2D {
    static func == (left: Vector2D, right: Vector2D) -> Bool {
        return (left.x == right.x) && (left.y == right.y)
    }
    static func != (left: Vector2D, right: Vector2D) -> Bool {
        return !(left == right)
    }
}

// +++vector
prefix operator +++
extension Vector2D {
    static prefix func +++ (vector: inout Vector2D) -> Vector2D {
        vector += vector
        return vector
    }
}

// left +- right
infix operator +- : AdditionPrecedence
extension Vector2D {
    static func +- (left: Vector2D, right: Vector2D) -> Vector2D {
        return Vector2D(x: left.x + right.x, y: left.y - right.y)
    }
}

protocol Container {
    associatedtype Item
    mutating func append(_ item: Item)
    var count: Int { get }
    subscript(i: Int) -> Item { get }
}

func allItemsMatch<C1: Container, C2: Container>
    (_ someContainer: C1, _ anotherContainer: C2) -> Bool
    where C1.Item == C2.Item, C1.Item: Equatable {
        
        // Check that both containers contain the same number of items.
        if someContainer.count != anotherContainer.count {
            return false
        }
        
        // Check each pair of items to see if they're equivalent.
        for i in 0..<someContainer.count {
            if someContainer[i] != anotherContainer[i] {
                return false
            }
        }
        
        // All items match, so return true.
        return true
}

struct Stack<Element> : Container {
    var items = [Element]()
    mutating func push(_ item: Element) {
        items.append(item)
    }
    mutating func pop() -> Element {
        return items.removeLast()
    }
    // Container protocol
    mutating func append(_ item: Element) {
        self.push(item)
    }
    var count: Int {
        return items.count
    }
    subscript(i: Int) -> Element {
        return items[i]
    }
}

extension Stack {
    var topItem: Element? {
        return items.isEmpty ? nil : items[items.count - 1]
    }
}

extension Stack where Element: SampleProtocol {
    var textualDescription: String {
        let itemsAsText = items.map { $0.writeFullName() }
        return "[" + itemsAsText.joined(separator: ", ") + "]"
    }
}

extension Stack where Element: Equatable {
    func isTop(_ item: Element) -> Bool {
        guard let topItem = items.last else {
            return false
        }
        return topItem == item
    }
}

func findIndex<T: Equatable>(of valueToFind: T, in array:[T]) -> Int? {
    for (index, value) in array.enumerated() {
        if value == valueToFind {
            return index
        }
    }
    return nil
}

protocol A {
    var A: Int { get set }
}

class B {
    var B: Int = 0
}

class C : B, A {
    var A: Int = 0
    var C: Int = 0
}

protocol SampleProtocol {
    var firstName : String { get set }
    var lastName : String { get }
    func writeFullName() -> String
}

class SampleClass : NSObject, SampleProtocol {
    
    subscript(index1: Int, index2: Int) -> String {
        get {
            if index1 + index2 ==  0 {
                return firstName
            } else {
                return lastName
            }
        }
        set {
            if index1 + index2 ==  0 {
                firstName = newValue
            } else {
                lastName = newValue
            }
        }
    }
    
    var signature : String {
        //get { //dont need get keyword, this is readonly property
        return "This is signature!!!"
        //}
    }
    
    lazy var lazySignature : String = "This is lazy signature!!! This variable will not be initialized until first usage. NOT THREAD SAFE"
    
    private var lastNameStorage : String
    private(set) public var lastName : String {
        get {
            return lastNameStorage
        }
        set/*(newValue)*/ {
            lastNameStorage = newValue
        }
    }
    
    private var firstNameStorage : String
    public var firstName: String {
        get {
            print("size of string firstName(\(firstNameStorage)) is \(firstNameStorage.count)")
            return String.init(format: "Getter(%@)", firstNameStorage)
        }
        set(newValue) {
            firstNameStorage = String.init(format: "Setter(%@)", newValue)
        }
        //willSet/*(newValue)*/ {
        //    print("lastName is going to be changed. newvalue: \(newValue)")
        //}
        //didSet/*(oldValue)*/ {
        //    print("lastName was changed. oldvalue: \(oldValue)")
        //}
    }
    
    init(fName: String, lName: String) {
        firstNameStorage = fName
        lastNameStorage = lName
    }
    
    enum SandwichError : Error {
        case invalidSelection
        case insufficientFunds(coinsNeeded: Int)
        case outOfStock
    }
    
    func makeASandwichThrows() throws {
        throw SandwichError.insufficientFunds(coinsNeeded: 5)
    }
    
    
    func makeASandwichNoThrows() {
        do {
            try makeASandwichThrows()
        } catch SandwichError.invalidSelection {
            print("invalidSelection error")
        } catch SandwichError.insufficientFunds(let coinsNeeded){
            print("insufficientFunds \(coinsNeeded)")
        } catch _ {
            
        }
    }
}

extension SampleClass {
    var fullName : String {
        return String(format: "%@ %@" , self.firstName, self.lastName)
    }
}

extension SampleClass {
    func writeFullName() -> String {
        let string = String(format:"Full Name function extension: %@", self.fullName)
        print(string)
        return string
    }
}
