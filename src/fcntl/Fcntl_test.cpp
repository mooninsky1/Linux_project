#include "Fcntl_test.h"
#include <sys/types.h>
#include <unistd.h>
#include <sys/socket.h>
void CFcntl::Test()
{
//	Fcntl1();
//	Fcntl2();
	FcntlToSocket();
}

void CFcntl::Fcntl1()
{
	const char *test_file = "test_lock.txt";
	int file_desc = -1;
	int byte_count = 0;
	const char *byte_to_write = "A";
	struct flock region_1;
	struct flock region_2;
	int res = 0;

	//打开一个文件描述符	
	file_desc = open(test_file, O_RDWR|O_CREAT, 0666);
	if(!file_desc)
	{
		fprintf(stderr, "Unable to open %s for read/write\n", test_file);
		exit(EXIT_FAILURE);
	}
	//给文件添加100个‘A’字符的数据
	for(byte_count = 0; byte_count < 100; ++byte_count)
	{
		write(file_desc, byte_to_write, 1);
	}
	//在文件的第10～29字节设置读锁（共享锁）
	region_1.l_type = F_RDLCK;
	region_1.l_whence = SEEK_SET;
	region_1.l_start = 10;
	region_1.l_len = 20;
	//在文件的40～49字节设置写锁（独占锁）
	region_2.l_type = F_WRLCK;
	region_2.l_whence = SEEK_SET;
	region_2.l_start = 40;
	region_2.l_len = 10;

	printf("Process %d locking file\n", getpid());
	//锁定文件
	res = fcntl(file_desc, F_SETLK, &region_1);
	if(res == -1)
	{
		fprintf(stderr, "Failed to lock region 1\n");
	}
	res = fcntl(file_desc, F_SETLK, &region_1);
	if(res == -1)
	{
		fprintf(stderr, "Failed to lock region 2\n");
	}
	//让程序休眠二分钟，用于测试
	sleep(120);
	printf("Process %d closing file\n", getpid());
	close(file_desc);
	exit(EXIT_SUCCESS);
}


void CFcntl::Fcntl2()
{
	const char *test_file = "test_lock.txt";
	int file_desc = -1;
	int res = 0;
	//打开数据文件
	file_desc = open(test_file, O_RDWR|O_CREAT, 0666);
	if(!file_desc)
	{
		fprintf(stderr, "Unable to open %s for read/write\n", test_file);
		exit(EXIT_FAILURE);
	}
	//设置区域1的锁类型
	struct flock region_test1;
	region_test1.l_type = F_RDLCK;
	region_test1.l_whence = SEEK_SET;
	region_test1.l_start = 10;
	region_test1.l_len = 20;
	region_test1.l_pid = -1;
	//设置区域2的锁类型
	struct flock region_test2;
	region_test2.l_type = F_RDLCK;
	region_test2.l_whence = SEEK_SET;
	region_test2.l_start = 40;
	region_test2.l_len = 10;
	region_test2.l_pid = -1;
	//对区域1的是否可以加一个读锁进行测试
	res = fcntl(file_desc, F_GETLK, &region_test1);
	if(res == -1)
	{
		fprintf(stderr, "Failed to get RDLCK\n");
	}
	if(region_test1.l_pid == -1)
	{
		//可以加一个读锁
		printf("test: Possess %d could lock\n", getpid());
	}
	else
	{
		//不允许加一个读锁
		printf("test:Prossess %d  get lock failure\n", getpid());
	}

	//对区域2是否可以加一个读锁进行测试
	res = fcntl(file_desc, F_GETLK, &region_test2);
	if(res == -1)
	{
		fprintf(stderr, "Failed to get RDLCK\n");
	}
	if(region_test2.l_pid == -1)
	{
		//可以加一个读锁
		printf("test: Possess %d could lock\n", getpid());
	}
	else
	{
		//不允许加一个读锁
		printf("test:Prossess %d  get lock failure\n", getpid());
	}
	exit(EXIT_SUCCESS);
}

//设置socket模式
void CFcntl::FcntlToSocket()
{
	int fd = socket(AF_INET,SOCK_STREAM,0);
	int nFlag = fcntl(fd,F_GETFL,0);
	printf("fd flag is:%d before set\n",nFlag);
	nFlag = fcntl(fd,F_SETFL,nFlag|O_NONBLOCK);
	printf("ret is:%d\n",nFlag);
	nFlag = fcntl(fd,F_GETFL,0);
	printf("fd flag is:%d after set\n",nFlag);
	
}