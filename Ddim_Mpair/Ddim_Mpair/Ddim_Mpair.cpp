/*Ddim_Mpair.cpp : 定义控制台应用程序的入口点。
设S中的点为平面上的点，它们都有2个坐标值x和y。
为了将平面上点集S线性分割为大小大致相等的2个子集S1和
S2，我们选取一垂直线l:x=m来作为分割直线。其中m为S中
各点x坐标的中位数。由此将S分割为S1={p∈S|px≤m}和S2
={p∈S|px>m}。从而使S1和S2分别位于直线l的左侧和右侧，且
S=S1∪S2 。由于m是S中各点x坐标值的中位数，因此S1和S2中
的点数大致相等。递归地在S1和S2上解最接近点对问题，我们分别得
到S1和S2中的最小距离d1和d2。现设d=min(d1,d2)。若S的最接近点
对(p,q)之间的距离d(p,q)<d则p和q必分属于S1和S2。
不妨设p∈S1，q∈S2。那么p和q距直线l的距离均小于d。
我们只知道对于P1中每个S1中的点p最多只需要检查P2中的6个点，但是我们并不
确切地知道要检查哪6个点。为了解决这个问题，我们可以将p和P2中所有S2的点投影
到垂直线l上。由于能与p点一起构成最接近点对候选者的S2中点一定在矩形R中，所以它们在直线
l上的投影点距p在l上投影点的距离小于d。由上面的分析可知，这种投影点最多只有6个。因
此，若将P1和P2中所有S的点按其y坐标排好序，则对P1中所有点p，对排好序的点列作一次扫描，
就可以找出所有最接近点对的候选者，对P1中每一点最多只要检查P2中排好序的相继6个点。
*/

#include "stdafx.h"
#include<ctime>
#include"iostream"
#include<cmath>
using namespace std;
const int M = 50;

//用类pointX和pointY表示X坐标和Y坐标排好序的点
class PointX
{
public:
	int ID;//点编号
	float x, y;//点坐标
	int operator<=(PointX a)const
	{
		return (x <= a.x);
	}
};
class PointY
{
public:
	int p;//同一点在数组x中的坐标
	float x, y;//点坐标
	int operator<=(PointY a)const
	{
		return(y <= a.y);
	}
};

float Random();
template<class Type>float dis(const Type&u, const Type&v);
bool Cpair2(PointX X[], int n, PointX&a, PointX&b, float&d);
void closest(PointX X[], PointY Y[], PointY Z[], int l, int r, PointX&a, PointX&b, float&d);
template<typename Type>void Copy(Type a[], Type b[], int left, int right);//"typename"是一个C++程序设计语言中的关键字。相当用于泛型编程时是另一术语"class"的同义词。
template<class Type>void Merge(Type c[], Type d[], int l,int m, int r);
template<class Type>void MergeSort(Type a[], Type b[], int left, int right);

int main()
{
	srand((unsigned)time(NULL));
	int length;
	cout << "请输入点对数：";
	cin >> length;
	PointX X[M];
	cout << "随机生成二维点对为：" << endl;
	for (int i = 0; i < length; i++)
	{
		X[i].ID = i;
		X[i].x = Random();
		X[i].y = Random();
		cout << "(" << X[i].x << "," << X[i].y << ")";
	}
	PointX a;
	PointX b;
	float d;
	Cpair2(X, length, a, b, d);
	cout << endl;
	cout << "最邻近点对为：（" << a.x << "，" << a.y << "）和（" << b.x << "，" << b.y << "）" << endl;
	cout << "最邻近距离为：" << d << endl;
	return 0;
}

float Random()
{
	float result = rand() % 10000;
	return result*0.01;
}
//平面上任意两点u和v之间的距离可计算如下
template<class Type>inline float dis(const Type&u, const Type&v)
{
	float dx = u.x - v.x;
	float dy = u.y - v.y;
	return sqrt(dx*dx + dy*dy);
}
//点对距离矩阵
bool Cpair2(PointX X[], int n, PointX&a, PointX&b, float&d)
{
	if (n < 2)
		return false;
	PointX* tmpX = new PointX[n];
	MergeSort(X, tmpX, 0, n - 1);
	PointY* Y = new PointY[n];
	for (int i = 0; i < n; i++)
	{
		//将数组复制到Y中
		Y[i].p = i;//在X中的位置
		Y[i].x = X[i].x;
		Y[i].y = X[i].y;
	}
	PointY* tmpY = new PointY[n];
	MergeSort(Y, tmpY, 0, n - 1);
	PointY*Z = new PointY[n];
	closest(X, Y, Z, 0, n - 1, a, b, d);
	delete []Y;
	delete []Z;
	delete []tmpX;
	delete []tmpY;
	return true;
}
void closest(PointX X[], PointY Y[], PointY Z[], int l, int r, PointX&a, PointX&b, float&d)
{
	if (r - l== 1)//两点
	{
		a = X[l];
		b = X[r];
		d = dis(X[l], X[r]);
		return;
	}
	if (r -l == 2)//三点
	{
		float d1 = dis(X[l], X[l+ 1]);
		float d2 = dis(X[l + 1], X[r]);
		float d3 = dis(X[l], X[r]);
		if ((d1 <= d2)&&(d1 <= d3))
		{
			a = X[l];
			b = X[l + 1];
			d = d1;
			return;
		}

		if (d2 <= d3)
		{
			a = X[l + 1];
			b = X[r];
			d = d2;
		}
		else
		{
			a = X[l];
			b = X[r];
			d = d3;
		}
		return;
	}
	//多余3点的情形，用分治
	int m = (l + r) / 2;
	int f = l, g = m + 1;
	/*
	子算法预处理阶段，将数组X中的点依照X坐标排序，将数组Y中的点依照y坐标排序
	算法分割阶段，将数组X划分成两个不相交的子集，取m=(1+r)/2,X[1:m]和X[M+1:r]就满足要求
	*/
	for (int i = l; i <= r; i++)
	{
		if (Y[i].p > m)
			Z[g++] = Y[i];
		else
			Z[f++] = Y[i];
	}
	closest(X, Z, Y, l, m, a, b, d);
	float dr;
	PointX ar, br;
	closest(X, Z, Y, m + 1, r, ar, br, dr);
	if (dr < d)
	{
		a = ar;
		b = br;
		d = dr;
	}
	Merge(Z,Y,l, m, r);//重构数组Y
	//d矩形条内的点置于z中
	int k =l;
	for (int i = l; i <= r; i++)
	{
		if (fabs(X[m].x - Y[i].x) < d)
			Z[k++] = Y[i];
	}
	//搜索Z[1:k-1]
	for (int i = l; i < k; i++)
	{
		for (int j = i + 1; (j < k )&& (Z[j].y - Z[i].y < d); j++)
		{
			float dp = dis(Z[i], Z[j]);
			if (dp < d)
			{
				d = dp;
				a = X[Z[i].p];
				b = X[Z[j].p];
			}
		}
	}
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
		for (int q =i; q <= m; q++)
		{
			d[k++] = c[q];
		}
	}
}
template<class Type>void MergeSort(Type a[], Type b[], int left, int right)
{
	if (left < right)
	{
		int i = (left + right) / 2;
		MergeSort(a, b, left, i);
		MergeSort(a, b, i + 1, right);
		Merge(a, b, left, i, right);//合并到数组b中
		Copy(a, b, left, right);
	}
}
template<typename Type>void Copy(Type a[], Type b[], int left, int right)
{
	for (int i = left; i <= right; i++)
		a[i] = b[i];
}