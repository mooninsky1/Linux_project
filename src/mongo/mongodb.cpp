#include "mongodb.h"

int CDBMgr::Init(const std::string ip, const std::string port)
{
	// 强制要求输入参数不能为空
	if (ip.empty() || port.empty())
	{
		printf(("invalid database host or port"));
		return -1;
	}

	std::string errmsg;
	if (!m_conn.connect(ip + ":" + port , errmsg)) 
	{
		printf(("mongo db [%s:%s] couldn't connect: %s", ip.c_str(), port.c_str(), errmsg.c_str()));
		return -1;
	}

	printf("server connected to database [%s:%s]\n", ip.c_str(), port.c_str());

	return 0;
}

int  CDBMgr::Insert(const std::string& collection, mongo::BSONObjBuilder& obj)
{
	m_conn.insert(collection, obj.obj());
	return 0;
}

int CDBMgr::Update(const std::string& collection, const mongo::Query& query,mongo::BSONObjBuilder& obj)
{
	m_conn.update(collection, query, obj.obj(), true);

	return 0;
}


int CDBMgr::Remove(const std::string& collection, const mongo::Query& query)
{
	//m_conn.update(collection.c_str(), obj());
	m_conn.remove(collection, query, false);

	return 0;
}

int CDBMgr::Truncate(const std::string& collection)
{
	m_conn.remove(collection , mongo::BSONObj());
	return 0;
}

