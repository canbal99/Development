//
//  SampleClassObjC.m
//  SampleSwift
//
//  Created by Can Canbolat on 08.09.17.
//  Copyright © 2017 Can Canbolat. All rights reserved.
//

#import "SampleClassObjC.h"

@interface SampleClassObjC ()

@end

@implementation SampleClassObjC

@synthesize firstName=_firstNameStorage, lastName=_lastNameStorage;

-(void)setLastName:(NSString*) newValue {
    _lastNameStorage = newValue;
}

-(NSString*) lastName {
    return _lastNameStorage;
}

-(void)setFirstName:(NSString*) newValue {
    _firstNameStorage = [NSString stringWithFormat:@"Setter(%@)", newValue];
}

-(NSString*) getFirstName {
    return [NSString stringWithFormat:@"Getter(%@)", _firstNameStorage];
}

- (id)init {
    if (self = [super init]) {
        self.firstName = @"Can";
        self.lastName = @"Canbolat";
        return self;
    }
    return nil;
}

- (NSString*) writeFullName: (NSString*) prefix {
    return [NSString stringWithFormat:@"%@ %@ %@", prefix, self.firstName, self.lastName];
}

@end
