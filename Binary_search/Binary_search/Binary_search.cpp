/*Binary_search.cpp : �������̨Ӧ�ó������ڵ㡣
�ö��������ٶ��ֲ����㷨�������������������߽���ͬ��
�Ƚ϶��������Բ���Ҳ���ö�������ʾ�������±Ƚϴ���Ϊ����Ԫ��������
�κ�һ���ԱȽ�Ϊ�����������㷨������������ʱ�䲻���ܵ���O(logn)��
*/

#include "stdafx.h"
#include"iostream"
using namespace std;

template <class Type> int BinarySearch(Type a[], const Type&x, int n);


int main()
{
	int x = 6;
	int a[10];
	for (int i = 0; i < 10; i++)
	{
		a[i] = i + 1;
	}
	cout << BinarySearch(a, x, 10) << endl;
	return 0;
}

template<class Type>int BinarySearch(Type a[], const Type&x, int n)
{
	int left = 0;
	int right = n - 1;
	while (left <= right)
	{
		int mid = (left + right) / 2;
		if (x == a[mid])
		{
			return mid;
		}
		if (x > a[mid])
		{
			left = mid + 1;
		}
		else
		{
			right = mid - 1;
		}
	}
	return -1;
}
