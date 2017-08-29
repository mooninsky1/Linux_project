
#include "MySqlConnection.h"
#include <iostream>

MySqlConnection::MySqlConnection(void)
{
	m_pMySQL = NULL;
}

MySqlConnection::~MySqlConnection(void)
{
	Close();
}

// 打开数据库
int MySqlConnection::Open(const char *szHost, int nPort, const char *szUser, const char *szPassword, const char *szDBName)
{
	if (m_pMySQL != NULL)
	{
		Close();
	}
	m_pMySQL = mysql_init(NULL);
	if (m_pMySQL == NULL)
	{
		std::cout << "Open MySql Error:m_pMySQL is NULL" << std::endl;
		return 0;
	}
	if (mysql_real_connect(m_pMySQL, szHost, szUser, szPassword, szDBName, nPort, NULL, CLIENT_MULTI_STATEMENTS) == NULL)
	{
		const char *lpszError = mysql_error(m_pMySQL);
		std::cout << "Open MySql Error:" << lpszError << std::endl;
		Close();
		return 0;
	}
	return 1;
}

// 关闭数据库
void MySqlConnection::Close(void)
{
	if ( m_pMySQL != NULL )
	{
		mysql_close(m_pMySQL);
		m_pMySQL = NULL;
	}
}

// 删除本身
void MySqlConnection::DeleteThis(void)
{
	delete this;
}

// 获取数据库对象
MYSQL* MySqlConnection::GetMySql(void)
{
	return m_pMySQL;
}

#ifdef __MY_SQL__

// 获取MYSQL连接对象
ISqlConnection* GetStaticMySqlConnection()
{
	static MySqlConnection *pMySqlConnection = NULL;
	if (pMySqlConnection == NULL)
	{
		pMySqlConnection = new MySqlConnection();
	}
	return pMySqlConnection;
}

// 实例化MYSQL连接对象
ISqlConnection* GetNewMySqlConnection()
{
	MySqlConnection *pMySqlConnection = new MySqlConnection();
	return pMySqlConnection;
}

#endif	// __MY_SQL__
