#include "LoginScene.h"
#include "Configs.h"
#include "util.h"
#include "CocoGUILIB/System/CocosGUI.h"
#include "CocosGUIUtils.h"

/*class Cocos2dFileReader : public QPLogic::IFileReader{
public:
	virtual char* readFile(const std::string& fileName, long& lSize)
	{
		unsigned long size = 0;
		char* pBuffer = (char*)cocos2d::CCFileUtils::sharedFileUtils()->getFileData(fileName.c_str(), "rb", &size);

		lSize = size;

		return pBuffer;
	}
};*/

std::string s_patch_1("<fsize=32><fdef=ui/font_wenzi.xml><c=0xFFFFFF>patch file, check network!");
std::string s_patch_2("<fsize=32><fdef=ui/font_wenzi.xml><c=0xFFFFFF>loading patch list ...");
std::string s_patch_3("<fsize=32><fdef=ui/font_wenzi.xml><c=0xFFFFFF>cur patching: %s - %2.1f (%d/%d)");

CCScene* l_loginScene;
CCScene* LoginScene::scene()
{
	CCScene * scene = NULL;
	do 
	{
		scene = CCScene::create();
		l_loginScene = scene;
		CC_BREAK_IF(! scene);
		LoginScene *layer = LoginScene::create();
		CC_BREAK_IF(! layer);
		scene->addChild(layer);

	} while (0);

	return scene;
}

void LoginScene::onExit() {
	CCLayer::onExit();
//	m_uiSystem.cleanUIScene();
}

bool LoginScene::_init()
{
	{
		std::string fullPath = cocos2d::CCFileUtils::sharedFileUtils()->fullPathForFilename("client.cfg");
	}

	{
		//random dynamic card
		int nRandCardID = 888888; //401 + ((int)(100000*CCRANDOM_0_1()))%13;

		//UINodeContainer* pContainer = (UINodeContainer*)CCUIHELPER->seekWidgetByName(m_pLoginWidget, "login_dcard");
		//pContainer->addCCNode(pDynamicCard);
	}

	{
		// 默认创建一个随机名字
		//g_pPlayerData->strName = g_pCfgProxy->RandName();
		//m_pInputNameEditBox->setText(g_pPlayerData->strName.c_str());
	}

	return true;
}

