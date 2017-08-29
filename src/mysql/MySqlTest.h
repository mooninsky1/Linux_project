#include "ISqlDataBase.h"

class CMySqlDbMgr
{
public:
	int Init();
	static CMySqlDbMgr* GetInstance()
		{
			static CMySqlDbMgr db;
			return &db;
		}
private:
	// 数据库连接对象
	ISqlConnection *m_pSqlConnection;
	// 数据库操作对象
	ISqlCommand *m_pSqlCommand;
	// 数据库读取对象
	ISqlDataReader *m_pSqlDataReader;

};

class CMySqlTest
{
public:
	static void Test();

};
