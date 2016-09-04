/*MinPair.cpp : 定义控制台应用程序的入口点。
问题描述：给定平面上n个点，找其中的一对点，使得在n个点的所有点对中，该点对的距离最小。
严格地说，最接近点对可能多于1对。为了简单起见，这里只限于找其中的一对。
1、一维最接近点对问题
算法思路：
这个问题很容易理解，似乎也不难解决。
我们只要将每一点与其他n-1个点的距离算出，找出达到最小距离的两个点即可。
然而，这样做效率太低，需要O(n^2)的计算时间。在问题的计算复杂性中我们可以看到，该问
题的计算时间下界为Ω(nlogn)。这个下界引导我们去找问题的一个θ(nlogn)算法。采用分治法思
想，考虑将所给的n个点的集合S分成2个子集S1和S2，每个子集中约有n/2个点，然后在每个子
集中递归地求其最接近的点对。在这里，一个关键的问题是如何实现分治法中的合并步骤，即由S1和S2的
最接近点对，如何求得原集合S中的最接近点对，因为S1和S2的最接近点对未必就是S的最接近点对。如果组成S
的最接近点对的2个点都在S1中或都在S2中，则问题很容易解决。但是，如果这2个点分别在S1和S2中，则对于S1中任
一点p，S2中最多只有n/2个点与它构成最接近点对的候选者，仍需做n^2/4次计算和比较才能确定S的最接近点对
。因此，依此思路，合并步骤耗时为O(n^2)。整个算法所需计算时间T(n)应满足:　T(n)=2T(n/2)+O(n^2)。
它的解为T(n)=O(n^2)，即与合并步骤的耗时同阶，这不比用穷举的方法好。从解递归方程的套用公式法，我们看到问题出
在合并步骤耗时太多。这启发我们把注意力放在合并步骤上。
*/

#include "stdafx.h"
#include"iostream"
#include<ctime>
using namespace std;

const int L = 100;
struct Pair
{
	//点对结构体
	float d;//点对距离
	float d1, d2;//点对的坐标
};
float Random();
int input(float s[]);
float Max(float s[], int p, int q);
float Min(float s[], int p, int q);
template<class Type>void Swap(Type&x, Type&y);
template<class Type>int Partition(Type s[], Type x, int l, int r);
Pair CPair(float s[], int l, int r);


int main()
{
	srand((unsigned)time(NULL));
	int m; float s[L];
	Pair d;
	m = input(s);
	d = CPair(s, 0, m - 1);
	cout << endl << "最近点对坐标为：(d1:" << d.d1 << ",d2:" << d.d2 << ")";
	cout << endl << "这两点距离：" << d.d << endl;
	return 0;
}

float Random()
{
	float result = rand() % 10000;
	return result*0.01;
}
int input(float s[])
{
	int length;
	cout << "输入点的数目：";
	cin >> length;
	cout << "点集在x轴上对的坐标为：";
	for (int i = 0; i < length; i++)
	{
		s[i] = Random();
		cout << s[i] << " ";
	}
	return length;
}
//返回s[]中的最大值
float Max(float s[], int l, int r)
{
	float s_max = s[l];
	for (int i = l + 1; i <= r; i++)
	{
		if (s_max < s[i])
			s_max = s[i];
	}
	return s_max;
}
//返回s[]中的额最小值
float Min(float s[], int l, int r)
{
	float s_min = s[l];
	for (int i = l + 1; i <= r; i++)
	{
		if (s_min > s[i])
			s_min = s[i];
	}
	return s_min;
}
template<class Type>void Swap(Type&x, Type&y)
{
	Type temp = x;
	x = y;
	y = temp;
}
template<class Type>int Partition(Type s[], Type x, int l, int r)
{
	int i = l - 1;
	int j = r + 1;
	while (true)
	{
		while ((s[++i] < x) && (i < r));
		while (s[--j]>x);
		if (i >= j)
		{
			break;
		}
		Swap(s[i], s[j]);
	}
	return j;
}
//返回s[]中具有最近距离的点对及其距离
Pair CPair(float s[], int l, int r)
{
	Pair min_d = {99999,0,0};//最短距离
	if (r - 1 < l)
		return min_d;
	float m1 = Max(s, l,r);
	float m2 = Min(s, l, r);
	float m = (m1 + m2) / 2;//找出点集的中位数
	int j = Partition(s, m, l, r);//将点集中的各元素按与m的大小关系分组
	Pair d1 = CPair(s, l, j);
	Pair d2 = CPair(s, j + 1, r);//递归
	float p = Max(s, l, j), q = Min(s, j + 1, r);
	//返回s[]中具有最近距离的点对及其距离
	if (d1.d < d2.d)
	{
		if ((q - p) < d1.d)
		{
			min_d.d = (q-p);
			min_d.d1 = q;
			min_d.d2 =p;
			return min_d;
		}
		else
			return d1;
	}
	else
	{
		if ((q - p) < d2.d)
		{
			min_d.d = (q - p);
			min_d.d1 = q;
			min_d.d2 = p;
			return min_d;
		}
		else
			return d2;
	}
}
/*
该算法的分割步骤和合并步骤总共耗时O(n)。因此，算法耗费的计算时间T(n)满足递归方程：
T(2)=1;T(n)=2T(n/2)+O(n);
解此递归方程可得T(n)=O(nlogn)。
*/