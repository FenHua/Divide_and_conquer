/*MinPair.cpp : �������̨Ӧ�ó������ڵ㡣
��������������ƽ����n���㣬�����е�һ�Ե㣬ʹ����n��������е���У��õ�Եľ�����С��
�ϸ��˵����ӽ���Կ��ܶ���1�ԡ�Ϊ�˼����������ֻ���������е�һ�ԡ�
1��һά��ӽ��������
�㷨˼·��
��������������⣬�ƺ�Ҳ���ѽ����
����ֻҪ��ÿһ��������n-1����ľ���������ҳ��ﵽ��С����������㼴�ɡ�
Ȼ����������Ч��̫�ͣ���ҪO(n^2)�ļ���ʱ�䡣������ļ��㸴���������ǿ��Կ���������
��ļ���ʱ���½�Ϊ��(nlogn)������½���������ȥ�������һ����(nlogn)�㷨�����÷��η�˼
�룬���ǽ�������n����ļ���S�ֳ�2���Ӽ�S1��S2��ÿ���Ӽ���Լ��n/2���㣬Ȼ����ÿ����
���еݹ��������ӽ��ĵ�ԡ������һ���ؼ������������ʵ�ַ��η��еĺϲ����裬����S1��S2��
��ӽ���ԣ�������ԭ����S�е���ӽ���ԣ���ΪS1��S2����ӽ����δ�ؾ���S����ӽ���ԡ�������S
����ӽ���Ե�2���㶼��S1�л���S2�У�����������׽�������ǣ������2����ֱ���S1��S2�У������S1����
һ��p��S2�����ֻ��n/2��������������ӽ���Եĺ�ѡ�ߣ�������n^2/4�μ���ͱȽϲ���ȷ��S����ӽ����
����ˣ�����˼·���ϲ������ʱΪO(n^2)�������㷨�������ʱ��T(n)Ӧ����:��T(n)=2T(n/2)+O(n^2)��
���Ľ�ΪT(n)=O(n^2)������ϲ�����ĺ�ʱͬ�ף��ⲻ������ٵķ����á��ӽ�ݹ鷽�̵����ù�ʽ�������ǿ��������
�ںϲ������ʱ̫�ࡣ���������ǰ�ע�������ںϲ������ϡ�
*/

#include "stdafx.h"
#include"iostream"
#include<ctime>
using namespace std;

const int L = 100;
struct Pair
{
	//��Խṹ��
	float d;//��Ծ���
	float d1, d2;//��Ե�����
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
	cout << endl << "����������Ϊ��(d1:" << d.d1 << ",d2:" << d.d2 << ")";
	cout << endl << "��������룺" << d.d << endl;
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
	cout << "��������Ŀ��";
	cin >> length;
	cout << "�㼯��x���϶Ե�����Ϊ��";
	for (int i = 0; i < length; i++)
	{
		s[i] = Random();
		cout << s[i] << " ";
	}
	return length;
}
//����s[]�е����ֵ
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
//����s[]�еĶ���Сֵ
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
//����s[]�о����������ĵ�Լ������
Pair CPair(float s[], int l, int r)
{
	Pair min_d = {99999,0,0};//��̾���
	if (r - 1 < l)
		return min_d;
	float m1 = Max(s, l,r);
	float m2 = Min(s, l, r);
	float m = (m1 + m2) / 2;//�ҳ��㼯����λ��
	int j = Partition(s, m, l, r);//���㼯�еĸ�Ԫ�ذ���m�Ĵ�С��ϵ����
	Pair d1 = CPair(s, l, j);
	Pair d2 = CPair(s, j + 1, r);//�ݹ�
	float p = Max(s, l, j), q = Min(s, j + 1, r);
	//����s[]�о����������ĵ�Լ������
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
���㷨�ķָ��ͺϲ������ܹ���ʱO(n)����ˣ��㷨�ķѵļ���ʱ��T(n)����ݹ鷽�̣�
T(2)=1;T(n)=2T(n/2)+O(n);
��˵ݹ鷽�̿ɵ�T(n)=O(nlogn)��
*/