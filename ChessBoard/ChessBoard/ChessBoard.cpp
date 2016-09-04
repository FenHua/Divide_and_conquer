/*ChessBoard.cpp : 定义控制台应用程序的入口点。
实现的基本原理是将2^k * 2^k的棋盘分成四块2^(k - 1) * 2^(k - 1)的子棋盘，
特殊方格一定在其中的一个子棋盘中，如果特殊方格在某一个子棋盘中，
继续递归处理这个子棋盘，直到这个子棋盘中只有一个方格为止如果特殊方格不在某一个子棋盘中，
将这个子棋盘中的相应的位置设为骨牌号，将这个无特殊方格的了棋盘转换为有特殊方格的子棋盘，然后再递归处理这个子棋盘。
*/

#include "stdafx.h"
#include"iostream"
using namespace std;

int tile = 1;//全局变量 骨牌编号
int Board[4][4];//棋盘
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
tr:棋盘左上角行号，tc棋盘左上角列号
dr,dc:特殊方格的行号和列号
size:size=2^k 棋盘规格为2^k*2^k
*/
void ChessBoard(int tr, int tc, int dr, int dc, int size)
{
	if (size == 1)
	{
		return;
	}
	int t = tile++;//L型骨牌编号
	int s = size / 2;//分割棋盘

	//覆盖左上角子棋盘
	if ((dr < tr + s) && (dc < tc + s))
	{
		ChessBoard(tr, tc, dr, dc, s);//特殊方格在此方格中
	}
	else
	{
		//特殊方格不在此棋盘中
		Board[tr + s - 1][tc + s - 1] = t;//用编号为t的骨牌覆盖右下角
		ChessBoard(tr, tc, tr + s - 1, tc + s - 1, s);//覆盖其余的方格
	}
	//覆盖右上角子棋盘
	if ((dr<tr + s) && (dc>=tc + s))
	{
		ChessBoard(tr, tc + s, dr, dc, s);//特殊方格在此棋盘中
	}
	else
	{
		//特殊方格不在此棋盘中
		Board[tr + s - 1][tc + s] = t;//用编号为t的骨牌覆盖左下角
		ChessBoard(tr, tc + s, tr + s - 1, tc + s, s);//覆盖其它方格
	}
	//覆盖左下角的棋盘
	if ((dr >=tr + s) &&(dc < tc + s))
	{
		ChessBoard(tr + s, tc, dr, dc, s);//特殊棋盘在此棋盘中
	}
	else
	{
		//特殊方格不在此棋盘中
		Board[tr + s][tc + s - 1] = t;//用编号为t的骨牌覆盖右上角
		ChessBoard(tr + s, tc, tr + s, tc + s - 1, s);//覆盖其余方格
	}
	//覆盖右下角的子棋盘
	if ((dr >= tr + s) && (dc >= tc + s))
	{
		//特殊方格在此棋盘中
		ChessBoard(tr + s, tc + s, dr, dc, s);
	}
	else
	{
		//特殊方格不在此棋盘中
		Board[tr + s][tc + s] = t;//用编号为t的骨牌覆盖左上角
		ChessBoard(tr + s, tc + s, tr + s, tc + s, s);//覆盖其它方格
	}

}

