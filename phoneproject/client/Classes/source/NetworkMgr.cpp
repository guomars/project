#include "NetworkMgr.h"
#include "callid.hxx"
#include "ClientManager.h"
#include "DataMgr.h"

#include "gutil.h"
#include "WStrToUTF8.h"
#include "protoerrno.h"

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
#include "FMLayerWebView.h"
#endif
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
#include "JavaWebViewWrap.h"
#endif

//#include "gamedatasend.hpp"

#include <time.h>
#define HI_WORD(l)           ((unsigned short)(((unsigned long)(l) >> 16) & 0xFFFF))

USING_NS_CC;
using namespace GNET;

static GNET::Marshal::OctetsStream os_protocol;
static GNET::Marshal::OctetsStream os_unknownProtocol;
static GNET::Marshal::OctetsStream os_gameDataSend;
static GNET::Marshal::OctetsStream os_send;
static int sendProtocolType;static int sendPType;

//ios6 阿拉伯字符串漏洞过滤
BYTE alab_buf[24] = {
		0xD8, 0xB3, 0xD9, 0x85, 0xD9, 0x8E, 0xD9, 0x80, 0xD9, 0x8E, 0xD9, 0x91, 0xD9, 0x88, 0xD9, 0x8F, 0xD9, 0x88, 0xD9, 0x8F, 0xD8, 0xAD, 0xD8, 0xAE,
	};

// 闰年计算
int runnian(int x)
{
	if(x%4==0)
	{
		if(x%100==0)
		{
			if(x%400==0)
				x=2;
			else 
				x=1;
		}
		else 
			x=2;
	}
	else
		x=1;

	return (x);
}

#define MAXNUM_CUSTOM_ITEM 255
enum EditboxItemType
{
	enumEIEmotion = 0,
	enumEIIvtrlItem,
	enumEICoord,
	enumEIImage,
	enumEIScriptItem,
	enumEIBox,
	enumEITask,
	enumEICustom,
	enumEINum = enumEICustom + MAXNUM_CUSTOM_ITEM // 自定义类型 custom->num，最多255种，custom类型需要通过继承EditBoxItemBase来实现，子类中必须添加静态对象
};

enum ProtocolDealType
{
	enumProtocol = 0,
	enumUnknownProtocol,
	enumGameDataSend,
};

void NetMarshal(GNET::Marshal::OctetsStream&os,const char*vType,const std::string&strValue,bool bReverse)
{
	std::string valueType = vType;
	std::stringstream ss;
	ss << strValue;
	if (valueType == "char")
	{	
		char value = 0;
		ss >> value;
		
		os << value;
	}
	else if (valueType == "uchar")
	{
		unsigned char value = 0;
		ss >> value;

		os << value;
	}
	else if (valueType == "short")
	{
		short value = 0;
		ss >> value;

		if(bReverse)
			value = byteorder_16(value);

		os << value;
	}
	else if (valueType == "ushort")
	{
		unsigned short value = 0;
		ss >> value;

		if(bReverse)
			value = byteorder_16(value);

		os << value;
	}
	else if (valueType == "int")
	{
		int value = 0;
		ss >> value;

		if(bReverse)
			value = byteorder_32(value);

		os << value;
	}
	else if (valueType == "uint")
	{
		unsigned int value = 0;
		ss >> value;

		if(bReverse)
			value = byteorder_32(value);

		os << value;
	}
	else if (valueType == "int64")
	{
		long long value = 0;
		ss >> value;

		if(bReverse)
			value = byteorder_64(value);

		os << value;
	}
	else if (valueType == "uint64")
	{
		long long value = 0;
		ss >> value;

		if(bReverse)
			value = byteorder_64(value);

		os << value;
	}
	else if (valueType == "string")
	{
		GNET::Octets o;
		o.replace(strValue.c_str(),strValue.size());

		os << o;

	}
	else if (valueType == "wstring")
	{
		GNET::Octets o;
		
		std::vector<char> str;
		int count = Utf8ToWStr(strValue.c_str(), str);

		if(count > 0)
		{
			o.replace(&str.front(), count);
		}

		os << o;
	}
	else if (valueType == "compactuint")
	{
		unsigned int value = 0;
		ss >> value;

		os << GNET::CompactUINT(value);
	}
}

