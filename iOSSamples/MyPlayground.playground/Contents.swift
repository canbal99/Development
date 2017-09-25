//: Playground - noun: a place where people can play

import UIKit

var str = "Hello, playground"

var test: String = "My test string"
print(test[test.startIndex...test.index(test.startIndex, offsetBy:3)])

for ch in test.unicodeScalars {
    print("char \(ch) has a value of \(String.init(format: "%02x", ch.value))")
}

print("index of char t is \(String(describing: test.index(of: "t")?.encodedOffset))")

let flag = "🇵🇷"
print(flag.count)
// Prints "1"
print(flag.characters.count)
// Prints "1"
print(flag.unicodeScalars.count)
// Prints "2"
print(flag.utf16.count)
// Prints "4"
print(flag.utf8.count)
// Prints "8"

var arr = test.split(separator: " ")
print(arr)
print(type(of: arr))


// Swizzling
extension NSObject {
    
    class func swizzleMethods(origSelector: Selector, withSelector: Selector,
                              forClass: AnyClass) {
        
        if  let swizzledMethod = class_getInstanceMethod(forClass, withSelector) {
            if let originalMethod = class_getInstanceMethod(forClass, origSelector) {
                method_exchangeImplementations(originalMethod, swizzledMethod)
            }
        }
    }
    
    func swizzleMethods(origSelector: Selector, withSelector: Selector) {
        let aClass: AnyClass! = object_getClass(self)
        NSObject.swizzleMethods(origSelector: origSelector, withSelector: withSelector, forClass: aClass)
    }
}

// Use Swizzling
public extension UIColor {
    
    @objc func colorDescription() -> String {
        return "Some Custom text Here"
    }
    
    public class func swizzleDesription() {
        let instance: UIColor = UIColor.red
        instance.swizzleMethods(origSelector: #selector(colorDescription), withSelector: #selector(description))
    }
}

print("test1: \(UIColor.red)")
print("test2: \(UIColor.green)")
UIColor.swizzleDesription()
print("test3: \(UIColor.red)")
print("test4: \(UIColor.green)")



/*for i in str.indices {
    print(str[i])
}*/





