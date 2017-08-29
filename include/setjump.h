#include <setjmp.h>
#include <process.h>
jmp_buf jmpbuffer;
int Test1();
int Test2();
int Test3();
void Test()
{
	int nJmpRet = 0;
	nJmpRet = setjmp(jmpbuffer);
	{
		printf("jmpret = :%d\n",nJmpRet);
	}
	int nget = 0;
	int npid = getpid();
	while(nget = getchar())
	{
		switch(nget)
		{
		case '1':
			Test1();
			break;
		case '2':
			Test2();
			break;
		default:
			Test3();
			break;
		}
	}
}
int Test1()
{
	longjmp(jmpbuffer,1);
	return 0;
}
int Test2()
{
	longjmp(jmpbuffer,2);
	return 0;
}
int Test3()
{
	longjmp(jmpbuffer,3);
	return 0;
}