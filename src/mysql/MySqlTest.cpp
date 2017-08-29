#include "MySqlTest.h"
#include <iostream>
int CMySqlDbMgr::Init()
{
	int bReturn = 0;

	m_pSqlConnection = GetStaticMySqlConnection();

	if (m_pSqlConnection == NULL)
	{
		return 0;
	}

	m_pSqlCommand = GetStaticMySqlCommand();

	if (m_pSqlCommand == NULL)
	{
		return 0;
	}
	//

	m_pSqlDataReader = GetStaticMySqlDataReader();

	if (m_pSqlDataReader == NULL)
	{
		return 0;
	}
	//DataBaseInfo *pDataBaseInfo = g_pServerConfig->GetGameDataBaseConfig()->GetGameDataBaseInfo();
	//bReturn = m_pSqlConnection->Open(pDataBaseInfo->szHost, pDataBaseInfo->uPort, pDataBaseInfo->szUserName, pDataBaseInfo->szUserPassword, pDataBaseInfo->szDataBaseName);
	bReturn =m_pSqlConnection->Open("192.168.1.200", 3306, "root", "root", "game");
	if (!bReturn)
	{
		return 0;
	}
	m_pSqlCommand->SetSqlConnection(m_pSqlConnection);
	std::cout<<"mysql init success!\n";
}

void CMySqlTest::Test()
{
	CMySqlDbMgr* pMYSQL = CMySqlDbMgr::GetInstance();
	pMYSQL->Init();
}


