
#include "MySqlDataReader.h"
#include <stdlib.h>
#include <string.h>



MySqlDataReader::MySqlDataReader(void)
{
	// MySQL对象
	m_pMySQL = NULL;
	// MySQL返回的数据集
	m_pMySQL_Res = NULL;
	// 行数据
	m_pMySqlRow = NULL;
	// 行数量
	m_nRowCount = 0;
	// 列数量
	m_nColumnCount = 0;
	// 列字段长度
	m_pColumnLength = NULL;
}

MySqlDataReader::MySqlDataReader(MYSQL *pMySQL, MYSQL_RES *pMySQL_Res)
{
	// MySQL对象
	m_pMySQL = pMySQL;
	// MySQL返回的数据集
	m_pMySQL_Res = pMySQL_Res;
	//定位游标位置到第一个位置
	mysql_data_seek(m_pMySQL_Res, 0);
	// 得到行数量
	m_nRowCount = (int)mysql_num_rows(m_pMySQL_Res); 
	// 得到列数量
	m_nColumnCount = mysql_num_fields(m_pMySQL_Res);
	// 获取字段长度
	m_pColumnLength = mysql_fetch_lengths(m_pMySQL_Res);
}

MySqlDataReader::~MySqlDataReader(void)
{
	Close();
}

/** @name 公共成员函数 *///////////////////////////////////////////////////
/// @{

void MySqlDataReader::SetMySQLRes(MYSQL *pMySQL, MYSQL_RES *pMySQL_Res)
{
	// MySQL对象
	m_pMySQL = pMySQL;
	// MySQL返回的数据集
	m_pMySQL_Res = pMySQL_Res;
	//定位游标位置到第一个位置
	mysql_data_seek(m_pMySQL_Res, 0);
	// 得到行数量
	m_nRowCount = (int)mysql_num_rows(m_pMySQL_Res); 
	// 得到列数量
	m_nColumnCount = mysql_num_fields(m_pMySQL_Res);
}

/// @}

int MySqlDataReader::Read()
{
	m_pMySqlRow =  mysql_fetch_row(m_pMySQL_Res);
	if (m_pMySqlRow == NULL)
	{
		return 0;
	}
	// 获取字段长度
	m_pColumnLength = mysql_fetch_lengths(m_pMySQL_Res);
	return 1;
}
int MySqlDataReader::MoveNext()
{
	return 1;
}


// 获取索引字符串
const char* MySqlDataReader::GetFieldValue(const char *strFieldName)
{
	int nFiledIndex = GetFieldIndex(strFieldName);
	if (nFiledIndex == -1)
	{
		return NULL;
	}
	return GetFieldValue(nFiledIndex);

}

// 获取索引字符串
const char* MySqlDataReader::GetFieldValue(int nField)
{
	if (nField >= m_nColumnCount)
	{
		return NULL;
	}
	if (m_pMySqlRow == NULL)
	{
		return NULL;
	}
	return m_pMySqlRow[nField];

}

	

// 获取索引整数
int MySqlDataReader::GetIntField(int nField, int nNullValue/*=0*/)
{
	const char* pszFieldValue = GetFieldValue(nField);
	if (pszFieldValue == NULL)
	{
		return nNullValue;
	}
	return atoi(pszFieldValue);

}

// 获取索引整数
int MySqlDataReader::GetIntField(const char *strFieldName, int nNullValue/*=0*/)
{
	int nFieldIndex = GetFieldIndex(strFieldName);
	return GetIntField(nFieldIndex, nNullValue);
}

// 获取索引浮点数
float MySqlDataReader::GetFloatField(int nField, float fNullValue/*=0.0*/)
{
	const char* pszFieldValue = GetFieldValue(nField);
	if (pszFieldValue == NULL)
	{
		return fNullValue;
	}
	return (float)atof(pszFieldValue);
}

// 获取索引浮点数
float MySqlDataReader::GetFloatField(const char *strFieldName, float fNullValue/*=0.0*/)
{
	int nFieldIndex = GetFieldIndex(strFieldName);
	return GetFloatField(nFieldIndex, fNullValue);
}

// 获取索引浮点数
double MySqlDataReader::GetDoubleField(int nField, double dNullValue/*=0.0*/)
{
	const char* pszFieldValue = GetFieldValue(nField);
	if (pszFieldValue == NULL)
	{
		return dNullValue;
	}
	return atof(pszFieldValue);
}

// 获取索引浮点数
double MySqlDataReader::GetDoubleField(const char *strFieldName, double dNullValue/*=0.0*/)
{
	int nFieldIndex = GetFieldIndex(strFieldName);
	return GetDoubleField(nFieldIndex, dNullValue);
}