bool LoginScene::init()
{
	//m_KpPatcher = NULL;
	bool bRet = false;
	do 
	{
		//g_ae_isSoundOn = g_pPlayerData->m_bSoundOn;

//		UISystem::setUISystem(&m_uiSystem);
		CC_BREAK_IF(! CCLayerColor::initWithColor(ccc4(0,0,0,255)));

//		COCOUISYSTEM->resetSystem(this,1);
		m_pUILayer = UILayer::create();
		m_pUILayer->scheduleUpdate();
		this->addChild(m_pUILayer);

		m_actionRunner = aeditor::ActionTemplateTable::create("aeditor/template.xml", l_loginScene);
		//m_actionRunner->SetPlaySpeed(g_pPlayerData->m_fGameSpeed);

		//========================================== bg json
// 		m_pBgWidget = CreateWidgetFromJsonFile(GET_PATH(PATH_UI, "dcard.json"));
// 		m_pBgWidget->setName("dcard");
// 		m_pUILayer->addWidget(m_pBgWidget);
// 		m_pBgWidget->setPosition(ccp(g_winSize.width/2, g_winSize.height/2));

		//random dynamic card
// 		int nRandCardID = 888888; //401 + ((int)(100000*CCRANDOM_0_1()))%13;
// 		DynamicCard* pDynamicCard = DynamicCard::create(nRandCardID);
// 		pDynamicCard->setAnchorPoint(ccp(0.0f, 0.0f));
// 		pDynamicCard->ShowBorder(false);
// 		pDynamicCard->setScale(2.0f);
// 
// 		UINodeContainer* pContainer = UINodeContainer::create();
// 		pContainer->addCCNode(pDynamicCard);
// 		pContainer->setWidgetZOrder(-1);
// 
// 		m_pBgWidget->addChild(pContainer);

		//========================================== login json
		m_pLoginWidget = CreateWidgetFromJsonFile(GET_PATH(PATH_UI, "login.json"));
		m_pLoginWidget->setName("login");
		m_pUILayer->addWidget(m_pLoginWidget);
		m_pLoginWidget->setPosition(ccp(g_winSize.width/2, g_winSize.height/2));

		// move to _init()
/*
		//random dynamic card
		int nRandCardID = 888888; //401 + ((int)(100000*CCRANDOM_0_1()))%13;
		DynamicCard* pDynamicCard = DynamicCard::create(nRandCardID);
		pDynamicCard->setAnchorPoint(ccp(0.0f, 0.0f));
		pDynamicCard->ShowBorder(false);
		pDynamicCard->setScale(2.0f);

		UINodeContainer* pContainer = (UINodeContainer*)CCUIHELPER->seekWidgetByName(m_pLoginWidget, "login_dcard");
		pContainer->addCCNode(pDynamicCard);
*/		
		UIButton* pBtn = (UIButton*)(CCUIHELPER->seekWidgetByName(m_pLoginWidget, "login_button_login"));
		pBtn->addReleaseEvent(this, coco_releaseselector(LoginScene::OnBtnLogin));

		// load ip from config.xml
		/*XmlConfig config;
		config.Reload("config.xml");
		const XmlConfig::Node * pRoot = config.Root();
		if ( !pRoot )
		{
			CCLOG("LoginScene::OnBtnLogin failed, can't load file:  config.xml");
			return false;
		}

		// ip
		const XmlConfig::Node* pNode = pRoot->GetFirstChild("ip");
		if(pNode)
		{
			pNode->GetStrAttr("address", m_strIP);
			pNode->GetIntAttr("port", &m_nPort);
		}

		pNode = pRoot->GetFirstChild("updateinfo");
		if(pNode)
		{
			pNode->GetStrAttr("url", m_strUpdateInfoUrl);
		}

		pNode = pRoot->GetFirstChild("patch");
		if(pNode)
		{
			pNode->GetStrAttr("url", m_strPatchUrl);
		}*/

		// 更新公告
		CCHttpRequest* request = new CCHttpRequest();
		request->setUrl(m_strUpdateInfoUrl.c_str());
		request->setRequestType(CCHttpRequest::kHttpGet);
		request->setResponseCallback(this, httpresponse_selector(LoginScene::onHttpRequestGetUpdateInfo));

		CCHttpClient::getInstance()->send(request);
		request->release();

		//========================================== create role json		
		m_pCreateRoleWidget = CreateWidgetFromJsonFile(GET_PATH(PATH_UI, "createrole.json"));
		m_pCreateRoleWidget->setName("createrole");
		m_pUILayer->addWidget(m_pCreateRoleWidget);
		m_pCreateRoleWidget->setPosition(ccp(g_winSize.width/2, g_winSize.height/2));
		m_pCreateRoleWidget->setVisible(false);

		// 随机名字
		pBtn = (UIButton*)(CCUIHELPER->seekWidgetByName(m_pCreateRoleWidget, "button_randomname"));
		pBtn->addReleaseEvent(this, coco_releaseselector(LoginScene::OnBtnGenRandName));

		// for input player name
		UINodeContainer* container = UINodeContainer::create();
		m_pInputNameEditBox = CCEditBox::create(CCSizeMake(400, 60), CCScale9Sprite::create(GET_PATH(PATH_UI, "sliderballnormal.png"))); // 200 50
		m_pInputNameEditBox->setMaxLength(8);
		container->addCCNode(m_pInputNameEditBox);
		container->setPosition(ccp(0, 150)); // 330 150
		container->setWidgetZOrder(100);
		m_pCreateRoleWidget->addChild(container);

		// move to _init()
/*
		// 默认创建一个随机名字
		g_pPlayerData->strName = g_pCfgProxy->RandName();
		m_pInputNameEditBox->setText(g_pPlayerData->strName.c_str());
*/
		// ok
		pBtn = (UIButton*)(CCUIHELPER->seekWidgetByName(m_pCreateRoleWidget, "button_sure"));
		pBtn->addReleaseEvent(this, coco_releaseselector(LoginScene::OnBtnOK));

		// cancel
		pBtn = (UIButton*)(CCUIHELPER->seekWidgetByName(m_pCreateRoleWidget, "button_cancel"));
		pBtn->addReleaseEvent(this, coco_releaseselector(LoginScene::OnBtnCancel));

//		单机测试模式，暂时取消；
// 		UIButton* danjiTestButton = (UIButton*)(CCUIHELPER->seekWidgetByName(m_pCreateRoleWidget, "button_test"));
// 		danjiTestButton->addReleaseEvent(this, coco_releaseselector(LoginScene::OnBtnDanjiMode));

// 		if(g_pPlayerData->m_nDevice == DEVICE_IPAD)
// 			SetLabelText("login_txt_serversname", "iPad");
// 		else if(g_pPlayerData->m_nDevice == DEVICE_IPHONE4)
// 			SetLabelText("login_txt_serversname", "iPhone4");
// 		else if(g_pPlayerData->m_nDevice == DEVICE_IPHONE5)
// 			SetLabelText("login_txt_serversname", "iPhone5");

		// after patched. 
		HideWidget(m_pLoginWidget, "login_button_login");
		HideWidget(m_pLoginWidget, "login_button_servers");
		HideWidget(m_pLoginWidget, "login_name_loading");

		//========================================== notice json 公告		
		m_pNoticeWidget = CreateWidgetFromJsonFile(GET_PATH(PATH_UI, "notice.json"));
		m_pNoticeWidget->setName("notice");
		m_pUILayer->addWidget(m_pNoticeWidget);
		m_pNoticeWidget->setWidgetZOrder(20);
		m_pNoticeWidget->setPosition(ccp(g_winSize.width/2, g_winSize.height/2));
//		m_pNoticeWidget->setVisible(false);

		pBtn = (UIButton*)(CCUIHELPER->seekWidgetByName(m_pNoticeWidget, "notice_button_sure"));
		pBtn->addReleaseEvent(this, coco_releaseselector(LoginScene::OnBtnNoticeClose));

		//============================================ 无法连接服务器 弹出框
		m_pLostConnectWidget = CreateWidgetFromJsonFile(GET_PATH(PATH_UI, "tanchu1.json"));
		m_pLostConnectWidget->setName("lostconnect");
		m_pUILayer->addWidget(m_pLostConnectWidget);
		m_pLostConnectWidget->setPosition(ccp(g_winSize.width/2, g_winSize.height/2));

		SetWidgetAnchorPoint(m_pLostConnectWidget, "tc1_container", ccp(0.5f, 0.5f));

		pBtn = (UIButton*)(CCUIHELPER->seekWidgetByName(m_pLostConnectWidget, "tc1_button_ok"));
		pBtn->addReleaseEvent(this, coco_releaseselector(LoginScene::OnBtnReConnect));

		m_pLostConnectWidget->setVisible(false);

		//PLAY_MUSIC("login_bg.mp3");

		//StartPatching();
		bRet = true;
	}while(0);
	return bRet;
}

