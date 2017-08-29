#include "mongodbTest.h"
#include "../common/game_util.h"
#include <memory>
#include <iostream>

void CMongoHelp::Test()
{
	Init();
	Query();
}
void CMongoHelp::Init()
{
	int iRet = P_DB_MGR->Init("127.0.0.1","27018");
	if (iRet != 0)
	{	
		printf("DB init error");
		return;
	}
}
void CMongoHelp::Update()
{
	int roleid=100;
	int playerid=1000;
	for (int i=1; i<10; i++)
	{
		mongo::BSONObjBuilder obj;
		obj.appendNumber("id", roleid);
		obj.append("player_id", playerid);
		obj.append("battle_id", i);
		P_DB_MGR->Update("test.lhf",QUERY("id" << (long long)roleid << "player_id" << playerid << "battle_id" <<i), obj);
	}
}

void CMongoHelp::Query()
{
	int roleid=0;
	std::string scolections;
	std::cout<<"intput db collection eg:gamedb.role\n";
	std::cin>>scolections;
	
	while(true)
	{
		//std::cin.clear();
		//std::cin.sync();
		std::cout<<std::flush;
		std::cout<<"input roleid:";
		std::cin>>roleid;
		std::cout<<std::endl;
		if(0 == roleid)
		{
			std::cout<<"input id:"<<roleid<<"exit"<<std::endl;
			break;
		}
		else
		{
			cTimeEscape time("test mongo query",true);
			std::cout<<"col:"<<scolections<<"id:"<<roleid<<std::endl;
			std::auto_ptr<mongo::DBClientCursor> cursor = P_DB_MGR->GetInstance()->query(scolections.c_str(), QUERY("id" <<(long long)roleid));
			if(cursor->more()) 
			{
				std::cout<<"find"<<std::endl;
			}
			else
			{
				std::cout<<"not find"<<std::endl;
			}
		}
	}
	
}