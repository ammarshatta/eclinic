//
//  CJGuestCallSelfView.h
//  JabberGuest
//
//  Copyright (c) 2013 Cisco Systems, Inc. All rights reserved.
//

#import <UIKit/UIKit.h>

/**
 * The CJGuestCallSelfView provides UI elements for displaying the self view
 * video from CJGuestCall. In addition to the video, it provides a button
 * for changing the camera and when the output video is muted, it will indicate
 * the video has stopped.
 * @sa CJGuestCall::selfView
 */
@interface CJGuestCallSelfView : UIView
@property (nonatomic) BOOL switchCameraVisible;
/**
 * The selfView video feed auto rotate can be turn off.
 * The auto rotate will not be detected by the selfview.
 */
@property (nonatomic) BOOL videoCaptureAutoRotate;
@end
