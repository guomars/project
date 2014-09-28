#ifndef __LOGINSCENE_H__
#define __LOGINSCENE_H__

#include "cocos2d.h"
#include "CocoGUILIB/BaseClasses/UIWidget.h"
#include "CocoGUILIB/UIWidgets/UINodeContainer.h"
#include "CocoGUILIB/System/UILayer.h"
#include "CocoGUILIB/System/UIHelper.h"
#include "GUI/CCEditBox/CCEditBox.h"
#include "network/HttpClient.h"
#include "ActionStubs.h"

USING_NS_CC;
USING_NS_CC_EXT;
using namespace std;

class LoginScene : public CCLayerColor
{
	bool _init();

public:
	virtual bool init();

	virtual void onExit();

	static CCScene* scene();

	CREATE_FUNC(LoginScene);

	void Update(float dt);

	void IOSelect(float dt);

	void StartPatching();

	void PatchingUpdate(float dt);

	void OnBtnLogin(CCObject* sender);					// "登陆" 按钮
	void OnBtnGenRandName(CCObject* sender);	// "随机" 按钮
	void OnBtnOK(CCObject* sender);						// 创建角色界面 "确定" 按钮
	void OnBtnCancel(CCObject* sender);				// 创建角色界面 "取消" 按钮

	void OnBtnReConnect(CCObject* sender);			// 重新连接

	void SendLoginCmd();			// 发送登陆连接请求

	void JumpToCreateRolePage();
	void JumpToLoginPage();

	// just for test
	void OnBtnDanjiMode(CCObject* sender);

	void onHttpRequestGetUpdateInfo(CCHttpClient *sender, CCHttpResponse *response);

	void OnBtnNoticeClose(CCObject* sender);

	UIWidget* m_pLoginWidget;
	UIWidget* m_pCreateRoleWidget;
	UIWidget* m_pNoticeWidget;					// 更新公告
	UIWidget* m_pLostConnectWidget;			// 无法连接服务器弹出框

	cocos2d::extension::CCEditBox* m_pInputNameEditBox;

	UIHelper m_uiSystem;

	UILayer* m_pUILayer;

	aeditor::ActionTemplateTable* m_actionRunner;

	// data from config.xml
	std::string m_strIP;
	int m_nPort;
	std::string m_strUpdateInfoUrl;
	std::string m_strPatchUrl;
};

#endif
