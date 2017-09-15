//
//  ViewController.swift
//  RESTfulSample
//
//  Created by Can Canbolat on 15.09.17.
//  Copyright © 2017 Can Canbolat. All rights reserved.
//

import UIKit

class ViewController: UIViewController {

    @IBOutlet weak var idLabel: UILabel!
    @IBOutlet weak var contentLabel: UILabel!
    
    override func viewDidLoad() {
        super.viewDidLoad()
        // Do any additional setup after loading the view, typically from a nib.
    }

    override func didReceiveMemoryWarning() {
        super.didReceiveMemoryWarning()
        // Dispose of any resources that can be recreated.
    }
    
    @IBAction func onRefreshButtonPressed(_ sender: UIButton) {
        if let urlRest = URL.init(string: "http://rest-service.guides.spring.io/greeting") {
            var request = URLRequest.init(url: urlRest)
            request.addValue("testdata", forHTTPHeaderField: "MyHeader")
            let task: URLSessionDataTask = URLSession.shared.dataTask(with: request) { (data:Data?, response:URLResponse?, error:Error?) in
                if let err = error {
                    print("error occured: \(err.localizedDescription)")
                    return
                }
                if let respData = data {
                    print("data received: \(String.init(data: respData, encoding: String.Encoding.utf8)!)")
                    
                    let jsonWithObjectRoot = try? JSONSerialization.jsonObject(with: respData, options: [])
                    if let dictionary = jsonWithObjectRoot as? [String: Any] {
                        if let id = dictionary["id"] as? Int {
                            DispatchQueue.main.async {
                                self.idLabel.text = String(id)
                            }
                        }
                        if let content = dictionary["content"] as? String {
                            DispatchQueue.main.async {
                                self.contentLabel.text = content
                            }
                        }
                        
                        var newDictionart = dictionary
                        newDictionart["MyDict"] = ["One":1,"Two":2,"Three":3,"Four":4,"Five":5]
                        if let jsonData = try? JSONSerialization.data(withJSONObject: newDictionart, options: JSONSerialization.WritingOptions.init(rawValue: 0)) {
                            if let jsonString = String.init(data: jsonData, encoding: .utf8) {
                                print("data generated: \(jsonString)")
                            }
                        }
                    }
                }
            }
            task.resume()
        }
    }
    
}

