#ifndef __I_SQL_DATABASE_H__
#define __I_SQL_DATABASE_H__
#include <string>
using namespace std;
class ISqlConnection
{
public:
	// 打开数据库
	virtual int Open(const char *szHost, int nPort, const char *szUser, const char *szPassword, const char *szDBName) = 0;
	// 关闭数据库
	virtual void Close(void) = 0;
	// 删除本身
	virtual void DeleteThis(void) = 0;
};

//#if defined (__MS_SQL__)
// 获取MSSQL连接对象
//ISqlConnection* GetStaticMsSqlConnection();
// 实例化MSSQL连接对象
//ISqlConnection* GetNewMsSqlConnection();
//#elif defined (__MY_SQL__)
// 获取MYSQL连接对象
ISqlConnection* GetStaticMySqlConnection();
// 实例化MYSQL连接对象
ISqlConnection* GetNewMySqlConnection();
//#endif

class ISqlDataReader
{
public:
	// 是否已经结束
	virtual int Read() = 0;
	// 移动下一条记录
	virtual int MoveNext() = 0;
	// 获取索引字符串
	virtual const char* GetFieldValue(int nField) = 0;
	// 获取索引字符串
	virtual const char* GetFieldValue(const char *strFieldName) = 0;
	// 获取索引整数
	virtual int GetIntField(int nField, int nNullValue = 0) = 0;
	// 获取索引整数
	virtual int GetIntField(const char *strFieldName, int nNullValue = 0) = 0;
	// 获取索引浮点数
	virtual float GetFloatField(int nField, float fNullValue = 0.0) = 0;
	// 获取索引浮点数
	virtual float GetFloatField(const char *strFieldName, float fNullValue = 0.0) = 0;
	// 获取索引浮点数
	virtual double GetDoubleField(int nField, double dNullValue = 0.0) = 0;
	// 获取索引浮点数
	virtual double GetDoubleField(const char *strFieldName, double dNullValue = 0.0) = 0;
	// 获取索引字符串
	virtual string GetStringField(int nField, const char *strNullValue = "") = 0;
	// 获取索引字符串
	virtual string GetStringField(const char *strFieldName, const char *strNullValue = "") = 0;
	// 获取索引二进制
	virtual int GetBinaryField(int nField, char *lpszContent, unsigned int uMaxLen, int nNullValue = 0) = 0;
	// 获取索引二进制
	virtual int GetBinaryField(const char *strFieldName, char *lpszContent, unsigned int uMaxLen, int nNullValue = 0) = 0;
	// 判断字段是否为空
	virtual int IsFieldNull(int nField) = 0;
	// 判断字段是否为空
	virtual int IsFieldNull(const char *strFieldName) = 0;
	// 获取索引字段名称
	virtual const char* GetFieldName(int nColumn) = 0;
	// 获取索引位置
	virtual int GetFieldIndex(const char *strFieldName) = 0;
	// 获取字段列总数
	virtual int GetFieldCount() = 0;
	// 获取记录总数
	virtual int GetRowCount() = 0;
	// 终结操作
	virtual void Close() = 0;
	// 删除本身
	virtual void DeleteThis(void) = 0;
};

//#if defined (__MS_SQL__)
// 获取MSSQL读取对象
//ISqlDataReader* GetStaticMsSqlDataReader();
// 实例化MSSQL读取对象
//ISqlDataReader* GetNewMsSqlDataReader();
//#elif defined (__MY_SQL__)
// 获取MYSQL读取对象
ISqlDataReader* GetStaticMySqlDataReader();
// 实例化MYSQL读取对象
ISqlDataReader* GetNewMySqlDataReader();
//#endif

class ISqlCommand
{
public:
	
	/** @name 添加输入参数函数 *///////////////////////////////////////////////////
    /// @{
	
	// 添加存储过程参数（整数类型）
	virtual void AddIntInputParameter(const char *lpszName, int nValue) = 0;
	// 添加存储过程参数（短整数类型）
	virtual void AddShortInputParameter(const char *lpszName, short nValue) = 0;
	// 添加存储过程参数（字节类型）
	virtual void AddByteInputParameter(const char *lpszName, char byValue) = 0;
	// 添加存储过程参数（字符类型）
	virtual void AddStringInputParameter(const char *lpszName, const char *lpszValue) = 0;
	// 添加存储过程参数（二进制类型）
	virtual void AddBinaryInputParameter(const char *lpszName, char *lpszValue, int nLen) = 0;

	/// @}

public:

	/** @name 添加输出参数函数 *///////////////////////////////////////////////////
    /// @{

	// 添加输出存储过程参数（整数类型）
	virtual void AddIntOutputParameter(const char *lpszName) = 0;

	/// @}

public:

	/** @name 获取返回参数函数 *///////////////////////////////////////////////////
    /// @{

	// 获取存储过程返回的参数（整数类型）
	virtual int GetIntParameterValue(const char *lpszName) = 0;

	/// @}

public:

	/** @name 清空对象参数函数 *///////////////////////////////////////////////////
    /// @{

	// 清空对象参数
	virtual void ClearParameter() = 0;

	/// @}

public:

	/** @name 执行SQL语句函数 *///////////////////////////////////////////////////
    /// @{


	// 执行无返回值
	virtual void ExecuteNonQuery(const char * strSQL, int bUseStoredProc = 0) = 0;
	// 执行无返回值
	virtual int ExecuteQuery(const char * strSQL, int bUseStoredProc = 0) = 0;
	// 执行查询结果
	virtual ISqlDataReader* ExecuteReader(const char * strSQL, int bUseStoredProc = 0) = 0;
	// 执行查询结果
	virtual int ExecuteReader(ISqlDataReader *pSqlDataReader, const char * strSQL, int bUseStoredProc = 0) = 0;
	// 执行查询结果
	virtual int ExecuteScalar(const char * strSQL, int bUseStoredProc = 0) = 0;

	/// @}

public:

	/** @name 虚成员函数 *///////////////////////////////////////////////////
    /// @{

	// 设置SqlConnection指针
	virtual void SetSqlConnection(ISqlConnection *pSqlConnection) = 0;
	// 开始执行
	virtual void ExecuteBegin(void) = 0;
	// 结束执行
	virtual void ExecuteEnd(void) = 0;
	// 删除本身
	virtual void DeleteThis(void) = 0;

	/// @}
};

//#if defined (__MS_SQL__)
// 获取MSSQL命令对象
//ISqlCommand* GetStaticMsSqlCommand();
// 实例化MSSQL命令对象
//ISqlCommand* GetNewMsSqlCommand();
//#elif defined (__MY_SQL__)
// 获取MYSQL命令对象
ISqlCommand* GetStaticMySqlCommand();
// 实例化MYSQL命令对象
ISqlCommand* GetNewMySqlCommand();
//#endif

#endif	// __I_SQL_DATABASE_H__