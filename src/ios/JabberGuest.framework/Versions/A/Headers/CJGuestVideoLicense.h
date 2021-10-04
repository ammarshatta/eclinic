//
//  CJGuestVideoLicense.h
//  JabberGuestSDK
//
//  Copyright (c) 2014 Cisco Systems, Inc. All rights reserved.
//

#import <Foundation/Foundation.h>

typedef void(^CJGuestVideoLicenseCompletion)(BOOL isActivated);

/**
 * @class CJGuestVideoLicense CJGuestVideoLicense.h JabberGuest/JabberGuest.h
 * This class handle the activation of the system video license
 */
@interface CJGuestVideoLicense : NSObject

/**
 * This method returns the shared videoLicense instance.
 * @return The videoLicense instance.
 */
+ (CJGuestVideoLicense *)sharedInstance;

/**
 * Call this method to prevent the JabberGuest SDK from either checking for
 * or activating the Cisco license for video.
 */
- (void) disableActivation;

@end