void LoginScene::IOSelect(float dt)
{
	/*if(QAuthc::instance().GetState() == QAuthc::ESTATE_IO_CLOSED) // 已关闭
	{
		// 弹出对话框
		m_pLostConnectWidget->setVisible(true);

		// 隐藏 “正在连接服务器”
		HideWidget(m_pLoginWidget, "login_name_loading");
	}

	QAuthc::instance().Run();*/
}

static void LoadString(const char *name, std::vector<std::string>& vStr)
{
	unsigned long size;
	const char* urls_data = (char*)(cocos2d::CCFileUtils::sharedFileUtils()->getFileData(name,"rb" , &size));
	for (size_t i = 0, start = 0; i < size; ++i) {
		if (urls_data[i] == '\n') {
			size_t end = i > 0 && urls_data[i-1] == '\r' ? i - 1 : i;
			vStr.push_back(std::string(urls_data + start, end - start));
			start = i + 1;
		} else if (i == size - 1) {
			size_t end = size;
			vStr.push_back(std::string(urls_data + start, end - start));
		}
	}
	delete urls_data;
}

/*void LoginScene::StartPatching()
{
	CC_SAFE_DELETE(m_KpPatcher);

//	ShowWidget(m_pLoginWidget, "cr_name_loading");
	ShowWidget(m_pLoginWidget, "login_name_update");
	HideWidget(m_pLoginWidget, "login_img_loginprobase");
	ShowWidget(m_pLoginWidget, "login_img_loginpro1");
	ShowWidget(m_pLoginWidget, "login_pro_loginpro2");

	std::vector<std::string> urls;
	LoadString("patch_urls.txt", urls);

	if (urls.size() == 0) { // add test url
		urls.push_back(m_strPatchUrl);
	}

	{
		std::vector<std::string> tips;
		LoadString("patch_strs.txt", tips);
		if (tips.size() >= 3)
		{
			s_patch_1 = tips[0];
			s_patch_2 = tips[1];
			s_patch_3 = tips[2];
		}
	}

#ifdef WIN32
	m_KpPatcher = new cocos2d::kp::KpPatcher("./", "../Documents", "../tmp", urls);
#elif (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
	std::string docDir = CCFileUtils::sharedFileUtils()->getWritablePath();
    std::string tmpDir = docDir + "tmp/";
	MakeDir(tmpDir.c_str(), tmpDir.size());
    m_KpPatcher = new cocos2d::kp::KpPatcher("", docDir.c_str(), tmpDir.c_str(), urls);
#else
    std::string docDir = CCFileUtils::sharedFileUtils()->getWritablePath();
    std::string tmpDir = docDir + "../tmp/";
    std::string appDir = docDir + "../mokachuanshuo.app/";
    m_KpPatcher = new cocos2d::kp::KpPatcher(appDir.c_str(), docDir.c_str(), tmpDir.c_str(), urls);
#endif
	m_KpPatcher->StartPatching();

	schedule( schedule_selector(LoginScene::PatchingUpdate), 0.01f);
}

void LoginScene::PatchingUpdate(float dt)
{
	char szBuff[256];
	cocos2d::kp::PatchProgress pp;
	int state = m_KpPatcher->UpdateState(pp);
	if (state == cocos2d::kp::KpPatcher::ESTATE_FAIL) {
		ShowWidget(m_pLoginWidget, "login_name_update");
		unschedule(schedule_selector(LoginScene::PatchingUpdate));
		SetLabelText(m_pLoginWidget, "login_name_update", s_patch_1.c_str());
	} else if (state == cocos2d::kp::KpPatcher::ESTATE_Internal_PatchList) {
		ShowWidget(m_pLoginWidget, "login_name_update");
		SetLabelText(m_pLoginWidget, "login_name_update", s_patch_2.c_str());
	} else if (state == cocos2d::kp::KpPatcher::ESTATE_Internal_Patching) {
		ShowWidget(m_pLoginWidget, "login_name_update");
		sprintf(szBuff, s_patch_3.c_str(), pp.filename.c_str(), pp.progress * (float)100, pp.curPatchNum, pp.totalPatchNum);
		SetLabelText(m_pLoginWidget, "login_name_update", szBuff);

		UILoadingBar* pPro = (UILoadingBar*)(CCUIHELPER->seekWidgetByName(m_pLoginWidget, "login_pro_loginpro2"));
		if (pPro) {
			pPro->setPercent((int)(pp.progress * 100));
		}
	} else if (state == cocos2d::kp::KpPatcher::ESTATE_FAIL_NOT_FIND_PATH) {
		ShowWidget(m_pLoginWidget, "login_name_update");
		// shoud be open the new downloading shop
		// TODO ....
	} else if (state == cocos2d::kp::KpPatcher::ESTATE_SUCCESS) {
		unschedule(schedule_selector(LoginScene::PatchingUpdate));
		HideWidget(m_pLoginWidget, "login_name_loading");
		HideWidget(m_pLoginWidget, "cr_name_loading");
		//HideWidget(m_pLoginWidget, "login_name_update");
		HideWidget(m_pLoginWidget, "login_img_loginprobase");
		HideWidget(m_pLoginWidget, "login_img_loginpro1");
		HideWidget(m_pLoginWidget, "login_pro_loginpro2");

		ShowWidget(m_pLoginWidget, "login_button_login");
		ShowWidget(m_pLoginWidget, "login_button_servers");
//		ShowWidget(m_pLoginWidget, "login_name_loading");

		// after update complete
		{
			sprintf(szBuff, "curVersion:%d", m_KpPatcher->GetVersion());
			SetLabelText(m_pLoginWidget, "login_name_update", szBuff);

			_init();
		}
	}
}*/

