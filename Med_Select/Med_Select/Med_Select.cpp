/*Med_Select.cpp : 定义控制台应用程序的入口点。
算法思路：如果能在线性时间内找到一个划分基准使得按这个基准所划分出的2个子数组的长度都至少为原数组长度的ε倍(0<ε<1),那么就可以在最坏情况下用O(n)时间完成选择任务。例如，当ε=9/10，算法递归调用所产生的子数组的长度至少缩短1/10。所以，
在最坏情况下，算法所需的计算时间T(n)满足递推式T(n)<=T(9n/10)+O(n)。由此可得T(n)=O(n)。
*/
//利用中位数进行线性时间选择
#include "stdafx.h"
#include<ctime>
#include"iostream"
using namespace std;

template<class Type>void Swap(Type&x, Type&y);
inline int Random(int x,int y);
template<class Type>void BubbleSort(Type a[], int p, int r);//Bubble冒泡
template<class Type>int Partition(Type a[], int p, int r, Type x);
template<class Type>Type Select(Type a[], int p, int r, int k);


int main()
{
	int a[100];//初始化数组
	srand((unsigned)time(0));//随机种子
	for (int i = 0; i < 100; i++)
	{
		a[i] = Random(0, 500);
		cout << a[i] << " ";
	}
	cout << endl;
	cout << "第83小元素是：" << Select(a, 0, 99, 83) << endl;
	BubbleSort(a, 0, 99);//排序
	for (int j = 0; j < 100; j++)
	{
		cout << a[j] << " ";
	}
	cout << endl;
}

template <class Type>void Swap(Type &x, Type &y)
{
	Type temp = x;
	x = y;
	y = temp;
}
inline int Random(int x, int y)
{
	int ran_num = rand() % (y - x) + x;
	return ran_num;
}
//冒泡排序
template<class Type>void BubbleSort(Type a[], int p, int r)
{
	for (int i = p; i <=r; i++)
	{
		for (int j = i + 1; j <= r; j++)
		{
			if (a[j] < a[i])
			{
				Swap(a[j], a[i]);
			}
		}
	}
}
template<class Type>int Partition(Type a[], int p, int r, Type x)
{
	int i = p - 1;
	int j = r + 1;
	while (true)
	{
		while ((a[++i] < x) && (i < r));
		while (a[--j]>x);
		if (i >= j)
		{
			break;
		}
		Swap(a[i], a[j]);
	}
	return j;
}
template<class Type>Type Select(Type a[], int p, int r, int k)
{
	if (r - p < 75)
	{
		BubbleSort(a, p, r);
		return a[p + k - 1];
	}
	//(r-p-4)/5相当于n-5(数组下标从0开始)
	for (int i = 0; i <= (r - p - 4) / 5; i++)
	{
		/*
		将元素每5个分成一组，分别排序，并将该数组的中位数与a[p+i]交换位置
		使所有的中位数排列在数组的最左侧，一边进一步查找中位数的中位数
		*/
		BubbleSort(a, p + 5 * i, p + 5 * i + 4);
		Swap(a[p + 5 * i + 2], a[p + i]);
	}
	//找中位数中的中位数
	Type x = Select(a,p,p+(r-p-4)/5,(r-p-4)/20);
	int i = Partition(a, p, r, x);
	int j = i - p + 1;
	if (k <= j)
	{
		return Select(a, p, i, k);
	}
	else
	{
		return Select(a, i + 1, r, k - j);
	}
}