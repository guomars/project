#include "MyTestClass.h"

MyTestClass * MyTestClass::Create(int _a, char _b, float _c) 
{
	MyTestClass * tmp = new MyTestClass(_a,_b,_c);
	return tmp;
}

void MyTestClass::PRINT()
{
	int t = (int)(a+b+c);
}

int MyTestClass::TOTAL()
{
	return (int)(a+b+c);
}