//
//  CJGuestCallViewController.h
//  JabberGuest
//
//  Copyright (c) 2013 Cisco Systems, Inc. All Rights Reserved.
//

#import <UIKit/UIKit.h>
#import <JabberGuest/JabberGuest.h>

#import <MessageUI/MessageUI.h>
// #import "JabberGuest.h"

@protocol CJGuestCallViewControllerDelegate;


/**JabberGuest/JabberGuestSDK/JabberGuestSDKLib
 * The high-level Jabber Guest controller object.
 */
@interface CJGuestCallViewController : UIViewController <CJGuestCallBarViewDelegate>

/**
 * The Jabber Guest server name.
 */
@property (nonatomic, readwrite, strong) NSString * serverName;

/**
 * The URI to call.
 */
@property (nonatomic, readwrite, strong) NSString * toURI;

/**
 * The Url including server name, toURI and extra prefetched configurations.
 */
@property (nonatomic, readwrite, strong) NSString * fullServerUrl;

/**
 * The delegate that implements the CJGuestCallViewControllerDelegate protocol.
 */
@property (weak) id <CJGuestCallViewControllerDelegate> delegate;

/**
 * The number of seconds to keep the call bar visible after it is made visible.
 */
@property (nonatomic, readwrite) NSTimeInterval secondsCallBarHide;

/**
 * Controls whether the pressing End Call during screen share requires confirmation
 * - true - Prompt user before hangup during screen share.
 * - false(default) - Do not prompt user before hangup during screen share.
 */
@property(nonatomic, readwrite) BOOL confirmBeforeHangupDuringScreenShare;

/**
 * Returns YES if the call state is connected, connecting, or disconnecting.
 */
+ (BOOL)hasActiveCall;

/**
 * displays a tranparent window showing call statistics for an active call
 */
- (void)showCallStatistics;

/**
 * Configures the controller by parsing a URL.  The URL must follow the format as
 * defined in the Custom URL Schemes documentation.
 *
 * Typically, you would call this from your app delegate's `handleURL:` method.
 *
 * #serverName and #toURI are set to the values pulled out of the URL.
 *
 * @param url The URL to parse.
 */
- (void)configureFromURL:(NSURL *)url;

/**
 * Handles all the details of having an active call go to the background.
 *
 * Call this method from your app delegate's `applicationWillResignActive:` or
 * `applicationDidEnterBackground:` implementations.
 *
 * \deprecated as of v.10.5
 */
- (void)enterBackground;

/**
 * Handles all the details of having an active call go to the foreground.
 *
 * Call this method from your app delegate's `applicationWillEnterForeground:` or
 * `applicationDidBecomeActive:` implementations.  
 *
 * \deprecated as of v.10.5
 */
- (void)enterForeground;

/**
 * Handles terminating an active call when your app terminates.  
 *
 * Call this method from your app delegate's `applicationWillTerminate:` implementation.
 */
- (void)terminate;

@end


/**
 * The delegate for CJGuestCallViewController.
 */
@protocol CJGuestCallViewControllerDelegate <NSObject>

@optional

/**
 * The call is finished (end button is pressed or disconnect occurs).
 *
 * @param callController The controller whose call is finished.
 */
- (void)callFinishedForCallController:(CJGuestCallViewController *)callController;

/**
 * The more button was pressed in CJGuestCallViewController's navigation bar.
 *
 * @param callController  The controller whose button was pressed.
 */
- (void)moreButtonPressedForCallController:(CJGuestCallViewController *)callController;

/**
 * Received an invalid certificate from the Jabber Guest server.
 *
 * If this is not implemented, an alert view will be presented to the user by default.  They can 
 * choose to not place the call, or to continue.
 */
- (void) onInvalidCert:(NSString*)certFingerprint
         certSubjectCN:(NSString*)certSubjectCN
           referenceID:(NSString*)referenceID
         invalidReason:(NSArray*)invalidReason
subjectCertificateData:(NSString*)subjectCertificateData
intermediateCACertificateData:(NSArray*)intermediateCACertificateData
   invalidCertCallback:(id <CJGuestInvalidCertCallback>)invalidCertCallback;

@end
