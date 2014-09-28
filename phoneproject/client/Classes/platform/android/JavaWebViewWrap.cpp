#include "JavaWebViewWrap.h"
#include "GWebManager.h"
#include <jni.h>
#include "platform/android/jni/JniHelper.h"
#include <android/log.h>

enum
{
	FSM_STATE_THIRDPARTLOGIN,// 第三方登录
	FSM_STATE_NONE, // 空状态
};
static GPhoneFSM s_thirdPartLoginFsm;

void noneState(float)
{
}
void thirdPartLogin(float dt)
{
	GWebManager::GetInstance()->OnThirdPartLogin(JavaWebView::GetInstance()->GetUserID(),
												 JavaWebView::GetInstance()->GetAgent(),
												 JavaWebView::GetInstance()->GetTicket());
	JavaWebView::GetInstance()->GetFSM().ChangeState(FSM_STATE_NONE);
}

extern "C" {

	 void Java_com_wanmei_w2i_GPhoneDevice_nativeOnThirdPartLogin(JNIEnv*  env, jobject thiz, jstring userId,jstring agent, jstring ticket) {
    	const char* pszUserId = env->GetStringUTFChars(userId, NULL);
    	const char* pszAgent = env->GetStringUTFChars(agent, NULL);
    	const char* pszTicket = env->GetStringUTFChars(ticket, NULL);
    	JavaWebView::GetInstance()->SetUserID(pszUserId);
		JavaWebView::GetInstance()->SetAgent(pszAgent);
		JavaWebView::GetInstance()->SetTicket(pszTicket);
    	JavaWebView::GetInstance()->GetFSM().ChangeState(FSM_STATE_THIRDPARTLOGIN);
		env->ReleaseStringUTFChars(userId, pszUserId);
		env->ReleaseStringUTFChars(agent, pszAgent);
		env->ReleaseStringUTFChars(ticket, pszTicket);
    }
}

JavaWebView::JavaWebView()
{
	// 初始化安卓第三方登录状态机
	m_thirdPartLoginFsm.AddState(FSM_STATE_THIRDPARTLOGIN,thirdPartLogin);
	m_thirdPartLoginFsm.AddState(FSM_STATE_NONE,noneState);
	m_thirdPartLoginFsm.ChangeState(FSM_STATE_NONE);
}

void JavaWebView::tick(float dt)
{
	m_thirdPartLoginFsm.Update(dt);
}
	
void JavaWebView::OpenWebView(const char * url)
{
	JniMethodInfo t;

	bool isHave = JniHelper::getStaticMethodInfo(t,"com/wanmei/w2i/GPhoneDevice","openWebView","(Ljava/lang/String;)V");

	if (isHave) {

		jstring stringArg1;

		if (!url) {
			stringArg1 = t.env->NewStringUTF("");
		} else {
			stringArg1 = t.env->NewStringUTF(url);
		}

		t.env->CallStaticVoidMethod(t.classID, t.methodID,stringArg1);

		t.env->DeleteLocalRef(stringArg1);
		t.env->DeleteLocalRef(t.classID);
	}
}

void JavaWebView::CloseWebView()
{
	JniMethodInfo t;

	bool isHave = JniHelper::getStaticMethodInfo(t,"com/wanmei/w2i/GPhoneDevice","closeWebView","()V");

	if (isHave) {

		t.env->CallStaticVoidMethod(t.classID, t.methodID);

		t.env->DeleteLocalRef(t.classID);
	}
}

int JavaWebView::IsConnectToNetwork()
{
	int ntype = 0;

	JniMethodInfo t;

	bool isHave = JniHelper::getStaticMethodInfo(t,"com/wanmei/w2i/GPhoneDevice","connectedToNetwork","()I");

	if (isHave) {

		jint ret = t.env->CallStaticIntMethod(t.classID, t.methodID);
		ntype = ret;

		t.env->DeleteLocalRef(t.classID);
	}

	return ntype;
}