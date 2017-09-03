//
//  SampleClass.m
//  SampleApp
//
//  Created by Can Canbolat on 01.09.17.
//  Copyright © 2017 Can Canbolat. All rights reserved.
//

#import "SampleClass.h"

@interface SampleClass ()

@end

@implementation SampleClass

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

@end
