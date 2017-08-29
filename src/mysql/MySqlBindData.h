

#ifndef __MY_SQL_BIND_DATA_H__
#define __MY_SQL_BIND_DATA_H__

class MySqlBindData
{
protected:
	// 长度
	int m_nLength;
	// 缓冲区类型
	int m_nBufferType;
	// 缓冲区
	void *m_pBuffer;
public:
	MySqlBindData(void);
	~MySqlBindData(void);
public:
	// 设置整数类型
	void SetValue(int nValue);
	// 设置短整数类型
	void SetValue(short nValue);
	// 设置字节类型
	void SetValue(char byValue);
	// 设置字符类型
	void SetValue(const char *lpszValue);
	// 设置二进制类型
	void SetValue(char *lpBinaryValue, int nBinaryLen);
public:
	// 获取指向长度指针
	int GetLength();
	// 获取缓冲区类型
	int GetBufferType();
	// 获取指向缓冲区指针
	void* GetBufferPointer();
};


#endif	// __MY_SQL_BIND_DATA_H__
