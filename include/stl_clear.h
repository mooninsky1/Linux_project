//lihf 2012/11/13 检查vector clear会不会释放内存
#include <vector>
class Test
{
public:
	Test(){a=0;}
	std::vector<int> intVect;
	int a;
};
void Test()
{
	char szName[10];
	std::vector< int > IntVect;
	for (int i=0; i<10000; i++)
	{
		IntVect.push_back(i);
	}
	IntVect.clear();
	IntVect.resize(0);
	for (int i=0; i<10000; i++)
	{
		IntVect.push_back(i);
	}
	{
		std::vector< int > IntVect1;
		IntVect1.swap(IntVect);

	}
}