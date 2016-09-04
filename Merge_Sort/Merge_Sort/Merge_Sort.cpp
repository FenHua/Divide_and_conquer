/*Merge_Sort.cpp : 定义控制台应用程序的入口点。
合并排序是建立在归并操作上的一种有效的排序算法。
该算法是采用分治法（Divide and Conquer）的一个非常典型的应用。
合并排序法是将两个（或两个以上）有序表合并成一个新的有序表，即把待排序序列分为若干个子序列，每个子序列是有序的。
然后再把有序子序列合并为整体有序序列。将已有序的子序列合并，得到完全有序的序列；
即先使每个子序列有序，再使子序列段间有序，合并排序也叫归并排序。
*/

#include "stdafx.h"
#include"iostream"
using namespace std;

int a[] = { 10, 5, 9, 4, 3, 7, 8 };
int b[7];//输出的结果数组

template <class Type>void Merge(Type c[], Type d[], int l, int m, int r);
template<class Type> void MergeSort(Type a[], int left, int right);


int main()
{
	for (int i = 0; i < 7; i++)
	{
		cout << a[i] << " ";
	}
	cout << endl;
	MergeSort(a, 0, 6);
	for (int i = 0; i < 7; i++)
	{
		cout << a[i] << " ";
	}
	cout << endl;
}

template<class Type>void Merge(Type c[], Type d[], int l, int m, int r)
{
	int i = l;
	int j = m +1; 
	int k = l;
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
template<class Type>void  MergeSort(Type a[], int left, int right)
{
	if (left < right)
	{
		int i = (left + right) / 2;
		MergeSort(a, left, i);
		MergeSort(a, i + 1, right);
		Merge(a, b, left, i, right);//合并到数组b
		//复制回数组a
		for (int g = left; g <=right; g++)
		{
			a[g] = b[g];
		}
	}
}

