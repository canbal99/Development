//
//  ViewController.swift
//  SampleSwift
//
//  Created by Can Canbolat on 01.09.17.
//  Copyright © 2017 Can Canbolat. All rights reserved.
//

import UIKit

// https://developer.apple.com/library/content/documentation/Swift/Conceptual/Swift_Programming_Language/Functions.html

class Foo: NSObject {
    @objc dynamic var bar = 0
    
    override func observeValue(forKeyPath keyPath: String?, of object: Any?, change: [NSKeyValueChangeKey : Any]?, context: UnsafeMutableRawPointer?) {
        if keyPath == #keyPath(Foo.bar) {
            if let myObject = object as? Foo {
                print("bar property is now \(myObject.bar)")
            }
        }
    }
}

class SomeClass: NSObject {
    @objc dynamic var someProperty: Int
    init(someProperty: Int = 10) {
        self.someProperty = someProperty
    }
}

class ViewController: UIViewController {
    
    @IBOutlet weak var labelText: UILabel!
    @IBOutlet weak var textField: UITextField!
    @IBOutlet weak var buttonOK: UIButton!
    @IBOutlet weak var imageView: UIImageView!
    
    private var myObject : SampleClass = SampleClass(fName: "Can", lName: "Canbolat")
    private var myObjCObject : SampleClassObjC = SampleClassObjC()
    
    override func viewDidLoad() {
        super.viewDidLoad()
        // Do any additional setup after loading the view, typically from a nib.
    }

    override func didReceiveMemoryWarning() {
        super.didReceiveMemoryWarning()
        // Dispose of any resources that can be recreated.
    }
    
    override func viewWillAppear(_ animated: Bool) {
        super.viewWillAppear(animated)
        self.imageView.image = UIImage.init(named: "/Users/can/Desktop/TEST/debug000.png")
    }
    
    private var token: NSKeyValueObservation!
    var objectToObserve = Foo()
    var objectToObserve2 = SomeClass()
    
    @objc func onButtonClicked2(_ sender: Any) {
        print("TESTTEST!!!")
    }
    
