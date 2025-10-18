#include "ELS.h"


ELS::ELS()
{

}


ELS::~ELS()
{

}

int ELS::run()
{
	//创建界面
	initgraph(600, 800);
	//设置背景图案
	rectangle(PX_X, PX_Y, PX_X+PX_W, PX_Y+PX_H);
	BeginBatchDraw();
	int stime = 0;
	int stime2 = 0;

	int wtime = 0;
	int wtime2 = 0;
	createBox();
CREAT://创建方块
	clearLine();
	if (createBox())
		goto END;
	while (1)
	{
		FlushBatchDraw();
		if (wtime2 > 1000/FPS)
		{
			//画面更新
			update();
			update_ui();
			stime2 = GetTickCount();
		}
		wtime2 = GetTickCount() - stime2;
		//玩家操作
		if (move() == 2)
		{
			if (curBox())
				goto CREAT;
			update_map();
		}
		
		if (wtime > 500)
		{
			//固定方块
			if (curBox())
				goto CREAT;
			//更新地图（不绘制）
			update_map();
			stime = GetTickCount();
		}
		wtime = GetTickCount() - stime;


	}
END:
	EndBatchDraw();
	return 0;
}


int ELS::move()
{
	//cin >> input;
	int ret = 0; 
	ExMessage msg;
	while (peekmessage(&msg))
	{
		if (msg.prevdown)
		{

			switch (msg.vkcode)
			{
			case 'W':
				ret = runBox('w');
				break;
			case 'S':
				ret = runBox('s');
				break;
			case 'D':
				ret = runBox('d');
				break;
			case 'A':
				ret = runBox('a');
				break;
			}
		}
	}
	return ret;
}

int ELS::update()
{

	//system("cls");
	//for (int y = 0; y < MAP_H; y++)
	//{
	//	for (int x = 0; x < MAP_W; x++)
	//	{
	//		std::cout << " " << gamemap[y][x];
	//	}
	//	std::cout << std::endl;
	//}
	setlinecolor(WHITE);
	setfillcolor(GREEN);
	fillrectangle(PX_X, PX_Y, PX_X+PX_W, PX_Y+PX_H);

	for (int y = 0; y < MAP_H; y++)
	{
		line(PX_X,        PX_Y + y * D_S,
			 PX_X + PX_W, PX_Y + y * D_S);
	}
	for (int x = 0; x < MAP_W; x++)
	{
		if (x % 2 == 0)
			setlinecolor(BLACK);
		else
			setlinecolor(WHITE);
		line(PX_X + x * D_S , PX_Y,
			 PX_X + x * D_S , PX_Y + PX_H);
	}
	for (int y = 0; y < MAP_H; y++)
	{
		for (int x = 0; x < MAP_W; x++)
		{
			if (gamemap[y][x] == 1)
			{
				setfillcolor(color_[cr_col]);
				fillrectangle(
					PX_X + x * D_S,
					PX_Y + y * D_S,
					PX_X + (x + 1) * D_S,
					PX_Y + (y + 1) * D_S);
			}
			else if (gamemap[y][x] == 2)
			{
				setfillcolor(color_[gamemap_color[y][x]]);
				fillrectangle(
					PX_X + x * D_S,
					PX_Y + y * D_S,
					PX_X + (x + 1) * D_S,
					PX_Y + (y + 1) * D_S);
			}
		}

	}

	return 0;
}

int ELS::update_ui()
{
	//下一个方块预览
	setlinecolor(WHITE);
	rectangle(UI_X,UI_Y,UI_X+D_S* BOX_S,UI_Y+D_S* BOX_S);
	setfillcolor(GREEN);
	fillrectangle(UI_X, UI_Y, UI_X + D_S * BOX_S, UI_Y + D_S * BOX_S);
	 
	//根据 ne_box 和 ne_col 来绘制下一个方块
	for (int y = 0; y < BOX_S; y++)
	{
		for (int x = 0; x < BOX_S; x++)
		{
			if (boxs[ne_box][y][x] == 1)
			{
				setfillcolor(color_[ne_col]);
				fillrectangle(
					UI_X + D_S * x,
					UI_Y + D_S * y,
					UI_X + D_S * (x+1),
					UI_Y + D_S * (y+1));
			}
		}
	}

	//文字和分数
	settextstyle(40,0,"微软雅黑");
	outtextxy(UI_X,UI_Y + 150,"分数");
	char fs[16] = {0};
	sprintf_s(fs,"%d",score);
	outtextxy(UI_X,UI_Y + 200,fs);
	outtextxy(UI_X,UI_Y + 250,"等级");
	char dj[16] = { 0 };
	sprintf_s(dj, "%d", level);
	outtextxy(UI_X, UI_Y + 300, dj);
	return 0;
}

