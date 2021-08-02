//
//  CJGuestCall.h
//  JabberGuest
//
//  Copyright (c) 2013 Cisco Systems, Inc. All Rights Reserved.
//

#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>

//#import <JabberGuest/CJGuestMediaStatistics.h>
//#import <JabberGuest/CJGuestVideoLicense.h>
#import "CJGuestMediaStatistics.h"
#import "CJGuestVideoLicense.h"



/**
 * An object implementing this protocol is passed to the CJGuestInvalidCertDelegate.
 * The delegate should call one of the methods to indicate whether to accept or reject
 * the invalid certificate.
 */
@protocol CJGuestInvalidCertCallback <NSObject>
/**
 * The delegate calls this to accept the invalid certificate.
 */
- (void)accept;
/**
 * The delegate calls this to reject the invalid certificate.
 */
- (void)reject;
@end

/**
 * An object implementing this potocol is passed to CJGuestServerConfiguraionCallDelegate.
 * The delegate should call one of the methods to indicate the configuration is ready for use.
 * The delegate will also get the information of automatic-start call.
 */
@protocol CJGuestServerConfiguraionCallDelegate <NSObject>
@optional
/**
 * This is called to indicate the server configuration of automatic-start call is retrieved
 * @param secs The time of the scheduled automatic-start call in seconds. If secs is smaller than 0, there is no call scheduled.
 */
-(void) serverConfiguraionDidRetriveWithScheduledCallInfo:(NSInteger)secs;

/**
 * This is called when the scheduled automatic-start call is executed.
 */
-(void) scheduledCallDidExecute;

/**
 * This is called to indicate all the server configuration is retrieved
 */
- (void)allServerConfigurationDidRetrieve;
@end

/**
 * This protocol provides a notification if any of the HTTP requests performed by
 * CJGuestCall encounter an invalid certificate.
 */
@protocol CJGuestInvalidCertDelegate <NSObject>
@optional
/**
 * This is called after encountering an invalid certificate in an HTTP request.
 * @param certFingerprint The digital fingerprint of the certificate.
 * @param certSubjectCN The CN subject from the certificate.
 * @param referenceID The reference ID of the certificate.
 * @param invalidReason A list of reasons of why the certificate is invalid.
 * @param subjectCertificateData Additional subject information about the certificate.
 * @param intermediateCACertificateData A list of the certificate authorities authorizing
 *        the chain of certificates.
 * @param invalidCertCallback The callback object used to accept or reject the certificate.
 */
- (void) onInvalidCert:(NSString*)certFingerprint
         certSubjectCN:(NSString*)certSubjectCN
           referenceID:(NSString*)referenceID
         invalidReason:(NSArray*)invalidReason
subjectCertificateData:(NSString*)subjectCertificateData
intermediateCACertificateData:(NSArray*)intermediateCACertificateData
   invalidCertCallback:(id <CJGuestInvalidCertCallback>)invalidCertCallback;
@end

#pragma mark Notifications
/**
 * @defgroup cjgnotifications Notification Event Names
 * @{
 */
/**
 * Register for this event to be notified when the call state changes.
 * @sa CJGuestCall::callState
 */
extern NSString *const CJGuestCallStateChangeNotification;
/**
 * Register for this event to be notified when an error occurs during call processing.
 * The userInfo element of the NSNotification object will contain a dictionary with
 * the key "JabberGuestError" mapped to an NSError object containing error information.
 */
extern NSString *const CJGuestCallErrorNotification;
/**
 * The key for the value in the userInfo dictionary of the NSNotification received from the
 * CJGuestCallErrorNotification event.  The value is an NSError object.
 */
extern NSString *const CJGuestCallErrorKey;
/**
 * Register for this event to be notified when the size of the self view video changes.
 * @sa CJGuestCall::selfSize
 */
extern NSString *const CJGuestCallSelfVideoResolutionNotification;
/**
 * Register for this event to be notified when the size of the remote view video changes.
 * @sa CJGuestCall::remoteSize
 */
extern NSString *const CJGuestCallRemoteVideoResolutionNotification;
/**
 * Register for this event to be notified when the size of the remotePreso view video changes.
 * @sa CJGuestCall::remotePresoSize
 */
