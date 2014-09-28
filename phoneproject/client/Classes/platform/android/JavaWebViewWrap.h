#ifndef __JAVAWEBVIEWWRAP_H__
#define __JAVAWEBVIEWWRAP_H__

#include <string>
#include <stdio.h>
#include "util.h"

class JavaWebView
{
	std::string m_userId;
	std::string m_agent;
	std::string m_ticket;
	GPhoneFSM m_thirdPartLoginFsm;
	JavaWebView();
public:
	static JavaWebView * GetInstance()
	{
		static JavaWebView jwebview;
		return &jwebview;
	}
	const std::string& GetUserID()
	{
		return m_userId;
	}
	void SetUserID(const char* pUserID)
	{
		m_userId = pUserID;
	}
	const std::string& GetAgent()
	{
		return m_agent;
	}
	void SetAgent(const char* pAgent)
	{
		m_agent = pAgent;
	}
	const std::string& GetTicket()
	{
		return m_ticket;
	}
	void SetTicket(const char* pTicket)
	{
		m_ticket = pTicket;
	}
	GPhoneFSM& GetFSM()
	{
		return m_thirdPartLoginFsm;
	}
public:
	void tick(float dt);
	void OpenWebView(const char * url);
	void CloseWebView();
	int IsConnectToNetwork();
};

#endif