std::string NetUnMarshal(GNET::Marshal::OctetsStream&os,const char*vType,bool bReverse)
{
	std::string valueType = vType;
	std::string strRet;

	if (valueType == "char")
	{
		char value = 0;
		os >> value;
				
		strRet = TToString(value);
	}
	else if (valueType == "uchar")
	{
		unsigned char value = 0;
		os >> value;

		strRet = TToString(value);
	}
	else if (valueType == "short")
	{
		short value = 0;
		os >> value;

		if(bReverse)
			value = byteorder_16(value);

		strRet = TToString(value);
	}
	else if (valueType == "ushort")
	{
		unsigned short value = 0;
		os >> value;

		if(bReverse)
			value = byteorder_16(value);

		strRet = TToString(value);
	}
	else if (valueType == "int")
	{
		int value = 0;
		os >> value;

		if(bReverse)
			value = byteorder_32(value);

		strRet = TToString(value);
	}
	else if (valueType == "uint")
	{
		unsigned int value = 0;
		os >> value;

		if(bReverse)
			value = byteorder_32(value);

		strRet = TToString(value);
	}
	else if (valueType == "int64")
	{
		long long value = 0;
		os >> value;

		if(bReverse)
			value = byteorder_64(value);

		strRet = TToString(value);
	}
	else if (valueType == "uint64")
	{
		long long value = 0;
		os >> value;

		if(bReverse)
			value = byteorder_64(value);

		strRet = TToString(value);
	}
	else if (valueType == "string")
	{
		GNET::Octets o;
		os >> o;

		std::string s((char*)o.begin(),o.size());

		strRet = s;
	}
	else if (valueType == "wstring")
	{
		GNET::Octets o;
		os >> o;

		strRet = WStrToUTF8(o);
	}
	else if (valueType == "compactuint")
	{
		unsigned int value = 0;
		os >> GNET::CompactUINT(value);

		strRet = TToString(value);
	}

	return strRet;
}

int NetworkMgr::GetNetworkType()
{
	int ntype = 0;
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    if (FMLayerWebView::connectedToNetwork(ntype))
		return ntype;
	else
		return 0;
#endif
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    return JavaWebView::GetInstance()->IsConnectToNetwork();
#endif
	return 1;	//wifi
}

// pType，表示已知协议，未知协议，gamedataSend
int  NetworkMgr::UnMarshalIntFromProtocol(int pType,const char*valueType)
{
	return StringToT<int>(UnMarshalStringFromProtocol(pType,valueType));
}
	
std::string NetworkMgr::UnMarshalStringFromProtocol(int pType,const char*valueType)
{
	std::string strRet;

	switch(pType)
	{
	case enumProtocol:
		{
			strRet = NetUnMarshal(os_protocol,valueType,false);
		}
		break;
	case enumUnknownProtocol:
		{
			strRet = NetUnMarshal(os_unknownProtocol,valueType,false);
		}
		break;
	case enumGameDataSend:
		{
			strRet = NetUnMarshal(os_gameDataSend,valueType,true);
		}
		break;
	default:
		break;
	}

	return strRet;
}

void NetworkMgr::MarshalProtocolStart(int protocolType,int pType)
{
	sendProtocolType = protocolType;
	sendPType = pType;

	// 重置一下，先不写protocolType和size
	GNET::Marshal::OctetsStream os;
	os_send = os;
}
	
void NetworkMgr::MarshalIntToProtocol(const char*valueType,int value)
{
	std::string v = TToString(value);
	MarshalStringToProtocol(valueType,v.c_str());
}
	
void NetworkMgr::MarshalStringToProtocol(const char*valueType,const char* value)
{
	NetMarshal(os_send,valueType,value,sendPType == enumGameDataSend);
}

void NetworkMgr::MarshalProtocolEndAndSend()
{
	GNET::Marshal::OctetsStream os;
	// 写入协议类型和size
	os << CompactUINT(sendProtocolType);

	// 写入内容
	if(sendPType == enumGameDataSend)
	{
		//sendGameData(os_send.begin(),os_send.size());
		return;
	}
	else
	{
		os << os_send;
	}
	// 发送拼装协议
	ClientManager::GetInstance()->Send(os);
}

void NetworkMgr::SetDealProtocol(GNET::Marshal::OctetsStream& os)
{
	os_protocol = os;
}

void NetworkMgr::SetDealUnknownProtocol(GNET::Marshal::OctetsStream& os)
{
	os_unknownProtocol = os;
}
	
void NetworkMgr::SetDealGameDataSend(GNET::Marshal::OctetsStream& os)
{
	os_gameDataSend = os;
}

int NetworkMgr::FindFlag(unsigned short*srcStr,int&srcIndex,unsigned short flag,int srcSize)
{
	unsigned short c;
	while(srcIndex <= srcSize)
	{
		c = srcStr[srcIndex];
		srcIndex++;
		if(c == flag)
			return srcIndex - 1;
	}
	return -1;
}

