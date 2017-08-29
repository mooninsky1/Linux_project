#include <iostream>
#include <stdlib.h>
//lihf 2012/11/20 算法导论15章

//进入流水线1的时间
const int e1 = 2;
//进入流水线2的时间
const int e2 = 4;

//经过装配站的时间
const int s1[6] = {7,9,3,4,8,4};
const int s2[6] = {8,5,6,4,5,7};

//切换流水线装配站时间
const int t[2][5] = {2,3,1,3,4,
					 2,1,2,2,1};
//退出流水线时间
const int x1 = 3;
const int x2 = 2;

//求解：计算出一条最快流水线

//子问题最优解
int f1[5]={0};
int f2[5];

//最优解跟踪过程，打印最快流水线路径
int l1[6];
int l2[6];
void Test()
{
	//子问题最优解
	f1[0] = e1 + s1[0];
	f2[0] = e2 + s2[0];
	//FasttestWay();
	for (int i = 1; i < 6; i++)
	{
		if (f1[i-1]+s1[i] < f2[i-1]+t[1][i-1]+s1[i])
		{
			f1[i] = f1[i-1]+s1[i];
			l1[i] = 1;
		}
		else
		{
			f1[i] = f2[i-1]+t[1][i-1]+s1[i];
			l1[i] = 2;
		}

		if ( (f2[i-1]+s2[i]) < (f1[i-1]+t[2][i-1]+s1[i]) )
		{
			f2[i] = f2[i-1]+s2[i];
			l2[i] = 1;
		}
		else
		{
			f2[i] = f1[i-1]+t[2][i-1]+s1[i];
			l2[i] = 2;
		}
	}
	std::cout<<f1[5]<<std::endl;
	std::cout<<f2[5]<<std::endl;
}