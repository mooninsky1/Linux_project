#include "MySqlBindData.h"
#include "mysql.h"
#include <string.h>

MySqlBindData::MySqlBindData(void)
{
	// 长度
	m_nLength = 0;
	// 缓冲区类型
	m_nBufferType = 0;
	// 分配足够大的缓冲区
	m_pBuffer = new char[8000];
}

MySqlBindData::~MySqlBindData(void)
{
	if (m_pBuffer != 0)
	{
		delete[] m_pBuffer;
		m_pBuffer = 0;
	}
}

// 设置整数类型
void MySqlBindData::SetValue(int nValue)
{
	m_nLength = 4;
	m_nBufferType = MYSQL_TYPE_LONG;
	*(int*)m_pBuffer = nValue;
}

// 设置短整数类型
void MySqlBindData::SetValue(short nValue)
{
	m_nLength = 2;
	m_nBufferType = MYSQL_TYPE_SHORT;
	*(short*)m_pBuffer = nValue;
}

// 设置字节类型
void MySqlBindData::SetValue(char byValue)
{
	m_nLength = 1;
	m_nBufferType = MYSQL_TYPE_TINY;
	*(char*)m_pBuffer = byValue;
}

// 设置字符类型
void MySqlBindData::SetValue(const char *lpszValue)
{
	int nTextLen = (int)strlen(lpszValue);
	m_nLength = nTextLen + 1;
	m_nBufferType = MYSQL_TYPE_VARCHAR;
	strcpy((char*)m_pBuffer, lpszValue);
}

// 设置二进制类型
void MySqlBindData::SetValue(char *lpBinaryValue, int nBinaryLen)
{
	m_nLength = nBinaryLen;
	m_nBufferType = MYSQL_TYPE_BLOB;
	memcpy(m_pBuffer, lpBinaryValue, nBinaryLen);
}


// 获取指向长度指针
int MySqlBindData::GetLength()
{
	return m_nLength;
}


// 获取指向缓冲区指针
void* MySqlBindData::GetBufferPointer()
{
	return m_pBuffer;
}

// 获取缓冲区类型
int MySqlBindData::GetBufferType()
{
	return m_nBufferType;
}