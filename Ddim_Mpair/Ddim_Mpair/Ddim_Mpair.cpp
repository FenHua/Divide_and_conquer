/*Ddim_Mpair.cpp : �������̨Ӧ�ó������ڵ㡣
��S�еĵ�Ϊƽ���ϵĵ㣬���Ƕ���2������ֵx��y��
Ϊ�˽�ƽ���ϵ㼯S���Էָ�Ϊ��С������ȵ�2���Ӽ�S1��
S2������ѡȡһ��ֱ��l:x=m����Ϊ�ָ�ֱ�ߡ�����mΪS��
����x�������λ�����ɴ˽�S�ָ�ΪS1={p��S|px��m}��S2
={p��S|px>m}���Ӷ�ʹS1��S2�ֱ�λ��ֱ��l�������Ҳ࣬��
S=S1��S2 ������m��S�и���x����ֵ����λ�������S1��S2��
�ĵ���������ȡ��ݹ����S1��S2�Ͻ���ӽ�������⣬���Ƿֱ��
��S1��S2�е���С����d1��d2������d=min(d1,d2)����S����ӽ���
��(p,q)֮��ľ���d(p,q)<d��p��q�ط�����S1��S2��
������p��S1��q��S2����ôp��q��ֱ��l�ľ����С��d��
����ֻ֪������P1��ÿ��S1�еĵ�p���ֻ��Ҫ���P2�е�6���㣬�������ǲ���
ȷ�е�֪��Ҫ�����6���㡣Ϊ�˽��������⣬���ǿ��Խ�p��P2������S2�ĵ�ͶӰ
����ֱ��l�ϡ���������p��һ�𹹳���ӽ���Ժ�ѡ�ߵ�S2�е�һ���ھ���R�У�����������ֱ��
l�ϵ�ͶӰ���p��l��ͶӰ��ľ���С��d��������ķ�����֪������ͶӰ�����ֻ��6������
�ˣ�����P1��P2������S�ĵ㰴��y�����ź������P1�����е�p�����ź���ĵ�����һ��ɨ�裬
�Ϳ����ҳ�������ӽ���Եĺ�ѡ�ߣ���P1��ÿһ�����ֻҪ���P2���ź�������6���㡣
*/

#include "stdafx.h"
#include<ctime>
#include"iostream"
#include<cmath>
using namespace std;
const int M = 50;

//����pointX��pointY��ʾX�����Y�����ź���ĵ�
class PointX
{
public:
	int ID;//����
	float x, y;//������
	int operator<=(PointX a)const
	{
		return (x <= a.x);
	}
};
class PointY
{
public:
	int p;//ͬһ��������x�е�����
	float x, y;//������
	int operator<=(PointY a)const
	{
		return(y <= a.y);
	}
};

float Random();
template<class Type>float dis(const Type&u, const Type&v);
bool Cpair2(PointX X[], int n, PointX&a, PointX&b, float&d);
void closest(PointX X[], PointY Y[], PointY Z[], int l, int r, PointX&a, PointX&b, float&d);
template<typename Type>void Copy(Type a[], Type b[], int left, int right);//"typename"��һ��C++������������еĹؼ��֡��൱���ڷ��ͱ��ʱ����һ����"class"��ͬ��ʡ�
template<class Type>void Merge(Type c[], Type d[], int l,int m, int r);
template<class Type>void MergeSort(Type a[], Type b[], int left, int right);

int main()
{
	srand((unsigned)time(NULL));
	int length;
	cout << "������������";
	cin >> length;
	PointX X[M];
	cout << "������ɶ�ά���Ϊ��" << endl;
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
	cout << "���ڽ����Ϊ����" << a.x << "��" << a.y << "���ͣ�" << b.x << "��" << b.y << "��" << endl;
	cout << "���ڽ�����Ϊ��" << d << endl;
	return 0;
}

float Random()
{
	float result = rand() % 10000;
	return result*0.01;
}
//ƽ������������u��v֮��ľ���ɼ�������
template<class Type>inline float dis(const Type&u, const Type&v)
{
	float dx = u.x - v.x;
	float dy = u.y - v.y;
	return sqrt(dx*dx + dy*dy);
}
//��Ծ������
bool Cpair2(PointX X[], int n, PointX&a, PointX&b, float&d)
{
	if (n < 2)
		return false;
	PointX* tmpX = new PointX[n];
	MergeSort(X, tmpX, 0, n - 1);
	PointY* Y = new PointY[n];
	for (int i = 0; i < n; i++)
	{
		//�����鸴�Ƶ�Y��
		Y[i].p = i;//��X�е�λ��
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
	if (r - l== 1)//����
	{
		a = X[l];
		b = X[r];
		d = dis(X[l], X[r]);
		return;
	}
	if (r -l == 2)//����
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
	//����3������Σ��÷���
	int m = (l + r) / 2;
	int f = l, g = m + 1;
	/*
	���㷨Ԥ����׶Σ�������X�еĵ�����X�������򣬽�����Y�еĵ�����y��������
	�㷨�ָ�׶Σ�������X���ֳ��������ཻ���Ӽ���ȡm=(1+r)/2,X[1:m]��X[M+1:r]������Ҫ��
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
	Merge(Z,Y,l, m, r);//�ع�����Y
	//d�������ڵĵ�����z��
	int k =l;
	for (int i = l; i <= r; i++)
	{
		if (fabs(X[m].x - Y[i].x) < d)
			Z[k++] = Y[i];
	}
	//����Z[1:k-1]
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
		Merge(a, b, left, i, right);//�ϲ�������b��
		Copy(a, b, left, right);
	}
}
template<typename Type>void Copy(Type a[], Type b[], int left, int right)
{
	for (int i = left; i <= right; i++)
		a[i] = b[i];
}