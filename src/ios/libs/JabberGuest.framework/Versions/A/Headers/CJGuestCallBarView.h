//
//  CJGuestCallBarView.h
//  JabberGuest
//
//  Copyright (c) 2013 Cisco Systems, Inc. All rights reserved.
//

#import <UIKit/UIKit.h>


/**
 * The CJGuestCallBarView custom view.
 */
@interface CJGuestCallBarView : UIView
/**
 * Enumeration bitmap describing the button types of the view.
 */
typedef NS_OPTIONS(NSInteger, CJGuestCallBarButtonOption) {
    /**
     * Option to show the audio mute toggle button
     * on the call bar view.
     */
    GuestCallBarButtonOptionAudioMute = 1 << 0,
    /**
     * Option to show the video mute toggle button
     * on the call bar view.
     */
    GuestCallBarButtonOptionVideoMute = 1 << 1,
    /**
     * Option to show the keypad button
     * on the call bar view.
     */
    GuestCallBarButtonOptionKeypad    = 1 << 2,
    /**
     * Option to show the call/end call button
     * on the call bar view.
     */
    GuestCallBarButtonOptionHook       = 1 << 3
};
/**
 * Enumeration describing the button types of the view.
 */
typedef NS_ENUM(NSInteger, CJGuestCallBarButtonType) {
    /**
     * Defines the button for muting/un-muting audio.
     */
    GuestCallBarButtonAudioMute,
    /**
     * Defines the button for muting/un-muting video.
     */
    GuestCallBarButtonVideoMute,
    /**
     * Defines the button to activate the keypad view.
     */
    GuestCallBarButtonKeypad,
    /**
     * Defines the button for starting/ending a call.
     */
    GuestCallBarButtonHook
};
/**
 * Initializes the view at the origin coordinates.
 * The view is fixed to a specific size. Attempting to
 * create or re-set the view to a different size may
 * result in undesired behavior.
 *
 * @param origin The x/y coordinates to present the view.
 */
- (id)initWithOrigin:(CGPoint)origin;
/**
 * Initializes the view at the origin coordinates and 
 * with a chosen set of buttons.
 * The view is fixed to a specific size. Attempting to
 * create or re-set the view to a different size may
 * result in undesired behavior.
 *
 * @param origin The x/y coordinates to present the view.
 * @param mask CJGuestCallBarButtonOption bitmap defining which buttons to create.
 */
- (id)initWithOrigin:(CGPoint)origin mask:(CJGuestCallBarButtonOption) mask;


/**
 * The delegate that implements the CJGuestCallBarViewDelegate protocol.
 */
@property(nonatomic,weak) id /*<CJGuestCallBarViewDelegate>*/ delegate;
/**
 * The keypad delegate that implements the CJGuestCallKeypadViewDelegate protocol.
 */
@property(nonatomic,weak) id /*<CJGuestCallKeypadViewDelegate>*/ keypadDelegate;
/**
 * Bitmask defining which buttons appear in the view.
 */
@property(nonatomic) CJGuestCallBarButtonOption buttonMask;
/**
 * Checks the CJGuestCallBarView to determine if there is an active KeypadView visible
 */
@property (nonatomic, readonly, getter = isKeypadOpen) BOOL keypadOpen;
/**
 * Sets the CJGuestCallBarView to use its default keypad view.
 * Use the CJGuestCallBarViewDelegate to know when the keypad
 * button us clicked
 */
@property(nonatomic,readwrite) BOOL useDefaultKeypad;
/**
 * Controls whether the keypad view will play a tone with each keypad
 * button press.
 * - true(default) - Play tones with each keypad button press.
 * - false - Do not play tones with each keypad button press.
 */
@property(nonatomic,readwrite) BOOL playKeypadTones;
/**
 * Controls whether the pressing End Call during screen share requires confirmation
 * - true - Prompt user before hangup during screen share.
 * - false(default) - Do not prompt user before hangup during screen share.
 */
@property(nonatomic, readwrite) BOOL confirmBeforeHangupDuringScreenShare;


/**
 * Helper method to provide the string representation
 * of the CJGuestCallBarButtonType
 *
 * @param type The button type.
 * @return NSString String representation of the button type.
 */
+ (NSString*)stringFromGuestCallBarButton:(CJGuestCallBarButtonType) type;
/**
 * Helper method to return the height and width of a single button
 * that can be used to calculate the size of the call bar before creating
 * an instance. These values vary by device.
 */
+(CGSize)callBarButtonSize;

@end

/**
 * The delegate for CJGuestCallBarViewDelegate.
 */
@protocol CJGuestCallBarViewDelegate <NSObject>
@optional
/**
 * A button on the view has been pressed.
 *
 * @param callBarView The view whose button was pressed.
 * @param buttonType The type of the button pressed. See: CJGuestCallBarButtonType
 */
- (void)callBarView:(CJGuestCallBarView *)callBarView
      clickedButton:(CJGuestCallBarButtonType)buttonType;
/**
 * The keypad view was dismissed from to the CallBarView.
 *
 * @param callBarView The view which dismissed the keypad.
 */
- (void)callBarViewDidDismissKeypad:(CJGuestCallBarView *)callBarView;
/**
 * The keypad view was presented from the CallBarView.
 *
 * @param callBarView The view which presentd the keypad.
 */
- (void)callBarViewDidPresentKeypad:(CJGuestCallBarView *)callBarView;
@end
