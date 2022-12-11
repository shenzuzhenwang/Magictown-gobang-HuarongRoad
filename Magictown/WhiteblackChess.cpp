#include "WhiteblackChess.h"
/*
    初始化黑白棋棋盘
*/
WhiteblackChess::WhiteblackChess()
{
	black_chess = 0;
	white_chess = 0;
	// 初始化棋盘为空
	memset(blackwhite_chess_map, 0, sizeof(blackwhite_chess_map));
}
/*
    绘制黑白棋棋盘
*/
void WhiteblackChess::InitGame()
{
	// 初始化画布，显示“黑白棋”
	initgraph(650, 650);
	setbkcolor(RGB(255, 215, 0));
	cleardevice();
	settextstyle(150, 0, L"黑体");
	settextcolor(BLACK);
	outtextxy(100, 250, L"黑白棋");
	Sleep(5000);
	cleardevice();

	// 绘制退出键
	setlinecolor(BLACK);
	setfillcolor(LIGHTGRAY);
	bar(580, 0, 650, 40);
	setbkmode(TRANSPARENT);
	settextstyle(30, 0, L"黑体");
	settextcolor(LIGHTCYAN);
	outtextxy(585, 0, L"退出");

	// 绘制棋盘
	for (int i = 0; i < 9; i++)
	{
		line(70 * i + 45, 45, 70 * i + 45, 605);
		line(45, 70 * i + 45, 605, 70 * i + 45);
	}
	// 线条加粗
	line(44, 44, 44, 606);
	line(44, 44, 606, 44);
	line(44, 606, 606, 606);
	line(606, 44, 606, 606);
	line(45, 45, 604, 45);
	line(45, 45, 45, 604);
	line(45, 604, 604, 604);
	line(604, 45, 604, 604);

	// 显示下棋方
	setbkmode(OPAQUE);
	settextcolor(RED);
	outtextxy(280, 7, L"黑方下");

	for (int i = 0; i < 8; i++)
		for (int j = 0; j < 8; j++)
			blackwhite_chess_map[i][j] = 0;

	// 开局中间两黑两白
	blackwhite_chess_map[3][3] = 1;
	blackwhite_chess_map[4][4] = 1;
	blackwhite_chess_map[3][4] = 2;
	blackwhite_chess_map[4][3] = 2;
	DrawChess(3, 3, 1);
	DrawChess(4, 4, 1);
	DrawChess(3, 4, 2);
	DrawChess(4, 3, 2);
	CountChess();
}
/*
    “黑白棋”游戏进行，根据鼠标点击坐标判断落子坐标
*/
void WhiteblackChess::PlayGame()
{
	InitGame();
	// 数组blackwhite_chess_map上的坐标
	int map_x = 0, map_y = 0;
	// 黑棋先下
	int color = 1;
	MOUSEMSG m;
	while (1)
	{
		m = GetMouseMsg();
		if (m.uMsg == WM_LBUTTONDOWN)
		{
			if (m.x > 580 && m.x < 650 && m.y>0 && m.y < 40)
			{
				// 鼠标点击退出键
				magic_town->PlayGame();
			}
			else if (m.x < 45 || m.y < 45 || m.x > 605 || m.y > 605)
			{
				// 鼠标点击界外
				settextcolor(LIGHTRED);
				outtextxy(280, 7, L"出界了");
				continue;
			}

			// 根据鼠标点击坐标，判断选中位置
			map_x = (m.x - 45) / 70;
			map_y = (m.y - 45) / 70;
			// 判断该坐标是否为空且是否可以落子
			if (blackwhite_chess_map[map_y][map_x] == 0 && CanSetThere(map_x, map_y, color))
			{
				blackwhite_chess_map[map_y][map_x] = color;
				DrawChess(map_x, map_y, color);
				TakeDown(map_x, map_y, color);

				// 交换选手
				if (color == 1)
				{
					color = 2;
					settextcolor(BLUE);
					outtextxy(280, 7, L"白方下");
				}
				else if (color == 2)
				{
					color = 1;
					settextcolor(RED);
					outtextxy(280, 7, L"黑方下");
				}
			}
			// 该位置有子，或不能落子
			else
			{
				settextcolor(LIGHTRED);
				outtextxy(280, 7, L"下不了");
				continue;
			}

			// 计算现有各方棋子数
			CountChess();

			if (CanNotSet(color) == 1)
			{
				if (CanNotSet(3 - color) == 1)
				{
					// 双方无子可下
					setbkmode(TRANSPARENT);
					settextcolor(LIGHTGRAY);
					settextstyle(100, 0, L"黑体");

					// 判断胜利方
					if (black_chess > white_chess)
					{
						outtextxy(175, 275, L"黑方胜");
						Sleep(3000);
						magic_town->PlayGame();
					}
					if (black_chess <= white_chess)
					{
						outtextxy(175, 275, L"白方胜");
						Sleep(3000);
						magic_town->PlayGame();
					}
				}
				else
				{
					// 一方无子可下则跳过该方
					if (color == 1)
					{
						color = 2;
						settextcolor(BLUE);
						outtextxy(280, 7, L"白方下");
					}
					else if (color == 2)
					{
						color = 1;
						settextcolor(RED);
						outtextxy(280, 7, L"黑方下");
					}
				}
			}
		}
	}

}
/*
    绘制落子：x、y为落子的坐标，color为颜色
*/
void WhiteblackChess::DrawChess(int x, int y, int color)
{
	if (color == 1)
		setfillcolor(BLACK);
	if (color == 2)
		setfillcolor(WHITE);
	fillcircle(x * 70 + 80, y * 70 + 80, 30);
}
/*
    黑白棋吃子  
	注意：应该先判断完所有被吃掉的子，最后将被吃掉的子变色
*/
void WhiteblackChess::TakeDown(int x, int y, int color)
{
	// 判断上方吃子
	for (int i = y - 1; i >= 0 && blackwhite_chess_map[i][x]; i--)
	{
		if (blackwhite_chess_map[i][x] == color)
		{
			for (int j = y - 1; j > i; j--)
			{
				// 上方棋子变色
				blackwhite_chess_map[j][x] = 4;
				DrawChess(x, j, color);
			}
			break;
		}
	}
	// 判断下方吃子
	for (int i = y + 1; i < 8 && blackwhite_chess_map[i][x]; i++)
	{
		if (blackwhite_chess_map[i][x] == color)
		{
			for (int j = y + 1; j < i; j++)
			{
				// 下方棋子变色
				blackwhite_chess_map[j][x] = 4;
				DrawChess(x, j, color);
			}
			break;
		}
	}
	// 判断左方吃子
	for (int i = x - 1; i >= 0 && blackwhite_chess_map[y][i]; i--)
	{
		if (blackwhite_chess_map[y][i] == color)
		{
			for (int j = x - 1; j > i; j--)
			{
				// 左方棋子变色
				blackwhite_chess_map[y][j] = 4;
				DrawChess(j, y, color);
			}
			break;
		}
	}
	// 判断右方吃子
	for (int i = x + 1; i < 8 && blackwhite_chess_map[y][i]; i++)
	{
		if (blackwhite_chess_map[y][i] == color)
		{
			for (int j = x + 1; j < i; j++)
			{
				// 右方棋子变色
				blackwhite_chess_map[y][j] = 4;
				DrawChess(j, y, color);
			}
			break;
		}
	}
	// 判断左上方吃子
	for (int i = y - 1, j = x - 1; i >= 0 && j >= 0 && blackwhite_chess_map[i][j]; i--, j--)
	{
		if (blackwhite_chess_map[i][j] == color)
		{
			for (int ii = y - 1, jj = x - 1; ii > i && jj > j; ii--, jj--)
			{
				// 左上方棋子变色
				blackwhite_chess_map[ii][jj] = 4;
				DrawChess(jj, ii, color);
			}
			break;
		}
	}
	// 判断左下方吃子
	for (int i = y + 1, j = x - 1; i < 8 && j >= 0 && blackwhite_chess_map[i][j]; i++, j--)
	{
		if (blackwhite_chess_map[i][j] == color)
		{
			for (int ii = y + 1, jj = x - 1; ii < i && jj > j; ii++, jj--)
			{
				// 左下方棋子变色
				blackwhite_chess_map[ii][jj] = 4;
				DrawChess(jj, ii, color);
			}
			break;
		}
	}
	// 判断右上方吃子
	for (int i = y - 1, j = x + 1; i >= 0 && j < 8 && blackwhite_chess_map[i][j]; i--, j++)
	{
		if (blackwhite_chess_map[i][j] == color)
		{
			for (int ii = y - 1, jj = x + 1; ii > i && jj < j; ii--, jj++)
			{
				// 右上方棋子变色
				blackwhite_chess_map[ii][jj] = 4;
				DrawChess(jj, ii, color);
			}
			break;
		}
	}
	// 判断右下方吃子
	for (int i = y + 1, j = x + 1; i < 8 && j < 8 && blackwhite_chess_map[i][j]; i++, j++)
	{
		if (blackwhite_chess_map[i][j] == color)
		{
			for (int ii = y + 1, jj = x + 1; ii < i && jj < j; ii++, jj++)
			{
				// 右下方棋子变色
				blackwhite_chess_map[ii][jj] = 4;
				DrawChess(jj, ii, color);
			}
			break;
		}
	}
	// 最后棋子变色
	for (int i = 0; i < 8; i++)
		for (int j = 0; j < 8; j++)
			if (blackwhite_chess_map[i][j] == 4)
				blackwhite_chess_map[i][j] = color;

}
/*
    判断这个位置能否落子
	规则：必须有吃子
*/
bool WhiteblackChess::CanSetThere(int x, int y, int color)
{
	// 是否越过敌方子
	bool sign[8] = { 0 };

	// 判断上方是否有同色子
	for (int i = y - 1; i >= 0 && blackwhite_chess_map[i][x]; i--)
	{
		if (blackwhite_chess_map[i][x] == color)
		{
			// 上方有同色子且不相邻，则可落子
			if (i != y - 1)
				sign[0] = true;
			break;
		}
	}
	// 判断下方是否有同色子
	for (int i = y + 1; i < 8 && blackwhite_chess_map[i][x]; i++)
	{
		if (blackwhite_chess_map[i][x] == color)
		{
			// 下方有同色子且不相邻，则可落子
			if (i != y + 1)
				sign[1] = true;
			break;
		}
	}
	// 判断左方是否有同色子
	for (int i = x - 1; i >= 0 && blackwhite_chess_map[y][i]; i--)
	{
		if (blackwhite_chess_map[y][i] == color)
		{
			// 左方有同色子且不相邻，则可落子
			if (i != x - 1)
				sign[2] = true;
			break;
		}
	}
	// 判断右方是否有同色子
	for (int i = x + 1; i < 8 && blackwhite_chess_map[y][i]; i++)
	{
		if (blackwhite_chess_map[y][i] == color)
		{
			// 右方有同色子且不相邻，则可落子
			if (i != x + 1)
				sign[3] = true;
			break;
		}
	}
	// 判断左上方是否有同色子
	for (int i = y - 1, j = x - 1; i >= 0 && j >= 0 && blackwhite_chess_map[i][j]; i--, j--)
	{
		if (blackwhite_chess_map[i][j] == color)
		{
			// 左上方有同色子且不相邻，则可落子
			if (i != y - 1 && j != x - 1)
				sign[4] = true;
			break;
		}
	}
	// 判断左下方是否有同色子
	for (int i = y + 1, j = x - 1; i < 8 && j >= 0 && blackwhite_chess_map[i][j]; i++, j--)
	{
		if (blackwhite_chess_map[i][j] == color)
		{
			// 左下方有同色子且不相邻，则可落子
			if (i != y + 1 && j != x - 1)
				sign[5] = true;
			break;
		}
	}
	// 判断右上方是否有同色子
	for (int i = y - 1, j = x + 1; i >= 0 && j < 8 && blackwhite_chess_map[i][j]; i--, j++)
	{
		if (blackwhite_chess_map[i][j] == color)
		{
			// 右上方有同色子且不相邻，则可落子
			if (i != y - 1 && j != x + 1)
				sign[6] = true;
			break;
		}
	}
	// 判断右下方是否有同色子
	for (int i = y + 1, j = x + 1; i < 8 && j < 8 && blackwhite_chess_map[i][j]; i++, j++)
	{
		if (blackwhite_chess_map[i][j] == color)
		{
			// 右下方有同色子且不相邻，则可落子
			if (i != y + 1 && j != x + 1)
				sign[7] = true;
			break;
		}
	}
	if (sign[0] || sign[1] || sign[2] || sign[3] || sign[4] || sign[5] || sign[6] || sign[7])
		return 1;
	else
		return 0;
}
/*
    判断是否还有地方落子
*/
bool WhiteblackChess::CanNotSet(int color)
{
	for (int i = 0; i < 8; i++)
		for (int j = 0; j < 8; j++)
			if (blackwhite_chess_map[i][j] == 0 && CanSetThere(j, i, color))
				return 0;
	return 1;
}
/*
    计算棋子数量
*/
void WhiteblackChess::CountChess()
{
	black_chess = 0;
	white_chess = 0;
	TCHAR s[100];
	for (int i = 0; i < 8; i++)
		for (int j = 0; j < 8; j++)
		{
			if (blackwhite_chess_map[i][j] == 1)
				black_chess++;
			if (blackwhite_chess_map[i][j] == 2)
				white_chess++;
		}
	settextcolor(BLACK);
	wsprintf(s, L"黑子：%d ", black_chess);
	outtextxy(100, 0, s);
	settextcolor(WHITE);
	wsprintf(s, L"白子：%d ", white_chess);
	outtextxy(430, 0, s);
}