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
        
        var formatter: NumberFormatter = NumberFormatter.init()
        do {
            var number: Double? = try? (formatter.number(from: self.textField.text!) as! Double)
            number = Double(1.234)
            print("Number entered: %d", number)
        } catch {
            
        }
        
        /*
        NSLog(@"Number entered: %d", [number intValue]);
        
        self.myObject.firstName = @"Yusuf Can";
        //self.myObject.lastName = @"Canbolat";
        NSLog(@"Name: %@ %@", self.myObject.firstName, self.myObject.lastName);
        */
    }
    
}

