#pragma once
#include "mongo/client/dbclient.h"


class CDBMgr
{
public:
	CDBMgr(){};
	~CDBMgr(){};
public:
	static CDBMgr*  Instance()
	{
		static CDBMgr obj;
		return &obj;
	}
	int Init(const std::string ip, const std::string port);
	mongo::DBClientConnection* GetInstance(){ return &m_conn;};
	int Insert(const std::string& collection, mongo::BSONObjBuilder& obj);
	int Update(const std::string& collection, const mongo::Query& query, mongo::BSONObjBuilder& obj);
	int Remove(const std::string& collection, const mongo::Query& query);
	int Truncate(const std::string& collection);
private:
	mongo::DBClientConnection m_conn;
};

#define P_DB_MGR CDBMgr::Instance()