void LoginScene::onHttpRequestGetUpdateInfo(CCHttpClient *sender, CCHttpResponse *response)
{
	std::vector<char>* vecResponseData = response->getResponseData();
	if(vecResponseData->size() > 0)
	{
		std::string str((char*)&(*vecResponseData->begin()), vecResponseData->size());
		// BOM
		if (str.length() >= 3 && str[0] == (char)0xEF && str[1] == (char)0xBB && str[2] == (char)0xBF) {
			str = str.substr(3, str.length() - 3);
		}
		int fontSize = 26;
		char szBuff[32];
		sprintf(szBuff, "<fsize=%d>", fontSize);
		str.insert(0, (char*)szBuff);
			
		// 设置公告内容
		SetLabelText(m_pNoticeWidget, "login_txt_notice", str.c_str());

		//str += "\n<c=0xFFFFFF>curVersion:";
		//sprintf(szBuff, "%d\n", m_KpPatcher->GetVersion());
		//str += szBuff;
			
		// 设置公告内容
		SetLabelText(m_pNoticeWidget, "login_txt_notice", str.c_str());

		UIScrollView* pScrollView = dynamic_cast<UIScrollView*>(CCUIHELPER->seekWidgetByName(m_pNoticeWidget, "notice_svbase"));
		UIWidget* pInner = CCUIHELPER->seekWidgetByName(m_pNoticeWidget, "login_txt_notice");
		if (pScrollView != 0 && pInner != 0) {
			pInner->setPosition(ccp(0, max(pScrollView->getContentSize().height, pInner->getContentSize().height) - fontSize / 2));
			pScrollView->setInnerContainerSize(pInner->getContentSize());
		}
		//
	}
}

