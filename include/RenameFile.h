#include <windows.h>
#include <stdio.h>
#include <string.h>
#define LEN 1024
// 深度优先递归遍历目录中所有的文件
BOOL  DirectoryList(LPCSTR Path)
{
	WIN32_FIND_DATA FindData;
	HANDLE hError;
	int FileCount = 0;
	char FilePathName[LEN];
	// 构造路径
	char FullPathName[LEN];
	strcpy(FilePathName, Path);
	strcat(FilePathName, "\\*.*");
	hError = FindFirstFile(FilePathName, &FindData);
	if (hError == INVALID_HANDLE_VALUE)
	{
		printf("搜索失败!");
		return 0;
	}
	while(::FindNextFile(hError, &FindData))
	{
		// 过虑.和..
		if (strcmp(FindData.cFileName, ".") == 0 
			|| strcmp(FindData.cFileName, "..") == 0 )
		{
			continue;
		}

		// 构造完整路径
		wsprintf(FullPathName, "%s\\%s", Path,FindData.cFileName);
		FileCount++;
		// 输出本级的文件
		printf("\n%d  %s  ", FileCount, FullPathName);
// 		FILE *file = fopen(FullPathName,"w");

		rename("新建 文本文档.txt","E:\\book\\TEST\\1.TXT");
		

		if (FindData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
		{
			printf("<Dir>");
			DirectoryList(FullPathName);
		}
	}
	return 0;
}

void Test()
{
	DirectoryList("E:\\book\\TEST");
}