//lihf 2012/11/26 快速排序
/*
它的基本思想是：
通过一趟排序将要排序的数据分割成独立的两部分，
其中一部分的所有数据都比另外一部分的所有数据都要小，
然后再按此方法对这两部分数据分别进行快速排序，
整个排序过程可以递归进行，
以此达到整个数据变成有序序列。

*/
 //int arry[8] = {2,8,7,1,3,5,6,4};
 
 int arry[8] = {1,2,3,4,5,6,7,8};

 /*
 设要排序的数组是A[0]……A[N-1]，
 首先任意选取一个数据（通常选用数组的第一个数）作为关键数据，
 然后将所有比它小的数都放到它前面，
 所有比它大的数都放到它后面，
 这个过程称为一趟快速排序。

 */
int Partion( int* a,int p, int r)
{
	//最小区域滑动窗口的指针
	int i = p;

	//主元
	int x = a[r];

	//移动遍历指针
	int j = i;
	for (; j < r; j++)
	{
		if (a[j] < x && j != i)
		{
			int nTemp = a[i];
			a[i] = a[j];
			a[j] = nTemp;
			i++;
			
		}
	}
	//最后交换主元 p 到 i 是小于 x 
	int nTemp = a[i];
	a[i] = a[j];
	a[j] = nTemp;
	return i;
}
void QuickSort(int* a,int p, int r)
{
	if (p < r)
	{
		int i = Partion(a,p,r);
		QuickSort(a,p,i-1);
		QuickSort(a,i+1,r);
	}
	
}
void Disp()
{
	for (int i=0; i<8; i++)
	{
		std::cout<<arry[i]<<" ";
	}
}
void Test()
{
	QuickSort(arry,0,7);
	Disp();
}


