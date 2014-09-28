#ifndef __G_UTIL_H__
#define __G_UTIL_H__

#include <vector>
#include <string>
#include <sstream>
#include "CCLuaEngine.h"

USING_NS_CC;

typedef std::vector<int> VectorInt;
typedef std::vector<float> VectorFloat;
typedef std::vector<std::string> VectorString;

template<typename T>
T StringToT(const std::string& str)
{
	T Value;
	std::stringstream ss;
	ss << str;
	ss >> Value;
	return Value;
}

template<typename T>
std::string TToString(const T& t)
{
	std::stringstream ss;
	ss << t;
	
	return ss.str();
}

template<typename T>
void SplitToList(const std::string& str,std::vector<T>& vec, char tag)
{
	vec.clear();

	int i = 0;
	int len = (int)str.size();

	std::string temp;
	while( i < len )
	{
		int j = str.find(tag, i);
		if (j == std::string::npos)
			j = len;
		temp = str.substr(i, j-i);
		if (temp.size() != 0)
			vec.push_back(StringToT<T>(temp) );
		i = j+1;
	}
}

template<typename T>
void SplitToList(const std::string& str,std::vector<T>& vec, const std::string& tag)
{
	vec.clear();

	int i = 0;
	int len = (int)str.size();

	std::string temp;
	while( i < len )
	{
		int j = str.find(tag, i);
		if (j == std::string::npos)
			j = len;
		temp = str.substr(i, j-i);
		if (temp.size() != 0)
			vec.push_back(StringToT<T>(temp) );
		i = j+tag.size();
	}
}

template<typename T>
class QuotWrapper
{
public:
	static T QuotT(const T& t)
	{
		return t;
	}
};

template<>
class QuotWrapper<std::string>
{
public:
	static std::string QuotT(const std::string& t)
	{
		std::string qt = "'";
		qt += t + "'";
		return qt;
	}
};

std::string GetFileData(const char *fileName,bool bIgnore = false);

// 执行lua脚本
void DoLuaString(std::stringstream& ss);
void DoLuaString(const char* luaFun);

template<class P1>
void DoLuaString(const char* luaFun, const P1& p1)
{
	std::stringstream ss;
	ss << luaFun << "(";
	ss << QuotWrapper<P1>::QuotT(p1);
	ss << ")";

	CCLuaEngine* pEngine = CCLuaEngine::defaultEngine();
	pEngine->executeString(ss.str().c_str());
}

template<class P1,class P2>
void DoLuaString(const char* luaFun, const P1& p1, const P2& p2)
{
	std::stringstream ss;
	ss << luaFun << "(";
	ss << QuotWrapper<P1>::QuotT(p1) << ",";
	ss << QuotWrapper<P2>::QuotT(p2);
	ss << ")";

	CCLuaEngine* pEngine = CCLuaEngine::defaultEngine();
	pEngine->executeString(ss.str().c_str());
}

template<class P1,class P2,class P3>
void DoLuaString(const char* luaFun, const P1& p1, const P2& p2, const P3& p3)
{
	std::stringstream ss;
	ss << luaFun << "(";
	ss << QuotWrapper<P1>::QuotT(p1) << ",";
	ss << QuotWrapper<P2>::QuotT(p2) << ",";
	ss << QuotWrapper<P3>::QuotT(p3);
	ss << ")";

	CCLuaEngine* pEngine = CCLuaEngine::defaultEngine();
	pEngine->executeString(ss.str().c_str());
}

template<class P1,class P2,class P3,class P4>
void DoLuaString(const char* luaFun, const P1& p1, const P2& p2, const P3& p3, const P4& p4)
{
	std::stringstream ss;
	ss << luaFun << "(";
	ss << QuotWrapper<P1>::QuotT(p1) << ",";
	ss << QuotWrapper<P2>::QuotT(p2) << ",";
	ss << QuotWrapper<P3>::QuotT(p3) << ",";
	ss << QuotWrapper<P4>::QuotT(p4);
	ss << ")";

	CCLuaEngine* pEngine = CCLuaEngine::defaultEngine();
	pEngine->executeString(ss.str().c_str());
}

template<class P1,class P2,class P3,class P4,class P5>
void DoLuaString(const char* luaFun, const P1& p1, const P2& p2, const P3& p3, const P4& p4, const P5& p5)
{
	std::stringstream ss;
	ss << luaFun << "(";
	ss << QuotWrapper<P1>::QuotT(p1) << ",";
	ss << QuotWrapper<P2>::QuotT(p2) << ",";
	ss << QuotWrapper<P3>::QuotT(p3) << ",";
	ss << QuotWrapper<P4>::QuotT(p4) << ",";
	ss << QuotWrapper<P5>::QuotT(p5);
	ss << ")";

	CCLuaEngine* pEngine = CCLuaEngine::defaultEngine();
	pEngine->executeString(ss.str().c_str());
}

template<class P1,class P2,class P3,class P4,class P5,class P6>
void DoLuaString(const char* luaFun, const P1& p1, const P2& p2, const P3& p3, const P4& p4, const P5& p5, const P6& p6)
{
	std::stringstream ss;
	ss << luaFun << "(";
	ss << QuotWrapper<P1>::QuotT(p1) << ",";
	ss << QuotWrapper<P2>::QuotT(p2) << ",";
	ss << QuotWrapper<P3>::QuotT(p3) << ",";
	ss << QuotWrapper<P4>::QuotT(p4) << ",";
	ss << QuotWrapper<P5>::QuotT(p5) << ",";
	ss << QuotWrapper<P6>::QuotT(p6);
	ss << ")";

	CCLuaEngine* pEngine = CCLuaEngine::defaultEngine();
	pEngine->executeString(ss.str().c_str());
}

//根据UTF8首字节判断该字符的字节数;(ascii:1 汉字:3)
int GetUtf8ByteNumByFirstWord(unsigned char firstCh);

//Get char's numbers of UTF8 string,no bytes.
int GetUTF8LogicStrLen(std::string utf_str);

//Get select char's bytes length by char ID.(根据输入的第几个字符，获取该字符前全部的字节长度)
int GetUTF8BytesByCharID(std::string utf_str,int charID);

int FormatString(std::string &result, const char *format, ...);

void TranslateString(std::string &str);
void ToLower(std::string &str);

typedef unsigned long A3DCOLOR;
#define A3DCOLORRGB(r, g, b) ((A3DCOLOR) (0xff000000 | ((r) << 16) | ((g) << 8) | (b)))
bool STRING_TO_A3DCOLOR(const std::string &str, A3DCOLOR &clr);

std::string GetDecryptedStr(const char * str, unsigned long size);
const char * GetLuaBuffer(const char* strFileName, unsigned long& size);

//以下是lua也能调用的功能接口
int LoadLuaFile(const char* strFileName);

#endif