// 获取索引字符串
string MySqlDataReader::GetStringField(int nField, const char *strNullValue/*=""*/)
{
	const char* pszFieldValue = GetFieldValue(nField);
	if (pszFieldValue == NULL)
	{
		return strNullValue;
	}
	return pszFieldValue;
}

// 获取索引字符串
string MySqlDataReader::GetStringField(const char *strFieldName, const char *strNullValue/*=""*/)
{
	int nFieldIndex = GetFieldIndex(strFieldName);
	return GetStringField(nFieldIndex, strNullValue);
}

// 获取索引二进制
int MySqlDataReader::GetBinaryField(int nField, char *lpszContent, unsigned int uMaxLen, int nNullValue/* = 0*/)
{
	int nFieldLength = GetFieldLength(nField);
	const char* pszFieldValue = GetFieldValue(nField);
	if (pszFieldValue == NULL)
	{
		return nNullValue;
	}
	if (uMaxLen < (unsigned int)nFieldLength)
	{
		return nNullValue;
	}
	memcpy(lpszContent, pszFieldValue, nFieldLength);
	return nFieldLength;
}

// 获取索引二进制
int MySqlDataReader::GetBinaryField(const char *strFieldName, char *lpszContent, unsigned int uMaxLen, int nNullValue/* = 0*/)
{
	int nFieldIndex = GetFieldIndex(strFieldName);
	return GetBinaryField(nFieldIndex, lpszContent, uMaxLen, nNullValue);
}

// 判断字段是否为空
int MySqlDataReader::IsFieldNull(int nField)
{
	const char* pszFieldValue = GetFieldValue(nField);
	if (pszFieldValue == NULL)
	{
		return 1;
	}
	return 0;
}

// 判断字段是否为空
int MySqlDataReader::IsFieldNull(const char *strFieldName)
{
	int nFieldIndex = GetFieldIndex(strFieldName);
	return IsFieldNull(nFieldIndex);
}

// 获取索引字段名称
const char* MySqlDataReader::GetFieldName(int nColumn)
{
	mysql_field_seek(m_pMySQL_Res, nColumn);
	MYSQL_FIELD *pMySQL_Field = mysql_fetch_field(m_pMySQL_Res);
	if (pMySQL_Field != NULL)
	{
		return pMySQL_Field->name;
	}
	return  NULL;
}

// 获取索引位置
int MySqlDataReader::GetFieldIndex(const char *strFieldName)
{
	if (strFieldName == NULL)
	{
		return -1;
	}
	// 定位到第0列
	for (int i = 0; i < m_nColumnCount; i++)
	{
		if (strcmp(GetFieldName(i), strFieldName) == 0)
		{
			return i;
		}
	}
	return -1;
}

// 获取字段长度
long MySqlDataReader::GetFieldLength(int nField)
{
	if (nField >= m_nColumnCount)
	{
		return NULL;
	}
	if (m_pMySqlRow == NULL)
	{
		return NULL;
	}
	return m_pColumnLength[nField];
}

// 获取字段长度
long MySqlDataReader::GetFieldLength(const char *strFieldName)
{
	int nFiledIndex = GetFieldIndex(strFieldName);
	if (nFiledIndex == -1)
	{
		return NULL;
	}
	return GetFieldLength(nFiledIndex);
}

// 获取字段列总数
int MySqlDataReader::GetFieldCount()
{
	return m_nColumnCount;
}

// 获取记录总数
int MySqlDataReader::GetRowCount()
{
	return m_nRowCount;
}

// 终结操作
void MySqlDataReader::Close()
{
	if (m_pMySQL != NULL)
	{
		do
		{
			MYSQL_RES* pMySQL_Res = mysql_store_result(m_pMySQL);
			mysql_free_result(pMySQL_Res);
		}
		while ((0 == mysql_next_result(m_pMySQL)));
	}
	m_pMySqlRow = NULL;
	m_pMySQL_Res = NULL;
	m_nColumnCount = 0;
	m_nRowCount = 0;
}

// 删除本身
void MySqlDataReader::DeleteThis(void)
{
	delete this;
}

#ifdef __MY_SQL__

// 获取MYSQL读取对象
ISqlDataReader* GetStaticMySqlDataReader()
{
	static MySqlDataReader *pMySqlDataReader = NULL;
	if (pMySqlDataReader == NULL)
	{
		pMySqlDataReader = new MySqlDataReader();
	}
	return pMySqlDataReader;
}

// 实例化MYSQL读取对象
ISqlDataReader* GetNewMySqlDataReader()
{
	MySqlDataReader *pMySqlDataReader = new MySqlDataReader();
	return pMySqlDataReader;
}

#endif	// __MY_SQL__

