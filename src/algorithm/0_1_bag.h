#include <stdio.h>
#define MAX 20
int n,c,w[MAX],v[MAX],m[MAX][MAX]={0};
void disp( )
{	
	int i;
	for (i=1; i<=n; i++)
	{
		if ( m[i][c]!=m[i+1][c] ) 
		{
			printf("%5d%5d\n",w[i],v[i]);
		}
	}
}
void knapsack()
{ 
	int i,j;
	for (j=w[n]; j<=c; j++)
	{
		m[n][j]=v[n];
	}
	for (i=n-1; i>=1;i--)
	{
		for (j=w[i]; j<=c; j++)
		{
			if ( m[i+1][j]>m[i+1][j-w[i]]+v[i] )
			{
				m[i][j]=m[i+1][j];
			}
			else  
			{
				m[i][j]=m[i+1][j-w[i]]+v[i];  
			}
		}
	}
}

void Test()
{
	int i,j;
	printf("输入物品种数:"); 
	scanf("%d",&n);

	printf("输入每种物品的重量与价值:\n");
	for (i=1; i<=n; i++)
		scanf("%d%d",&w[i],&v[i]);

	printf("输入背包的总重量:\n"); 
	scanf("%d",&c); 

	knapsack();  
	disp();

	printf("最大价值=%d\n",m[0][c]);
	for (i=1; i<=n; i++)
	{	for (j=0; j<=c; j++)
	printf("%3d",m[i][j]);
	printf("\n");   }

}