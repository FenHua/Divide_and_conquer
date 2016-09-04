/*Nature_Msort.cpp : 定义控制台应用程序的入口点。
从分支策略机制入手，可消除程序中的递归。
非递归实现的大致思路是先将数组a中元素两两配对，
用合并算法它们排序，构成n/2组长度为2的排好的子数组段，
然后再将它们排成长度为4的排好序的子数组段，如此继续下去，直到整个数组排好序。
*/

#include "stdafx.h"
#include"iostream"
using namespace std;

int a[] = { 10, 5, 9, 4, 3, 7, 8 };
int b[7];

template<class Type>void Merge(Type c[], Type d[], int l, int m, int r);
template<class Type>void MergePass(Type x[], Type y[], int s, int n);
template <class Type>void MergeSort(Type a[], int n);

int main()
{
	for (int i = 0; i < 7; i++)
	{
		cout << a[i] << " ";
	}
	cout << endl;
	MergeSort(a, 7);
	for (int i = 0; i < 7; i++)
	{
		cout << a[i] << " ";
	}
	cout << endl;
}

template<class Type>void Merge(Type c[], Type d[], int l, int m, int r)
{
	int i = l, j = m + 1, k = l;
	while ((i <= m) && (j <= r))
	{
		if (c[i] <= c[j])
		{
			d[k++] = c[i++];
		}
		else
		{
			d[k++] = c[j++];
		}
	}
	if (i > m)
	{
		for (int q = j; q <= r; q++)
		{
			d[k++] = c[q];
		}
	}
	else
	{
		for (int q = i; q <= m; q++)
		{
			d[k++] = c[q];
		}
	}
}

template<class Type>void MergePass(Type x[], Type y[], int s, int n)
{
	//先分为大小为s的块，然后合并相邻对的俩子段数组
	int i = 0;
	while (i <= n - 2 * s)
	{
		Merge(x, y, i, i + s - 1, i + 2 * s - 1);//合并大小为s的相邻子段
		i = i + 2 * s;
	}
	//剩余的元素个数少于2s
	if (i + s < n)
	{
		Merge(x, y, i, i + s - 1, n - 1);
	}
	else
	{
		for (int j = i; j <= n - 1; j++)
		{
			y[j] = x[j];
		}
	}
}
template<class Type>void MergeSort(Type a[], int n)
{
	Type*b = new Type[n];
	int s = 1;
	while (s<n)
	{
		MergePass(a, b, s, n);//合并到数组b  
		s += s;
		MergePass(b, a, s, n);//合并到数组a  
		s += s;
	}
}
