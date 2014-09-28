//
//  GPhoneDeviceAppController.h
//  GPhoneDevice
//
//  Created by guomars on 13-5-23.
//  Copyright __MyCompanyName__ 2013年. All rights reserved.
//

@class RootViewController;

@interface AppController : NSObject <UIAccelerometerDelegate, UIAlertViewDelegate, UITextFieldDelegate,UIApplicationDelegate> {
    UIWindow *window;
    RootViewController    *viewController;
}

@property (nonatomic, retain) UIWindow *window;
@property (nonatomic, retain) RootViewController *viewController;

@end

@interface UIImagePickerController (Nonrotating)
- (BOOL)shouldAutorotate;
@end