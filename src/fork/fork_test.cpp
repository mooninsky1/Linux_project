#include "fork_test.h"
#include <stdio.h>
void CForkTest::Test()
{
	printf("hi fork test now !\n");
	//ForkTest();
	VforkTest();
}
void CForkTest::ForkTest()
{
	int i=0;
	pid_t pid=0;
	pid = fork();
	if(pid < 0)
	{
		printf("fork error\n");
		return;
	}
	else if(0 == pid)
	{//child
		i++;
		printf("I am child pid:%d i:%d\n",getpid(),i);
	}
	else 
	{
		i++;
		printf("I am parent pid:%d i:%d\n",getpid(),i);
	}
}
void CForkTest::VforkTest()
{
	int i=0;
	pid_t pid=0;
	pid = vfork();
	if(pid < 0)
	{
		printf("fork error\n");
		return;
	}
	else if(0 == pid)
	{//child
		i++;
		printf("I am child pid:%d i:%d\n",getpid(),i);
		_exit(0);//vfork 保证子进程先执行，且子进程调用exit退出后父进程才继续执行
	}
	else 
	{
		i++;
		printf("I am parent pid:%d i:%d\n",getpid(),i);
		//vfork 共享数据段，打印i=2
	}
}


