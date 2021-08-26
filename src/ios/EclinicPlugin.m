/********* EclinicPlugin.m Cordova Plugin Implementation *******/

#import <Cordova/CDV.h>
#import "FirstViewController.h"
#import "MyGJController.h"
#import <UIKit/UIKit.h>
#import <JabberGuest/JabberGuest.h>
// #import "JabberGuest.h"
#import <AVFoundation/AVFoundation.h>

//--------------- Modify NSBunle behavior -------------
#import <Foundation/Foundation.h>


@interface NSBundle (Language)
+(void)setLanguage:(NSString*)language;
@end

#import <objc/runtime.h>

static const char _bundle=0;

@interface BundleEx : NSBundle
@end

@implementation BundleEx
-(NSString*)localizedStringForKey:(NSString *)key value:(NSString *)value table:(NSString *)tableName
{
    NSBundle* bundle=objc_getAssociatedObject(self, &_bundle);
    return bundle ? [bundle localizedStringForKey:key value:value table:tableName] : [super localizedStringForKey:key value:value table:tableName];
}
@end

@implementation NSBundle (Language)
+(void)setLanguage:(NSString*)language
{
    static dispatch_once_t onceToken;
    dispatch_once(&onceToken, ^
    {
        object_setClass([NSBundle mainBundle],[BundleEx class]);
    });
    objc_setAssociatedObject([NSBundle mainBundle], &_bundle, language ? [NSBundle bundleWithPath:[[NSBundle mainBundle] pathForResource:language ofType:@"lproj"]] : nil, OBJC_ASSOCIATION_RETAIN_NONATOMIC);
}
@end
//--------------- Demo ---------------------------------

static BOOL hasError;
@interface EclinicPlugin : CDVPlugin <CJGuestCallViewControllerDelegate,UINavigationControllerDelegate> {
    MyGJController * jabberG;
    NSString* callbackId;

}




@property (strong) UIViewController* CallController;
- (void)new_activity:(CDVInvokedUrlCommand*)command;
@end

@implementation EclinicPlugin

- (void)new_activity:(CDVInvokedUrlCommand*)command
{
    
  
   
   
   
    [[NSNotificationCenter defaultCenter] addObserver:self selector:@selector(handleError:) name:CJGuestCallErrorNotification object:nil];
    hasError= false;
    self->callbackId =command.callbackId;
    [self showAlert:command];

//    CDVPluginResult* pluginResult = nil;
       // NSString* server = [command.arguments objectAtIndex:0];
      //  NSString* address = [command.arguments objectAtIndex:1];
        
//
//    if (echo != nil && [echo length] > 0) {
//        pluginResult = [CDVPluginResult resultWithStatus:CDVCommandStatus_OK messageAsString:echo];
//    } else {
//        pluginResult = [CDVPluginResult resultWithStatus:CDVCommandStatus_ERROR];
//    }
//
//    [self.commandDelegate sendPluginResult:pluginResult callbackId:command.callbackId];
}
- (void)isAuthorized:(CDVInvokedUrlCommand*)command
{
    
    CDVPluginResult* pluginResult = nil;
       
        

    if ([self hasAllPermissions]) {
        pluginResult = [CDVPluginResult resultWithStatus:CDVCommandStatus_OK messageAsString:@"Authorized"];
    } else {
        pluginResult = [CDVPluginResult resultWithStatus:CDVCommandStatus_ERROR messageAsString:@"Not Authorized"];
    }

    [self.commandDelegate sendPluginResult:pluginResult callbackId:command.callbackId];
}
- (BOOL)hasAllPermissions
{
    AVAuthorizationStatus hasCameraPermission = [AVCaptureDevice authorizationStatusForMediaType:AVMediaTypeVideo];
    if(hasCameraPermission != AVAuthorizationStatusAuthorized){
        return false;
    }
    
    if( [[AVAudioSession sharedInstance] recordPermission] !=AVAudioSessionRecordPermissionGranted){
        return false;
    }
    
    return true;
}
- (void)requestPermissions:(CDVInvokedUrlCommand*)command
{
    
    __block CDVPluginResult* pluginResult =  nil;
       
    
    if ([self hasAllPermissions]) {
        pluginResult = [CDVPluginResult resultWithStatus:CDVCommandStatus_OK messageAsString:@"Ok"];
        [self.commandDelegate sendPluginResult:pluginResult callbackId:command.callbackId];
        return;
    } else {
       //check camera if authorize call mic
        [self requestCameraPermissions:command];
        
        
        
       
    }
   
   // [self.commandDelegate sendPluginResult:pluginResult callbackId:command.callbackId];
    
   
}

