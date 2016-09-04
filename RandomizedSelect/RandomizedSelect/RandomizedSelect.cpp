/*RandomizedSelect.cpp : �������̨Ӧ�ó������ڵ㡣
������������n��Ԫ�غ�һ������k��1��k��n��Ҫ���ҳ���n��Ԫ���е�kС��Ԫ�أ���������������Լ�������ģ���
����ʱ��ѡ��������ַ�����ģ����������������㷨��ơ�����˼���Ƕ�����������еݹ黮�֣����������ͬ��
�ǣ���ֻ�Ի��ֳ���������֮һ���еݹ鴦��
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
		//a[p:i]�е�Ԫ�ض�С�ڵ�k��Ԫ�أ������Ҫ��a[i+1,r]�е�k-jС��Ԫ��
		return RandomizedSelect(a, i + 1, r, k - j);
	}
}
