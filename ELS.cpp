#include "ELS.h"


ELS::ELS()
{

}


ELS::~ELS()
{

}

int ELS::run()
{

	while (1)
	{
		update();
		system("pause");

	}
	return 0;
}

int ELS::update()
{
	system("cls");
	for (int y = 0; y < MAP_H; y++)
	{
		for (int x = 0; x < MAP_W; x++)
		{
			std::cout << " " << gamemap[y][x];
		}
		std::cout << std::endl;
	}
	return 0;
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


	return 0;
}


