#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>

class CFcntl
{
public:
	static void Test();

	//对文件区域加锁
	static void Fcntl1();
	static void Fcntl2();

	//设置socket模式
	static void FcntlToSocket();
};
