/*Fast_Sort.cpp : �������̨Ӧ�ó������ڵ㡣
ͨ��һ������Ҫ��������ݷָ�ɶ����������֣�����һ����
���������ݶ�������һ���ֵ��������ݶ�ҪС��Ȼ���ٰ��˷�����
�����������ݷֱ���п�����������������̿��Եݹ���У��Դ˴ﵽ�������ݱ���������С�
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
		//ͬʱ����������������λ��
		if (i >= j)
		{
			break;
		}
		Swap(a[i], a[j]);
	}
	a[p] = a[j];
	a[j] = x;//����while(a[--j]>x);ִ�к�j����һ�£����ָ��a[j]��С��x,��ʱ��a[p]��ֵ��a[j]�����պ�������඼��xС���Ҳ඼��x��
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
