#ifndef _MAGICTOWN_H_
#define _MAGICTOWN_H_

#include <graphics.h>
#include <stdio.h>
#include <conio.h>

#include "HuaRongDao.h"
#include "WhiteblackChess.h"

class HuaRongDao;
class WhiteblackChess;

class MagicTown
{
private:
	IMAGE wall, wall2, floor, shang, xia, zuo, you, door1, door2, key1, key2, up, down;
	IMAGE huarongdao, blackwhitechess;
	int yellowkey_num, bluekey_num, floor_num; // 钥匙1数量，钥匙2数量，层数-1
	int place_x, place_y; // 现在位置
	int map[3][10][10]; // 魔塔地图

private:
	void LoadPicture(); // 加载魔塔图片
	void DrawGame(int floor); // 根据层数初始化地图
	void ShowThings(); // 显示钥匙与楼层
	void InitGame(); // 初始化魔塔地图

public:
	MagicTown();
	~MagicTown();
	void PlayGame(); // 开始魔塔游戏

public:
	// 调用HuaRongDao类和WhiteblackChess类的方法
	HuaRongDao* hua_rong_dao;
	WhiteblackChess* whiteblack_chess;

};

#endif // !_MAGICTOWN_H_