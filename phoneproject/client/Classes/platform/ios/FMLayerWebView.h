//
//  FMLayerWebView.h
//  GPhoneDevice
//
//  Created by wmgj on 13-6-17.
//
//

#ifndef WebViewDemo_FMLayerWebView_h

#define WebViewDemo_FMLayerWebView_h



#include "CCCommon.h"

#include "cocos2d.h"

USING_NS_CC;

class FMLayerWebView : public CCLayer{


public:
    
    FMLayerWebView();
    
    ~FMLayerWebView();
    
    virtual bool init(const char * url);
    
    static FMLayerWebView * create(const char * url);
    
    void webViewDidFinishLoad();
    
    void onBackbuttonClick();
    
    void onThirdPartLogin(std::string & userid, std::string & agent, std::string & ticket);
    
    void quitView();
    
    static bool connectedToNetwork(int& ntype);
    static int getnetworkType();
    
private:
    
    int mWebViewLoadCounter;
    
};  



#endif