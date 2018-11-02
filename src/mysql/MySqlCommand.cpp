
#include "MySqlCommand.h"
#include "MySqlDataReader.h"
#include <iostream>
#include <string.h>


MySqlCommand::MySqlCommand(void)
{
	m_pMySqlConnection = NULL;
	m_pMySqlParameter = NULL;
	m_pMySqlStmt = NULL;
}

MySqlCommand::~MySqlCommand(void)
{
	if (m_pMySqlParameter != NULL)
	{
		delete m_pMySqlParameter;
		m_pMySqlParameter = NULL;
	}
}

MySqlCommand::MySqlCommand(MySqlConnection *pMySqlConnection)
{
	m_pMySqlConnection = pMySqlConnection;
	if (m_pMySqlParameter == NULL)
	{
		m_pMySqlParameter = new MySqlParameter();
		m_pMySqlParameter->Init();
	}
}


void MySqlCommand::SetSqlConnection(ISqlConnection *pSqlConnection)
{
	m_pMySqlConnection = (MySqlConnection*)pSqlConnection;
	if (m_pMySqlParameter == NULL)
	{
		m_pMySqlParameter = new MySqlParameter();
		m_pMySqlParameter->Init();
	}
}

// 添加存储过程参数（整数类型）
void MySqlCommand::AddIntInputParameter(const char *lpszName, int nValue)
{

}

// 添加存储过程参数（短整数类型）
void MySqlCommand::AddShortInputParameter(const char *lpszName, short nValue)
{

}
	

// 添加存储过程参数（字节类型）
void MySqlCommand::AddByteInputParameter(const char *lpszName, char byValue)
{

}
	
// 添加存储过程参数（字符类型）
void MySqlCommand::AddStringInputParameter(const char *lpszName, const char *lpszValue)
{

}

// 添加存储过程参数（二进制类型）
void MySqlCommand::AddBinaryInputParameter(const char *lpszName, char *lpBinaryValue, int nLen)
{
	m_pMySqlParameter->AddBinaryInputParameter(lpszName, lpBinaryValue, nLen);
}

// 获取存储过程返回的参数（整数类型）
int MySqlCommand::GetIntParameterValue(const char *lpszName)
{
	return 0;
}
	
// 添加输出存储过程参数（整数类型）
void MySqlCommand::AddIntOutputParameter(const char *lpszName)
{

}

// 清空对象参数
void MySqlCommand::ClearParameter()
{

}

// 执行无返回值
void MySqlCommand::ExecuteNonQuery(const char * strSQL, int bUseStoredProc/* = 0*/)
{
	if (m_pMySqlConnection == NULL)
	{
		std::cout << "MySqlCommand::ExecuteNonQuery m_pMySqlConnection is NULL" << std::endl;
		return;
	}
	MYSQL *pMySQL = m_pMySqlConnection->GetMySql();
	if (pMySQL == NULL)
	{
		std::cout << "MySqlCommand::ExecuteNonQuery pMySQL is NULL" << std::endl;
		return;
	}
	if (!bUseStoredProc)
	{
		int nTextLen = (int)strlen(strSQL);
		if (mysql_real_query(pMySQL, strSQL, (long)nTextLen) != 0)
		{
			const char *lpszError = mysql_error(pMySQL);
			std::cout << "MySqlCommand::ExecuteNonQuery error:" << lpszError << std::endl;
			return;
		}
		//
		do
		{
			MYSQL_RES* pMySQL_Res = mysql_store_result(pMySQL);
			mysql_free_result(pMySQL_Res);
		}
		while ((0 == mysql_next_result(pMySQL)));
		return;
	}
	if (m_pMySqlStmt == NULL)
	{
		m_pMySqlStmt = mysql_stmt_init(pMySQL);
	}
	m_pMySqlParameter->RunExecuteBindParameter(pMySQL, m_pMySqlStmt, strSQL);
}

// 执行无返回值
int MySqlCommand::ExecuteQuery(const char * strSQL, int bUseStoredProc/* = 0*/)
{
	if (m_pMySqlConnection == NULL)
	{
		std::cout << "MySqlCommand::ExecuteQuery m_pMySqlConnection is NULL" << std::endl;
		return 0;
	}
	MYSQL *pMySQL = m_pMySqlConnection->GetMySql();
	if (pMySQL == NULL)
	{
		std::cout << "MySqlCommand::ExecuteQuery pMySQL is NULL" << std::endl;
		return 0;
	}
	
	int nTextLen = (int)strlen(strSQL);
	if (mysql_real_query(pMySQL, strSQL, (long)nTextLen) != 0)
	{
		const char *lpszError = mysql_error(pMySQL);
		std::cout << "MySqlCommand::ExecuteQuery error:" << lpszError << std::endl;
		return 0;
	}
	// 返回操作影响的行数
	int nReturn = (int)mysql_affected_rows(pMySQL);
	//
	do
	{
		MYSQL_RES* pMySQL_Res = mysql_store_result(pMySQL);
		mysql_free_result(pMySQL_Res);
	}
	while ((0 == mysql_next_result(pMySQL)));

	return nReturn;
}

