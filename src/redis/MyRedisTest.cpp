#include "MyRedisTest.h"
#include <string.h>
#include <stdlib.h>

 redisContext* CMyRedisTest::ConnectRedis()
 {
      //redis默认监听端口为6387 可以再配置文件中修改 
    redisContext* c = redisConnect("127.0.0.1", 6379); 
    if ( c->err) 
    { 
        redisFree(c); 
        printf("Connect to redisServer faile\n"); 
        return NULL; 
    } 
    printf("Connect to redisServer Success\n"); 

    //密码
    redisReply* r = (redisReply*)redisCommand(c, "auth 123456");     
    if( NULL == r) 
    { 
        printf("login  failure\n"); 
        redisFree(c); 
        return NULL; 
    } 
    return c;
 }
void CMyRedisTest::DoCmd( redisContext* c, const char* szCmd)
{
    if(NULL == c ||
       NULL == szCmd 
        )
        return;
    redisReply* r = (redisReply*)redisCommand(c,szCmd);
    if( NULL == r || 
        REDIS_REPLY_ERROR == r->type
      )
      {
          printf("do cmd %s failure\n",szCmd); 
      }
}
void CMyRedisTest::Test()
{
   //TestBinary();
   TestSaveObject();
   TestLoadObject();
   
}
 
 void CMyRedisTest::TestTest()
 {
    redisContext* c = ConnectRedis(); 
    if (NULL == c ) 
    { 
        return ; 
    } 
    printf("Connect to redisServer Success\n"); 


    DoCmd(c,"set stest1 value1");
   
    //测试二进制
    int a=10;
    //redisReply* r1 = (redisReply*)redisCommand(c, "set binnary %b",a,4); 
    const char *v[3];
	size_t vlen[3];
	v[0] = "set";
	vlen[0] = strlen("set");
 
	v[1] = "binnary";
	vlen[1] = strlen("binnary");
 
	v[2] = (const char *)&a;
	vlen[2] = sizeof(a);
 
	redisReply *r1 = (redisReply *)redisCommandArgv(c, sizeof(v) / sizeof(v[0]), v, vlen);

    if( NULL == r1) 
    { 
        printf("Execut command2 failure\n"); 
        redisFree(c); 
        return; 
    } 
    redisReply* r2 = (redisReply*)redisCommand(c, "get binnary");    
    if( NULL == r2) 
    { 
        printf("Execut command3 failure\n"); 
        redisFree(c); 
        return; 
    } 
    int b=0;
    if(r2->len != 4)
    {
          printf("size failure size:= %d\n",r2->len); 
    }
    else
    {
        b = *(int*)r2->str;
    }
    printf("b= %d\n",b); 
 }
 void CMyRedisTest::TestBinary()
    {
        //redis默认监听端口为6387 可以再配置文件中修改
        redisContext *c = ConnectRedis();
        if (NULL == c)
        {
            printf("Connect to redisServer faile\n");
            return;
        }
        printf("Connect to redisServer Success\n");

        DoCmd(c,"select 6");
        
        int a[4]={1,2,3,4};
        redisReply* r = (redisReply *)redisCommand(c, "set arr1 %b", a, sizeof(a));

        if (NULL == r)
        {
            printf("Execut set arr1  failure\n");
            redisFree(c);
            return;
        }

        //测试二进制
        int b[4] = {};

        redisReply *r2 = (redisReply *)redisCommand(c, "get arr1");
        if (NULL == r2)
        {
            printf("Execut get arr1 failure\n");
            redisFree(c);
            return;
        }
        if (r2->len != 16)
        {
            printf("size failure\n");
        }
        else
        {
                memcpy(b,r2->str,16);
        }
        printf("b= %d\n", b[3]);
    }
    void CMyRedisTest::TestSaveObject()
    {
        CRedisObj obj;
        obj.uuid = 1;
        obj.age = 10;
        obj.job = 1;
        obj.arr[0]= 1;
        obj.arr[1]= 1;
        obj.arr[2]= 1;
        obj.arr[3]= 1;

        memcpy(obj.name,"lhf",15);

        redisContext *c = ConnectRedis();
        if (NULL == c)
        {
            printf("Connect to redisServer faile\n");
            return;
        }
        printf("Connect to redisServer Success\n");

        DoCmd(c,"select 6");
        
       redisCommand(c, "HMSET  person_%d uuid %d", obj.uuid, obj.uuid );
       redisCommand(c, "HMSET  person_%d name %s", obj.uuid, obj.name );
       redisCommand(c, "HMSET  person_%d age %d", obj.uuid, obj.age );
       redisCommand(c, "HMSET  person_%d job %d", obj.uuid, obj.job );
       redisCommand(c, "HMSET  person_%d arr %b", obj.uuid, obj.arr,sizeof(obj.arr) );

    }
 void CMyRedisTest::TestLoadObject()
    {
        CRedisObj obj;
     
        redisContext *c = ConnectRedis();
        if (NULL == c)
        {
            printf("Connect to redisServer faile\n");
            return;
        }
        printf("Connect to redisServer Success\n");

        DoCmd(c,"select 6");
        
       redisReply *reply = (redisReply *)redisCommand(c, "HGETALL  person_%d ", 1 );
       if (reply && reply->type == REDIS_REPLY_ARRAY)
       {
           for (int j = 0; j < reply->elements; j++)
           {
               
              printf("type:%d,%s \n",reply->element[j]->type,reply->element[j]->str) ;
              //key vluae ,过滤value
              redisReply *replyValue = (redisReply *)redisCommand(c, "HGET person_%d %s ",1, reply->element[j]->str );
              //printf("%s, type:%d,len:%d\n",replyValue->str,replyValue->type,replyValue->len) ;
              if(replyValue)
              {
                  printf("%s:%s\n",reply->element[j]->str,replyValue->str) ;
                  if(0 == strcmp(reply->element[j]->str,"uuid"))
                  {
                      
                      //memcpy(&obj.uuid,replyValue->str,replyValue->len);
                      obj.uuid = atoi(replyValue->str);
                  }
                  else if(0 == strcmp(reply->element[j]->str,"name") )
                  {
                     memcpy(obj.name,replyValue->str,15);
                  }
                 else   if(0 == strcmp(reply->element[j]->str,"age"))
                  {
                     // memcpy(&obj.age,replyValue->str,replyValue->len);
                     obj.age =  atoi(replyValue->str);
                  }
                 else   if(0 == strcmp(reply->element[j]->str,"job"))
                  {
                      //memcpy(&obj.job,replyValue->str,replyValue->len);
                       obj.job = atoi(replyValue->str);
                  }
                 else   if(0 == strcmp(reply->element[j]->str,"arr"))
                  {
                     memcpy(obj.arr,replyValue->str,replyValue->len);
                  }
              }
              j++;
           }
       }
       printf("obj uuid:%d,name:%s,age:%d,job:%d\n",obj.uuid,obj.name,obj.age,obj.job);
    }