void LoginScene::OnBtnNoticeClose(CCObject* sender)
{
	PLAY_SOUND("main_button.wav");
	m_pNoticeWidget->setVisible(false);

	// 打开login动画
	std::string strAction = "aeditor/login_01.ue";
	m_actionRunner->RunUIAction(strAction, m_pLoginWidget);
}

void LoginScene::JumpToCreateRolePage()
{
	m_pLoginWidget->setVisible(false);
	m_pCreateRoleWidget->setVisible(true);
}
void LoginScene::JumpToLoginPage()
{
	m_pLoginWidget->setVisible(true);
	m_pCreateRoleWidget->setVisible(false);

	// 显示按钮
//	HideWidget(m_pLoginWidget, "login_name_loading");
// 	ShowWidget(m_pLoginWidget, "login_button_login");
// 	EnableWidget(m_pLoginWidget, "login_button_login");

	// run a cool back action
	float fActionTime = 0.8f;
	UIWidget* pButtonServers = CCUIHELPER->seekWidgetByName(m_pLoginWidget, "login_button_servers");
	CCActionInterval* pMoveToRight = CCEaseBackIn::create(CCMoveBy::create(fActionTime*0.5f, ccp(g_winSize.width, 0)));
	pButtonServers->runAction(pMoveToRight);

	UIWidget* pButtonLogin = CCUIHELPER->seekWidgetByName(m_pLoginWidget, "login_button_login");
	CCActionInterval* pMoveToLeft = CCEaseBackIn::create(CCMoveBy::create(fActionTime*0.5f, ccp(-g_winSize.width, 0)));
	pButtonLogin->runAction(pMoveToLeft);

// 	UIWidget* pPicLoginBase = CCUIHELPER->seekWidgetByName(m_pLoginWidget, "login_pic_loginbase2");
// 	CCActionInterval* pFadeIn = CCFadeIn::create(fActionTime);
// 	pPicLoginBase->runAction(pFadeIn);

	UIWidget* pLoginText = CCUIHELPER->seekWidgetByName(m_pLoginWidget, "login_name_loading");
	CCPoint vDestPos = pLoginText->getPosition();
	pLoginText->setPosition(ccp(vDestPos.x - g_winSize.width, vDestPos.y));
}
void LoginScene::OnBtnLogin(CCObject* sender)
{
	PLAY_SOUND("main_button.wav");
	
	// run a cool action first
	float fActionTime = 0.8f;
	UIWidget* pButtonServers = CCUIHELPER->seekWidgetByName(m_pLoginWidget, "login_button_servers");
	CCActionInterval* pMoveToLeft = CCEaseBackIn::create(CCMoveBy::create(fActionTime*0.5f, ccp(-g_winSize.width, 0)));
	pButtonServers->runAction(pMoveToLeft);

	UIWidget* pButtonLogin = CCUIHELPER->seekWidgetByName(m_pLoginWidget, "login_button_login");
	CCActionInterval* pMoveToRight = CCEaseBackIn::create(CCMoveBy::create(fActionTime*0.5f, ccp(g_winSize.width, 0)));
	pButtonLogin->runAction(pMoveToRight);

// 	UIWidget* pPicLoginBase = CCUIHELPER->seekWidgetByName(m_pLoginWidget, "login_pic_loginbase2");
// 	CCActionInterval* pFadeOut = CCFadeOut::create(fActionTime);
// 	pPicLoginBase->runAction(pFadeOut);

	UIWidget* pLoginText = CCUIHELPER->seekWidgetByName(m_pLoginWidget, "login_name_loading");
	CCPoint vDestPos = pLoginText->getPosition();
	pLoginText->setPosition(ccp(vDestPos.x - g_winSize.width, vDestPos.y));

	CCActionInterval* pTextMoveToLeft = CCEaseBackOut::create(CCMoveTo::create(fActionTime*1.5f, vDestPos));
	CCActionInstant* pSendLoginCmd= CCCallFunc::create(this, callfunc_selector(LoginScene::SendLoginCmd));
	pLoginText->setVisible(true);
	pLoginText->runAction(CCSequence::create(pTextMoveToLeft, pSendLoginCmd, NULL));
}

