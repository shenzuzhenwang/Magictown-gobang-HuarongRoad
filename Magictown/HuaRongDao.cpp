#include "HuaRongDao.h"
/*
    加载相关图片，并初始化华容道的四个地图
*/
HuaRongDao::HuaRongDao()
{
	LoadPicture(); 
	// 华容道地图：0墙，1空，2曹操，3关羽，4张飞，5赵云，6马超，7黄忠，8卒1，9卒2，10卒3，11卒4
	int temp_map[4][6][7] = { 0, 0, 0, 0, 0, 0, 0,
	                          0, 4, 4, 6, 6, 8, 0,
	                          0, 2, 2, 3, 9, 1, 0,
	                          0, 2, 2, 3, 10, 1, 0,
	                          0, 5, 5, 7, 7, 11, 0,
	                          0, 0, 0, 0, 0, 0, 0,
	
	                          0, 0, 0, 0, 0, 0, 0,
	                          0, 4, 4, 8, 6, 6, 0,
	                          0, 2, 2, 9, 3, 1, 0,
	                          0, 2, 2, 10, 3, 1, 0,
	                          0, 5, 5, 11, 7, 7, 0,
	                          0, 0, 0, 0, 0, 0, 0,
	
	                          0, 0, 0, 0, 0, 0, 0,
	                          0, 4, 4, 8, 6, 6, 0,
	                          0, 2, 2, 3, 9, 1, 0,
	                          0, 2, 2, 3, 10, 1, 0,
	                          0, 5, 5, 11, 7, 7, 0,
	                          0, 0, 0, 0, 0, 0, 0,
	
	                          0, 0, 0, 0, 0, 0, 0,
	                          0, 5, 5, 7, 7, 1, 0,
	                          0, 2, 2, 3, 6, 6, 0,
	                          0, 2, 2, 3, 4, 4, 0,
	                          0, 8, 9, 10, 11, 1,
	                          0, 0, 0, 0, 0, 0, 0
	};
	memcpy(huarongdao_map, temp_map, sizeof(temp_map));
}
/*
    绘制选择地图界面
*/
void HuaRongDao::DrawChooseMap()
{
	initgraph(600, 700);
	setbkcolor(RGB(250, 240, 230));
	cleardevice();
	settextcolor(BLACK);
	settextstyle(100, 0, L"黑体");
	outtextxy(150, 200, L"华容道");

	setbkmode(OPAQUE);
	setbkcolor(LIGHTBLUE);
	settextstyle(55, 0, L"黑体");
	outtextxy(50, 425, L"横刀立马");
	outtextxy(325, 425, L"齐头并进");
	outtextxy(50, 525, L"将守角楼");
	outtextxy(325, 525, L"围而不歼");

	setbkcolor(LIGHTGRAY);
	settextstyle(40, 0, L"黑体");
	outtextxy(520, 0, L"退出");
}
/*
    根据点击坐标，选择对应地图或退出
*/
void HuaRongDao::ChooseMap()
{
	DrawChooseMap();
	MOUSEMSG m;
	while (true)
	{
		m = GetMouseMsg();
		if (m.uMsg == WM_LBUTTONDOWN)
		{
			if (m.x >= 50 && m.x <= 275 && m.y >= 425 && m.y <= 480)
			{
				num = 0;
				break;
			}
			if (m.x >= 50 && m.x <= 275 && m.y >= 525 && m.y <= 580)
			{
				num = 2;
				break;
			}
			if (m.x >= 325 && m.x <= 550 && m.y >= 425 && m.y <= 480)
			{
				num = 1;
				break;
			}
			if (m.x >= 325 && m.x <= 550 && m.y >= 525 && m.y <= 580)
			{
				num = 3;
				break;
			}
			if (m.x > 520 && m.x < 600 && m.y < 50 && m.y>0)
			{
				magic_town->PlayGame();
			}
		}
	}
}
/*
    加载华容道所需图片
*/
void HuaRongDao::LoadPicture()
{
	loadimage(&empty, L"空.jpg");
	loadimage(&zu1, L"卒1.jpg");
	loadimage(&zu2, L"卒2.jpg");
	loadimage(&zu3, L"卒3.jpg");
	loadimage(&zu4, L"卒4.jpg");
	//	loadimage(&border, "IMAGE", "BORDER");
	loadimage(&caocao, L"曹操.jpg");
	loadimage(&guanyu, L"关羽.jpg");
	loadimage(&zhangfei, L"张飞.jpg");
	loadimage(&zhaoyun, L"赵云.jpg");
	loadimage(&machao, L"马超.jpg");
	loadimage(&huangzhong, L"黄忠.jpg");
	//	loadimage(&winimg, "IMAGE", "WIN");
}
/*
    显示地图标题并绘制人物
*/
void HuaRongDao::InitMap()
{
	setbkcolor(RGB(250, 240, 230));
	cleardevice();
	settextcolor(BROWN);
	setbkmode(TRANSPARENT);
	switch (num)
	{
	case 0:
		outtextxy(200, 10, L"横刀立马");
		break;
	case 1:
		outtextxy(200, 10, L"齐头并进");
		break;
	case 2:
		outtextxy(200, 10, L"将守角楼");
		break;
	case 3:
		outtextxy(200, 10, L"围而不歼");
		break;
	default:
		break;
	}
	setfillcolor(LIGHTGRAY);
	bar(500, 0, 600, 50);
	settextcolor(RED);
	settextstyle(45, 0, L"黑体");
	outtextxy(510, 0, L"退出");
	DrawGame();
}
/*
    根据所选的地图找出对应人物的坐标并绘制
*/
void HuaRongDao::DrawGame()
{
	position p;
	for (int i = 0; i < 6; i++)
		for (int j = 0; j < 7; j++)
		{
			if (huarongdao_map[num][i][j] == 1)
				putimage(i * 100, j * 100, &empty);

		}
	putimage(200, 600, &empty);
	putimage(300, 600, &empty);
	p = FindPosition(2);
	putimage(p.x * 100, p.y * 100, &caocao);
	p = FindPosition(3);
	putimage(p.x * 100, p.y * 100, &guanyu);
	p = FindPosition(4);
	putimage(p.x * 100, p.y * 100, &zhangfei);
	p = FindPosition(5);
	putimage(p.x * 100, p.y * 100, &zhaoyun);
	p = FindPosition(6);
	putimage(p.x * 100, p.y * 100, &machao);
	p = FindPosition(7);
	putimage(p.x * 100, p.y * 100, &huangzhong);
	p = FindPosition(8);
	putimage(p.x * 100, p.y * 100, &zu1);
	p = FindPosition(9);
	putimage(p.x * 100, p.y * 100, &zu2);
	p = FindPosition(10);
	putimage(p.x * 100, p.y * 100, &zu3);
	p = FindPosition(11);
	putimage(p.x * 100, p.y * 100, &zu4);

	setlinecolor(BLACK);
	rectangle(99, 99, 501, 601);
	rectangle(98, 98, 502, 602);
	rectangle(97, 97, 503, 603);
	rectangle(96, 96, 504, 604);
	rectangle(95, 95, 505, 605);
	rectangle(94, 94, 506, 606);
	rectangle(93, 93, 507, 607);
}
/*
    进行华容道游戏：num为选中地图的序号，以鼠标选中并拖动方向为移动人物方式
*/
void HuaRongDao::PlayGame()
{
	ChooseMap();
	InitMap();
	MOUSEMSG m;
	int down_x = 0, down_y = 0;
	int name = 0;
	while (true)
	{
		while (MouseHit())
		{
			m = GetMouseMsg();
			if (m.uMsg == WM_LBUTTONDOWN)
			{
				down_x = m.x;
				down_y = m.y;
				// 根据鼠标位置选择人物
				if (m.x < 500 && m.x>100 && m.y > 100 && m.x < 600)
				{
					if (huarongdao_map[num][m.x / 100][m.y / 100] != 1)
						name = huarongdao_map[num][m.x / 100][m.y / 100];
				}
				// 退出华容道
				else if (m.x > 500 && m.y < 50)
				{
					PlayGame();
				}
			}
			else if (m.uMsg == WM_LBUTTONUP)
			{
				// 判断鼠标移动方向，并移动棋子
				if (abs(m.x - down_x) >= abs(m.y - down_y) && abs(m.x - down_x) > 50)
				{
					if (m.x - down_x > 0)
						MoveChess(name, 1, 0);
					else
						MoveChess(name, -1, 0);
				}
				else if (abs(m.x - down_x) < abs(m.y - down_y) && abs(m.y - down_y) > 50)
				{
					if (m.y - down_y > 0)
						MoveChess(name, 0, 1);
					else
						MoveChess(name, 0, -1);
				}
				// 移动结束后重新绘制人物
				DrawGame();
			}
		}
	}
}
/*
    移动棋子：name为人物名字，x、y为移动方向，可取值0、-1,1
*/
void HuaRongDao::MoveChess(int name, int x, int y)
{
	// 竖着的将：马超、赵云、张飞、黄忠
	if (name > 3 && name < 8)
	{
		position shu;
		shu = FindPosition(name);
		if (x != 0)
		{
			if (huarongdao_map[num][shu.x + x][shu.y] == 1 && huarongdao_map[num][shu.x + x][shu.y + 1] == 1)
			{
				huarongdao_map[num][shu.x][shu.y] = 1;
				huarongdao_map[num][shu.x][shu.y + 1] = 1;
				huarongdao_map[num][shu.x + x][shu.y] = name;
				huarongdao_map[num][shu.x + x][shu.y + 1] = name;
			}
		}
		if (y == 1)
		{
			if (huarongdao_map[num][shu.x][shu.y + 2] == 1)
			{
				huarongdao_map[num][shu.x][shu.y] = 1;
				huarongdao_map[num][shu.x][shu.y + 2] = name;
			}
		}
		if (y == -1)
		{
			if (huarongdao_map[num][shu.x][shu.y - 1] == 1)
			{
				huarongdao_map[num][shu.x][shu.y + 1] = 1;
				huarongdao_map[num][shu.x][shu.y - 1] = name;
			}
		}
	}

	//横着的将：关羽
	if (name == 3)
	{
		position heng;
		heng = FindPosition(name);
		if (y != 0)
		{
			if (huarongdao_map[num][heng.x][heng.y + y] == 1 && huarongdao_map[num][heng.x + 1][heng.y + y] == 1)
			{
				huarongdao_map[num][heng.x][heng.y] = 1;
				huarongdao_map[num][heng.x + 1][heng.y] = 1;
				huarongdao_map[num][heng.x][heng.y + y] = 3;
				huarongdao_map[num][heng.x + 1][heng.y + y] = 3;
			}
		}
		if (x == 1)
		{
			if (huarongdao_map[num][heng.x + 2][heng.y] == 1)
			{
				huarongdao_map[num][heng.x + 2][heng.y] = 3;
				huarongdao_map[num][heng.x][heng.y] = 1;
			}
		}
		if (x == -1)
		{
			if (huarongdao_map[num][heng.x - 1][heng.y] == 1)
			{
				huarongdao_map[num][heng.x - 1][heng.y] = 3;
				huarongdao_map[num][heng.x + 1][heng.y] = 1;
			}
		}
	}

	//曹操
	if (name == 2)
	{
		position caocao;
		caocao = FindPosition(name);
		if (x == 1)
		{
			if (huarongdao_map[num][caocao.x + 2][caocao.y] == 1 && huarongdao_map[num][caocao.x + 2][caocao.y + 1] == 1)
			{
				huarongdao_map[num][caocao.x + 2][caocao.y] = 2;
				huarongdao_map[num][caocao.x + 2][caocao.y + 1] = 2;
				huarongdao_map[num][caocao.x][caocao.y] = 1;
				huarongdao_map[num][caocao.x][caocao.y + 1] = 1;
			}
		}
		if (x == -1)
		{
			if (huarongdao_map[num][caocao.x - 1][caocao.y] == 1 && huarongdao_map[num][caocao.x - 1][caocao.y + 1] == 1)
			{
				huarongdao_map[num][caocao.x - 1][caocao.y] = 2;
				huarongdao_map[num][caocao.x - 1][caocao.y + 1] = 2;
				huarongdao_map[num][caocao.x + 1][caocao.y] = 1;
				huarongdao_map[num][caocao.x + 1][caocao.y + 1] = 1;
			}
		}
		if (y == 1)
		{
			if (huarongdao_map[num][caocao.x][caocao.y + 2] == 1 && huarongdao_map[num][caocao.x + 1][caocao.y + 2] == 1)
			{
				huarongdao_map[num][caocao.x][caocao.y + 2] = 2;
				huarongdao_map[num][caocao.x + 1][caocao.y + 2] = 2;
				huarongdao_map[num][caocao.x][caocao.y] = 1;
				huarongdao_map[num][caocao.x + 1][caocao.y] = 1;
			}
		}
		if (y == -1)
		{
			if (huarongdao_map[num][caocao.x][caocao.y - 1] == 1 && huarongdao_map[num][caocao.x + 1][caocao.y - 1] == 1)
			{
				huarongdao_map[num][caocao.x][caocao.y - 1] = 2;
				huarongdao_map[num][caocao.x + 1][caocao.y - 1] = 2;
				huarongdao_map[num][caocao.x][caocao.y + 1] = 1;
				huarongdao_map[num][caocao.x + 1][caocao.y + 1] = 1;
			}
		}
		if (caocao.x + x == 2 && caocao.y + y == 4)
			WinGame();
	}

	//卒
	if (name > 7)
	{
		position zu;
		zu = FindPosition(name);
		if (huarongdao_map[num][zu.x + x][zu.y + y] == 1)
		{
			huarongdao_map[num][zu.x][zu.y] = 1;
			huarongdao_map[num][zu.x + x][zu.y + y] = name;
		}
	}
}
/*
    绘制华容道胜利画面
*/
void HuaRongDao::WinGame()
{
	DrawGame();
	settextcolor(LIGHTRED);
	setbkmode(TRANSPARENT);
	settextstyle(200, 0, L"黑体");
	outtextxy(100, 100, L"曹贼");
	outtextxy(100, 300, L"跑了");
	Sleep(5000);
	// 重新开始游戏
	PlayGame();
}
/*
    查找人物位置，以左上角为坐标值
*/
position HuaRongDao::FindPosition(int name)
{
	position p = { 0,0 };
	for (int i = 0; i < 6; i++)
		for (int j = 0; j < 7; j++)
			if (huarongdao_map[num][i][j] == name)
			{
				p.x = i;
				p.y = j;
				return p;
			}
	return p;
}