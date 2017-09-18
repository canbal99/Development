//: Playground - noun: a place where people can play

import UIKit
import Foundation


var str = "Hello, playground"

enum RideType {
    case Family
    case Kids
    case Thrill
    case Scary
    case Relaxing
    case Water
}

struct Ride {
    let name: String
    let types: Set<RideType>
    let waitTime: Double
}

let parkRides = [
    Ride(name: "Raging Rapids", types: [.Family, .Thrill, .Water], waitTime: 45.0),
    Ride(name: "Crazy Funhouse", types: [.Family], waitTime: 10.0),
    Ride(name: "Spinning Tea Cups", types: [.Kids], waitTime: 15.0),
    Ride(name: "Spooky Hollow", types: [.Scary], waitTime: 30.0),
    Ride(name: "Thunder Coaster", types: [.Family, .Thrill], waitTime: 60.0),
    Ride(name: "Grand Carousel", types: [.Family, .Kids], waitTime: 15.0),
    Ride(name: "Bumper Boats", types: [.Family, .Water], waitTime: 25.0),
    Ride(name: "Mountain Railroad", types: [.Family, .Relaxing], waitTime: 0.0)
]

//parkRides[0] = Ride(name: "Functional Programming", types: [.Thrill], waitTime: 5.0)

func sortedNames(rides: [Ride]) -> [String] {
    var sortedRides = rides
    
    // 1
    //for (i = 0; i < sortedRides.count; i++) {
        //key = sortedRides[i]
    for (i, key) in sortedRides.enumerated() {
        
        // 2
        //for (j = i; j > -1; j--) {
        for j in stride(from: i, to: -1, by: -1) {
            if key.name.localizedCompare(sortedRides[j].name) == .orderedAscending {
                sortedRides.remove(at: j + 1)
                sortedRides.insert(key, at: j)
                }
            }
        }
    
    // 3
    var sortedNames = [String]()
    for ride in sortedRides {
        sortedNames.append(ride.name)
    }
    
    print(sortedRides)
    
    return sortedNames
}

print(sortedNames(rides: parkRides))


var originalNames = [String]()
for ride in parkRides {
    originalNames.append(ride.name)
}

print(originalNames)

class A : NSCopying {
    var a: Int = 0
    init(_ value : Int = 0) {
        a = value
    }
    
    func copy(with zone: NSZone? = nil) -> Any {
        return A(self.a)
    }
}

struct B {
    var b : Int = 1
    init(_ value : Int = 1) {
        b = value
    }
}

struct C {
    var a : A = A()
    var b : B = B()
}

var obj1 : C = C()
obj1.a.a = 10
obj1.b.b = 11
print("obj1 a:\(obj1.a.a)  b:\(obj1.b.b)")

var obj2 = obj1
obj1.a.a = 98
obj1.b.b = 99
print("obj1 a:\(obj1.a.a)  b:\(obj1.b.b)")
print("obj2 a:\(obj2.a.a)  b:\(obj2.b.b)")

var arr = [1,3,12,4,23,12,4,23,4,21,3,4,457,123,68,2]
print(arr)
let compFunc : (Int, Int) -> Bool = { left,right in
    return left%2 == right%2 ? left < right : left%2 < right%2
}
arr = arr.sorted(by: compFunc)
print(arr)

// A family that has very young kids wants to go on as many rides as possible between frequent bathroom breaks, so they need to find which kid-friendly rides have the shortest lines. Help them out by finding all family rides with wait times less than 20 minutes and sort them by wait time (ascending).


print(parkRides.filter(){$0.types.contains(.Family) && $0.waitTime<20}.sorted(){$0.waitTime<$1.waitTime}.map(){String("name:'\($0.name)' time:\($0.waitTime)")})

do {
let ob1 = A(1)
let ob2 = A(2)
let ob3 = A(3)
let arr1 = [ob1, ob2, ob3]
print(arr1.map{$0.a})
ob1.a = 11
ob2.a = 12
print(arr1.map{$0.a})
}

do {
var ob1 = B(1)
var ob2 = B(2)
let ob3 = B(3)
let arr1 = [ob1, ob2, ob3]
print(arr1.map{$0.b})
ob1.b = 11
ob2.b = 12
print(arr1.map{$0.b})
}

func createRideTypeFilter(_ type: RideType) -> ([Ride]) -> [Ride] {
    return { (rides : [Ride]) -> [Ride] in
        rides.filter { $0.types.contains(type) }
    }
}

let kidRideFilter = createRideTypeFilter(.Kids)
print(kidRideFilter(parkRides).map {$0.name})

var can : Double

func printCan(rides: [String]) {
    print(rides)
}

precedencegroup PipelinePrecedence {
    associativity: left
    higherThan: AdditionPrecedence
}
infix operator |> : PipelinePrecedence
func |> <T, U>(value: T, function: (T) -> U ) -> U {
    return function(value)
}

parkRides.map{$0.name} |> printCan

var queue : DispatchQueue = DispatchQueue.init(label: "can", qos: DispatchQoS.userInteractive, attributes: DispatchQueue.Attributes.concurrent, autoreleaseFrequency: DispatchQueue.AutoreleaseFrequency.inherit, target: nil)
for i in stride(from: 1, to: 100, by: 1) {
    DispatchQueue.global().async() {
        if (i%10 != 0) {
            queue.async() {
                print("START \(i)")
                //usleep(300)
                print("END \(i)")
            }
        } else {
            queue.sync(flags: DispatchWorkItemFlags.barrier) {
                print("START BARRIER \(i)")
                //sleep(1)
                print("END BARRIER \(i)")
            }
        }
    }
}


