//
//  XCTestExtension.swift
//  DataStructures
//
//  Created by Ellen Shapiro on 8/4/14.
//  Copyright (c) 2014 Ray Wenderlich Tutorial Team. All rights reserved.
//

import Foundation
import XCTest

class PerformanceTestingCase : XCTestCase {
    var times = [TimeInterval]()
    
    /*
        This function takes all the recorded times and averages them. 
        This is necessary because the performance test will log not just
        the time for performing an operation, but for all the associated
        setup and teardown work.
     */
    func logAverageTime(_ times: [TimeInterval], operationName: String) {
        var totalTime: TimeInterval = 0
        for time in times {
            totalTime += time
        }
        
        let average =  Double(totalTime) / times.count as Double
        
        print("\(operationName) average: \(average)")
    }
    
    
    /*
        This function simulates the performance of the iOS app by making
        sure the test runs on a background thread with identical priority. 
        It also uses XCTestExpectation to ensure the test case waits for the 
        appropriate length of time for the operation to complete.
     */
    func performFunctionInBackgroundThenLog(_ name: String, function : @escaping () -> ()) {
        let expectation = self.expectation(description: name)
        //Use the same queue priority as in the application
        DispatchQueue.global(priority: DispatchQueue.GlobalQueuePriority.high).async {
            function()
            DispatchQueue.main.async {
                //Now that we're done, fulfill the expectation.
                expectation.fulfill()
            }
        }
        
        //Set a comically long wait time, since some of these take a while, 
        //especially with optimization off. 
        waitForExpectations(timeout: 100000000.0 as TimeInterval, handler: {
            error in //The error block has an error param=
            //Log the average time.
            self.logAverageTime(self.times, operationName: name)
        })
    }
}
