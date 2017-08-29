//lihf 2012/08/03 ÇóÍ¬£¬²îÒì³ı2
int Average(int a, int b)
{
	return (a&b) + ((a^b)>>1);
}
void Test()
{
// 	int a =5;
// 	int b =6;
	int a=-5;
	int b =1;
	int c = 0;

	c = Average(a,b);
}