void NetworkMgr::DoConvert(unsigned short*srcStr, int&srcIndex, int srcSize, int emotion, std::vector<unsigned short> &result)
{
	const unsigned short leftFlag = 60; // <
	const unsigned short rightFlag = 62;// >
	int typeStartIndex  = FindFlag(srcStr,srcIndex,leftFlag,srcSize);
	int typeEndIndex    = FindFlag(srcStr,srcIndex,rightFlag,srcSize);
	int valueStartIndex = FindFlag(srcStr,srcIndex,leftFlag,srcSize);
	int valueEndIndex   = FindFlag(srcStr,srcIndex,rightFlag,srcSize);

	if (typeStartIndex < 0 || typeEndIndex < 0 || valueStartIndex < 0 || valueEndIndex < 0){
		return ;
	}
	
	std::string typeStr = WStrToUTF8(srcStr + typeStartIndex + 1, typeEndIndex - typeStartIndex - 1);
	int enumType = StringToT<int>(typeStr);
	switch (enumType)
	{
	case enumEIEmotion:
		{
			/*std::string valueStr = WStrToUTF8(srcStr + valueStartIndex + 1, valueEndIndex - valueStartIndex - 1);
			VectorInt vec;
			SplitToList(valueStr,vec,':');
			if(vec.size() == 2){
				const int emotionOffset = 10000;
				if (emotion < 0) emotion = vec[0];
				std::string s = GSceneManager::GetInstance()->GetStringFromTable(emotionOffset + emotion * 100 + vec[1]);
				std::vector<char> converted;
				int count = Utf8ToWStr(s, converted);
				if (count > 0){
					const unsigned short *p = (const unsigned short *)&converted.front();
					result.insert(result.end(), p, p+count/2);
				}
			}*/
			break;
		}
	case enumEIIvtrlItem:
		{
			if (valueEndIndex - valueStartIndex > 8){
				result.insert(result.end(), srcStr + valueStartIndex + 8, srcStr + valueEndIndex);
			}
			break;
		}
	}
}

void NetworkMgr::ConvertItemAndEmotionStr(const GNET::Octets &msg, int emotion, std::string &result)
{
	int srcSize = msg.size()/sizeof(unsigned short);
	unsigned short *srcStr = (unsigned short *)msg.begin();

	const unsigned short AUICOMMON_ITEM_CODE_START = 0xE000;
	const unsigned short AUICOMMON_ITEM_CODE_END   = 0xE3FF;

	std::vector<unsigned short> tmp;
	tmp.reserve(srcSize);

	bool bAlabCheck = false;
	unsigned short c(0);
	int index = 0;
	while(index < srcSize)
	{
		c = srcStr[index];
		if(c >= AUICOMMON_ITEM_CODE_START && c <= AUICOMMON_ITEM_CODE_END)
		{
			++ index;
			DoConvert(srcStr, index, srcSize, emotion, tmp);
		}
		else
		{
			if(!bAlabCheck && c == 0x0633)//0x0633是以上alab_buf第一个utf8字符0xD8,0xB3的unicode字。
			{// 需要阿拉伯漏洞检测
				bAlabCheck = true;
			}
			tmp.push_back(c);
			++ index;
		}
	}

	if (!tmp.empty()){
		WStrToUTF8(result, &tmp[0], tmp.size());
		// 针对阿拉伯字符串漏洞进行过滤，一旦检测到有该子字符串，则整句不予显示！
		//（查看网上那句阿拉伯字符串，貌似显示和拷贝出来放到txt文本中的顺序居然会颠倒，即浏览器和notepad显示可能不一致，所以这里仅匹配其中的关键子串）
		int asize = sizeof(alab_buf);
		int msgsize = result.size();
		if(msgsize >= asize && bAlabCheck)
		{
			for(int i = 0;i <= msgsize - asize;i++)
			{
				if(memcmp(result.c_str() + i,alab_buf,asize) == 0)
				{
					result.clear();
					break;
				}
			}
		}
	}else{
		result.clear();
	}
}

NetworkMgr::NetworkMgr()
{
	m_counterKeepAlive.setPeriod(60.0f);// 60秒触发一次
	m_counterKeepAliveReceive.setPeriod(50.0f);
	m_counterKeepAliveReceive.setCounter(60.0f);
	m_counterServerTime.setPeriod(300.0f);// 5分钟同步一次服务器时间
}

void NetworkMgr::ConnectServer(const char* ip, int port)
{
	int ntype = 0;
	//if(GWebManager::GetInstance()->IsConnectToNetwork(ntype))
	{
		ClientManager::GetInstance()->SetNetType(ntype);
		GNET::Protocol::Client(ClientManager::GetInstance(),ip,port);
	}
	/*else
	{
		DoLuaString("LNetworkMgr:onConnectServerError");
	}*/
}

void NetworkMgr::CloseServer()
{
	// 主动断开设个标记
	m_counterKeepAliveReceive.setCounter(60.0f);
	DataMgr::sharedMgr()->SetInt("CloseServerFromSelf",1);
	ClientManager::GetInstance()->Close(ClientManager::GetInstance()->getSid());
	DoLuaString("LNetworkMgr:CloseServer");
}

