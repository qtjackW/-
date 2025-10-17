#pragma once
//#include "RE.cpp"
#include <Windows.h>
#include <iostream>
#include <vector>
#include <easyx.h>

using namespace std;
#define MAP_W 15
#define MAP_H 30
#define BOX_S 5
#define BOX_SIZE 7
#define COLOR_SIZE 5
#define FPS 12

#define PX_X 20
#define PX_Y 20
#define D_S 25
#define PX_W D_S*MAP_W
#define PX_H D_S*MAP_H
#define PX_VALUE 2


class ELS
{
public:
	ELS();
	~ELS();
	int run();

private:
	int move();			//移动（玩家操作）
	int update();		//更新地图
	int curBox();		//固化方块
	int createBox();	//创建方块
	int update_map();	//更新地图（不绘制）
	int runBox(char c);		//运动方块
	int restart();
	int spinBox();
	int clearLine();	//
	int re(vector<vector<int>> &map,int rex, int rey, int reS, int resize, int rereg = 1, int reValue = -1);
	
	
	class PO
	{
	public:
		PO(int a, int b)
		{
			y = a; x = b;
		}
		int y;
		int x;
	};
private:
	int gamemap[MAP_H][MAP_W] = { 0 };
	int gamemap_color[MAP_H][MAP_W] = { 0 };
	int color_[COLOR_SIZE] = { RED,BLUE,BLACK,LIGHTCYAN,DARKGRAY };
	
	int cr_box = 0;
	int cr_reg = 0;
	int cr_col = 0;

	int ne_box = 0;
	int ne_reg = 0;
	int ne_col = 0;


	int box_size = 1;
	int boxs[BOX_SIZE][BOX_S][BOX_S] = {
		{
			0,0,0,0,0,
			0,0,1,0,0,
			0,1,1,1,0,
			0,0,0,0,0,
			0,0,0,0,0
		},
		{
			0,0,0,0,0,
			0,0,0,1,0,
			0,1,1,1,0,
			0,0,0,0,0,
			0,0,0,0,0
		},
		{
			0,0,0,0,0,
			0,1,0,0,0,
			0,1,1,1,0,
			0,0,0,0,0,
			0,0,0,0,0
		},
		{
			0,0,0,0,0,
			0,0,0,0,0,
			1,1,1,1,0,
			0,0,0,0,0,
			0,0,0,0,0
		},
		{
			0,0,0,0,0,
			0,0,1,1,0,
			0,0,1,1,0,
			0,0,0,0,0,
			0,0,0,0,0
		},
		{
			0,0,0,0,0,
			0,1,1,0,0,
			0,0,1,1,0,
			0,0,0,0,0,
			0,0,0,0,0
		},
		{
			0,0,0,0,0,
			0,0,1,1,0,
			0,1,1,0,0,
			0,0,0,0,0,
			0,0,0,0,0
		}


	};

	vector<PO> po;

	char input = 0;
	
};