extern NSString *const CJGuestCallRemotePresoVideoResolutionNotification;
/**
 * Register for this event to be notified when the active state of the remotePreso view video changes.
 * @sa CJGuestCall::remotePresoActive
 */
extern NSString *const CJGuestCallRemotePresoVideoActiveNotification;
/**
 * Register for this event to be notified when the active state of the self view video changes.
 * @sa CJGuestCall::selfVideoActive
 */
extern NSString *const CJGuestCallSelfVideoActiveNotification;
/**
 * Register for this event to be notified when the first frame of the remotePreso video is received.
 * @sa CJGuestCall::remotePresoStarted
 */
extern NSString *const CJGuestCallRemotePresoVideoStartedNotification;
/**
 * Register for this event to be notified when the audio input mute state changes.
 * @sa CJGuestCall::audioInState
 */
extern NSString *const CJGuestCallAudioInStateNotification;
/**
 * Register for this event to be notified when the audio output mute state changes.
 * @sa CJGuestCall::audioOutState
 */
extern NSString *const CJGuestCallAudioOutStateNotification;
/**
 * Register for this event to be notified when the video input mute state changes.
 * @sa CJGuestCall::videoInState
 */
extern NSString *const CJGuestCallVideoInStateNotification;
/**
 * Register for this event to be notified when the video output mute state changes.
 * @sa CJGuestCall::videoOutState
 */
extern NSString *const CJGuestCallVideoOutStateNotification;
/**
 * Register for this event to be notified when the orientation of the remote view video changes.
 * @sa CJGuestCall::orientation
 */
extern NSString *const CJGuestCallOrientationNotification;
/**
 * Register for this event to be notified when a DTMF is sent to the remote endpoint.
 * @sa CJGuestCall::sentDTMF
 */
extern NSString *const CJGuestCallSentDTMFNotification;
/**
 * Register for this event to be notified when the video capture device is changed.
 */
extern NSString *const CJGuestCallCameraSwitchedNotification;
/**
 * Register for this event to be notified of the server version.
 */
extern NSString *const CJGuestCallServerVersionNotification;
/**
 * Register for this event to be notified of the remote participant display name.
 */
extern NSString *const CJGuestCallRemoteDisplayNameChangedNotification;



/**
 * @}
 */

#pragma mark Errors
/**
 * @defgroup cjgerrors Error Codes
 * @{
 */
/**
 * The error codes for the Jabber Guest Error Domain.
 */
typedef NS_ENUM(NSInteger, CJGuestErrorCode) {
    /**
     * The Jabber Guest server encountered a SIP error.
     */
    CJGuestSipError = 1,
    /**
     * There Jabber Guest server encountered an exception.
     */
    CJGuestRoapExceptionError,
    /**
     * The URI was invalid.
     */
    CJGuestBlankSipUriError,
    /**
     * There was a networking error between the device and the server.
     */
    CJGuestBlankSdpError,
    /**
     * The URI was invalid.
     */
    CJGuestInvalidSipUriError,
    /**
     * The media gateway is not defined.
     */
    CJGuestMediaGatewayUndefinedError,
    /**
     * The server was busy and could no resource allocation failed.
     */
    CJGuestMediaGatewayAllocationFailedError,
    /**
     * The ICE negotiation failed.
     */
    CJGuestMediaGatewayIceFailedError,
    /**
     * There was an error in the SIP configuration.
     */
    CJGuestSipConfigurationError,
    /**
     * The destination was busy.
     */
    CJGuestSipEndpointBusyError,
    /**
     * An invalid call state.
     */
    CJGuestInvalidCallStateError,
    /**
     * A TURN error.
     */
    CJGuestTurnCredAcquireFailedError,
    /**
     * The URI was not found.
     */
    CJGuestLinkNotFoundError = 50,
    /**
     * The URI is not active.
     */
    CJGuestLinkNotValidYetError,
    /**
     * The URI has expired.
     */
    CJGuestLinkExpiredError,
    /**
     * The URI has been disabled.
     */
    CJGuestLinkDisabledError,
    /**
     * An http error.
     */
    CJGuestHttpError = 1000,
    /**
     * There was a network error.  It is very common to get this error when the host can not be 
     * resolved.
     */
    CJGuestNetError,
    /**
     * An undefined error.
     */
    CJGuestUnknownError,
    /*
     * The version of the API reported by the Jabber Guest server was invalid.
     */
    CJGuestInvalidApiVersionError,
    /*
     * The version of the API reported by the Jabber Guest server is not supported with this version of the SDK.
     */
    CJGuestUnsupportedApiVersionError
};
/**
 * @}
 */


