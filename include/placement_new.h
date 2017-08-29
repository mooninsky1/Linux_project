#include <new>
class T1
{
public:
    T1()
    {
        t1 = 9;
    }
    int t1;
};
class T
{
public:
    T()
    {
        return;
        a =2;
        b =4;
    }
    int a;
    int b;
    T1 ta;
};
void Test()
{
    char *pMem = new char[1024];


    T *pT = new (pMem) T();
    pT->a = 0;
    pT->b = 4;
    T1 t1a;
    t1a.t1 = 8;
    pT->ta = t1a;

    T *ptss = new (pMem) T();

   
    int *pT1 = new int;
    int *pT2 = new int();
    int a=0;
    a++;
}
