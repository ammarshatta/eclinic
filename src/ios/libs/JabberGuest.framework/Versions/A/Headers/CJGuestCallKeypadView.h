//
//  CJGuestCallKeypadView.h
//  JabberGuest
//
//  Copyright (c) 2013 Cisco Systems, Inc. All rights reserved.
//

#import <UIKit/UIKit.h>

/**
 * @defgroup keypadbuttons Keypad Button Enumerations
 * @{
 */
/**
 * Enumeration describing the button types of the view.
 */
typedef NS_ENUM(NSInteger, CJGuestCallKeypadButtonType) {
    /**
     * Defines the keypad one button.
     */
    GuestCallKeypadButtonOne,
    /**
     * Defines the keypad two button.
     */
    GuestCallKeypadButtonTwo,
    /**
     * Defines the keypad three button.
     */
    GuestCallKeypadButtonThree,
    /**
     * Defines the keypad four button.
     */
    GuestCallKeypadButtonFour,
    /**
     * Defines the keypad five button.
     */
    GuestCallKeypadButtonFive,
    /**
     * Defines the keypad six button.
     */
    GuestCallKeypadButtonSix,
    /**
     * Defines the keypad seven button.
     */
    GuestCallKeypadButtonSeven,
    /**
     * Defines the keypad eight button.
     */
    GuestCallKeypadButtonEight,
    /**
     * Defines the keypad nine button.
     */
    GuestCallKeypadButtonNine,
    /**
     * Defines the keypad star button.
     */
    GuestCallKeypadButtonStar,
    /**
     * Defines the keypad zero button.
     */
    GuestCallKeypadButtonZero,
    /**
     * Defines the keypad pound button.
     */
    GuestCallKeypadButtonPound
};
/**
 * @}
 */

/**
 * The CJGuestCallKeypadView custom view.
 */
@interface CJGuestCallKeypadView : UIView
/**
 * Initializes the view at the origin coordinates.
 * The view is fixed to a specific size. Attempting to
 * create or re-set the view to a different size may
 * result in undesired behavior.
 *
 * @param origin The x/y coordinates to present the view.
 */
- (id)initWithOrigin:(CGPoint)origin;
@property(nonatomic,weak) id /*<CJGuestCallKeypadViewDelegate>*/ delegate;
/**
 * Controls whether the keypad view will play a tone with each keypad
 * button press.
 * - true(default) - Play tones with each keypad button press.
 * - false - Do not play tones with each keypad button press.
 */
@property(nonatomic,readwrite) BOOL playKeypadTones;
/**
 * Returns the keypad size
 * @return CGSize(CGFloat width, CGFloat height)
 */
- (CGSize)getKeypadSize;
/**
 * Helper method to provide the string representation
 * of the CJGuestCallKeypadButtonType
 *
 * @param type The button type.
 * @return NSString String representation of the button type.
 */
+ (NSString*)stringFromGuestKeypadButton:(CJGuestCallKeypadButtonType) type;
@end

/**
 * The delegate for CJGuestCallKeypadViewDelegate.
 */
@protocol CJGuestCallKeypadViewDelegate <NSObject>
/**
 * A button on the view has been pressed.
 *
 * @param keypadView The view whose button was pressed.
 * @param buttonIndex The index of the button pressed.
 * @sa CJGuestCallKeypadButtonType
 */
- (void)keypadView:(CJGuestCallKeypadView *)keypadView clickedButtonAtIndex:(NSInteger)buttonIndex;
@end
