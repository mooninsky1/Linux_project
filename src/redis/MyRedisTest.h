#pragma once
#include "hiredis/hiredis.h"
class CRedisObj
{
  public:
    int uuid;
    char name[16];
    int  age;
    int  job;
    int  arr[4];
    CRedisObj()
    {
      uuid = 0;
      age = 0;
      job = 0;
    }
};
class CMyRedisTest
{
  public:
    void Test();

  private:
    void TestTest();
    void TestBinary();
    void TestSaveObject();
    void TestLoadObject();

    redisContext* ConnectRedis(); 
    void DoCmd( redisContext* c ,const char* szCmd);
};