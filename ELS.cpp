#include "ELS.h"


ELS::ELS()
{

}


ELS::~ELS()
{

}

int ELS::run()
{
	//��������
	initgraph(600, 800,1);
	//���ñ���ͼ��
	rectangle(PX_X, PX_Y, PX_X+PX_W, PX_Y+PX_H);
	BeginBatchDraw();
	int stime = 0;
	int stime2 = 0;

	int wtime = 0;
	int wtime2 = 0;
CREAT://��������
	if (createBox())
		goto END;
	while (1)
	{
		FlushBatchDraw();
		if (wtime2 > 1000/FPS)
		{
			//�������
			update();
			stime2 = GetTickCount();
		}
		wtime2 = GetTickCount() - stime2;
		//��Ҳ���
		move();
		
		if (wtime > 500)
		{
			//�̶�����
			if (curBox())
				goto CREAT;
			//���µ�ͼ�������ƣ�
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
	ExMessage msg;
	while (peekmessage(&msg))
	{
		if (msg.prevdown)
		{

			switch (msg.vkcode)
			{
			case 'W':
				runBox('w');
				break;
			case 'S':
				runBox('s');
				break;
			case 'D':
				runBox('d');
				break;
			case 'A':
				runBox('a');
				break;
			}
		}
	}
	return 0;
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
		line(PX_X + x * D_S , PX_Y,
			 PX_X + x * D_S , PX_Y + PX_H);
	}
	for (int y = 0; y < MAP_H; y++)
	{
		for (int x = 0; x < MAP_W; x++)
		{
			if (gamemap[y][x] == 1)
			{
				setfillcolor(RED);
				fillrectangle(
					PX_X + x * D_S,
					PX_Y + y * D_S,
					PX_X + (x + 1) * D_S,
					PX_Y + (y + 1) * D_S);
			}
			else if (gamemap[y][x] == 2)
			{
				setfillcolor(YELLOW);
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

int ELS::curBox()
{
	//��������ķ����ܷ񳬹�����
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
	}
	po.clear();
	return 1;

}

int ELS::createBox()
{
	//test
	cr_box = 0;
	cr_reg = 0;//fix
	cr_col = 0;//fix

	//�����Լ��ķ����ͬʱ �鿴�ܷ񴴽����� ���Ҵ���һ������

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

	//����һ������

	for (int y = 0; y < BOX_S; y++)
	{
		for (int x = 0; x < BOX_S; x++)
		{
			//gamemap[y][x+5] = boxs[0][y][x]; 
			if (boxs[0][y][x] == 1)
			{
				po.push_back(ELS::PO(y,x+5));
			}
		}
	}


	return 0;
}

int ELS::update_map()
{
	//�Լ�¼������1 ��������
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
		update_map();
	}
	else if (c == 's')
	{
		update_map();
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
	return 0;
}

int ELS::spinBox()
{
	//1.��ȡ��Ҫ�ķ�Χ
	int x = MAP_W;
	int y = MAP_H;
	int max_x = 0;  // ����Ϊ max_x �������
	int max_y = 0;  // ����Ϊ max_y �������

	for (auto& z : po)
	{
		if (z.x < x)
			x = z.x;
		if (z.y < y)
			y = z.y;
		if (z.x > max_x)  // ��������¼���ֵ
			max_x = z.x;
		if (z.y > max_y)  // ��������¼���ֵ
			max_y = z.y;
	}

	int w = 0;
	int h = 0;
	int box_size = 0;
	w = max_x - x;  // �����������ֵ����Сֵ
	h = max_y - y;  // �����������ֵ����Сֵ

	box_size = w > h ? w : h;

	//��ȡ����
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
			//_map[y2][x2] = this->gamemap[y + y2][x + x2];
			_map3.push_back(gamemap[y + y2][x + x2]);
			//std::cout << " " << _map[y2][x2];
		}
		_map2.push_back(_map3);
		//std::cout << std::endl;
	}
	re(_map2, box_size/2, box_size/2,box_size,_map2.size(),box_size);
	for (auto& z : _map2)
	{
		for (auto& i : z)
		{
			std::cout << " " <<i;
		}
		std::cout << std::endl;
	}
	//��֤����λ���Ƿ�Ϸ�
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
	//ZeroMemory(gamemap,sizeof(gamemap));
	//system("pause");
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
	//1.��ת��ȡ���� Ĭ��ȫ����ת
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
				//�ֳ�������������
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



