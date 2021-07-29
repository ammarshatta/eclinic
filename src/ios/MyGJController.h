//
//  SecondViewController.h
//
//  Copyright (c) 2015 Cisco and/or its affiliates.  All rights reserved.
//

#import <UIKit/UIKit.h>
#import <JabberGuest/JabberGuest.h>

@interface MyGJController : CJGuestCallViewController


@property (copy)   NSString* callbackId;
@property (strong) UIView* webView;



@end


