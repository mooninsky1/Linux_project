#include "main.h"

int main(int argc, char* argv[])
{	
	//test mongo
	//CMongoHelp::Test();

	//fcntl test
	//CFcntl::Test();

	//ioctl test
	//CIoctl::Test();

	//mmap test
	//Cmmap::Test();

	//memmove test
	//CMemMoveTest::Test();

	//fork test
	//CForkTest::Test();

	//lua test
	//CLuaTest::Test();

	//python test
	//CPythonTest::Test();

	//mysql test
	//CMySqlTest::Test();

	//redis test
	CMyRedisTest().Test();
	printf("Press Enter key to continue...");
	fgetc(stdin);
	return 0;
}

