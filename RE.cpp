#include <iostream>
#include <vector>
#include <easyx.h>
#define s 5
using namespace std;

int map[s][s] = { 0 };

bool re(int rex, int rey, int reS, int resize, int rereg = 1, int reValue = -1)
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
			cout << map[rey + i][rex + z] << " ";
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
		vector<int> map3;
		for (int z = resize / 2 * -1; z <= resize / 2; z++)
		{
			map[rey + i][rex + z] = map4[i + resize / 2][z + resize / 2];
		}
	}
	return 1;
}