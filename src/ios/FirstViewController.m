//
//  FirstViewController.m
//
//  Copyright (c) 2015 Cisco and/or its affiliates.  All rights reserved.
//

#import "FirstViewController.h"

//#import "SecondViewController.h"

@interface FirstViewController ()

@end

@implementation FirstViewController

- (id)initWithNibName:(NSString *)nibNameOrNil bundle:(NSBundle *)nibBundleOrNil
{
    self = [super initWithNibName:nibNameOrNil bundle:nibBundleOrNil];
    if (self) {
        [[self navigationItem] setTitle:@"First"];
        
        UIBarButtonItem * bbi = [[UIBarButtonItem alloc] initWithBarButtonSystemItem:UIBarButtonSystemItemPlay
                                                                              target:self
                                                                              action:@selector(nextStep:)];
        
        [[self navigationItem] setRightBarButtonItem:bbi];
    }
    return self;
}

- (IBAction)nextStep:(id)sender
{
    //SecondViewController *svc = [[SecondViewController alloc] init];
    
    //[[self navigationController] pushViewController:svc animated:YES];
}

- (void)viewDidLoad
{
    [super viewDidLoad];
    // Do any additional setup after loading the view from its nib.
}

- (void)didReceiveMemoryWarning
{
    [super didReceiveMemoryWarning];
    // Dispose of any resources that can be recreated.
}

@end
