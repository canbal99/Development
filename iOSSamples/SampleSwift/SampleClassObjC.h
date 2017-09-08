//
//  SampleClassObjC.h
//  SampleSwift
//
//  Created by Can Canbolat on 08.09.17.
//  Copyright © 2017 Can Canbolat. All rights reserved.
//

#ifndef SampleClassObjC_h
#define SampleClassObjC_h

#import <Foundation/Foundation.h>

@interface SampleClassObjC : NSObject
{
@protected
    NSString* _firstNameStorage;
    NSString* _lastNameStorage;
}

@property (getter=getFirstName, setter=setFirstName:) NSString* firstName;
@property (readonly) NSString* lastName;

- (NSString*) writeFullName: (NSString*) prefix;

@end

#endif /* SampleClassObjC_h */
