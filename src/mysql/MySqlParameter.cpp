#include "MySqlParameter.h"
#include "MySqlDataReader.h"
#include <string.h>
#include <iostream>
using namespace std;
MySqlParameter::MySqlParameter(void)
{
	// 绑定参数列表
	m_pMySqlBindData = NULL;
}

MySqlParameter::~MySqlParameter(void)
{
	if (m_pMySqlBindData != NULL)
	{
		delete m_pMySqlBindData;
		m_pMySqlBindData = NULL;
	}
}

// 初始化
int MySqlParameter::Init()
{
	m_pMySqlBindData = new MySqlBindData();
	if (m_pMySqlBindData == NULL)
	{
		return 0;
	}
	return 1;
}


// 添加存储过程参数（二进制类型）
void MySqlParameter::AddBinaryInputParameter(const char *lpszName, char *lpBinaryValue, int nBinaryLen)
{
	m_pMySqlBindData->SetValue(lpBinaryValue, nBinaryLen);
}

// 执行绑定参数
void MySqlParameter::RunExecuteBindParameter(MYSQL *pMySql, MYSQL_STMT *pMySqlStmt, const char * strSQL)
{
	if (mysql_stmt_prepare(pMySqlStmt, strSQL, (unsigned long)strlen(strSQL)))   
	{
		const char *lpszError = mysql_stmt_error(pMySqlStmt);
		std::cout << "mysql_stmt_prepare error:" << lpszError << std::endl;
		return;
	}
	unsigned long length = 0;
	MYSQL_BIND myMySqlBind;
	memset(&myMySqlBind, 0, sizeof(MYSQL_BIND));
	void *lpszBuffer = m_pMySqlBindData->GetBufferPointer();
	int nLength = m_pMySqlBindData->GetLength();
	myMySqlBind.buffer = lpszBuffer;
	myMySqlBind.buffer_type = MYSQL_TYPE_BLOB;
	myMySqlBind.length = &length;
	myMySqlBind.is_null = 0;
	if (mysql_stmt_bind_param(pMySqlStmt, &myMySqlBind))
	{
		const char *lpszError = mysql_stmt_error(pMySqlStmt);
		std::cout << "mysql_stmt_bind_param error:" << lpszError << std::endl;
		return;
	}
	if (mysql_stmt_send_long_data(pMySqlStmt, 0, (const char*)lpszBuffer, nLength))
	{
		const char *lpszError = mysql_stmt_error(pMySqlStmt);
		std::cout << "mysql_stmt_send_long_data error:" << lpszError << std::endl;
		return;
	}
	if (mysql_stmt_execute(pMySqlStmt))
	{
		const char *lpszError = mysql_stmt_error(pMySqlStmt);
		std::cout << "mysql_stmt_execute error:" << lpszError << std::endl;
		return;
	}
	//
	do
	{
		MYSQL_RES* pMySQL_Res = mysql_store_result(pMySql);
		mysql_free_result(pMySQL_Res);
	}
	while ((0 == mysql_next_result(pMySql)));
}
