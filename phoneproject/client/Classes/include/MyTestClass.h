class MyTestClass
{
	int a;
	char b;
	float c;
public:
	MyTestClass(int _a, char _b, float _c): a(_a), b(_b), c(_c) {}
	static MyTestClass * Create(int _a, char _b, float _c);
	void PRINT();
	int TOTAL();
};