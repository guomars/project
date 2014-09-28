#include "gutil.h"
#include "WStrToUTF8.h"
#include <algorithm>

#include "cocos2d.h"

#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
#include "gnproto.h"
#include "gnsecure.h"
#else
#include "protocol.h"
#include "security.h"
#endif

#include "CCLuaEngine.h"

void DoLuaString(std::stringstream& ss)
{
	CCLuaEngine* pEngine = CCLuaEngine::defaultEngine();
	pEngine->executeString(ss.str().c_str());
}

void DoLuaString(const char* luaFun)
{
	std::stringstream ss;
	ss << luaFun << "(";
	ss << ")";

	CCLuaEngine* pEngine = CCLuaEngine::defaultEngine();
	pEngine->executeString(ss.str().c_str());
}

std::string GetFileData(const char *fileName,bool bIgnore)
{
	FILE*file = fopen(fileName,"rb");
	if (!file){
		return "";
	}
	
	long length = 0;
	fseek( file, 0, SEEK_END );
	length = ftell( file );
	fseek( file, 0, SEEK_SET );

	if ( length <= 0 )
	{
		fclose(file);
		return "";
	}

	unsigned char c = 0;

	int unicodeType = 0;
	if(!bIgnore) // 非忽略头的才检测（因：加密的文件怕加密后第一个字节正巧是0xff,0xef就不对了）
	{
		c = (unsigned char)fgetc(file);
		if(c == 0xff) // unicode
		{
			fgetc(file);
			unicodeType = 2;
		}
		else if(c == 0xEF) // utf-8
		{
			fgetc(file);
			fgetc(file);
			unicodeType = 3;
		}
		else
		{
			fseek(file,0,SEEK_SET );
		}
	}

	char* buf = new char[ length+1 ];
	memset(buf,0,length+1);

	if ( fread( buf, length-unicodeType, 1, file ) != 1 ) {
		delete [] buf;
		fclose(file);
		return "";
	}

	std::string temp;

	if(unicodeType == 2)
	{
		temp = WStrToUTF8((unsigned short*)buf,(length-2) / 2);
		delete[] buf;
		length = temp.size();
		buf = new char[ length+1 ];
		memset(buf,0,length+1);
		memcpy(buf,temp.c_str(),temp.size());
	}

	const char* p = buf;	// the read head
	char* q = buf;			// the write head
	const char CR = 0x0d;
	const char LF = 0x0a;
	while( *p ) {
		assert( p < (buf+length) );
		assert( q <= (buf+length) );
		assert( q <= p );

		if ( *p == CR ) {
			*q++ = LF;
			p++;
			if ( *p == LF ) {		// check for CR+LF (and skip LF)
				p++;
			}
		}
		else {
			*q++ = *p++;
		}
	}
	assert( q <= (buf+length) );
	*q = 0;

	temp = buf;
	delete [] buf;
	fclose(file);

	return temp;
}


//根据UTF8首字节判断该字符的字节数;(ascii:1 汉字:3)
int GetUtf8ByteNumByFirstWord(unsigned char firstCh)
{
	unsigned char temp = 0x80;
	int num = 0;


	if(firstCh < 0x80)//ascii code.(0-127)
	{
		//printf("AscII code,1 bytes\n");
		return 1;
	}		
	while(temp & firstCh)
	{
		num++;
		temp = (temp >> 1);
	}


	//printf("The char's bytes num is: %d", num);
	return num;
}


//Get char's numbers of UTF8 string,no bytes.
int GetUTF8LogicStrLen(std::string utf_str)
{
	int i,num,len = 0;
	
	for(i = 0;i<(int)utf_str.size();)
	{
		num = GetUtf8ByteNumByFirstWord(utf_str[i]);
		len++;
		i += num;
	}
	
	return len;		
}


//Get select char's bytes length by char ID.(根据输入的第几个字符，获取该字符前全部的字节长度)
int GetUTF8BytesByCharID(std::string utf_str,int charID)
{
	int i,num,len;
	
	len = utf_str.size();
	if((len < charID)||(charID <0))
		return -1;
	for(i = 0;charID>0;)
	{
		num = GetUtf8ByteNumByFirstWord(utf_str[i]);
		i += num;
		charID--;
	}
	
	return i;
}

int FormatString(std::string &result, const char *format, ...)
{
	const int BUFFER_SIZE = 1024;
	char buffer[BUFFER_SIZE];

	va_list argptr;
	va_start(argptr, format);
	int count = vsnprintf(buffer, BUFFER_SIZE, format, argptr);
	va_end(argptr);

	if (count > 0){
		result = buffer;
	}else{
		result.clear();
	}
	return count;
}