@class CJGuestCall;

/**
 * @class CJGuestCall CJGuestCall.h JabberGuest/JabberGuest.h
 * @nosubgrouping
 * This is the main class of the Jabber Guest iOS SDK. CJGuestCall represents the
 * lifecycle of a single entire call. Only one instance of this class exists, and
 * that instance is accessed through the sharedInstance() static method.
 *
 * CJGuestCall will also send out notifications via NSNotificationCenter whenever
 * specific events occur, like the call state changed, or a DTMF was sent on the call. Any
 * component interested in responding to these notifications should register for them
 * by adding an observer through the NSNotificationCenter.
 */

@interface CJGuestCall : NSObject

/**
 * @name Initializers
 * Although the initializers are accessible, the CJGuestCall object should be accessed
 * through the #sharedInstance method.
 * @{
 */
/**
 * Initializes an instance of CJGuestCall.
 * @return The initialized instance of CJGuestCall.
 */
- (id)init;


/**
 * Initializes an instance of CJGuestCall with the serverName and toURI.
 * @param serverName The name of the server through which we will connected with the remote endpoint.
 * @param toURI The URI of the endpoint to which we would like to connect.
 * @param callerName Guest caller name displayed on remote destination
 * @return The initialized instance of CJGuestCall
 * @sa #serverName, #toURI
 */
- (id)initWithServerName:(NSString *)serverName toURI:(NSString *)toURI callerName:(NSString*)callerName;

/**
 * @}
 */

/**
 * @name Configuration
 * @{
 */
/**
 * The server name through which we will establish this call.
 */
@property (nonatomic, readwrite, strong) NSString *serverName;
/**
 * The URI of the remote end point to which the call should be established.
 * Examples:
 *  * 18005551212
 *  * 5000
 *  * 5000@example.com
 */
@property (nonatomic, readwrite, strong) NSString *toURI;
/**
 * The whole url including server name, protocol, toURI and also some prefeteched configuration from server response.
 */
@property (nonatomic, readwrite, strong) NSString *fullServerUrl;

/**
 * The remote participant display name from server
 */
@property (nonatomic, readonly) NSString *remoteDisplayName;

/**
 * Guest caller name displayed on remote destination
 */
@property (nonatomic, readwrite) NSString *callerName;


/**
 * @}
 */

/**
 * @name Video Control
 * @{
 */
/**
 * The selfView will be updated with video from the camera on the device, providing
 * feedback so the user can see what is being sent to the remote party in the call.
 */
@property (nonatomic, readwrite, strong) IBOutlet UIImageView * selfView;

/**
 * The size of the self view video image.
 */
@property (nonatomic, readonly) CGSize selfSize;

/**
 * This will be updated with video sent from the remote endpoint of the call.
 */
@property (nonatomic, readwrite, strong) IBOutlet UIImageView * remoteView;

/**
 * The size of the remote video image.
 */
@property (nonatomic, readonly) CGSize remoteSize;

/**
 * This will be updated with video sent from the remotePreso endpoint of the call.
 */
@property (nonatomic, readwrite, strong) IBOutlet UIImageView * remotePresoView;

/**
 * The size of the remotePreso video image.
 */
@property (nonatomic, readonly) CGSize remotePresoSize;

/**
 * The active state of the remotePreso video stream.
 */
@property (nonatomic, readonly) BOOL remotePresoActive;

/**
 * The active state of the self video stream
 */
@property (nonatomic, readonly) BOOL selfVideoActive;

/**
 * The active state of the remotePreso video stream.
 */