void LoginScene::SendLoginCmd()
{
	// io connection
	//qp::line::AuthInfo authInfo;

	//QAuthc::instance().Init(&myHandler);
	//QAuthc::instance().Connect(m_strIP, m_nPort);

	schedule( schedule_selector(LoginScene::IOSelect), 0.2f);

	g_bTestMode = false;
}

void LoginScene::OnBtnGenRandName(CCObject* sender)
{
	PLAY_SOUND("main_button.wav");
	//g_pPlayerData->strName = g_pCfgProxy->RandName();
	//m_pInputNameEditBox->setText(g_pPlayerData->strName.c_str());
}

// 创建角色界面 "确定" 按钮
void LoginScene::OnBtnOK(CCObject* sender)
{
	PLAY_SOUND("main_button.wav");
	// create a new user
	/*qp::gs::CreateUser createUser;
	g_pPlayerData->strName = std::string(m_pInputNameEditBox->getText());

	if(g_pPlayerData->strName.size() == 0)	
	{
		g_pPlayerData->strName = g_pCfgProxy->RandName();
	}

	createUser.player_name = QPLogic::UTF8_TO_OCTETS(g_pPlayerData->strName);
	bool bSend = QAuthc::instance().Send(createUser);

	// 隐藏几个按钮
	HideWidget(m_pCreateRoleWidget, "button_randomname");
	HideWidget(m_pCreateRoleWidget, "button_sure");
	HideWidget(m_pCreateRoleWidget, "button_cancel");

	ShowWidget(m_pCreateRoleWidget, "cr_name_loading");*/
}

// 创建角色界面 "取消" 按钮
void LoginScene::OnBtnCancel(CCObject* sender)
{
	PLAY_SOUND("return.wav");
	JumpToLoginPage();
}
void LoginScene::OnBtnDanjiMode(CCObject* sender)
{
	// load test data

	g_bTestMode = true;

	//g_pPlayerData->m_nCurrPage = PAGE_MAIN;
	//CCScene *pScene = MainScene::scene();
	//CCDirector::sharedDirector()->replaceScene(pScene);
}

void LoginScene::OnBtnReConnect(CCObject* sender)
{
	SendLoginCmd();

	m_pLostConnectWidget->setVisible(false);

	// 显示 “正在连接服务器”
	ShowWidget(m_pLoginWidget, "login_name_loading");
}
