#ifndef _BLACKWHITE_H_
#define _BLACKWHITE_H_

#include <graphics.h>
#include <stdio.h>

#include "MagicTown.h"

class MagicTown;

class WhiteblackChess
{
private:
	int blackwhite_chess_map[8][8];  // 黑白棋棋盘
	int black_chess, white_chess; // 黑白棋子数

private:
	void InitGame(); // 绘制黑白棋棋盘
	void DrawChess(int a, int b, int color); // 绘制落子
	bool CanSetThere(int x, int y, int color); // 判断这个位置能否落子
	void TakeDown(int x, int y, int color); // 黑白棋吃子
	bool CanNotSet(int color); // 判断是否还有地方落子
	void CountChess(); // 计算棋子数量

public:
	WhiteblackChess();
	void PlayGame(); // “黑白棋”游戏进行

public:
	// 调用MagicTown类的方法
	MagicTown* magic_town;

};

#endif // !_BLACKWHITE_H_