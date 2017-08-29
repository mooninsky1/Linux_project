
#include "game_util.h"

//格式 时 分 秒 2013-07-19-10:30:59 用于打印日志
std::string GetTimeSecond()
{
    time_t theCurrentTime = time(NULL);
    tm * myCurrentTime = localtime(&theCurrentTime);
    char szTime[10] = {'0'};
    sprintf(szTime, "%d:%.2d:%.2d", myCurrentTime->tm_hour, myCurrentTime->tm_min, myCurrentTime->tm_sec);
    std::string str = szTime;
    return str;
}
cTimeEscape::~cTimeEscape()
{
	timeval timeend;
	gettimeofday(&timeend, NULL);
	double dMopCost = 0;
	dMopCost = (timeend.tv_sec*1000 - m_timestart.tv_sec*1000 + 0.001*(timeend.tv_usec - m_timestart.tv_usec));
	if (dMopCost > 100.0 || m_bPrint)
	{
		printf("%s begin time:%s cost time: %f  ms\n",m_strTag.c_str(),m_strTimeStart.c_str(),dMopCost );
		std::multimap<std::string,double>::iterator it = m_mapTagTime.begin();
		if (it != m_mapTagTime.end())
		{
			printf(("---------------------------------------------------"));
			for (; it != m_mapTagTime.end(); it++)
			{
				printf("%s  cost time: %f  ms\n",it->first.c_str(),it->second );
			}
			printf(("++++++++++++++++++++++++++++++++++++++++++++++++++++"));
		}
	} 
	if (NULL != m_pTimeFather)
	{
		m_pTimeFather->GetDate(m_strTag,dMopCost);
	}
}
//观测其他模块的数据
void cTimeEscape::Register(cTimeEscape* Father)
{
	m_pTimeFather = Father;
}
//收集数据
void cTimeEscape::GetDate(std::string strTag,double timecost) 
{
	m_mapTagTime.insert(
		make_pair(strTag,timecost)
		);
}