- (void)requestCameraPermissions:(CDVInvokedUrlCommand*)command
{
   __block CDVPluginResult* pluginResult = nil;
    AVAuthorizationStatus status = [AVCaptureDevice authorizationStatusForMediaType:AVMediaTypeVideo];

    if(status == AVAuthorizationStatusAuthorized) { // authorized
        NSLog(@"camera authorized");
        [self requestMicPermissions:command];
    }
    else if(status == AVAuthorizationStatusDenied){ // denied
        [[UIApplication sharedApplication] openURL:[NSURL URLWithString:UIApplicationOpenSettingsURLString]];
        pluginResult = [CDVPluginResult resultWithStatus:CDVCommandStatus_ERROR messageAsString:@"Camera not authorized"];
        [self.commandDelegate sendPluginResult:pluginResult callbackId:command.callbackId];
        return;
    }
    else if(status == AVAuthorizationStatusRestricted){ // restricted
        [[UIApplication sharedApplication] openURL:[NSURL URLWithString:UIApplicationOpenSettingsURLString]];
        pluginResult = [CDVPluginResult resultWithStatus:CDVCommandStatus_ERROR messageAsString:@"Camera is Restricted"];
        [self.commandDelegate sendPluginResult:pluginResult callbackId:command.callbackId];
        return;
    }
    else if(status == AVAuthorizationStatusNotDetermined){ // not determined

        [AVCaptureDevice requestAccessForMediaType:AVMediaTypeVideo completionHandler:^(BOOL granted) {
            if(granted){ // Access has been granted ..do something
                NSLog(@"camera authorized");
                [self requestMicPermissions:command];
            } else { // Access denied ..do something
                
           pluginResult = [CDVPluginResult resultWithStatus:CDVCommandStatus_ERROR messageAsString:@"Camera permission rejected"];
            [self.commandDelegate sendPluginResult:pluginResult callbackId:command.callbackId];
                return;
            }
        }];
    }
    
}

- (void)requestMicPermissions:(CDVInvokedUrlCommand*)command
{
    __block CDVPluginResult* pluginResult = nil;
    AVAudioSessionRecordPermission Micstatus = [[AVAudioSession sharedInstance] recordPermission] ;

     if(Micstatus == AVAudioSessionRecordPermissionGranted) { // authorized
         NSLog(@"Mic authorized");
         pluginResult = [CDVPluginResult resultWithStatus:CDVCommandStatus_OK messageAsString:@"Ok"];
         [self.commandDelegate sendPluginResult:pluginResult callbackId:command.callbackId];
         return;
     }
     else if(Micstatus == AVAudioSessionRecordPermissionDenied){ // denied
         [[UIApplication sharedApplication] openURL:[NSURL URLWithString:UIApplicationOpenSettingsURLString]];
         pluginResult = [CDVPluginResult resultWithStatus:CDVCommandStatus_ERROR messageAsString:@"Microphone not authorized"];
         [self.commandDelegate sendPluginResult:pluginResult callbackId:command.callbackId];
         return;
     }
     
     else if(Micstatus == AVAudioSessionRecordPermissionUndetermined){ // not determined
        
         [[AVAudioSession sharedInstance] requestRecordPermission:^(BOOL granted){
             if(granted){ // Access has been granted ..do something
                 NSLog(@"Microphone authorized");
                 pluginResult = [CDVPluginResult resultWithStatus:CDVCommandStatus_OK messageAsString:@"Ok"];
                 [self.commandDelegate sendPluginResult:pluginResult callbackId:command.callbackId];
                 return;
             } else { // Access denied ..do something
                 
            pluginResult = [CDVPluginResult resultWithStatus:CDVCommandStatus_ERROR messageAsString:@"Microphone permission rejected"];
            [self.commandDelegate sendPluginResult:pluginResult callbackId:command.callbackId];
                 return;
             }
         }];
     }
    
}




