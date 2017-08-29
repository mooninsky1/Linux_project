#include "mmap_test.h"
#include <sys/fcntl.h>
#include <stddef.h>
#include <string.h>
#include <unistd.h>
#include <stdio.h>
#include <errno.h>

void Cmmap::Test()
{
	mmap_my();
}

void Cmmap::mmap_other()
{
	int fd;
	off_t length;
	char *addr;
	char *inserted = "## inserted ##"; // this str will be inserted to the file
	int pos = 5; // the position to insert
	fd = open("map.txt", O_RDWR | O_CREAT, 0644);
	if(fd == -1)
	{
	        printf("open file error");
	}
	length = lseek(fd, 1, SEEK_END);
	write(fd, "\0", 1);
	addr = (char *)mmap(NULL, length + strlen(inserted), PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
	memcpy(addr + pos + strlen(inserted), addr + pos, length - pos);
	memcpy(addr + pos, inserted, strlen(inserted));
	//printf("addr: %s", addr);
	close(fd);
	munmap((void *)addr, length);
}
void Cmmap::mmap_my()
{

	const char *test_file = "map.txt";
	int fd = open(test_file,O_RDWR,0666);
	//映射
	//off_t length = lseek(fd, 1, SEEK_END);
    //write(fd, "\0", 1);
	//char* ptr = (char*)mmap(NULL,/*length+*/3,PROT_READ|PROT_WRITE,MAP_SHARED,fd,0);
	char* ptr = (char*)mmap(NULL,/*length+*/10,PROT_READ|PROT_WRITE,MAP_SHARED,fd,0);
	printf("before %s \n",ptr);
	//close(fd);
	//modify
	strcpy(ptr,"lhf00");
	
	//memcpy(ptr,"lhf00",5);
	printf("after %s \n",ptr);
	//解除 只有在调用了munmap()后或者msync()时，才把内存中的相应内容写回磁盘文件，所写内容仍然不能超过文件的大小。
	close(fd);
//	int nFlagUnmap = munmap((void*)ptr,3);
//	printf("ret nFlagUnmap: %d \n",nFlagUnmap);
	int nFlagSync = msync(ptr,10,MS_SYNC);
	printf("ret nFlagSync: %d \n",nFlagSync);
	if(nFlagSync != 0)
	{
		printf("errno:%s \n",strerror(errno));
	}

}