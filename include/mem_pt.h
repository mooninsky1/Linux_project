#pragma once
class A
{
public:
	A(int i):a(i){}
	void Print()
	{
		std::cout<<a;
	}
private:
	int a;
};

void Test()
{
	typedef void (A::*pmf)();
	A a(2);
	A b(3);
	pmf f =&A::Print;
	(a.*f)();
	(b.*f)();
}