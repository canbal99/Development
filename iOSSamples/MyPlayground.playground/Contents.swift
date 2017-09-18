//: Playground - noun: a place where people can play

import UIKit

var str = "Hello, playground"

var test: String = "My test string"
print(test[test.startIndex...test.index(test.startIndex, offsetBy:3)])

for ch in test.unicodeScalars {
    print("char \(ch) has a value of \(String.init(format: "%02x", ch.value))")
}

print("index of char t is \(test.index(of: "t")?.encodedOffset)")

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

