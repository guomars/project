#ifndef __BYTEORDER_H
#define __BYTEORDER_H

//#include "platform.h"

namespace GNET
{

#if defined BYTE_ORDER_BIG_ENDIAN
	#define byteorder_16(x)	(x)
	#define byteorder_32(x)	(x)
	#define byteorder_64(x)	(x)
#elif defined __GNUC_IOS__
    /*
     #define byteorder_16 htons
     #define byteorder_32 htonl
     */
	inline unsigned short byteorder_16(unsigned short x)
	{
		register unsigned short v;
		((char*)&v)[0] = ((char*)&x)[1];
        ((char*)&v)[1] = ((char*)&x)[0];
		return v;
	}
	inline unsigned long byteorder_32(unsigned long x)
	{
		register unsigned long v;
		((char*)&v)[0] = ((char*)&x)[3];
        ((char*)&v)[1] = ((char*)&x)[2];
        ((char*)&v)[2] = ((char*)&x)[1];
        ((char*)&v)[3] = ((char*)&x)[0];
		return v;
	}
	inline unsigned long long byteorder_64(unsigned long long x)
	{
		unsigned long long v;
		((char*)&v)[0] = ((char*)&x)[7];
        ((char*)&v)[1] = ((char*)&x)[6];
        ((char*)&v)[2] = ((char*)&x)[5];
        ((char*)&v)[3] = ((char*)&x)[4];
        ((char*)&v)[4] = ((char*)&x)[3];
        ((char*)&v)[5] = ((char*)&x)[2];
        ((char*)&v)[6] = ((char*)&x)[1];
        ((char*)&v)[7] = ((char*)&x)[0];
		return v;
	}
#elif defined __GNUC__
	/*
	#define byteorder_16 htons
	#define byteorder_32 htonl
	*/
	inline unsigned short byteorder_16(unsigned short x)
	{
		register unsigned short v;
		__asm__ ("xchg %b0, %h0" : "=q"(v) : "0"(x));
		return v;
	}
	inline unsigned long byteorder_32(unsigned long x)
	{
		register unsigned long v;
		__asm__ ("bswap %0" : "=r"(v) : "0"(x));
		return v;
	}
	inline unsigned long long byteorder_64(unsigned long long x)
	{
		union
		{
			unsigned long long __ll;
			unsigned long __l[2];
		} i, o;
		i.__ll = x;
		o.__l[0] = byteorder_32(i.__l[1]);
		o.__l[1] = byteorder_32(i.__l[0]);
		return o.__ll;
	}

#elif defined WIN32
	inline unsigned __int16 byteorder_16(unsigned __int16 x)
	{
		__asm ror x, 8
		return x;
	}
	inline unsigned __int32 byteorder_32(unsigned __int32 x)
	{
		__asm mov eax, x
		__asm bswap eax
		__asm mov x, eax
		return x;
	}
	inline unsigned __int64 byteorder_64(unsigned __int64 x)
	{
		union
		{
			unsigned __int64 __ll;
			unsigned __int32 __l[2];
		} i, o;
		i.__ll = x;
		o.__l[0] = byteorder_32(i.__l[1]);
		o.__l[1] = byteorder_32(i.__l[0]);
		return o.__ll;
	}
#endif
};

#endif
