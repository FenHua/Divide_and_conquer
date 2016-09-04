/*Nature_Msort.cpp : �������̨Ӧ�ó������ڵ㡣
�ӷ�֧���Ի������֣������������еĵݹ顣
�ǵݹ�ʵ�ֵĴ���˼·���Ƚ�����a��Ԫ��������ԣ�
�úϲ��㷨�������򣬹���n/2�鳤��Ϊ2���źõ�������Σ�
Ȼ���ٽ������ųɳ���Ϊ4���ź����������Σ���˼�����ȥ��ֱ�����������ź���
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
	//�ȷ�Ϊ��СΪs�Ŀ飬Ȼ��ϲ����ڶԵ����Ӷ�����
	int i = 0;
	while (i <= n - 2 * s)
	{
		Merge(x, y, i, i + s - 1, i + 2 * s - 1);//�ϲ���СΪs�������Ӷ�
		i = i + 2 * s;
	}
	//ʣ���Ԫ�ظ�������2s
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
		MergePass(a, b, s, n);//�ϲ�������b  
		s += s;
		MergePass(b, a, s, n);//�ϲ�������a  
		s += s;
	}
}
