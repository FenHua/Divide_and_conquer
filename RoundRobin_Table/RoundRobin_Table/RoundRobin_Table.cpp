/*RoundRobin_Table.cpp : 定义控制台应用程序的入口点。
设有n=2^k个运动员要进行网球循环赛。现要设计一个满足以下要求的比赛日程表：
(1)每个选手必须与其他n-1个选手各赛一次；
(2)每个选手一天只能参赛一次；
(3)循环赛在n-1天内结束。
请按此要求将比赛日程表设计成有n行和n-1列的一个表。在表中的第i行，第j列处填入第i个选手在第j天所遇到的选手。其中1≤i≤n，1≤j≤n-1。

算法思路：按分治策略，我们可以将所有的选手分为两半，则n个选手的比赛日程表可以通过n/2个选手的比赛日程表来决定。
递归地用这种一分为二的策略对选手进行划分，直到只剩下两个选手时，比赛日程表的制定就变得很简单。
这时只要让这两个选手进行比赛就可以了。如上图，所列出的正方形表是8个选手的比赛日程表。其中左上角与左下角的两小块分别
为选手1至选手4和选手5至选手8前3天的比赛日程。据此，将左上角小块中的所有数字按其相对位置抄到右下角，又将左下角
小块中的所有数字按其相对位置抄到右上角，这样我们就分别安排好了选手1至选手4和选手5至选手8在后4天的比赛日程。
依此思想容易将这个比赛日程表推广到具有任意多个选手的情形。
*/

#include "stdafx.h"
#include<iostream>
#include<cmath>
using namespace std;

void Table(int k, int n, int **a);
void input(int &k);
void output(int**a, int n);

int main()
{
	int k;
	input(k);
	int n = 1;//n=(2k)(k>=1)个选手参加比赛
	for (int i = 1; i <= k; i++)
		n *= 2;
	int**a = new int*[n + 1];
	for (int i = 0; i <= n; i++)
		a[i] = new int[n + 1];
	Table(k, n, a);
	cout << "循环赛事日程表为：" << endl;
	output(a, n);
	//释放开辟的空间
	for (int i = 0; i <= n; i++)
	{
		delete[]a[i];
	}
	delete[]a;//释放最外空间
	return 0;
}

void input(int &k)
{
	cout << "请输入K值：" << endl;
	cin >> k;
}
void output(int**a, int n)
{
	for (int i = 1; i <= n; i++)
	{
		for (int j = 1; j <= n; j++)
		{
			cout << a[i][j] << " ";
		}
		cout << endl;
	}
}
void Table(int k, int n, int**a)
{
	for (int i = 1; i <= n; i++)
	{
		a[1][i] = i;//设置日程表第一行
	}
	int m = 1;//每次填充的起始位置
	for (int s = 1; s <= k; s++)
	{
		n /= 2;
		for (int t = 1; t <= n; t++)
		{
			for (int i = m + 1; i <= 2 * m; i++)
			{
				for (int j = m + 1; j <= 2 * m; j++)
				{
					//i和j分别控制行和列
					a[i][j + (t - 1)*m * 2] = a[i - m][j + (t-1)*m * 2 - m];//右下角等于左上角
					a[i][j + (t - 1)*m * 2 - m] = a[i - m][j + (t - 1)*m * 2];//左下角等于右上角
				}
			}
		}
		m *= 2;
	}
}