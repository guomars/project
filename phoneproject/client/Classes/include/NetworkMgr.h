#ifndef __NETWORKMGR_H__
#define __NETWORKMGR_H__

#include "cocos2d.h"
#include <list>
#include <string>
#include <sstream>
#ifdef WIN32
#include "gnproto.h"
#else
#include "protocol.h"
#endif

#include "Counter.h"
#include "EC_SendC2sCmds.h"
using namespace GNET;

class NetworkMgr
{
	Counter m_counterKeepAliveReceive;
	Counter m_counterKeepAlive;
	Counter m_counterServerTime;
	NetworkMgr();
public:
	static NetworkMgr * sharedMgr()
	{
		static NetworkMgr event_mgr;
		return &event_mgr;
	}

	void tick(float dt);

	bool receiveProtocol(const GNET::Protocol* pProtocol);

	struct LoginParameter
	{
		std::string		name;
		std::string		passwd;
		GNET::Octets	nonce;
		char			algo;
	};
	void SendResponse(LoginParameter &);

	//	Send game data
	bool sendGameData(void* pData, int iSize);
	void processGameData(const GNET::Octets& Data);
	void onMatrixChallenge(int algo,unsigned int nonce);
	void RefreshServerTime(int ltime);
	bool SumUpMonthState(int year_state, int state);
	void ConvertItemAndEmotionStr(const GNET::Octets &msg, int emotion, std::string &result);
	void DoConvert(unsigned short*srcStr, int&srcIndex, int srcSize, int emotion, std::vector<unsigned short> &result);
	int FindFlag(unsigned short*srcStr,int&srcIndex,unsigned short flag,int srcSize);
	void SetDealProtocol(GNET::Marshal::OctetsStream& os);
	void SetDealUnknownProtocol(GNET::Marshal::OctetsStream& os);
	void SetDealGameDataSend(GNET::Marshal::OctetsStream& os);
	void SendKeepAlive();

	int GetNetworkType();
public:
	///////////////////////////////////////////////////
	// 暴露给lua用的
	void ConnectServer(const char* ip, int port);
	void CloseServer();
	int  UnMarshalIntFromProtocol(int pType,const char*valueType);
	std::string UnMarshalStringFromProtocol(int pType,const char*valueType);
	void MarshalProtocolStart(int protocolType,int pType);
	void MarshalIntToProtocol(const char*valueType,int value);
	void MarshalStringToProtocol(const char*valueType,const char* value);
	void MarshalProtocolEndAndSend();
public:
	// 通用GameDataSend c2s
	void c2s_CmdGameDataSend(int cmd_header_type,void*pData,int iSize) { ::c2s_SendCmdGameDataSend(cmd_header_type,pData,iSize);}
};

#endif