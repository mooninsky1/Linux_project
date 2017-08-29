void print(char* szTag)
{
    printf("%s\n",szTag);
}

#define PT(x,i) print(x##i)
void Test()
{
    for (int i=0; i< 10 ; i++)
    {
        PT("lhf","i");
    }
}