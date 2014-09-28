//
//  FMLayerWebView.mm
//  GPhoneDevice
//
//  Created by wmgj on 13-6-17.
//
//

#include "FMLayerWebView.h"

#include "FMUIWebViewBridge.h"
//#include "GWebManager.h"


#import <sys/socket.h>
#import <netinet/in.h>
#import <arpa/inet.h>
#import <netdb.h>
#import <SystemConfiguration/SCNetworkReachability.h>
#include <ifaddrs.h>



static FMUIWebViewBridge *g_FMUIWebViewBridge=nil;

FMLayerWebView* FMLayerWebView::create(const char * url)
{
    FMLayerWebView *pRet = new FMLayerWebView();
    if (pRet && pRet->init(url))
    {
        pRet->autorelease();
        return pRet;
    }
    else
    {
        delete pRet;
        pRet = NULL;
        return NULL;
    }
}


FMLayerWebView::FMLayerWebView(){
    
}



FMLayerWebView::~FMLayerWebView(){
    
    [g_FMUIWebViewBridge release];
    
}

void FMLayerWebView::onThirdPartLogin(std::string & userid, std::string & agent, std::string & ticket)
{
    //GWebManager::GetInstance()->OnThirdPartLogin(userid, agent, ticket);
}

void FMLayerWebView::quitView()
{
    [g_FMUIWebViewBridge quitView];
}

void FMLayerWebView::webViewDidFinishLoad(){
    NSString *title = [[g_FMUIWebViewBridge getWebView] stringByEvaluatingJavaScriptFromString:@"document.title"];
    
    //if ([title isEqualToString:@"完美世界旗下游戏"])
    {
        NSString *tcontent = [[g_FMUIWebViewBridge getWebView] stringByEvaluatingJavaScriptFromString:@"document.documentElement.innerHTML"];
        const char * pcontent = [tcontent UTF8String];
        std::string content = pcontent;
        std::string ticket,agent,userid;
        std::string::size_type ticket_pos = content.find("\"ticket\"");
        if (ticket_pos != std::string::npos) {
            std::string::size_type value_pos_b = content.find("value=", ticket_pos);
            std::string::size_type value_pos_e = content.find("\"", value_pos_b+7);
            ticket = content.substr(value_pos_b+7, value_pos_e-value_pos_b-7);
        }
        std::string::size_type agent_pos = content.find("\"agent\"");
        if (agent_pos != std::string::npos) {
            std::string::size_type value_pos_b = content.find("value=", agent_pos);
            std::string::size_type value_pos_e = content.find("\"", value_pos_b+7);
            agent = content.substr(value_pos_b+7, value_pos_e-value_pos_b-7);
        }
        std::string::size_type userid_pos = content.find("\"userId\"");
        if (userid_pos != std::string::npos) {
            std::string::size_type value_pos_b = content.find("value=", userid_pos);
            std::string::size_type value_pos_e = content.find("\"", value_pos_b+7);
            userid = content.substr(value_pos_b+7, value_pos_e-value_pos_b-7);
        }
        if (ticket_pos != std::string::npos && agent_pos != std::string::npos && userid_pos != std::string::npos) {
            printf("userid = %s agent=%s ticked=%s \n", userid.c_str(), agent.c_str(), ticket.c_str());
            onThirdPartLogin(userid, agent, ticket);
            //printf("content = %s \n", [tcontent UTF8String]);
        }
        //printf("content = %s \n", [content UTF8String]);
    }
    
}



void FMLayerWebView::onBackbuttonClick(){
    
    this->removeFromParentAndCleanup(true);
    
}



bool FMLayerWebView::init(const char * url){
    
    if ( !CCLayer::init() ){
        
        return false;
        
    }
    
    g_FMUIWebViewBridge = [[FMUIWebViewBridge alloc] init];
    
    [g_FMUIWebViewBridge setLayerWebView : this URLString:url];
    
    return true;
    
}

bool FMLayerWebView::connectedToNetwork(int& ntype)
{
    struct sockaddr_in zeroAddress;
    
    bzero(&zeroAddress, sizeof(zeroAddress));
    
    zeroAddress.sin_len = sizeof(zeroAddress);
    
    zeroAddress.sin_family = AF_INET;
    
    // Recover reachability flags
    
    SCNetworkReachabilityRef defaultRouteReachability = SCNetworkReachabilityCreateWithAddress(NULL, (struct sockaddr *)&zeroAddress);
    
    SCNetworkReachabilityFlags flags;
    
    BOOL didRetrieveFlags = SCNetworkReachabilityGetFlags(defaultRouteReachability, &flags);
    
    CFRelease(defaultRouteReachability);
    
    
    if (!didRetrieveFlags)
    {
        return NO;
    }
    
    BOOL isReachable = flags & kSCNetworkFlagsReachable;
    
    BOOL needsConnection = flags & kSCNetworkFlagsConnectionRequired;
    
    BOOL ret = (isReachable && !needsConnection) ? YES : NO;
    ntype = 0;
    
    if(ret)
    {
       // ntype = getnetworkType();
        
        if ((flags & kSCNetworkReachabilityFlagsReachable) == 0)            
        {            
            ntype = 0; // no network            
        }        
     
        if ((flags & kSCNetworkReachabilityFlagsConnectionRequired) == 0)            
        {            
            // if target host is reachable and no connection is required            
            //  then we'll assume (for now) that your on Wi-Fi            
            ntype = 1; // wifi            
        }
        
        if ((((flags & kSCNetworkReachabilityFlagsConnectionOnDemand ) != 0) ||             
             (flags & kSCNetworkReachabilityFlagsConnectionOnTraffic) != 0))            
        {            
            // ... and the connection is on-demand (or on-traffic) if the            
            //     calling application is using the CFSocketStream or higher APIs            
            if ((flags & kSCNetworkReachabilityFlagsInterventionRequired) == 0)                
            {                
                // ... and no [user] intervention is needed
                
                ntype = 1; // wifi                
            }
        }
        if ((flags & kSCNetworkReachabilityFlagsIsWWAN) == kSCNetworkReachabilityFlagsIsWWAN)            
        {
            if((flags & kSCNetworkReachabilityFlagsReachable) == kSCNetworkReachabilityFlagsReachable) {
                if ((flags & kSCNetworkReachabilityFlagsTransientConnection) == kSCNetworkReachabilityFlagsTransientConnection) {
                    ntype = 3; // 3G
                    if((flags & kSCNetworkReachabilityFlagsConnectionRequired) == kSCNetworkReachabilityFlagsConnectionRequired) {
                        ntype = 2; // 2G
                    }     
                }                 
            }            
        }
    }
    return ret;
}
int FMLayerWebView::getnetworkType()
{
    int ret = 0;
    struct ifaddrs * first_ifaddr, * current_ifaddr;
    NSMutableArray* activeInterfaceNames = [[NSMutableArray alloc] init];
    getifaddrs( &first_ifaddr );
    current_ifaddr = first_ifaddr;
    while( current_ifaddr!=NULL )
    {
        if( current_ifaddr->ifa_addr->sa_family == AF_INET )
        {
            [activeInterfaceNames addObject:[NSString stringWithFormat:@"%s", current_ifaddr->ifa_name]];
        }
        current_ifaddr = current_ifaddr->ifa_next;
    }
    if( [activeInterfaceNames containsObject:@"en0"] )
        ret = 1;
    else if( [activeInterfaceNames containsObject:@"en1"])
        ret = 2;
    
    [activeInterfaceNames release];
    return ret;
}