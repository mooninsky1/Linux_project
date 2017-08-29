#ifndef __MYSQL_DATA_READER_H__
#define __MYSQL_DATA_READER_H__


#include "mysql.h"
#include "ISqlDataBase.h"

class MySqlDataReader : public ISqlDataReader
{
private:

	/** @name  私有成员变量 */////////////////////////////////////////////////////
    /// @{

	// MySQL对象
	MYSQL *m_pMySQL;
	// MySQL返回的数据集
	MYSQL_RES *m_pMySQL_Res;
	// 行数量
	int	m_nRowCount;
	// 列数量
	int m_nColumnCount;
	// 点段数据长度
	unsigned long *m_pColumnLength;
	// 行数据
	MYSQL_ROW m_pMySqlRow;

	/// @}

public:
	MySqlDataReader(void);
	~MySqlDataReader(void);

public:
	MySqlDataReader(MYSQL *pMySQL, MYSQL_RES *pMySQL_Res);
public:

	/** @name 公共成员函数 *///////////////////////////////////////////////////
    /// @{

	void SetMySQLRes(MYSQL *pMySQL, MYSQL_RES *pMySQL_Res);
	
	/// @}

public:

	/** @name 虚成员函数 *///////////////////////////////////////////////////
    /// @{

	// 是否已经读取结束
	virtual int Read();
	// 移动记录到下一条
	virtual int MoveNext();
	// 获取索引字符串
	virtual const char* GetFieldValue(int nField);
	// 获取索引字符串
	virtual const char* GetFieldValue(const char *strFieldName);
	// 获取索引整数
	virtual int GetIntField(int nField, int nNullValue = 0);
	// 获取索引整数
	virtual int GetIntField(const char *strFieldName, int nNullValue = 0);
	// 获取索引浮点数
	virtual float GetFloatField(int nField, float fNullValue = 0.0);
	// 获取索引浮点数
	virtual float GetFloatField(const char *strFieldName, float fNullValue = 0.0);
	// 获取索引浮点数
	virtual double GetDoubleField(int nField, double dNullValue = 0.0);
	// 获取索引浮点数
	virtual double GetDoubleField(const char *strFieldName, double dNullValue = 0.0);
	// 获取索引字符串
	virtual string GetStringField(int nField, const char *strNullValue = "");
	// 获取索引字符串
	virtual string GetStringField(const char *strFieldName, const char *strNullValue = "");
	// 获取索引二进制
	virtual int GetBinaryField(int nField, char *lpszContent, unsigned int uMaxLen, int nNullValue = 0);
	// 获取索引二进制
	virtual int GetBinaryField(const char *strFieldName, char *lpszContent, unsigned int uMaxLen, int nNullValue = 0);
	// 判断字段是否为空
	virtual int IsFieldNull(int nField);
	// 判断字段是否为空
	virtual int IsFieldNull(const char *strFieldName);
	// 获取索引字段名称
	virtual const char* GetFieldName(int nColumn);
	// 获取索引位置
	virtual int GetFieldIndex(const char *strFieldName);
	// 获取字段列总数
	virtual int GetFieldCount();
	// 获取记录总数
	virtual int GetRowCount();
	// 终结操作
	virtual void Close();
	// 删除本身
	virtual void DeleteThis(void);

	/// @}

private:

	/** @name 私有员函数 *///////////////////////////////////////////////////
    /// @{

	// 获取字段长度
	long GetFieldLength(int nField);
	// 获取字段长度
	long GetFieldLength(const char *strFieldName);

	/// @}
};


#endif	// __MYSQL_DATA_READER_H__