void TranslateString(std::string &str)
{
	if (str.empty()){
		return;
	}

	const char * tmp = str.c_str();

	std::string result;
	result.reserve(strlen(tmp));
	while(*tmp) //一个字符串的形式为： "内容"  
	{  
		//测试是否非转义字符  
		if(*tmp != '\\')
		{
			result.push_back(*tmp++);
			continue;
		} //这里是转义字符  
		tmp ++;
		switch(*tmp)
		{
		case '\n':
			tmp++;
			break; //连接两行的标志   

		case '0':
		case '1':
		case '2':
		case '3':
		case '4':
		case '5':
		case '6':
		case '7':
			{
				int value = 0;
				int count = 3;
				while(*tmp <='7' && *tmp >='0' && count)
				{
					count --;
					value *=8;
					value += *tmp-'0';
					tmp ++;
				}
				if(value > 255) break;
				result.push_back(value & 0xFF);
				break;
			}

		case '"': 
		case '\'':
		case '\\':
			result.push_back(*tmp++);
			break;
		case 'n':
			result.push_back('\n');
			tmp++;
			break;
		case 'r':
			result.push_back('\r');
			tmp++;
			break;
		case 't':
			result.push_back('\r');
			tmp++;
			break;
		case 'v':
			result.push_back('\r');
			tmp++;
			break;
		default:
			break;
		}
	}
	str.swap(result);
}

void ToLower(std::string &str)
{
	std::transform(str.begin(), str.end(), str.begin(), tolower);
}

bool STRING_TO_A3DCOLOR(const std::string &str, A3DCOLOR &clr)
{
	// 完成 A3DCOLOR_TO_STRING 的逆向转换
	// 

	bool ret(false);

	BYTE rgb[6];

	int nLen = (int)str.size();
	while (nLen==7)
	{
		if (str[0] != '^')
			break;		

		char c;
		int i;
		for (i=1; i<nLen; ++i)
		{
			c = str[i];
			if (c>='0' && c<='9')
			{
				rgb[i-1]=c-'0';
			}
			else if (c>='a' && c<='f')
			{
				rgb[i-1]=10+(c-'a');
			}
			else if (c>='A' && c<='F')
			{
				rgb[i-1]=10+(c-'A');
			}
			else
			{
				break;
			}
		}
		if (i<nLen)
			break;

		BYTE r = (rgb[0]<<4)+rgb[1];
		BYTE g = (rgb[2]<<4)+rgb[3];
		BYTE b = (rgb[4]<<4)+rgb[5];
		clr = A3DCOLORRGB(r, g, b);

		ret = true;
		break;
	}

	return ret;
}

std::string GetDecryptedStr(const char * str, unsigned long size)
{
	static const BYTE key_buf[128] = {
		0xbf, 0x61, 0x09, 0x72, 0x1d, 0xbb, 0x6e, 0xe9, 0x9a, 0x01, 0x3d, 0x47, 0x0a, 0x11, 0x60, 0xbe, 
		0xf8, 0x48, 0x36, 0x3f, 0xdf, 0xf5, 0x9a, 0xc5, 0xca, 0x1c, 0x79, 0xcb, 0xbb, 0x90, 0x96, 0xde, 
		0x58, 0xff, 0x60, 0xbe, 0x8d, 0x4e, 0xd8, 0xe1, 0x83, 0x47, 0xd0, 0x57, 0x6d, 0x62, 0x49, 0x66, 
		0x71, 0x0d, 0x6a, 0xfe, 0x3b, 0xdc, 0xd2, 0x33, 0xd7, 0x8f, 0x5c, 0x5e, 0x4b, 0x86, 0x25, 0xd0, 
		0x6f, 0xd2, 0xd0, 0x8c, 0x53, 0x46, 0xd0, 0xc4, 0x3a, 0x10, 0xae, 0xcf, 0x75, 0xcd, 0xfd, 0x74,
		0xe8, 0xfe, 0x80, 0x0b, 0x14, 0xf9, 0x94, 0x66, 0xcc, 0x19, 0x7d, 0xda, 0x89, 0x27, 0x91, 0xab, 
		0x5c, 0x73, 0xb0, 0x78, 0xc9, 0x1c, 0x48, 0xd9, 0xe2, 0xc3, 0xfc, 0xfa, 0x3e, 0x74, 0xb9, 0xec, 
		0x81, 0x66, 0x5f, 0x5b, 0x3e, 0x73, 0x1e, 0xd2, 0x31, 0x99, 0xc7, 0xb5, 0xe7, 0x3e, 0xbc, 0x02,
	};

	GNET::ARCFourSecurity arc4;
	GNET::Octets o(str,size);
	arc4.SetParameter(GNET::Octets(key_buf, sizeof(key_buf)/sizeof(key_buf[0])));
	GNET::Octets decrypted = arc4.Update(o);
	std::string s((char*)decrypted.begin(),decrypted.size());
	return s;
}

int LoadLuaFile(const char* strFileName)
{
	unsigned long size = 0;
	const char * buf = GetLuaBuffer(strFileName,size);
	CCLuaEngine* pEngine = CCLuaEngine::defaultEngine();
	int ret = pEngine->executeString(buf);
	delete [] buf;
	return ret;
}

const char * GetLuaBuffer(const char* strFileName, unsigned long& size)
{
	unsigned char* pData = CCFileUtils::sharedFileUtils()->getFileData(strFileName, "rb", &size);
	if (!pData || 0 == size)
		return NULL;

	char * buf = NULL;
#ifdef USE_ARC4
	std::string tmpstr;
	tmpstr.swap(GetDecryptedStr((char *)pData,size).c_str());
	size_t len = tmpstr.size();
	buf = new char[len+1];
	memcpy(buf,tmpstr.c_str(),len);
	buf[len] = '\0';
#else
	buf =new char[size+1];
	memcpy(buf,pData,size);
	buf[size] = '\0';
#endif
	return buf;
}