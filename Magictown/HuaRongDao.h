#ifndef _HUARONGDAO_H_
#define _HUARONGDAO_H_

#include <graphics.h>
#include <stdio.h>

#include "MagicTown.h"

class MagicTown;

typedef struct
{
	int x;
	int y;
}position;

class HuaRongDao
{
private:
	int huarongdao_map[4][6][7];  //华容道地图
	int num = 0;
	IMAGE empty, caocao, guanyu, zhangfei, zhaoyun, machao, huangzhong, zu1, zu2, zu3, zu4;

private:
	void MoveChess(int name, int x, int y); // 移动棋子
	void ChooseMap();  // 选择地图，或退出
	void InitMap();  // 初始化对应地图的界面
	void DrawChooseMap();  // 显示地图标题并绘制人物
	void LoadPicture();  // 加载华容道所需图片
	void DrawGame();  // 根据地图找出对应人物的坐标并绘制
	void WinGame();  // 绘制华容道胜利画面
	position FindPosition(int name); // 查找人物位置，以左上角为坐标值

public:
	HuaRongDao();
	void PlayGame(); // 进行华容道游戏

public:
	// 调用MagicTown类方法
	MagicTown* magic_town;
};

#endif // !HUARONGDAO_H_