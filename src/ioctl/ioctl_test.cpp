#include "ioctl_test.h"
#include <sys/socket.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/fcntl.h>

void CIoctl::Test()
{
	SetSocketNonblock();
}

	//设置socet非阻塞
void CIoctl::SetSocketNonblock()
	{
		int fd = socket(AF_INET,SOCK_STREAM,0);
		int flag =0;//0: clear 1: set
		flag = fcntl(fd,F_GETFL,0);
		printf("flag is:%d before ioctl\n",flag);
		/*FIONBIO ： 根据ioctl的第三个参数指向一个0 或非0 值分别清除或设置本套接口的非阻塞标志。
		本请求和O_NONBLOCK 文件状态标志等效，而该标志通过fcntl 的F_SETFL 命令清除或设置。*/
		ioctl(fd,FIONBIO,flag);
		flag = fcntl(fd,F_GETFL,0);
		printf("flag is:%d after ioctl\n",flag);
	}