    let llama = SomeClass()
    private var llamatoken: NSKeyValueObservation!
    @IBAction func onButtonClicked(_ sender: Any) {
        self.labelText.text = self.textField.text
        
        autoreleasepool {
            /* code */
        }
        
        
        let array: NSArray = ["delta", "alpha", "zulu"]
        // Not a compile-time error because NSDictionary has this selector.
        let selector1 = #selector(NSDictionary.allKeys(for:))
        // Raises an exception because NSArray does not respond to this selector.
        //array.perform(selector1)
        
        
        
        
        
        let string: NSString = "Hello, Cocoa!"
        let selector2 = #selector(NSString.lowercased(with:))
        let locale = Locale.current
        if let result = string.perform(selector2, with: locale) {
            print(result.takeUnretainedValue())
        }
        
        
        
        let action = #selector(ViewController.onButtonClicked2)
        self.buttonOK.addTarget(self, action: action, for: .touchUpInside)
        
        print("myObjCObject \(myObjCObject.writeFullName("name: "))");
        
        
        
        
        do {
        //let initializer: (Int) -> String = String.init
        let initializer: (Int) -> String = String.self.init
        let oneTwoThree = [1, 2, 3].map(initializer).reduce("start:", +)
        print(oneTwoThree)
        }
        
        
        
        
        // Key Value observing
        token = objectToObserve2.observe(\.someProperty) { [weak self] object, change in  // the `[weak self]` is to avoid strong reference cycle; obviously, if you don't reference `self` in the closure, then `[weak self]` is not needed
            print("someProperty property is now \(object.someProperty)")
        }
        objectToObserve.addObserver(objectToObserve, forKeyPath: #keyPath(Foo.bar), options: [.old, .new, .initial], context: nil)
        
        DispatchQueue.main.asyncAfter(deadline: .now() + 1.0, execute: { [weak self] in
            self?.objectToObserve.bar = 15
            self?.objectToObserve2.someProperty = 20
        })
        
        let selectorForPropertyGetter = #selector(getter: SomeClass.someProperty)
        print("selectorForPropertyGetter: \(selectorForPropertyGetter)");
        
        let keyPath = #keyPath(SomeClass.someProperty)
        print("somePropertyValue: \(objectToObserve2.value(forKey: keyPath)!)");

        
        var nummer : Double
        nummer = 9999
        nummer = 0b1111
        nummer = 0o7777
        nummer = 0xFFFF
        nummer = 1.25e-2 // 0.0125
        
        var asdCan : Any = "String"
        var asdCan2 : String = asdCan as! String
        func f1(_ any: Any) { print("Function for Any") }
        func f2(_ int: Int) { print("Function for Int") }
        let xxx = 10
        f2(xxx)
        // Prints "Function for Int"
        let yyy: Any = xxx
        f2((yyy as? Int)!)
        f2(yyy as! Int)
        // Prints "Function for Any"
        f1(xxx as Any)
        // Prints "Function for Any"
        
        var myFunction1 = { (x: Int, y: Int) -> Int in return x + y }
        var myFunction2 : (Int, Int) -> Int = { x, y in return x + y }
        var myFunction3 : (Int, Int) -> Int = { return $0 + $1 }
        var myFunction4 : (Int, Int) -> Int = { $0 + $1 }
        
        //var mySampleClassMetaType : SampleClass.Type = SampleClass.self
        //var mySampleClassInstance : SampleClass = mySampleClassMetaType.init(fName: "Can", lName: "Canbolat")
        //mySampleClassInstance = mySampleClassMetaType.self.init(fName: "Can", lName: "Canbolat")
        
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
        //let somePoint = (1, 1)
        let somePoint = (Int(arc4random()%2), Int(arc4random()%2))
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
        
        //let anotherPoint = (2, 0)
        let anotherPoint = (Int(arc4random()%2), Int(arc4random()%2))
        switch anotherPoint {
        case (let x, 0):
            print("on the x-axis with an x value of \(x)")
        case (0, let y):
            print("on the y-axis with a y value of \(y)")
        case let (x, y):
            print("somewhere else at (\(x), \(y))")
        }
        
        //let yetAnotherPoint = (1, -1)
        let yetAnotherPoint = (Int(arc4random()%2), Int(arc4random()%2))
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
        
        let digitNames = [ 0: "Zero", 1: "One", 2: "Two",   3: "Three", 4: "Four", 5: "Five", 6: "Six", 7: "Seven", 8: "Eight", 9: "Nine"]
        let numbers = [16, 58, 510]
        let strings = numbers.map { (number) -> String in
            var number = number
            var output = ""
            repeat {
                output = digitNames[number % 10]! + output
                number /= 10
            } while number > 0
            return output
        }
        print(strings)
        
        // ERROR HANDLING
        func someThrowingFunction() throws -> Int {
            return 0
        }
        
        var x = try? someThrowingFunction()
        let y: Int?
        do {
            y = try someThrowingFunction()
        } catch {
            y = nil
        }
        if x != nil {
            x = y
        }
        // disables error probogation and will give a runtime error if there is a problem
        x = try! someThrowingFunction()
        
        func exists(_ filename: String) -> Bool {return true}
        func open(_ filename: String) -> Int {return 0}
        func close(_ number: Int) {}
        func processFile(filename: String) throws {
            if exists(filename) {
                let file = open(filename)
                defer {
                    close(file)
                }
                //while let line = try file.readline() {
                    // Work with the file.
                //}
                // close(file) is called here, at the end of the CURRENT SCOPE (in case of return break throw).
            }
        }
        
        // TYPE CASTING (is / as? / as!)
        let library = [
            Movie(name: "Casablanca", director: "Michael Curtiz"),
            Song(name: "Blue Suede Shoes", artist: "Elvis Presley"),
            Movie(name: "Citizen Kane", director: "Orson Welles"),
            Song(name: "The One And Only", artist: "Chesney Hawkes"),
            Song(name: "Never Gonna Give You Up", artist: "Rick Astley")
        ]
        var movieCount = 0
        var songCount = 0
        for item in library {
            if item is Movie {
                movieCount += 1
            } else if item is Song {
                songCount += 1
            }
        }
        for item in library {
            if let movie = item as? Movie {
                print("Movie: \(movie.name), dir. \(movie.director)")
            } else if let song = item as? Song {
                print("Song: \(song.name), by \(song.artist)")
            }
        }
        
        // Any for anything, AnyObject for class instances
        var things = [Any]()
        things.append(0)
        things.append(0.0)
        things.append(42)
        things.append(3.14159)
        things.append("hello")
        things.append((3.0, 5.0))
        things.append(Movie(name: "Ghostbusters", director: "Ivan Reitman"))
        things.append({ (name: String) -> String in "Hello, \(name)" })
        for thing in things {
            switch thing {
            case 0 as Int:
                print("zero as an Int")
            case 0 as Double:
                print("zero as a Double")
            case let someInt as Int:
                print("an integer value of \(someInt)")
            case let someDouble as Double where someDouble > 0:
                print("a positive double value of \(someDouble)")
            case is Double:
                print("some other double value that I don't want to print")
            case let someString as String:
                print("a string value of \"\(someString)\"")
            case let (x, y) as (Double, Double):
                print("an (x, y) point at \(x), \(y)")
            case let movie as Movie:
                print("a movie called \(movie.name), dir. \(movie.director)")
            case let stringConverter as (String) -> String:
                print(stringConverter("Michael"))
            default:
                print("something else")
            }
        }
    }
    
    class MediaItem {
        var name: String
        init(name: String) {
            self.name = name
        }
    }
    
    class Movie: MediaItem {
        var director: String
        init(name: String, director: String) {
            self.director = director
            super.init(name: name)
        }
    }
    
    class Song: MediaItem {
        var artist: String
        init(name: String, artist: String) {
            self.artist = artist
            super.init(name: name)
        }
    }
    
    func addThree(keys: inout [String], values: inout [Int]) {
        keys.append("Three")
        values.append(3)
    }
    
    func minMax(array: [Int], count: Int = 10) -> (min: Int, max: Int)? {
        if array.isEmpty { return nil }
        var currentMin = array[0]
        var currentMax = array[0]
        for value in array[1..<array.count] {
            if value < currentMin {
                currentMin = value
            } else if value > currentMax {
                currentMax = value
            }
        }
        return (currentMin, currentMax)
    }
    
    // Variadic Parameters
    func arithmeticMean(_ numbers: Double...) -> Double {
        //numbers is a Double array => [Double]
        var total: Double = 0
        for number in numbers {
            total += number
        }
        return total / Double(numbers.count)
    }
    
    func callAddTwoInts(mathFunc: (Int,Int)->Int, a:Int, b:Int ) -> Int {
        return mathFunc(a,b)
    }
    
    static func addTwoInts(_ a: Int, _ b: Int) -> Int {
        return a + b
    }
    
    var mathFunction : (Int, Int) -> Int = addTwoInts
    
    func chooseStepFunction(backward: Bool) -> (Int) -> Int {
        func stepForward(input: Int) -> Int { return input + 1 }
        func stepBackward(input: Int) -> Int { return input - 1 }
        return backward ? stepBackward : stepForward
    }
    
    func sortStringArrayInDescendingOrder(array: [String], useClosure: Bool) -> [String] {
        if useClosure {
            return array.sorted(by: { (left:String, right:String) -> Bool in
                return left > right
            })
            //return array.sorted(by: { left, right in return left > right }) // omit (String, String) -> Bool
            //return array.sorted(by: { left, right in left > right }) // omit return
            //return array.sorted(by: { $0 > $1 }) // omit param name definition and use $
            //return array.sorted(by: > ) // only return operator (this is not a new closure, there is no {})
            //return array.sorted() { $0 > $1 } // Trailing closure
        } else {
            func descendingOrderComparison(left:String, right:String) -> Bool {return left > right}
            return array.sorted(by: descendingOrderComparison)
        }
    }
    
    // ESCAPING it is used to call closure after function is called (like completion handlers)
    var completionHandlers: [() -> Void] = []
    func someFunctionWithEscapingClosure(completionHandler: @escaping () -> Void) {
        completionHandlers.append(completionHandler)
    }
    
    // AUTOCLOSURES
    //serve1(customer: { customersInLine.remove(at: 0) } )
    func serve1(customer customerProvider: () -> String) {
        print("Now serving \(customerProvider())!")
    }
    //serve2(customer: customersInLine.remove(at: 0))
    func serve2(customer customerProvider: @autoclosure () -> String) {
        print("Now serving \(customerProvider())!")
    }
    
    // all raw values are assigned as incrementing first value
    enum Planet: Int {
        case mercury = 1, venus, earth, mars, jupiter, saturn, uranus, neptune
    }
    
    // all raw values are setas same string value like "north"
    enum CompassPoint: String {
        case north, south, east, west
    }
}

