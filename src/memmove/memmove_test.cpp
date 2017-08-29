#include "memmove_test.h"
#include <stdio.h>
#include <string.h>

void CMemMoveTest::Test()
{
	if(1)
	{
		char sz[]= "hello world";
		memmove(sz,sz+4,3);
		printf("%s\n",sz); //验证是不是 " wo      rld"  实际打印: "o wlo world"
		//结论memmove是不会清空dst 到 src这段地址,也就是不是我想的会置0在将src拷贝3个字节，还有一点拷贝起始包括src
	}
	
}

