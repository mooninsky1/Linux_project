#ifndef __MYSQL_COMMAND_H__
#define __MYSQL_COMMAND_H__

#include "ISqlDataBase.h"
#include "MySqlConnection.h"
#include "MySqlParameter.h"

class MySqlCommand : public ISqlCommand
{
private:

	/** @name  私有成员变量 */////////////////////////////////////////////////////
    /// @{

	// MySql连接对象
	MySqlConnection *m_pMySqlConnection;
	// 操作超时
	int m_nBusyTimeout;
	// 绑定参数
	int m_nBandParamPostion;
	// 预分配参数总数
	int m_nBindParamTotal;
	//
	MySqlParameter *m_pMySqlParameter;
	// 绑定参数列表
	MYSQL_BIND *m_pMySqlBindParamArray;
	MYSQL_STMT *m_pMySqlStmt;
	/// @}

public:
	MySqlCommand(void);
	~MySqlCommand(void);
public:
	MySqlCommand(MySqlConnection *pMySqlConnection);
public:
	
	/** @name 添加输入参数函数 *///////////////////////////////////////////////////
    /// @{
	
	// 添加存储过程参数（整数类型）
	virtual void AddIntInputParameter(const char *lpszName, int nValue);
	// 添加存储过程参数（短整数类型）
	virtual void AddShortInputParameter(const char *lpszName, short nValue);
	// 添加存储过程参数（字节类型）
	virtual void AddByteInputParameter(const char *lpszName, char byValue);
	// 添加存储过程参数（字符类型）
	virtual void AddStringInputParameter(const char *lpszName, const char *lpszValue);
	// 添加存储过程参数（二进制类型）
	virtual void AddBinaryInputParameter(const char *lpszName, char *lpBinaryValue, int nLen);

	/// @}

public:

	/** @name 添加输出参数函数 *///////////////////////////////////////////////////
    /// @{

	// 添加输出存储过程参数（整数类型）
	virtual void AddIntOutputParameter(const char *lpszName);

	/// @}

public:

	/** @name 获取返回参数函数 *///////////////////////////////////////////////////
    /// @{

	// 获取存储过程返回的参数（整数类型）
	virtual int GetIntParameterValue(const char *lpszName);

	/// @}

public:

	/** @name 清空对象参数函数 *///////////////////////////////////////////////////
    /// @{

	// 清空对象参数
	virtual void ClearParameter();

	/// @}
public:


	/** @name 虚成员函数 *///////////////////////////////////////////////////
    /// @{

	// 设置CMySqlConnection指针
	virtual void SetSqlConnection(ISqlConnection *pSqlConnection);
	// 执行无返回值
	virtual void ExecuteNonQuery(const char * strSQL, int bUseStoredProc = 0);
	// 执行无返回值
	virtual int ExecuteQuery(const char * strSQL, int bUseStoredProc = 0);
	// 执行查询结果
	virtual ISqlDataReader* ExecuteReader(const char * strSQL, int bUseStoredProc = 0);
	// 执行查询结果
	virtual int ExecuteReader(ISqlDataReader *pSqlDataReader, const char * strSQL, int bUseStoredProc = 0);
	// 执行查询结果
	virtual int ExecuteScalar(const char * strSQL, int bUseStoredProc = 0);
	// 
	virtual void ExecuteBegin(void);
	//
	virtual void ExecuteEnd(void);
	// 删除本身
	virtual void DeleteThis(void);

	/// @}
};

#endif	// __MYSQL_COMMAND_H__
