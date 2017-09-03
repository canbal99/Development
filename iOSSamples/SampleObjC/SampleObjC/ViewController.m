//
//  ViewController.m
//  SampleApp
//
//  Created by Can Canbolat on 01.09.17.
//  Copyright © 2017 Can Canbolat. All rights reserved.
//

#import "ViewController.h"

@interface ViewController ()

@property (weak, nonatomic) IBOutlet UIButton *buttonOK;
@property (weak, nonatomic) IBOutlet UILabel *labelText;
@property (weak, nonatomic) IBOutlet UITextField *textField;

@end

@implementation ViewController

@synthesize myObject = _myObject;

- (void)viewDidLoad {
    [super viewDidLoad];
    // Do any additional setup after loading the view, typically from a nib.
    
    self.myObject = [[SampleClass alloc] init];
}


- (void)didReceiveMemoryWarning {
    [super didReceiveMemoryWarning];
    // Dispose of any resources that can be recreated.
}

- (IBAction)onButtonOKClicked:(id)sender {
    self.labelText.text = self.textField.text;
    
    NSNumberFormatter* formatter = [[NSNumberFormatter alloc] init];
    NSNumber* number = [formatter numberFromString:self.textField.text];
    number = [NSNumber numberWithDouble:2.4];
    NSLog(@"Number entered: %d", [number intValue]);
    
    self.myObject.firstName = @"Yusuf Can";
    //self.myObject.lastName = @"Canbolat";
    NSLog(@"Name: %@ %@", self.myObject.firstName, self.myObject.lastName);
}

@end
