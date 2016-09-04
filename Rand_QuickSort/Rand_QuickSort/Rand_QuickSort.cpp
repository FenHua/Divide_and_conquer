/*Rand_QuickSort.cpp : �������̨Ӧ�ó������ڵ㡣
δ���������Ŀ����������������ڻ��ֹ��̲���������
����ֱ����n-1��Ԫ�غ�1��Ԫ�ص�ʱ�����ں���Partition�ļ���ʱ��
ΪO(n),��������㷨Partition��ÿһ�����������ֲ��Գƻ��֣���T(n)=O(n^2)��

���������£�ÿ�λ�����ȡ�Ļ�׼��ǡ��Ϊ��ֵ����ÿ�λ��ֶ�����������СΪn/2������
��ʱT(n)=O(nlogn)����ˣ����������㷨������ȡ���ڻ��ֵĶԳ��ԡ��޸�Partition����
����Ƴ��������ѡ����ԵĿ��������㷨���ڿ��������㷨��ÿһ���У������黹û�б�����
ʱ��������a[p:r]�����ѡ��һ��Ԫ����Ϊ���ֻ�׼��
*/

#include "stdafx.h"
#include<iostream>
#include<ctime>
using namespace std;

int a[] = { 5, 7, 3, 4, 8, 6, 9, 1, 2 };

template<class Type>void Swap(Type&x, Type&y);
inline int Random(int x, int y);
template<class Type>int Partition(Type a[], int p, int r);
template<class Type>int RandomizedPartition(Type a[], int p, int r);
template<class Type>void RandomizedQuickSort(Type a[], int p, int r);

int main()
{
	for (int i = 0; i<9; i++)
	{
		cout << a[i] << " ";
	}
	cout << endl;
	RandomizedQuickSort(a, 0, 8);
	for (int i = 0; i<9; i++)
	{
		cout << a[i] << " ";
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
	srand((unsigned)time(0));
	/*
	Srand�������������������ÿ�����µ����Ӳ�һ������Rand�õ���������Ͳ�һ����Ϊ��ÿ������һ����һ������
	�ӣ����Ծ�ѡ��Time(0)��Time(0)�ǵõ���ǰʱʱ��ֵ����Ϊÿʱÿ��ʱ���ǲ�һ�����ˣ���
	*/
	int ran_num = rand() % (y - x) + x;
	return ran_num;
}
template<class Type>int Partition(Type a[], int p, int r)
{
	int i = p, j = r + 1;
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
template<class Type>void RandomizedQuickSort(Type a[], int p, int r)
{
	if (p < r)
	{
		int q = RandomizedPartition(a, p, r);
		RandomizedQuickSort(a, p, q - 1);
		RandomizedQuickSort(a, q + 1, r);
	}
}

