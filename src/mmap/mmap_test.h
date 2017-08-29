#include <sys/mman.h>
/*
1.mmap 使用MAP_SHARED可以改写回文件 用MAP_PRIVATE无法写回文件
*/
class Cmmap
{
public:
	static void Test();

	//跟文件内存映射，直接访问内存，修改文件
	static void mmap_other();
	static void mmap_my();
};