@property (nonatomic, readonly) BOOL remotePresoStarted;

/**
 * Indicates the orientation of the device so the video capture can compensate and
 * send the video in the correct orientation.
 */
@property (nonatomic, readwrite) UIInterfaceOrientation captureOrientation;

#if 0
/**
 * This will begin capturing video from the local capture device and sending
 * the video to the #selfView if it was set.
 * @return YES on success, NO on failure (video license not activated)
 */
- (BOOL)startSelfView;
#endif

/**
 * This will begin capturing video from the local capture device and sending
 * the video to the #selfView if it was set.
 * @param completion: block to be executed upon completion
 */
- (void)startSelfView:(CJGuestVideoLicenseCompletion) completion;

/**
 * This will stop capturing video from the local capture device and sending
 * the video to the #selfView if it was set.
 */
- (void)stopSelfView;

/**
 * Cycle the local capture device to the next available one.
 */
- (void)switchCamera;

/**
 * @}
 */

/**
 * @name Call Control
 * @{
 */

#if 0
/**
 * After setting the #serverName and #toURI properties, call this method to establish
 * a call with the remote endpoint.
 * @return YES on success, NO on failure (video license not activated)
 */
- (BOOL)startCall;
#endif

/**
 * After setting the #serverName and #toURI properties, call this method to establish
 * a call with the remote endpoint.
 * @param completion: block to be executed upon completion
 */
- (void)startCall:(CJGuestVideoLicenseCompletion) completion;

/**
 * After calling startCall() to establish the call with the remote endpoint, call this
 * method to end the call and stop any media transmission between the local and remote
 * endpoint.
 */
- (void)endCall;

/**
 * When a automatic-start call is scheduled, call this to cancel the scheduled call.
 */
- (void)cancelAutoStartCall;

/**
 * @}
 */

/**
 * @name Call State
 * @{
 */
/**
 * This identifies the progress of the call as the call is established with the
 * remote endpoint.
 */
typedef NS_ENUM(NSInteger, CJGuestCallStateType) {
    /**
     * CJGuestCall has not been initialized with a valid server name
     */
    GuestCallStateNotInitialized,
    
    /**
     * CJGuestCall is not communicating with any remote endpoints and is ready
     * to establish a new communication session.
     */
    GuestCallStateDisconnected,
    
    /**
     * CJGuestCall is trying to connect a call to the called
     * party from the URI that it was given. During this time, the
     * CJGuestCall instance is attempting to connect to the called party,
     * negotiate audio and/or video via SDP, and setup the multimedia streams as
     * appropriate.
     */
    GuestCallStateConnecting,
    
    /**
     * CJGuestCall instance is currently connected to the called party from the
     * URI that it was given. All applicable audio and/or video
     * streams are established and an active call is in progress.
     */
    GuestCallStateConnected,

    /**
     * CJGuestCall instance is either attempting to end an active call at the
     * request of the device user, or the called party has ended the active call.
     * During this state, the CJGuestCall instance will begin cleaning up all
     * resources related to the previous call as appropriate.
     */
    GuestCallStateDisconnecting
};
/**
 * Indicates the current state of the call.
 */
@property (nonatomic, readonly) CJGuestCallStateType callState;

/**
 * @}
 */

/**
 * @name Mute State
 * @{
 */
/**
 * Muting or unmuting a media stream requires some coordination between resources, so
 * the state of the media stream will transition between these values.
 */
typedef NS_ENUM(NSInteger, CJGuestMuteStateType) {
    /**
     * The media stream is muted, no media is passing.
     */
    GuestMuteStateMuted,
    
    /**
     * The media stream is transitioning to the unmuted state and may not be passing
     * media.
     */
    GuestMuteStateUnmuting,
    
    /**
     * The media stream is unmuted, media is passing.
     */
    GuestMuteStateUnmuted,
    
    /**
     * The media stream is transitioning to the muted state and may be passing media.
     */
    GuestMuteStateMuting
};

/**
 * Represents the mute state of the audio being sent to the remote end point.
 */
@property (nonatomic, readonly) CJGuestMuteStateType audioOutState;
/**
 * Represents the mute state of the video being sent to the remote end point.
 */
