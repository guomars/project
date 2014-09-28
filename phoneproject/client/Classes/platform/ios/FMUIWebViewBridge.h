#import <Foundation/Foundation.h>

#import <CoreLocation/CoreLocation.h>

#import <UIKit/UIKit.h>



#import "FMLayerWebView.h"



@interface FMUIWebViewBridge : NSObject<UIWebViewDelegate,UIAlertViewDelegate>{
    
    FMLayerWebView * mLayerWebView;
    
    UIView    *mView;
    
    UIWebView *mWebView;
    
    UIToolbar *mToolbar;
    
    UIBarButtonItem *mBackButton;
    
}

-(UIWebView *) getWebView;

-(void) setLayerWebView : (FMLayerWebView*) iLayerWebView URLString:(const char*) urlString;

-(void) backClicked:(id)sender;

-(void) quitView;

@end