- (void)showAlert:(CDVInvokedUrlCommand*)command  {

    NSDictionary* _args=  [command argumentAtIndex:0 withDefault:nil];
    
    NSString* _server = _args[@"server"];
   // NSString* _server =  [command argumentAtIndex:0 withDefault:nil];
   
    NSString* _address =_args[@"address"];
	NSString* _lang =_args[@"language"];
	NSString * _langlower = [_lang lowercaseString];
	
	// NSString* path= [[NSBundle mainBundle] pathForResource:@"ar" ofType:@"lproj"]; 

	// NSBundle* languageBundle = [NSBundle bundleWithPath:path];
	
	if ([_langlower containsString:@"en"]) {
	  [[NSUserDefaults standardUserDefaults] setObject:[NSArray arrayWithObjects:@"en", nil] forKey:@"AppleLanguages"];
	  [NSBundle setLanguage:@"en"];
	  NSLog(@"en selected");
	} else {
	 [NSBundle setLanguage:@"ar"];
	  NSLog(@"ar selected");
	    [[NSUserDefaults standardUserDefaults] setObject:[NSArray arrayWithObjects:@"ar", nil] forKey:@"AppleLanguages"];
	}

   [[NSUserDefaults standardUserDefaults] synchronize]; //to make the change immediate
   
	// AppDelegate *delegate = [[UIApplication sharedApplication] delegate];
    // NSString *storyboardName = @"Main";
    // UIStoryboard *storybaord = [UIStoryboard storyboardWithName:storyboardName bundle:nil];
    // delegate.window.rootViewController = [storybaord instantiateInitialViewController];
   
   // refresh
	   NSArray *windows = [UIApplication sharedApplication].windows;
		for (UIWindow *window in windows) {
			for (UIView *view in window.subviews) {
			[view removeFromSuperview];
			[window addSubview:view];
		}
	}
   
   //end
   
     
    dispatch_async(dispatch_get_main_queue(), ^{
        //code
      //  CJGuestCallViewController *
       // jabberG = [[CJGuestCallViewController alloc] init];
        jabberG = [[MyGJController alloc] init ];
        if (jabberG) {

           // [jabberG setServerName:@"telemedicine.cchmc.org"];
          //  [jabberG setToURI:@"device.test"];
             [jabberG setServerName:_server];
             [jabberG setToURI:_address];
            jabberG.delegate = self;
            jabberG.callbackId = callbackId;
            jabberG.webView = self.webView;

            //        UIBarButtonItem * backButton = [[UIBarButtonItem alloc] initWithTitle:@"Back"
            //                                                                           style:UIBarButtonItemStyleBordered
            //                                                                          target:nil
            //                                                                          action:nil];
            jabberG.modalPresentationStyle = UIModalPresentationFullScreen;
         
            
            
            [self.viewController presentViewController:jabberG animated:YES completion:nil];

          //[self.viewController presentViewController:jabberG animated:YES completion:nil];
            
 }

    
    
   
       
        
       
        });
    
    

    
    

   
    

}
- (void)didReceiveMemoryWarning
{
   // [super didReceiveMemoryWarning];
    // Dispose of any resources that can be recreated.
}

- (void)callFinishedForCallController:(CJGuestCallViewController *)callController
{
    if(!hasError){
        
        __weak CJGuestCallViewController* jabberGCall = jabberG;
        __weak EclinicPlugin* weakSelf = self;

        dispatch_block_t invoke = ^ (void) {
            CDVPluginResult* result;
            
                result = [CDVPluginResult resultWithStatus:CDVCommandStatus_OK messageAsString:@"Call finished"];
            


           // [weakSelf.commandDelegate sendPluginResult:result callbackId:jabberGCall.callbackId];
            [weakSelf.commandDelegate sendPluginResult:result callbackId:self->callbackId];

            
        };

        [[jabberGCall presentingViewController] dismissViewControllerAnimated:YES completion:invoke];
       
    }
    
}


- (void)handleError:(NSNotification *)notification
   {
       if(!hasError){
           NSError * error = [[notification userInfo] valueForKey:CJGuestCallErrorKey];
           
           hasError = true;
           __weak CJGuestCallViewController* jabberGCall = jabberG;
           __weak EclinicPlugin* weakSelf = self;
           NSString * errorstring =[NSString stringWithFormat:@"%s",error.localizedDescription.UTF8String];
           dispatch_block_t invoke = ^ (void) {
               CDVPluginResult* result;

                   result = [CDVPluginResult resultWithStatus:CDVCommandStatus_ERROR messageAsString:errorstring];



              // [weakSelf.commandDelegate sendPluginResult:result callbackId:jabberGCall.callbackId];
               [weakSelf.commandDelegate sendPluginResult:result callbackId:self->callbackId ];


           };

           [[jabberGCall presentingViewController] dismissViewControllerAnimated:YES completion:invoke];
           NSLog(@"Jabber Guest error: %s", error.localizedDescription.UTF8String);
       }
       
   }




    @end
