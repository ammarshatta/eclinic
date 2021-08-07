//
//  CJGuestMediaStatistics.h
//  JabberGuestSDK
//
//  Copyright (c) 2014 Cisco Systems, Inc. All rights reserved.
//

#import <Foundation/Foundation.h>

/**
 * @class CJGuestCodecStatistics CJGuestMediaStatistics.h JabberGuest/JabberGuest.h
 * This class holds parameters related to the codecs being used in the audio and video sessions.
 */
@interface CJGuestCodecStatistics : NSObject
/**
 * The name of the codec.
 */
@property (nonatomic, readonly, strong) NSString *name;
/**
 * The payload type of the codec.
 */
@property (nonatomic, readonly) NSInteger payloadType;
/**
 * The clockrate of the codec.
 */
@property (nonatomic, readonly) NSInteger clockRate;

@end


/**
 * @class CJGuestMediaStatistics CJGuestMediaStatistics.h JabberGuest/JabberGuest.h
 * This class holds parameters common to the audio and video streams of the call.
 */
@interface CJGuestMediaStatistics : NSObject
/**
 * Codec properties used to receive the media.
 */
@property (nonatomic, readonly, strong) CJGuestCodecStatistics *receiveCodec;
/**
 * Packets received over the current media stream.
 */
@property (nonatomic, readonly) NSInteger receivedPackets;
/**
 * Packets lost over the current media stream.
 */
@property (nonatomic, readonly) NSInteger receivePacketsLost;
/**
 * Percent of packets lost during the period of last observation.
 */
@property (nonatomic, readonly) float receivePercentLost;
/**
 * Overall percent of packets lost over the current media stream.
 */
@property (nonatomic, readonly) float receiveCumPercentLost;
/**
 * Average bitrate for stream received during the period of last observation (bits per second).
 */
@property (nonatomic, readonly) NSInteger receiveBitrate;
/**
 * Average jitter (in milliseconds) for stream received during the period of last observation.
 */
@property (nonatomic, readonly) NSInteger receiveJitter;
    
/**
 * Packets sent over the current media stream.
 */
@property (nonatomic, readonly) NSInteger sentPackets;
/**
 * Codec properties used to transmit the media.
 */
@property (nonatomic, readonly, strong) CJGuestCodecStatistics *transmitCodec;
/**
 * Packets received by remote endpoint(s) over the current media stream.
 */
@property (nonatomic, readonly) NSInteger transmitPacketsReceived;
/**
 * Number of packets expected but not received by remote endpoint(s) over the current media stream.
 */
@property (nonatomic, readonly) NSInteger transmitPacketsLost;
/**
 * Percent of packets expected but not received by remote endpoint(s) during the period covered
 * by the most recent RTCP reception report received from the remote endpoint.
 */
@property (nonatomic, readonly) float transmitPercentLost;
/**
 * Percent of packets expected but not received by remote endpoint(s) over the current media stream.
 */
@property (nonatomic, readonly) float transmitCumPercentLost;
/**
 * Average bitrate for stream sent during the period of last observation.
 */
@property (nonatomic, readonly) NSInteger transmitBitrate;
/**
 * Jitter (in milliseconds) for stream sent during the period covered by the most recent
 * RTCP reception report received from the remote endpoint.
 */
@property (nonatomic, readonly) NSInteger transmitJitter;
/**
 * Round trip calculation based on most recent sent and received RTP and RTCP statistics.
 */
@property (nonatomic, readonly) NSInteger transmitRoundTrip;

@end

/**
 * @class CJGuestAudioStatistics CJGuestMediaStatistics.h JabberGuest/JabberGuest.h
 * This class holds parameters specific to the audio stream of the call.
 */
@interface CJGuestAudioStatistics : CJGuestMediaStatistics

@end

/**
 * @class CJGuestVideoStatistics CJGuestMediaStatistics.h JabberGuest/JabberGuest.h
 * This class holds parameters specific to the video stream of the call.
 */
@interface CJGuestVideoStatistics : CJGuestMediaStatistics
/**
 * Width of video frames received in the current stream.
 */
@property (nonatomic, readonly) NSInteger receiveFrameWidth;
/**
 * Height of video frames received in the current stream.
 */
@property (nonatomic, readonly) NSInteger receiveFrameHeight;
/**
 * Number of video frames received per second in the current stream.
 */
@property (nonatomic, readonly) float receivedFramesPerSecond;

/**
 * Width of video frames transmitted in the current stream.
 */
@property (nonatomic, readonly) NSInteger transmitFrameWidth;
/**
 * Height of video frames transmitted in the current stream.
 */
@property (nonatomic, readonly) NSInteger transmitFrameHeight;
/**
 * Number of video frames transmitted per second in the current stream.
 */
@property (nonatomic, readonly) float transmittedFramesPerSecond;

@end

