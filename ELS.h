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

class ELS
{
public:
	ELS();
	~ELS();
	int run();

private:
	int update();
	int createBox();
	

private:
	int gamemap[MAP_H][MAP_W] = { 0 };
	
	int cr_box = 0;
	int cr_reg = 0;
	int cr_col = 0;

	int ne_box = 0;
	int ne_reg = 0;
	int ne_col = 0;


	int box_size = 1;
	int boxs[1][BOX_S][BOX_S] = {
		{
			0,0,0,0,0,
			0,0,1,0,0,
			0,1,1,1,0,
			0,0,0,0,0,
			0,0,0,0,0
		}
	};

	
};

