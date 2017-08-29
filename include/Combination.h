//排列组合
#include <vector>
std::vector<int> Vec1;
std::vector<int> Vec2;
void Disp()
{
	for (int i=0; i<Vec1.size(); i++)
	{
		std::cout<< Vec1[i]<<" "<<Vec2[i] <<" 和:"<<Vec1[i]+Vec2[i]<<" 积:"<<Vec1[i]*Vec2[i]<<std::endl;
	}
}
void Test()
{
	int a[20];
	for (int i=0; i<20; i++)
	{
		 a[i] = i+1;
	}
	for (int j=0; j<20; j++ )
	{
		for (int k=j+1; k<20; k++)
		{
			Vec1.push_back(a[j]);
			Vec2.push_back(a[k]);
		}
	}
	//打印组合的和 积
	Disp();
}