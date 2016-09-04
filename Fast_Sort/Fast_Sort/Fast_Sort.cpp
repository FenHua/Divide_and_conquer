/*Fast_Sort.cpp : 定义控制台应用程序的入口点。
通过一趟排序将要排序的数据分割成独立的两部分，其中一部分
的所有数据都比另外一部分的所有数据都要小，然后再按此方法对
这两部分数据分别进行快速排序，整个排序过程可以递归进行，以此达到整个数据变成有序序列。
*/

#include "stdafx.h"
#include<iostream>
using namespace std;

int a[] = {5,7,3,4,8,6,9,1,2};

template<class Type>void Swap(Type&x, Type&y);
template<class Type>int Partition(Type a[], int p, int r);
template<class Type>void QuickSort(Type a[], int p, int r);

int main()
{
	for (int i = 0; i<9; i++)
	{
		cout << a[i] << " ";
	}
	cout << endl;
	QuickSort(a, 0, 8);
	for (int i = 0; i<9; i++)
	{
		cout << a[i] << " ";
	}
	cout << endl;
}

template<class Type>void Swap(Type&x, Type&y)
{
	Type temp = x;
	x = y;
	y = temp;
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
		//同时遇到不满足条件的位置
		if (i >= j)
		{
			break;
		}
		Swap(a[i], a[j]);
	}
	a[p] = a[j];
	a[j] = x;//由于while(a[--j]>x);执行后，j会多减一下，最后指向a[j]会小于x,这时候将a[p]的值与a[j]交换刚好满足左侧都比x小，右侧都比x大。
	return j;
}
template<class Type>void QuickSort(Type a[], int p, int r)
{
	if (p < r)
	{
		int q = Partition(a, p, r);
		QuickSort(a, p, q - 1);
		QuickSort(a, q + 1, r);
	}
}
