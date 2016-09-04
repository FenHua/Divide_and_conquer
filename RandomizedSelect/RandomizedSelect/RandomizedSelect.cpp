/*RandomizedSelect.cpp : 定义控制台应用程序的入口点。
给定线性序集中n个元素和一个整数k，1≤k≤n，要求找出这n个元素中第k小的元素，（这里给定的线性集是无序的）。
线性时间选择随机划分法可以模仿随机化快速排序算法设计。基本思想是对输入数组进行递归划分，与快速排序不同的
是，它只对划分出的子数组之一进行递归处理。
*/

#include "stdafx.h"
#include"iostream"
#include<ctime>
using namespace std;

int a[] = {5,7,3,4,8,6,9,1,2};

template<class Type>void Swap(Type&x, Type&y);
inline int Random(int x, int y);
template<class Type>int Partition(Type a[], int p, int r);
template<class Type>int RandomizedPartition(Type a[], int p, int r);
template<class Type>Type RandomizedSelect(Type a[], int p, int r, int k);

int main()
{
	for (int i = 0; i < 9; i++)
	{
		cout << a[i] << " ";
	}
	cout << endl;
	cout << RandomizedSelect(a, 0, 8,3) << endl;
}

template<class Type>void Swap(Type&x, Type&y)
{
	Type temp = x;
	x = y;
	y = temp;
}
inline int Random(int x, int y)
{
	srand((unsigned)time(0));
	int ran_num = rand() % (y - x) + x;
	return ran_num;
}
template<class Type>int Partition(Type a[], int p, int r)
{
	int i = p;
	int j = r + 1;
	Type x = a[p];
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
	a[p] = a[j];
	a[j] = x;
	return j;
}
template<class Type>int RandomizedPartition(Type a[], int p, int r)
{
	int i = Random(p, r);
	Swap(a[i], a[p]);
	return Partition(a, p, r);
}
template<class Type>Type RandomizedSelect(Type a[], int p, int r, int k)
{
	if (p == r)
	{
		return a[p];
	}
	int i = RandomizedPartition(a, p, r);
	int j = i - p + 1;
	if (k <= j)
	{
		return RandomizedSelect(a, p, i, k);
	}
	else
	{
		//a[p:i]中的元素都小于第k个元素，因此需要找a[i+1,r]中第k-j小的元素
		return RandomizedSelect(a, i + 1, r, k - j);
	}
}
