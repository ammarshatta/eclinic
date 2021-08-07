//
//  CJGuestHelper.h
//  JabberGuestSDK 32
//
//  Created by MyMACBook on 2020/7/30.
//  Copyright © 2020 Cisco Systems, Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>

NS_ASSUME_NONNULL_BEGIN

@interface CJGuestHelper : NSObject

+ (BOOL)isStatusBarHidden;
+ (UIWindow *)keyWindow;

+ (UIInterfaceOrientation)interfaceOrientation;

@end

NS_ASSUME_NONNULL_END
