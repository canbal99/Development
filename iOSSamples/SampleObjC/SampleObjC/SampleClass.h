//
//  SampleClass.h
//  SampleApp
//
//  Created by Can Canbolat on 01.09.17.
//  Copyright © 2017 Can Canbolat. All rights reserved.
//

#import <Foundation/Foundation.h>

@interface SampleClass : NSObject
{
    @protected
    NSString* _firstNameStorage;
    NSString* _lastNameStorage;
}

@property (getter=getFirstName, setter=setFirstName:) NSString* firstName;
@property (readonly) NSString* lastName;

@end