// 执行查询结果
int MySqlCommand::ExecuteScalar(const char * strSQL, int bUseStoredProc/* = 0*/)
{
	if (m_pMySqlConnection == NULL)
	{
		std::cout << "MySqlCommand::ExecuteScalar m_pMySqlConnection is NULL" << std::endl;
		return 0;
	}
	MYSQL *pMySQL = m_pMySqlConnection->GetMySql();
	if (pMySQL == NULL)
	{
		std::cout << "MySqlCommand::ExecuteScalar pMySQL is NULL" << std::endl;
		return 0;
	}
	//
	MySqlDataReader myMySqlDataReader;
	int nTextLen = (int)strlen(strSQL);
	if (mysql_real_query(pMySQL, strSQL, (long)nTextLen) != 0)
	{
		const char *lpszError = mysql_error(pMySQL);
		std::cout << "MySqlCommand::ExecuteScalar error:" << lpszError << std::endl;
		return 0;
	}
	MYSQL_RES *m_pMySQL_Res = mysql_store_result(pMySQL);
	myMySqlDataReader.SetMySQLRes(pMySQL, m_pMySQL_Res);
	int nReturn = 0;
	if (myMySqlDataReader.Read())
	{
		nReturn = myMySqlDataReader.GetIntField(0);
	}
	myMySqlDataReader.Close();
	return nReturn;
}

// 执行查询结果
ISqlDataReader* MySqlCommand::ExecuteReader(const char * strSQL, int bUseStoredProc/* = 0*/)
{
	if (m_pMySqlConnection == NULL)
	{
		std::cout << "ISqlDataReader MySqlCommand::ExecuteReader::m_pMySqlConnection is NULL" << std::endl;
		return NULL;
	}
	MYSQL *pMySQL = m_pMySqlConnection->GetMySql();
	if (pMySQL == NULL)
	{
		std::cout << "ISqlDataReader MySqlCommand::ExecuteReader::pMySQL is NULL" << std::endl;
		return NULL;
	}
	//
	int nTextLen = (int)strlen(strSQL);
	if (mysql_real_query(pMySQL, strSQL, (long)nTextLen) != 0)
	{
		const char *lpszError = mysql_error(pMySQL);
		std::cout << "ISqlDataReader MySqlCommand::ExecuteReader::error:" << lpszError << std::endl;
		return NULL;
	}
	MYSQL_RES *m_pMySQL_Res = mysql_store_result(pMySQL);
	MySqlDataReader *pMySqlDataReader = new MySqlDataReader(pMySQL, m_pMySQL_Res);
	return pMySqlDataReader;
}

// 执行查询结果
int MySqlCommand::ExecuteReader(ISqlDataReader *pSqlDataReader, const char * strSQL, int bUseStoredProc/* = 0*/)
{
	if (m_pMySqlConnection == NULL)
	{
		std::cout << "int MySqlCommand::ExecuteReader::m_pMySqlConnection is NULL" << std::endl;
		return 0;
	}
	MYSQL *pMySQL = m_pMySqlConnection->GetMySql();
	if (pMySQL == NULL)
	{
		std::cout << "int MySqlCommand::ExecuteReader::pMySQL is NULL" << std::endl;
		return 0;
	}
	//
	int nTextLen = (int)strlen(strSQL);
	if (mysql_real_query(pMySQL, strSQL, (long)nTextLen) != 0)
	{
		const char *lpszError = mysql_error(pMySQL);
		std::cout << "int MySqlCommand::ExecuteReader::error:" << lpszError << std::endl;
		return 0;
	}
	MYSQL_RES *pMySQL_Res = mysql_store_result(pMySQL);
	MySqlDataReader *pMySqlDataReader = (MySqlDataReader*)pSqlDataReader;
	pMySqlDataReader->SetMySQLRes(pMySQL, pMySQL_Res);
	return 1;
}

// 
void MySqlCommand::ExecuteBegin(void)
{
	if (m_pMySqlConnection == NULL)
	{
		return;
	}
	MYSQL *pMySQL = m_pMySqlConnection->GetMySql();
	if (pMySQL == NULL)
	{
		return;
	}
	//
	if (mysql_real_query(pMySQL, "START TRANSACTION", (unsigned long)strlen("START TRANSACTION")) != 0)
	{
		return;
	}
}

//
void MySqlCommand::ExecuteEnd(void)
{
	if (m_pMySqlConnection == NULL)
	{
		return;
	}
	MYSQL *pMySQL = m_pMySqlConnection->GetMySql();
	if (pMySQL == NULL)
	{
		return;
	}
	//
	if (mysql_real_query( pMySQL, "COMMIT", (unsigned long)strlen("COMMIT")) != 0)
	{
		return;
	}
}

// 删除本身
void MySqlCommand::DeleteThis(void)
{
	delete this;
}

#ifdef __MY_SQL__

// 获取MYSQL命令对象
ISqlCommand* GetStaticMySqlCommand()
{
	static MySqlCommand *pMySqlCommand = NULL;
	if (pMySqlCommand == NULL)
	{
		pMySqlCommand = new MySqlCommand();
	}
	return pMySqlCommand;
}

// 实例化MYSQL命令对象
ISqlCommand* GetNewMySqlCommand()
{
	MySqlCommand *pMySqlCommand = new MySqlCommand();
	return pMySqlCommand;
}


#endif	// __MY_SQL__
