/*Med_Select.cpp : �������̨Ӧ�ó������ڵ㡣
�㷨˼·�������������ʱ�����ҵ�һ�����ֻ�׼ʹ�ð������׼�����ֳ���2��������ĳ��ȶ�����Ϊԭ���鳤�ȵĦű�(0<��<1),��ô�Ϳ�������������O(n)ʱ�����ѡ���������磬����=9/10���㷨�ݹ������������������ĳ�����������1/10�����ԣ�
�������£��㷨����ļ���ʱ��T(n)�������ʽT(n)<=T(9n/10)+O(n)���ɴ˿ɵ�T(n)=O(n)��
*/
//������λ����������ʱ��ѡ��
#include "stdafx.h"
#include<ctime>
#include"iostream"
using namespace std;

template<class Type>void Swap(Type&x, Type&y);
inline int Random(int x,int y);
template<class Type>void BubbleSort(Type a[], int p, int r);//Bubbleð��
template<class Type>int Partition(Type a[], int p, int r, Type x);
template<class Type>Type Select(Type a[], int p, int r, int k);


int main()
{
	int a[100];//��ʼ������
	srand((unsigned)time(0));//�������
	for (int i = 0; i < 100; i++)
	{
		a[i] = Random(0, 500);
		cout << a[i] << " ";
	}
	cout << endl;
	cout << "��83СԪ���ǣ�" << Select(a, 0, 99, 83) << endl;
	BubbleSort(a, 0, 99);//����
	for (int j = 0; j < 100; j++)
	{
		cout << a[j] << " ";
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
	int ran_num = rand() % (y - x) + x;
	return ran_num;
}
//ð������
template<class Type>void BubbleSort(Type a[], int p, int r)
{
	for (int i = p; i <=r; i++)
	{
		for (int j = i + 1; j <= r; j++)
		{
			if (a[j] < a[i])
			{
				Swap(a[j], a[i]);
			}
		}
	}
}
template<class Type>int Partition(Type a[], int p, int r, Type x)
{
	int i = p - 1;
	int j = r + 1;
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
	return j;
}
template<class Type>Type Select(Type a[], int p, int r, int k)
{
	if (r - p < 75)
	{
		BubbleSort(a, p, r);
		return a[p + k - 1];
	}
	//(r-p-4)/5�൱��n-5(�����±��0��ʼ)
	for (int i = 0; i <= (r - p - 4) / 5; i++)
	{
		/*
		��Ԫ��ÿ5���ֳ�һ�飬�ֱ����򣬲������������λ����a[p+i]����λ��
		ʹ���е���λ�����������������࣬һ�߽�һ��������λ������λ��
		*/
		BubbleSort(a, p + 5 * i, p + 5 * i + 4);
		Swap(a[p + 5 * i + 2], a[p + i]);
	}
	//����λ���е���λ��
	Type x = Select(a,p,p+(r-p-4)/5,(r-p-4)/20);
	int i = Partition(a, p, r, x);
	int j = i - p + 1;
	if (k <= j)
	{
		return Select(a, p, i, k);
	}
	else
	{
		return Select(a, i + 1, r, k - j);
	}
}