int ELS::curBox()
{
	//搜索下面的方块受否超过索引
	for (auto& z : po)
	{
		if (z.y + 1 == MAP_H || gamemap[z.y + 1][z.x] == 2)
		{
			goto CUR;
		}
	}
	return 0;

CUR:
	for (auto& z : po)
	{
		gamemap[z.y][z.x] = 2;
		gamemap_color[z.y][z.x] = cr_col;
	}
	po.clear();
	return 1;

}

int ELS::createBox()
{
	//test
	cr_box = ne_box;
	cr_reg = ne_reg;//fix
	cr_col = ne_col;//fix

	srand(time(NULL));
	ne_box = rand() % BOX_SIZE;
	ne_reg = 0;//fix
	ne_col = rand() % COLOR_SIZE;//fix

	//设置自己的方块的同时 查看能否创建方块 并且创建一个方块

	for (int y = 0; y < BOX_S; y++)
	{
		for (int x = 0; x < MAP_W; x++)
		{
			if (gamemap[y][x] == 1)
			{
				return -1;
			}
		}
	}

	//创建一个方块
	po.clear();
	for (int y = 0; y < BOX_S; y++)
	{
		for (int x = 0; x < BOX_S; x++)
		{
			//gamemap[y][x+5] = boxs[0][y][x]; 
			if (boxs[cr_box][y][x] == 1)
			{
				po.push_back(ELS::PO(y,x+5));
			}
		}
	}


	return 0;
}

int ELS::update_map()
{
	//对记录的所有1 进行下落
	for (auto& z : po)
	{
		gamemap[z.y][z.x] = 0;
	}
	for (auto& z : po)
	{
		gamemap[z.y+1][z.x] = 1;
		(z.y)++;
	}

	return 0;
}

int ELS::runBox(char c)
{
	if (c == 'a')
	{
		for (auto& z : po)
		{
			if (z.x - 1 == -1 || gamemap[z.y][z.x - 1] == 2)
			{
				return 0;
			}
		}
		for (auto& z : po)
		{
			gamemap[z.y][z.x] = 0;
		}
		for (auto& z : po)
		{
			gamemap[z.y][z.x-1] = 1;
			(z.x)--;
		}

	}
	else if (c == 'd')
	{
		for (auto& z : po)
		{
			if (z.x + 1 == MAP_W || gamemap[z.y][z.x + 1] == 2)
			{
				return 0;
			}
		}
		for (auto& z : po)
		{
			gamemap[z.y][z.x] = 0;
		}
		for (auto& z : po)
		{
			gamemap[z.y][z.x + 1] = 1;
			(z.x)++;
		}
	}
	else if (c == 'w')
	{
		spinBox();
		restart();
		update();
	}
	else if (c == 's')
	{
		return 2;
	}

	return 0;
}

int ELS::restart()
{
	for (int y = 0; y < MAP_H; y++)
	{
		for (int x = 0; x < MAP_W; x++)
		{
			if (gamemap[y][x] == 1)
				gamemap[y][x] = 0;
		}
	}
	for (auto& z : po)
	{
		gamemap[z.y][z.x] = 1;
	}
	return 0;
}

