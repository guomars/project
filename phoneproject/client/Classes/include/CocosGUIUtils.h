#ifndef __COCOSGUIUTILS_H__
#define __COCOSGUIUTILS_H__

// 此文件定义了一些CocosGUI简易的接口

#include "cocos2d.h"
#include "CocoGUILIB/BaseClasses/UIWidget.h"

USING_NS_CC;
USING_NS_CC_EXT;

CCSprite* CreateStrideLabelContainer(const char* szText, int fontSize, const ccColor3B& color = ccc3(0xff, 0xff, 0xff), const ccColor3B& strideColor = ccc3(0, 0, 0), const CCPoint& anchor = ccp(0,0));
void SetMultiColorLabelText(UIWidget* pRoot, const char* szLabelName, const char* szText);
void SetWidgetAnchorPoint(UIWidget* pRoot, const char* szName, CCPoint vAnchorPoint);
void SetLabelColor(UIWidget* pRoot, const char* szLabelName, const ccColor3B& color);
void SetTextAreaText(UIWidget* pRoot, const char* szName, const char* szText);

void SetLabelText(UIWidget* pRoot, const char* szLabelName, const char* szText);
void SetLabelTextWithInt(UIWidget* pRoot, const char* szLabelName, int nNumber, bool bAnim = true);
void SetLabelTextWithIntSign(UIWidget* pRoot, const char* szLabelName, int nNumber);
int GetLabelValue(UIWidget* pRoot, const char* szLabelName);

void SetLabelAtlasText(UIWidget* pRoot, const char* szLabelName, const char* szText);
void SetLabelAtlasTextWithInt(UIWidget* pRoot, const char* szLabelName, int nNumber);

void SetProgressBarPercent(UIWidget* pRoot, const char* szPBName, int nPercent);
void HideWidget(UIWidget* pRoot, const char* szName);	
void ShowWidget(UIWidget* pRoot, const char* szName);
void SetTabHighlight(UIWidget* pRoot, const char* szTabBtn, const char* szHighlightPic);
void SetWidgetTag(UIWidget* pRoot, const char* szName, int tag);

void EnableWidget(UIWidget* pRoot, const char* szName);
void DisableWidget(UIWidget* pRoot, const char* szName);
CCPoint GetWidgetPosition(UIWidget* pRoot, const char* szName);

void AddEffectToWidget(UIWidget* pRoot, const char* szWidgetName, const char* szEffectName);

void AddDynamicDigitLabel(UIWidget* pRoot, const char* szLabelName, float fDuration, int nBeginValue, int nEndValue);

void RunProgressBarEffect(CCProgressTimer* progressTimer, float fDestPercent);

// font_ui.xml
void SetWidgetName2Font(const char* pFileName);

UIWidget* CreateWidgetFromJsonFile(const char* pFileName);

float CalcCostMS(char* str = "");
float CalcCostMS2(int index,char* str);

//void RestoreUISystemTouch(cs::CCNode* pUiSystemContainer);

//void CloseUISystemTouch(cs::CCNode* pUiSystemContainer);

#endif