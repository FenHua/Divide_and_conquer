/*ChessBoard.cpp : �������̨Ӧ�ó������ڵ㡣
ʵ�ֵĻ���ԭ���ǽ�2^k * 2^k�����̷ֳ��Ŀ�2^(k - 1) * 2^(k - 1)�������̣�
���ⷽ��һ�������е�һ���������У�������ⷽ����ĳһ���������У�
�����ݹ鴦����������̣�ֱ�������������ֻ��һ������Ϊֹ������ⷽ����ĳһ���������У�
������������е���Ӧ��λ����Ϊ���ƺţ�����������ⷽ���������ת��Ϊ�����ⷽ��������̣�Ȼ���ٵݹ鴦����������̡�
*/

#include "stdafx.h"
#include"iostream"
using namespace std;

int tile = 1;//ȫ�ֱ��� ���Ʊ��
int Board[4][4];//����
void ChessBoard(int tr, int tc, int dr, int dc, int size);


int main()
{
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			Board[i][j] = 0;
		}
	}
	ChessBoard(0, 0, 2, 3, 4);
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			cout << Board[i][j] << " ";
		}
		cout << endl;
	}
}

/*
tr:�������Ͻ��кţ�tc�������Ͻ��к�
dr,dc:���ⷽ����кź��к�
size:size=2^k ���̹��Ϊ2^k*2^k
*/
void ChessBoard(int tr, int tc, int dr, int dc, int size)
{
	if (size == 1)
	{
		return;
	}
	int t = tile++;//L�͹��Ʊ��
	int s = size / 2;//�ָ�����

	//�������Ͻ�������
	if ((dr < tr + s) && (dc < tc + s))
	{
		ChessBoard(tr, tc, dr, dc, s);//���ⷽ���ڴ˷�����
	}
	else
	{
		//���ⷽ���ڴ�������
		Board[tr + s - 1][tc + s - 1] = t;//�ñ��Ϊt�Ĺ��Ƹ������½�
		ChessBoard(tr, tc, tr + s - 1, tc + s - 1, s);//��������ķ���
	}
	//�������Ͻ�������
	if ((dr<tr + s) && (dc>=tc + s))
	{
		ChessBoard(tr, tc + s, dr, dc, s);//���ⷽ���ڴ�������
	}
	else
	{
		//���ⷽ���ڴ�������
		Board[tr + s - 1][tc + s] = t;//�ñ��Ϊt�Ĺ��Ƹ������½�
		ChessBoard(tr, tc + s, tr + s - 1, tc + s, s);//������������
	}
	//�������½ǵ�����
	if ((dr >=tr + s) &&(dc < tc + s))
	{
		ChessBoard(tr + s, tc, dr, dc, s);//���������ڴ�������
	}
	else
	{
		//���ⷽ���ڴ�������
		Board[tr + s][tc + s - 1] = t;//�ñ��Ϊt�Ĺ��Ƹ������Ͻ�
		ChessBoard(tr + s, tc, tr + s, tc + s - 1, s);//�������෽��
	}
	//�������½ǵ�������
	if ((dr >= tr + s) && (dc >= tc + s))
	{
		//���ⷽ���ڴ�������
		ChessBoard(tr + s, tc + s, dr, dc, s);
	}
	else
	{
		//���ⷽ���ڴ�������
		Board[tr + s][tc + s] = t;//�ñ��Ϊt�Ĺ��Ƹ������Ͻ�
		ChessBoard(tr + s, tc + s, tr + s, tc + s, s);//������������
	}

}

