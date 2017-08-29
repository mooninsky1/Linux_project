#ifndef __MYSQL_CONNECTION_H__
#define __MYSQL_CONNECTION_H__

#if defined __WINDOWS__
	#include <winsock.h>
#endif

#include "mysql.h"
#include "ISqlDataBase.h"

class MySqlConnection : public ISqlConnection
{
private:

	/** @name  私有成员变量 */////////////////////////////////////////////////////
    /// @{

	// MySQL对象
	MYSQL *m_pMySQL;

	/// @}

public:
	MySqlConnection(void);
	~MySqlConnection(void);
public:

	/** @name 公共成员函数 *///////////////////////////////////////////////////
    /// @{

	// 获取数据库对象
	MYSQL* GetMySql(void);

	/// @}

public:

	/** @name 虚成员函数 *///////////////////////////////////////////////////
    /// @{

	// 打开数据库
	virtual int Open(const char *szHost, int nPort, const char *szUser, const char *szPassword, const char *szDBName);
	// 关闭数据库
	virtual void Close(void);
	// 删除本身
	virtual void DeleteThis(void);

	/// @}
};

#endif	// __MYSQL_CONNECTION_H__
