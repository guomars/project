#import <UIKit/UIKit.h>

#import<sys/utsname.h>
NSString* machineName()
{
    struct utsname systemInfo;
    uname(&systemInfo);
    
    return [NSString stringWithCString:systemInfo.machine encoding:NSUTF8StringEncoding];
}


// Under iOS and the Simulator, we can use an alternate Accelerometer interface
#import "AccelerometerSimulation.h"
#include "UncaughtExceptionHandler.h"

int main(int argc, char *argv[]) {
    
    NSAutoreleasePool * pool = [[NSAutoreleasePool alloc] init];
    
    /*
    struct utsname systemInfo;
    uname(&systemInfo);
    
    int nDevice = -1; // 0:iPad, 1: iPhone4 2:iPhone5
    
    NSString* strMachineName = [NSString stringWithCString:systemInfo.machine encoding:NSUTF8StringEncoding];
    if([strMachineName rangeOfString:@"iPhone5"].length > 0 ||
       [strMachineName rangeOfString:@"iPhone6"].length > 0 )
    {
        nDevice = 2;
    }
    else if([strMachineName rangeOfString:@"iPhone4"].length > 0||
            [strMachineName rangeOfString:@"iPhone3"].length > 0)
    {
        nDevice = 1;
    }
    else if([strMachineName rangeOfString:@"iPad"].length > 0)
    {
        nDevice = 0;
    }
    */
    
    InstallUncaughtExceptionHandler();
    
    int retVal = UIApplicationMain(argc, argv, nil, @"AppController");
    
    
    [pool release];
    return retVal;
}
