//
//  ViewController.swift
//  SampleSwift
//
//  Created by Can Canbolat on 01.09.17.
//  Copyright © 2017 Can Canbolat. All rights reserved.
//

import UIKit

class ViewController: UIViewController {
    
    @IBOutlet weak var labelText: UILabel!
    @IBOutlet weak var textField: UITextField!
    @IBOutlet weak var buttonOK: UIButton!
    
    private var myObject : SampleClass = SampleClass(fName: "Can", lName: "Canbolat")
    
    override func viewDidLoad() {
        super.viewDidLoad()
        // Do any additional setup after loading the view, typically from a nib.
    }

    override func didReceiveMemoryWarning() {
        super.didReceiveMemoryWarning()
        // Dispose of any resources that can be recreated.
    }

    @IBAction func onButtonClicked(_ sender: Any) {
        self.labelText.text = self.textField.text
        
        let number: Double? = Double(self.textField.text!)
        if let n = number {
            print("1. Number entered: ", n)
        }
        print("2. Number entered: \(number ?? 0)");
        
        self.myObject.firstName = "Yusuf Can";
        //self.myObject.lastName = "Canbolat";
        print("Name: ", self.myObject.firstName, "-",self.myObject.lastName);
        print("Full Name member extension: ", self.myObject.fullName);
        print(self.myObject.writeFullName())
        print("Signature: ", self.myObject.signature)
        
        let http404Error = (statusCode: 404, description: "Not Found")
        print("HTTP Error: \(http404Error.0) \(http404Error.description)")
        
        // FOR LOOPS
        for index in 1...5 {
            print("\(index) times 5 is \(index * 5)")
        }
        for index in 1..<5 {
            print("\(index) times 5 is \(index * 5)")
        }
        
        let minutes = 60
        let minuteInterval = 10
        for tickMark in stride(from: 0, to: minutes, by: minuteInterval) {
            // render the tick mark every 10 minutes (0, 10 ... 50)
            print("minutes => \(tickMark)")
        }
        for tickMark in stride(from: 0, through: minutes, by: minuteInterval) {
            // render the tick mark every 10 minutes (0, 10 ... 50, 60)
            print("minutes => \(tickMark)")
        }
        
        let names = ["Anna", "Alex", "Brian", "Jack"]
        // index from 2
        for name in names[2...] {
            print(name)
        }
        // index till 2
        for name in names[...2] {
            print(name)
        }
        // index till 1
        for name in names[..<2] {
            print(name)
        }
        
        // SWITCH
        let somePoint = (1, 1)
        switch somePoint {
        case (0, 0):
            print("\(somePoint) is at the origin")
        case (_, 0):
            print("\(somePoint) is on the x-axis")
        case (0, _):
            print("\(somePoint) is on the y-axis")
        case (-2...2, -2...2):
            print("\(somePoint) is inside the box")
        default:
            print("\(somePoint) is outside of the box")
        }
        
        let anotherPoint = (2, 0)
        switch anotherPoint {
        case (let x, 0):
            print("on the x-axis with an x value of \(x)")
        case (0, let y):
            print("on the y-axis with a y value of \(y)")
        case let (x, y):
            print("somewhere else at (\(x), \(y))")
        }
        
        let yetAnotherPoint = (1, -1)
        switch yetAnotherPoint {
        case let (x, y) where x == y:
            print("(\(x), \(y)) is on the line x == y")
        case let (x, y) where x == -y:
            print("(\(x), \(y)) is on the line x == -y")
        case let (x, y):
            print("(\(x), \(y)) is just some arbitrary point")
        }
        
        // STIRNGS
        let quotation : String = """
            The White Rabbit put on his spectacles.  "Where shall I begin,
            please your Majesty?" he asked.

            "Begin at the beginning," the King said gravely, "and go on
            till you come to the end; then stop."
            """
        print(quotation)
        let greeting = "Hello, world!"
        let index = greeting.index(of: ",") ?? greeting.endIndex
        let beginning = greeting[..<index]
        // beginning is "Hello" => substring share memory
        
        // Convert the result to a String for long-term storage.
        let newString = String(beginning)
        
        let st = greeting.index(greeting.startIndex, offsetBy: 2)
        let en = greeting.index(of: "o") ?? greeting.endIndex
        print("SUBSTRING:",greeting[st...en])
        
        let myString: String = "yusuf can canbolat"
        for item in myString.split(separator: " ") {
            print(item)
        }
        
        // ARRAY
        //var keys: [String] = ["One", "Two"]
        var keys: Array<String> = ["One", "Two"]
        var values: [Int] = [1, 2]
        for item in keys {
            print(item)
        }
        addThree(keys: &keys, values: &values);
        for item in keys {
            print(item)
        }
        
        // SET
        var favoriteGenres: Set<String> = ["Rock", "Classical", "Hip hop"]
        var favoriteGenres2: Set<String> = ["Pop", "Classical", "Electronic"]
        for item in favoriteGenres {
            print(item)
        }
        for item in favoriteGenres.sorted() {
            print(item)
        }
        print("SETS: ", favoriteGenres , favoriteGenres2)
        print("intersection: ", favoriteGenres.intersection(favoriteGenres2))
        print("union: ", favoriteGenres.union(favoriteGenres2))
        print("symmetricDifference: ", favoriteGenres.symmetricDifference(favoriteGenres2))
        // !!! subtract will change set but subtracting will not
        print("subtracting: ", favoriteGenres.subtracting(favoriteGenres2))
        print("isSubset: ", favoriteGenres.isSubset(of: favoriteGenres2))
        print("isSuperset: ", favoriteGenres.isSuperset(of: favoriteGenres2))
        print("isDisjoint: ", favoriteGenres.isDisjoint(with: favoriteGenres2))
        
        // DICTIONARY
        //var dictionary : [String: Int] = ["Four": 4 , "Five": 5]
        var dictionary : Dictionary<String, Int> = ["Four": 4 , "Five": 5]
        for (key,value) in dictionary {
            print("\(key) - \(value)")
        }
        
    }
    
    func addThree(keys: inout [String], values: inout [Int]) {
        keys.append("Three")
        values.append(3)
    }
    
}

