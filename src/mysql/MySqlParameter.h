#ifndef __MYSQL_PARAMETER_H__
#define __MYSQL_PARAMETER_H__

#include "ISqlDataBase.h"
#include "MySqlConnection.h"
#include "MySqlBindData.h"

class MySqlParameter
{
private:

	/** @name  私有成员变量 */////////////////////////////////////////////////////
    /// @{

	// 绑定参数列表
	MySqlBindData *m_pMySqlBindData;

	/// @}

public:
	MySqlParameter(void);
	~MySqlParameter(void);
public:
	// 初始化
	int Init();
public:
	
	/** @name 添加输入参数函数 *///////////////////////////////////////////////////
    /// @{
	
	// 添加存储过程参数（二进制类型）
	void AddBinaryInputParameter(const char *lpszName, char *lpBinaryValue, int nBinaryLen);
	// 执行绑定参数
	void RunExecuteBindParameter(MYSQL *pMySql, MYSQL_STMT *pMySqlStmt, const char * strSQL);

	/// @}

public:

	/** @name 添加输出参数函数 *///////////////////////////////////////////////////
    /// @{

	// 添加输出存储过程参数（整数类型）
	void AddIntOutputParameter(const char *lpszName);

	/// @}

public:

	/** @name 获取返回参数函数 *///////////////////////////////////////////////////
    /// @{

	// 获取存储过程返回的参数（整数类型）
	int GetIntParameterValue(const char *lpszName);

	/// @}

};

#endif	// __MYSQL_PARAMETER_H__
