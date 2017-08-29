#pragma once
#include "time.h"
void Test()
{
	time_t nTimeNow = time(NULL);
	tm* ptm=NULL;
	ptm = gmtime(&nTimeNow);
	printf("utc hour%d\n",ptm->tm_hour);
	ptm = localtime(&nTimeNow);
	printf("local hour%d\n",ptm->tm_hour);
}