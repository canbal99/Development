//
//  SampleCFile.c
//  SampleSwift
//
//  Created by Can Canbolat on 08.09.17.
//  Copyright © 2017 Can Canbolat. All rights reserved.
//

#include "SampleCFile.h"

int product(int multiplier, int multiplicand) {
    return multiplier * multiplicand;
}

int quotient(int dividend, int divisor, int *remainder) {
    if (remainder) {
        *remainder = dividend % divisor;
    }
    return dividend / divisor;
}
