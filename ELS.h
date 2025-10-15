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
	int move();			//�ƶ�����Ҳ�����
	int update();		//���µ�ͼ
	int curBox();		//�̻�����
	int createBox();	//��������
	int update_map();	//���µ�ͼ�������ƣ�
	int runBox(char c);		//�˶�����
	int spinBox();
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

	vector<PO> po;

	char input = 0;
	
};

