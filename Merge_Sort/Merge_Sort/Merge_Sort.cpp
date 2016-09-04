/*Merge_Sort.cpp : �������̨Ӧ�ó������ڵ㡣
�ϲ������ǽ����ڹ鲢�����ϵ�һ����Ч�������㷨��
���㷨�ǲ��÷��η���Divide and Conquer����һ���ǳ����͵�Ӧ�á�
�ϲ������ǽ����������������ϣ������ϲ���һ���µ���������Ѵ��������з�Ϊ���ɸ������У�ÿ��������������ġ�
Ȼ���ٰ����������кϲ�Ϊ�����������С���������������кϲ����õ���ȫ��������У�
����ʹÿ��������������ʹ�����жμ����򣬺ϲ�����Ҳ�й鲢����
*/

#include "stdafx.h"
#include"iostream"
using namespace std;

int a[] = { 10, 5, 9, 4, 3, 7, 8 };
int b[7];//����Ľ������

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
		Merge(a, b, left, i, right);//�ϲ�������b
		//���ƻ�����a
		for (int g = left; g <=right; g++)
		{
			a[g] = b[g];
		}
	}
}

