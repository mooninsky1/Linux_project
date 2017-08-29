//请定义一个宏，比较两个数a、b的大小，不能使用大于、小于、if语句
#define max(a,b) (a)/(b)?a:b   //不对，除0，-5 ，1 测试不过
#define MAX(a,b)  (a-b)&(0x1<<31)?b:a // 没考虑溢出问题
#define max1(a,b)   ((((long)((a)-(b)))&0x80000000)?b:a) 
// 两位数求和 a+b = (a&b)<<1 + (a^b)  平均值 就是 ((a)&(b)) + ( ( (a)^(b) ) >> 1 )
//可以看作：每个二进数都可以分解为各个位与其权的乘积的和



void Test()
{
	int a=-5;
	int b =1;
	int c = max1(a,b);
}