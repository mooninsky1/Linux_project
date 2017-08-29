#include <sys/types.h>
#include <unistd.h>

class CForkTest
{
public:
	static void Test();
	static void ForkTest();
	static void VforkTest();
};