int ELS::spinBox()
{
	//1.提取需要的范围
	int x = MAP_W;
	int y = MAP_H;
	int max_x = 0;  // 改名为 max_x 避免混淆
	int max_y = 0;  // 改名为 max_y 避免混淆

	for (auto& z : po)
	{
		if (z.x < x)
			x = z.x;
		if (z.y < y)
			y = z.y;
		if (z.x > max_x)  // 修正：记录最大值
			max_x = z.x;
		if (z.y > max_y)  // 修正：记录最大值
			max_y = z.y;
	}

	int w = 0;
	int h = 0;
	int box_size = 0;
	w = max_x - x;  // 修正：用最大值减最小值
	h = max_y - y;  // 修正：用最大值减最小值

	box_size = w > h ? w : h;
	if (box_size % 2 != 0)
		box_size++;
	//提取方块
	vector<vector<int>> _map2;
	for (int y2 = 0; y2 <= box_size; y2++)
	{
		vector<int> _map3;
		for (int x2 = 0; x2 <= box_size; x2++)
		{
			if (y + y2 >= MAP_H || y + y2 < 0)
				return 1;
			if (x + x2 >= MAP_W || x + x2 < 0)
				return 1;
			_map3.push_back(gamemap[y + y2][x + x2]);
		}
		_map2.push_back(_map3);
		//std::cout << std::endl;
	}
	re(_map2, box_size/2, box_size/2,box_size,_map2.size(),box_size);
	//验证方块位置是否合法
	for (int y2 = 0; y2 <= box_size; y2++)
	{
		for (int x2 = 0; x2 <= box_size; x2++)
		{
			if (_map2[x2][y2] == 1)
			{
				if (gamemap[y + y2][x + x2] == 2)
				{
					return 1;
				}
			}
		}
	}
	po.clear();
	for (int y2 = 0; y2 <= box_size; y2++)
	{
		for (int x2 = 0; x2 <= box_size; x2++)
		{
			gamemap[y + y2][x + x2] == 0;
			if (_map2[y2][x2] == 1)
			{
				po.push_back(PO((y + y2),(x + x2)));
			}
		}
	}
	return 0;
}

int ELS::clearLine()
{
	for (int y = BOX_SIZE; y < MAP_H; y++)
	{
		int isclear = 1;
		for (int x = 0; x < MAP_W; x++)
		{
			if (gamemap[y][x] == 0)
			{
				isclear = 0;
				break;
			}
		}
		if (isclear)
		{
			//将上面的往下面复制
			for (int i = y; i>1; i--)
			{
				for (int x = 0; x < MAP_W; x++)
				{
					gamemap[i][x] = gamemap[i - 1][x];
					gamemap_color[i][x] = gamemap_color[i - 1][x];
				}
			}
			score++;
		}
	}
	return 0;
}

int ELS::re(vector<vector<int>> &map,int rex, int rey, int reS, int resize, int rereg, int reValue)
{
	if (rex - resize / 2 < 0)
		return 0;
	if (rey - resize / 2 < 0)
		return 0;
	if (rex + resize / 2 > reS)
		return 0;
	if (rey + resize / 2 > reS)
		return 0;
	if (!(resize % 2))
		return 0;
	vector<vector<int>> map2;
	//1.翻转提取数组 默认全部翻转
	for (int i = resize / 2 * -1; i <= resize / 2; i++)
	{
		vector<int> map3;
		for (int z = resize / 2 * -1; z <= resize / 2; z++)
		{
			map3.push_back(map[rey + i][rex + z]);
			cout << " " << map[rey + i][rex + z];
		}
		map2.push_back(map3);
		cout << endl;
	}
	cout << endl;
	vector<vector<int>> map4 = map2;
	for (int i = 0; i < resize; i++)
	{
		for (int z = 0; z < resize; z++)
		{
			if (resize % 2)//5 2 1 2
			{
				//分成上中下两部分
				if (i == resize / 2 + 1)
					map4[z][resize - i - 1] = map2[i][z];
				else
					map4[z][resize - i - 1] = map2[i][z];
			}
			else
				map4[z][resize - i - 1] = map2[i][z];

		}
	}
	for (int i = resize / 2 * -1; i <= resize / 2; i++)
	{
		//vector<int> map3;
		for (int z = resize / 2 * -1; z <= resize / 2; z++)
		{
			map[rey + i][rex + z] = map4[i + resize / 2][z + resize / 2];
		}
	}
	return 0;
}



