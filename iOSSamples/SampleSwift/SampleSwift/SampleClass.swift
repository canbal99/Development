//
//  SampleClass.swift
//  SampleSwift
//
//  Created by Can Canbolat on 04.09.17.
//  Copyright © 2017 Can Canbolat. All rights reserved.
//

import Foundation

protocol SampleProtocol {
    var firstName : String { get set }
    var lastName : String { get }
    func writeFullName() -> String
}

class SampleClass : NSObject, SampleProtocol {
    
    public var signature : String {
        return "This is signature!!!"
    }
    
    private var lastNameStorage : String
    private(set) public var lastName : String {
        get {
            return lastNameStorage
        }
        set(newValue) {
            lastNameStorage = newValue
        }
        
    }
    
    private var firstNameStorage : String
    public var firstName: String {
        get {
            return String.init(format: "Getter(%@)", firstNameStorage)
        }
        set(newValue) {
            firstNameStorage = String.init(format: "Setter(%@)", newValue)
        }
    }
    
    init(fName: String, lName: String) {
        firstNameStorage = fName
        lastNameStorage = lName
    }
    
    enum SandwichError : Error {
        case invalidSelection
        case outOfStock
    }
    
    func makeASandwichThrows() throws {
        throw SandwichError.invalidSelection
    }
    
    
    func makeASandwichNoThrows() {
        do {
            try makeASandwichThrows()
        } catch SandwichError.invalidSelection {
            
        } catch {
            
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
