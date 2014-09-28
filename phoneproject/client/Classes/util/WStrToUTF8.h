#ifndef __APP_WSTRTOUTF8_H__
#define __APP_WSTRTOUTF8_H__

#include <string>
#include <vector>

namespace GNET{
	class Octets;
}

extern int Utf8ToWStr(const char* pInput, char* pOutput);

extern int Utf8ToWStr(const char* pInput, std::vector<char> &result);

extern int Utf8ToWStr(const std::string &src, std::vector<char> &result);

extern void WStrToUTF8(std::string& dest, const unsigned short* src, int size);

extern std::string WStrToUTF8(const unsigned short* str, int size);

extern std::string WStrToUTF8(const GNET::Octets &o);

#endif  // __APP_WSTRTOUTF8_H__