//	Send game data
bool NetworkMgr::sendGameData(void* pData, int iSize)
{
	/*GamedataSend p;
	p.data.replace(pData, iSize);
	return ClientManager::GetInstance()->Send(p);*/
	return true;
}

////////////////////////////////////////////////////

bool NetworkMgr::receiveProtocol(const Protocol* pProtocol)
{
	bool bRet = true;
	switch(pProtocol->GetType())
	{
	default:
		//
		bRet = false;
		break;
	}

	GNET::Marshal::OctetsStream os;
	pProtocol->marshal(os);
	SetDealProtocol(os);

	DoLuaString("LNetworkMgr:onReceiveProtocol",pProtocol->GetType());
	return bRet;
}


unsigned int calcS2CCmdDataSize(int iCmd, BYTE* pDataBuf, unsigned int dwDataSize)
{
	using namespace S2C;

	#define CHECK_VALID(type) \
		{\
		if (!reinterpret_cast<type*>(pDataBuf)->CheckValid(dwDataSize, sz) || dwDataSize != sz) {\
		CCLog("Invalid calcS2CCmdDataSize(iCmd = %d,dwDataSize= %d)",iCmd,dwDataSize);}\
		else\
		dwSize = (unsigned int)(-2);\
		}

	unsigned int dwSize = (unsigned int)(-1);
	//size_t sz;

	switch (iCmd)
	{
	case PLAYER_INFO_1:				break;
	case PLAYER_INFO_2:				break;
	case PLAYER_INFO_3:				break;
	case PLAYER_INFO_4:				break;
	default:
		break;
	}

	return dwSize;
}

bool NetworkMgr::SumUpMonthState(int year_state, int state)
{
	int month_state(0);
	for (int i = 0; i < 12; ++i) { 
		month_state = (year_state >> (i * 2)) & 0x3;
		if (month_state < state) return false;
	}
	return true;
}

////////////////////////////////////////
// 处理S2C协议
void NetworkMgr::processGameData(const GNET::Octets& Data)
{
	using namespace S2C;

	unsigned int dwDataSize = Data.size();

	if (dwDataSize < sizeof(cmd_header))
	{
		CCLog("Invalid PROTOCOL_GAMEDATASEND head");
		assert(0);
		return;
	}

	dwDataSize -= sizeof(cmd_header);

	//	Get common command header
	BYTE* pDataBuf = (BYTE*)Data.begin();
	cmd_header* pCmdHeader = (cmd_header*)pDataBuf;
	pDataBuf += sizeof (cmd_header);

	//	Check command size
	unsigned int dwCmdSize = calcS2CCmdDataSize(pCmdHeader->cmd, pDataBuf, dwDataSize);

	// log the command and data
	// LogS2CCmdData(pCmdHeader->cmd, (BYTE *)Data.begin(), Data.size());

	//	Size == -1 means we haven't handled this command
	if (dwCmdSize == (unsigned int)(-1))
	{
		CCLog("GameDataSend(%d) ignored: unknown or changed", pCmdHeader->cmd);
		return;
	}
	else if (dwCmdSize != (unsigned int)(-2))
	{
		if (dwCmdSize != dwDataSize)
		{
			CCLog("GameDataSend(%d) ignored: size invalid(server=%d, client=%d)", pCmdHeader->cmd, dwDataSize, dwCmdSize);
			return;
		}
	}

	switch (pCmdHeader->cmd)
	{
	case PLAYER_INFO_2:
	case PLAYER_INFO_3:
	case PLAYER_INFO_4:

		break;

	case PLAYER_INFO_1:
		break;

	default:
		break;
	}

	Octets odata;
	odata.replace(pCmdHeader,dwDataSize);

	GNET::Marshal::OctetsStream os(odata);
	SetDealGameDataSend(os);

	DoLuaString("LNetworkMgr:onGameDataSend",pCmdHeader->cmd);
}

void NetworkMgr::RefreshServerTime(int ltime)
{
	time_t t = (time_t)(ltime);
	tm* ptm = localtime(&t);
	if(ptm == NULL)
		return;
			
	DataMgr::sharedMgr()->SetInt("servertime_localtime",ltime);
	int year = ptm->tm_year + 1900;
	DataMgr::sharedMgr()->SetString("servertime_year",TToString(year).c_str());
	DataMgr::sharedMgr()->SetString("servertime_month",TToString(ptm->tm_mon+1).c_str());
	DataMgr::sharedMgr()->SetString("servertime_day",TToString(ptm->tm_mday).c_str());

	int k[12]={31,27+runnian(year),31,30,31,30,31,31,30,31,30,31};
	for(int i = 0;i < 12;++i)
	{// 将本年的每个月的天数保存
		std::stringstream ss;
		ss << "servertime_month" << (i+1);
		DataMgr::sharedMgr()->SetString(ss.str().c_str(),TToString(k[i]).c_str());
	}
}
