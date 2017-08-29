//lihf 2012/11/22 ÄÚ´æÐ¹Â©¼ì²é
#include <crtdbg.h>

void Test()
{
	//_CrtSetDbgFlag(_CrtSetDbgFlag(_CRTDBG_REPORT_FLAG) | _CRTDBG_LEAK_CHECK_DF);
	_CrtSetBreakAlloc(156);
	int *a = new int[10];

}