@property (nonatomic, readonly) CJGuestMuteStateType videoOutState;
/**
 * Represents the mute state of the audio being received by the local end point.
 */
@property (nonatomic, readonly) CJGuestMuteStateType audioInState;
/**
 * Represents the mute state of the video being received by the local end point.
 */
@property (nonatomic, readonly) CJGuestMuteStateType videoInState;


/**
 * Convenience property for determining whether the audio output is muted.
 * @sa audioOutState
 */
@property (nonatomic, readonly, getter = isAudioOutMuted) BOOL audioOutMuted;
/**
 * Convenience property for determining whether the audio output is unmuted.
 * @sa audioOutState
 */
@property (nonatomic, readonly, getter = isAudioOutUnmuted) BOOL audioOutUnmuted;
/**
 * Convenience property for determining whether the audio input is muted.
 * @sa audioInState
 */
@property (nonatomic, readonly, getter = isAudioInMuted) BOOL audioInMuted;
/**
 * Convenience property for determining whether the audio input is unmuted.
 * @sa audioInState
 */
@property (nonatomic, readonly, getter = isAudioInUnmuted) BOOL audioInUnmuted;
/**
 * Convenience property for determining whether the video output is muted.
 * @sa videoOutState
 */
@property (nonatomic, readonly, getter = isVideoOutMuted) BOOL videoOutMuted;
/**
 * Convenience property for determining whether the video output is unmuted.
 * @sa videoOutState
 */
@property (nonatomic, readonly, getter = isVideoOutUnmuted) BOOL videoOutUnmuted;
/**
 *  Convenience property for determining whether the video ouput control is disabled by policy from server
 */
@property (nonatomic, readonly, getter = isVideoControlEnabled) BOOL videoControlEnabled;
/**
 * Convenience property for determining whether the video input is muted.
 * @sa videoInState
 */
@property (nonatomic, readonly, getter = isVideoInMuted) BOOL videoInMuted;
/**
 * Convenience property for determining whether the video input is unmuted.
 * @sa videoInState
 */
@property (nonatomic, readonly, getter = isVideoInUnmuted) BOOL videoInUnmuted;

/**
 * Start the process of muting the audio output. The audio output will not be muted
 * immediately, but #audioOutState will transition from unmuted to muting and then
 * to muted.
 */
- (void)muteAudioOut;

/**
 * Start the process of unmuting the audio output. The audio output will not be unmuted
 * immediately, but #audioOutState will transition from muted to unmuting and then
 * to unmuted.
 */
- (void)unmuteAudioOut;

/**
 * Start the process of muting the video output. The video output will not be muted
 * immediately, but #videoOutState will transition from unmuted to muting and then
 * to muted.
 */
- (void)muteVideoOut;

/**
 * Start the process of unmuting the video output. The video output will not be unmuted
 * immediately, but #videoOutState will transition from muted to unmuting and then
 * to unmuted.
 */
- (void)unmuteVideoOut;

/**
 * @}
 */

/**
 * @name DTMF Control
 * @{
 */
/**
 * Provides a string representation of the last DTMF digit sent.
 */
@property (nonatomic, readonly) NSString *sentDTMF;

/**
 * Add a single digit to the queue of digits being sent to the remote endpoint.
 * @param dtmf The DTMF (0-9, *, #) to add to the queue.
 * @sa sendDTMFString:
 */
- (void)sendDTMF:(char)dtmf;

/**
 * Add a sequence of DTMF (0-9, *, #) to the queue of digits being sent to the remote endpoint.
 * Once you've added the DTMF to the queue, they will be sent to the remote endpoint
 * with specific timing.  Use the #sentDTMF property and CJGuestCallSentDTMFNotification
 * to determine which DTMF was last sent.
 * @param dtmfString the sequence of DTMF to add to the queue.
 */
- (void)sendDTMFString:(NSString *)dtmfString;

/**
 * @}
 */

/**
 * @name Miscellaneous
 * @{
 */
/**
 * This delegate is called when HTTP requests encounter problems verifying the certificate
 * for a web site. Implementing this delegate gives control over accepting or rejecting
 * the certificate being verified.
 */
