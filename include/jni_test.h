
#include <jni.h>
#include <string.h>
#include <stdio.h>
#include <exception>
#ifdef _WIN32
#define PATH_SEPARATOR ';'
#else
#define PATH_SEPARATOR ':'
#endif

#pragma comment(lib,"jvm.lib")
/*
    HINSTANCE hInstance = ::LoadLibrary(L"C:\\Program Files\\Java\\jdk1.5.0\\jre\\bin\\client\\jvm.dll");  
    if (hInstance == NULL)  
    {  
    printf("加载JVM动态库错误。%l", ::GetLastError());
    return false;  
    } 
    printf("加载JVM动态库成功。");
    */
void Test(void)
{
    JavaVMOption options[1];
    JNIEnv *env;
    JavaVM *jvm;
    JavaVMInitArgs vm_args;

    long status;
    jclass cls;
    jmethodID mid;
    jfieldID fid;
    jobject obj;

 
    HINSTANCE hInstance = ::LoadLibrary(L"C:\\Program Files\\Java\\jdk1.7.0_09\\jre\\bin\\client\\jvm.dll");  
    if (hInstance == NULL)  
    {  
    printf("加载JVM动态库错误。%l", ::GetLastError());
    return false;  
    } 
    printf("加载JVM动态库成功。");
  
    options[0].optionString = "-Djava.class.path=.;E:\\workhome\\Test\\Test;E:\\workhome\\Test;E:\\server\\server;E:\\server\\server\\debug";
    memset(&vm_args, 0, sizeof(vm_args));
    vm_args.version = JNI_VERSION_1_6;
    vm_args.nOptions = 1;
    vm_args.options = options;
    vm_args.ignoreUnrecognized = false;

    // 启动虚拟机
    status = JNI_CreateJavaVM(&jvm, (void**)&env, &vm_args);

    if (status != JNI_ERR)
    {
        // 先获得class对象
        cls = env->FindClass("Sample2");
        if (cls != 0)
        {
            // 获取方法ID, 通过方法名和签名, 调用静态方法
            mid = env->GetStaticMethodID(cls, "sayHello", "(Ljava/lang/String;)Ljava/lang/String;");
            if (mid != 0)
            {
                const char* name = "World";
                jstring arg = env->NewStringUTF(name);
                jstring result = (jstring)env->CallStaticObjectMethod(cls, mid, arg);
                const char* str = env->GetStringUTFChars(result, 0);
                printf("Result of sayHello: %s\n", str);
                env->ReleaseStringUTFChars(result, 0);
            }

            /*** 新建一个对象 ***/
            // 调用默认构造函数
            //obj = env->AllocObjdect(cls); 

            // 调用指定的构造函数, 构造函数的名字叫做<init>
            mid = env->GetMethodID(cls, "<init>", "()V");
            obj = env->NewObject(cls, mid);
            if (obj == 0)
            {
                printf("Create object failed!\n");
            }
            /*** 新建一个对象 ***/

            // 获取属性ID, 通过属性名和签名
            fid = env->GetFieldID(cls, "name", "Ljava/lang/String;");
            if (fid != 0)
            {
                const char* name = "icejoywoo";
                jstring arg = env->NewStringUTF(name);
                env->SetObjectField(obj, fid, arg); // 修改属性
            }

            // 调用成员方法
            mid = env->GetMethodID(cls, "sayHello", "()Ljava/lang/String;");
            if (mid != 0)
            {
                jstring result = (jstring)env->CallObjectMethod(obj, mid);
                const char* str = env->GetStringUTFChars(result, 0);
                printf("Result of sayHello: %s\n", str);
                env->ReleaseStringUTFChars(result, 0);
            }
        }

        jvm->DestroyJavaVM();
        return;
    }
    else
    {
        printf("JVM Created failed!\n");
        return ;
    }
}