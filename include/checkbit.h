//取一个整数 第几位到第位的内容
#include "stdio.h"
void Test()
{
	int lvalue =0;
	int nbitposSta = 48;
	int nbitposEnd = 56;
	int nbitlen = 8; // 56-48
	long lowMask = 0x00FF; // 1 << nbitlen
	scanf("%d",&lvalue);
	printf("input value is:%d\n",lvalue);
	while(lvalue)
	{
		lvalue = lvalue >> 48;
		lvalue = lvalue | lowMask;
		printf("cut  value is:%l\n",lvalue);

		scanf("input value:%l",&lvalue);
		printf("input value is:%l\n",lvalue);

	}
}