@property (nonatomic, readwrite, weak) IBOutlet id <CJGuestInvalidCertDelegate> invalidCertDelegate;

/**
 * This delegate is called when server enable automatically start call feature. Implementing this delegate gives information about scheduled automatic-start call.
 * Ignore it or set nil value to it will disable the automatic-start call featrue despite the server configuration and safely fall back to the original behavior.
 * This property must be set before serverName, which will trigger the retrive of configuration.
 */
@property (nonatomic, readwrite, weak) IBOutlet id <CJGuestServerConfiguraionCallDelegate> autoStartCallDelegate;

/**
 * Indicates the call is ready and active (it is not disconnected).
 */
@property (nonatomic, readonly, getter = isReady) BOOL ready DEPRECATED_ATTRIBUTE;

/**
 * Provides access to the audio stream statistics.
 */
@property (nonatomic, readonly, weak) CJGuestAudioStatistics * audioStatistics;

/**
 * Provides access to the video stream statistics.
 */
@property (nonatomic, readonly, weak) CJGuestVideoStatistics * videoStatistics;

/**
 * Provides access to the share stream statistics.
 */
@property (nonatomic, readonly, weak) CJGuestVideoStatistics * shareStatistics;


/**
 * Provides an HTML formatted view of the audio and video statistics for display in a web view,
 * or web browser.
 */
@property (nonatomic, readonly, weak) NSString * htmlCallStatistics;

/**
 * Changes the state of the audio session, giving or removing control over the audio
 * inputs to the application. It also allows the application to use a bluetooth device
 * for audio input.
 * @param active
 *  - true - Activate the audio session for the application.
 *  - false - Deactivate the audio session for the application, allowing other applications
 * to gain control over the audio session.
 */
- (void)audioSetActive:(BOOL) active;


/**
 * @name Network Status
 * @{
 */
typedef NS_ENUM(NSInteger, CJGuestNetworkStatus) {
    CJGuestNetworkStatus_Unknown,
    CJGuestNetworkStatus_Online,
    CJGuestNetworkStatus_Changed,
    CJGuestNetworkStatus_Offline
};

/**
 * Notify that network status has changed
 * @param networkStatus
 *  - see above
 */
- (void)updateNetworkStatus:(CJGuestNetworkStatus) networkStatus;

/**
 * Enable 30 FPS for Mobile video
 * @param enable If set to true, 30 fps will be enabled for iOS. If set to false, 30 fps will be disabled for iOS.
 * default is false
 */
- (void)setMobile30FpsEnabled:(BOOL)enabled;

/**
 * This method returns the active call instance.
 * @return The active call instance.
 */
+ (CJGuestCall *)sharedInstance;

/**
 * This is a utility method that can be used to parse a Jabber Guest formatted URI
 * passed to the iOS app on start-up.
 * @param query The query string to parse for name value pairs.
 * @return A dictionary containing the key value pairs from the passed query string.
 */
+ (NSDictionary *)parseQueryString:(NSString *)query;

/**
 * Returns an array of file names corresponding to the log files that exist on the device.
 * @return A list of file names corresponding to the log files.
 */
+ (NSArray * )getAllLogs;

/**
 * Call this method to enable the detailed log of JabberGuestSDK
 * @param enable  enable or Disable detail log, default is NO.
 */
+ (void)enableDetailLog:(BOOL)enable;

/**
 * This will convert the call state enumeration to a string representation for diagnostics
 * or troubleshooting.
 * @param state The call state for which you would like the string representation.
 * @return The string representation of the state value.
 */
+ (NSString*)stringFromCallState:(CJGuestCallStateType)state;

/**
 * This will convert the mute state enumeration to a string representation for diagnostics
 * or troubleshooting.
 * @param state The mute state for which you would like the string representation.
 * @return The string representation of the state value.
 */
+ (NSString*)stringFromMuteState:(CJGuestMuteStateType)state;


/**
 * Call this method anytime to stop or restart logging to console and disk file.
 * @param enabled Enable the logger or not.
 */
+ (void)setGlobalLoggingEnabled:(BOOL)enabled;

@end
