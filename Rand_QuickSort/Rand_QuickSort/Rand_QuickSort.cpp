/*Rand_QuickSort.cpp : 定义控制台应用程序的入口点。
未随机化处理的快速排序最坏情况发生在划分过程产生的两个
区域分别包含n-1个元素和1个元素的时候。由于函数Partition的计算时间
为O(n),所以如果算法Partition的每一步都出现这种不对称划分，则T(n)=O(n^2)。

在最好情况下，每次划分所取的基准都恰好为中值，即每次划分都产生两个大小为n/2的区域。
此时T(n)=O(nlogn)。因此，快速排序算法的性能取决于划分的对称性。修改Partition，可
以设计出采用随机选择策略的快速排序算法。在快速排序算法的每一步中，当数组还没有被划分
时，可以在a[p:r]中随机选择一个元素作为划分基准。
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
	Srand是种下随机种子数，你每回种下的种子不一样，用Rand得到的随机数就不一样。为了每回种下一个不一样的种
	子，所以就选用Time(0)，Time(0)是得到当前时时间值（因为每时每刻时间是不一样的了）。
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

