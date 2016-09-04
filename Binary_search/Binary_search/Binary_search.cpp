/*Binary_search.cpp : 定义控制台应用程序的入口点。
用二叉树描速二分查找算法，最坏情况下与二叉树的最高阶相同。
比较二叉树线性查找也可用二叉树表示，最坏情况下比较次数为数组元素数量。
任何一种以比较为基础的搜索算法，其最坏情况所用时间不可能低于O(logn)。
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
