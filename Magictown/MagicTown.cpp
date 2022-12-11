#include "MagicTown.h"
/*
   加载魔塔图片，初始化全部地图，并且初始化各类
*/
MagicTown::MagicTown()
{
	LoadPicture();
	// 创建HuaRongDao类和WhiteblackChess类
	hua_rong_dao = new HuaRongDao();
	whiteblack_chess = new WhiteblackChess();
	// 使HuaRongDao类和WhiteblackChess类包含MagicTown类以调用方法
	hua_rong_dao->magic_town = this;
	whiteblack_chess->magic_town = this;

	// 钥匙1数量，钥匙2数量，层数-1
	yellowkey_num = 0, bluekey_num = 0, floor_num = 0;
	// 现在位置
	place_x = 1, place_y = 1;
	// 魔塔地图：0墙，1地，2门1，3门2，4钥匙1，5钥匙2，6楼梯1，7楼梯2，8人，9华容道，10黑白棋，11隐藏格子
	int temp_map[3][10][10] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
						        0, 8, 1, 4, 1, 0, 1, 1, 1, 0,
						        0, 0, 0, 0, 1, 0, 1, 0, 1, 0,
						        0, 1, 4, 0, 1, 0, 1, 0, 1, 0,
						        0, 1, 1, 0, 1, 0, 1, 0, 5, 0,
						        0, 2, 0, 0, 1, 0, 2, 0, 0, 0,
						        0, 1, 1, 1, 1, 1, 1, 1, 1, 0,
						        0, 2, 0, 1, 0, 0, 0, 3, 0, 0,
						        0, 4, 0, 1, 0, 1, 1, 1, 6, 0,
						        0, 0, 0, 0, 0, 0, 0, 0, 0, 0,

						        0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
						        0, 9, 9, 0, 6, 6, 0, 10, 10, 0,
						        0, 9, 9, 0, 1, 1, 0, 10, 10, 0,
			    		        0, 1, 1, 0, 1, 1, 0, 1, 1, 0,
					            0, 1, 1, 0, 1, 1, 0, 1, 1, 0,
					            0, 0, 3, 0, 1, 1, 0, 3, 0, 0,
						        0, 1, 1, 1, 1, 1, 1, 1, 1, 0,
						        0, 2, 0, 0, 0, 0, 0, 0, 0, 0,
						        0, 4, 1, 1, 1, 1, 1, 1, 7, 0,
						        0, 0, 0, 0, 0, 0, 0, 0, 0, 0,

						        0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
						        0, 0, 0, 0, 7, 7, 0, 0, 0, 0,
       						    0, 0, 0, 1, 1, 1, 1, 0, 0, 0,
						        0, 0, 1, 1, 1, 1, 1, 1, 0, 0,
						        0, 1, 1, 1, 0, 0, 1, 1, 1, 0,
						        0, 1, 1, 0, 0, 0, 0, 1, 1, 0,
						        0, 1, 1, 0, 5, 5, 0, 1, 1, 0,
						        0, 1, 0, 0, 11, 11, 0, 0, 1, 0,
						        0, 1, 1, 11, 11, 11, 11, 1, 1, 0,
						        0, 0, 0, 0, 0, 0, 0, 0, 0, 0
	};
	memcpy(map, temp_map, sizeof(temp_map));
}
/*
    析构生成的类
*/
MagicTown::~MagicTown()
{
	delete hua_rong_dao;
	delete whiteblack_chess;
}
/*
    初始化魔塔开始地图
*/
void MagicTown::InitGame()
{
	initgraph(600, 500);
	DrawGame(floor_num);
}
/*
    加载魔塔图片
*/
void MagicTown::LoadPicture()
{
	loadimage(&wall, L"墙.png");
	loadimage(&wall2, L"墙2.png");
	loadimage(&floor, L"地.png");
	loadimage(&shang, L"上上.png");
	loadimage(&xia, L"下下.png");
	loadimage(&zuo, L"左左.png");
	loadimage(&you, L"右右.png");
	loadimage(&door1, L"门1.png");
	loadimage(&door2, L"门2.png");
	loadimage(&key1, L"钥匙1.png");
	loadimage(&key2, L"钥匙2.png");
	loadimage(&up, L"楼梯1.png");
	loadimage(&down, L"楼梯2.png");
	loadimage(&huarongdao, L"华容道.png");
	loadimage(&blackwhitechess, L"黑白棋.png");
}
/*
    根据层数绘制地图：floor_num为选中楼层
*/
void MagicTown::DrawGame(int floor_num)
{
	// 记录两个四格图是否被加载
	int flag[2] = { 0,0 };
	for (int i = 0; i < 10; i++)
		for (int j = 0; j < 10; j++)
		{
			if (map[floor_num][i][j] == 0)
				putimage(j * 50, i * 50, &wall);
			else if (map[floor_num][i][j] == 1)
				putimage(j * 50, i * 50, &floor);
			else if (map[floor_num][i][j] == 2)
				putimage(j * 50, i * 50, &door1);
			else if (map[floor_num][i][j] == 3)
				putimage(j * 50, i * 50, &door2);
			else if (map[floor_num][i][j] == 4)
				putimage(j * 50, i * 50, &key1);
			else if (map[floor_num][i][j] == 5)
				putimage(j * 50, i * 50, &key2);
			else if (map[floor_num][i][j] == 6)
				putimage(j * 50, i * 50, &up);
			else if (map[floor_num][i][j] == 7)
				putimage(j * 50, i * 50, &down);
			else if (map[floor_num][i][j] == 8)
				putimage(j * 50, i * 50, &shang);
			else if (map[floor_num][i][j] == 9 && flag[0] == 0)
			{
				putimage(j * 50, i * 50, &huarongdao);
				flag[0] = 1;
			}
			else if (map[floor_num][i][j] == 10 && flag[1] == 0)
			{
				putimage(j * 50, i * 50, &blackwhitechess);
				flag[1] = 1;
			}
			else if (map[floor_num][i][j] == 11)
				putimage(j * 50, i * 50, &wall2);
		}
	// 绘制物品的数量
	ShowThings();
}
/*
    显示钥匙数量与楼层
*/
void MagicTown::ShowThings()
{
	settextstyle(30, 0, L"黑体");
	TCHAR s[10];
	putimage(525, 70, &key1);
	putimage(525, 200, &key2);
	wsprintf(s, L"%d个", yellowkey_num);
	outtextxy(530, 130, s);
	wsprintf(s, L"%d个", bluekey_num);
	outtextxy(530, 260, s);
	settextstyle(40, 0, L"黑体");
	wsprintf(s, L"第%d层", floor_num + 1);
	outtextxy(500, 400, s);
}
/*
    开始魔塔游戏，以键盘按键wasd移动
*/
void MagicTown::PlayGame()
{
	InitGame();
	// 面向方向：1下，2上，3左，4右
	int face_to = 1;
	while (true)
	{
		char key = _getch();
		switch (key)
		{
		// 向上移动
		case 'w':
		case 'W':
		{
			face_to = 2;
			// 上方为空或物品
			if (map[floor_num][place_y - 1][place_x] == 1 || map[floor_num][place_y - 1][place_x] == 4 || map[floor_num][place_y - 1][place_x] == 5 || map[floor_num][place_y - 1][place_x] == 11)
			{
				if (map[floor_num][place_y - 1][place_x] == 4)
					yellowkey_num++;
				else if (map[floor_num][place_y - 1][place_x] == 5)
					bluekey_num++;
				map[floor_num][place_y - 1][place_x] = 8;
				map[floor_num][place_y][place_x] = 1;
				putimage(place_x * 50, place_y * 50, &floor);
				place_y--;
			}
			// 上方为门
			else if (map[floor_num][place_y - 1][place_x] == 2)
			{
				if (yellowkey_num > 0)
				{
					yellowkey_num--;
					map[floor_num][place_y - 1][place_x] = 8;
					map[floor_num][place_y][place_x] = 1;
					putimage(place_x * 50, place_y * 50, &floor);
					place_y--;
				}
			}
			else if (map[floor_num][place_y - 1][place_x] == 3)
			{
				if (bluekey_num > 0)
				{
					bluekey_num--;
					map[floor_num][place_y - 1][place_x] = 8;
					map[floor_num][place_y][place_x] = 1;
					putimage(place_x * 50, place_y * 50, &floor);
					place_y--;
				}
			}
			// 上方为楼梯
			else if (map[floor_num][place_y - 1][place_x] == 6 || map[floor_num][place_y - 1][place_x] == 7)
			{
				if (map[floor_num][place_y - 1][place_x] == 6)
				{
					map[floor_num][place_y][place_x] = 1;
					floor_num++;
				}
				else if (map[floor_num][place_y - 1][place_x] == 7)
				{
					map[floor_num][place_y][place_x] = 1;
					floor_num--;
				}
				DrawGame(floor_num);
			}
			// 进入华容道
			else if (map[floor_num][place_y - 1][place_x] == 9)
			{
				hua_rong_dao->PlayGame();
			}
			// 进入黑白棋
			else if (map[floor_num][place_y - 1][place_x] == 10)
			{
				whiteblack_chess->PlayGame();
			}
		}
		break;
		//向下
		case 's':
		case 'S':
		{
			face_to = 1;
			// 下方为空或物品
			if (map[floor_num][place_y + 1][place_x] == 1 || map[floor_num][place_y + 1][place_x] == 4 || map[floor_num][place_y + 1][place_x] == 5 || map[floor_num][place_y + 1][place_x] == 11)
			{
				if (map[floor_num][place_y + 1][place_x] == 4)
					yellowkey_num++;
				else if (map[floor_num][place_y + 1][place_x] == 5)
					bluekey_num++;
				map[floor_num][place_y + 1][place_x] = 8;
				map[floor_num][place_y][place_x] = 1;
				putimage(place_x * 50, place_y * 50, &floor);
				place_y++;
			}
			// 下方为门
			else if (map[floor_num][place_y + 1][place_x] == 2)
			{
				if (yellowkey_num > 0)
				{
					yellowkey_num--;
					map[floor_num][place_y + 1][place_x] = 8;
					map[floor_num][place_y][place_x] = 1;
					putimage(place_x * 50, place_y * 50, &floor);
					place_y++;
				}
			}
			else if (map[floor_num][place_y + 1][place_x] == 3)
			{
				if (bluekey_num > 0)
				{
					bluekey_num--;
					map[floor_num][place_y + 1][place_x] = 8;
					map[floor_num][place_y][place_x] = 1;
					putimage(place_x * 50, place_y * 50, &floor);
					place_y++;
				}
			}
			// 下方为楼梯
			else if (map[floor_num][place_y + 1][place_x] == 6 || map[floor_num][place_y + 1][place_x] == 7)
			{
				if (map[floor_num][place_y + 1][place_x] == 6)
					floor_num++;
				else if (map[floor_num][place_y + 1][place_x] == 7)
					floor_num--;
				DrawGame(floor_num);
			}
		}
		break;
		//向右
		case 'd':
		case 'D':
		{
			face_to = 4;
			// 右方为空或物品
			if (map[floor_num][place_y][place_x + 1] == 1 || map[floor_num][place_y][place_x + 1] == 4 || map[floor_num][place_y][place_x + 1] == 5 || map[floor_num][place_y][place_x + 1] == 11)
			{
				if (map[floor_num][place_y][place_x + 1] == 4)
					yellowkey_num++;
				else if (map[floor_num][place_y][place_x + 1] == 5)
					bluekey_num++;
				map[floor_num][place_y][place_x + 1] = 8;
				map[floor_num][place_y][place_x] = 1;
				putimage(place_x * 50, place_y * 50, &floor);
				place_x++;
			}
			// 右方为门
			else if (map[floor_num][place_y][place_x + 1] == 2)
			{
				if (yellowkey_num > 0)
				{
					yellowkey_num--;
					map[floor_num][place_y][place_x + 1] = 8;
					map[floor_num][place_y][place_x] = 1;
					putimage(place_x * 50, place_y * 50, &floor);
					place_x++;
				}
			}
			else if (map[floor_num][place_y][place_x + 1] == 3)
			{
				if (bluekey_num > 0)
				{
					bluekey_num--;
					map[floor_num][place_y][place_x + 1] = 8;
					map[floor_num][place_y][place_x] = 1;
					putimage(place_x * 50, place_y * 50, &floor);
					place_x++;
				}
			}
			// 右方为楼梯
			else if (map[floor_num][place_y][place_x + 1] == 6 || map[floor_num][place_y][place_x + 1] == 7)
			{
				if (map[floor_num][place_y][place_x + 1] == 6)
					floor_num++;
				else if (map[floor_num][place_y][place_x + 1] == 7)
					floor_num--;
				DrawGame(floor_num);
			}
		}
		break;
		//向左
		case 'A':
		case 'a':
		{
			face_to = 3;
			// 左方为物品或空
			if (map[floor_num][place_y][place_x - 1] == 1 || map[floor_num][place_y][place_x - 1] == 4 || map[floor_num][place_y][place_x - 1] == 5 || map[floor_num][place_y][place_x - 1] == 11)
			{
				if (map[floor_num][place_y][place_x - 1] == 4)
					yellowkey_num++;
				else if (map[floor_num][place_y][place_x - 1] == 5)
					bluekey_num++;
				map[floor_num][place_y][place_x - 1] = 8;
				map[floor_num][place_y][place_x] = 1;
				putimage(place_x * 50, place_y * 50, &floor);
				place_x--;
			}
			// 左方为门
			else if (map[floor_num][place_y][place_x - 1] == 2)
			{
				if (yellowkey_num > 0)
				{
					yellowkey_num--;
					map[floor_num][place_y][place_x + 1] = 8;
					map[floor_num][place_y][place_x] = 1;
					putimage(place_x * 50, place_y * 50, &floor);
					place_x--;
				}
			}
			else if (map[floor_num][place_y][place_x - 1] == 3)
			{
				if (bluekey_num > 0)
				{
					bluekey_num--;
					map[floor_num][place_y][place_x + 1] = 8;
					map[floor_num][place_y][place_x] = 1;
					putimage(place_x * 50, place_y * 50, &floor);
					place_x--;
				}
			}
			// 左方为楼梯
			else if (map[floor_num][place_y][place_x - 1] == 6 || map[floor_num][place_y][place_x - 1] == 7)
			{
				if (map[floor_num][place_y][place_x - 1] == 6)
					floor_num++;
				else if (map[floor_num][place_y][place_x - 1] == 7)
					floor_num--;
				DrawGame(floor_num);
			}
		}
		break;
		default:
			break;
		}
		// 根据朝向显示图像
		if (face_to == 1)
			putimage(place_x * 50, place_y * 50, &xia);
		else if (face_to == 2)
			putimage(place_x * 50, place_y * 50, &shang);
		else if (face_to == 3)
			putimage(place_x * 50, place_y * 50, &zuo);
		else if (face_to == 4)
			putimage(place_x * 50, place_y * 50, &you);
		// 绘制物品数量
		ShowThings();
	}

}
