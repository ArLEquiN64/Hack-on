#pragma once
#include<stdio.h>
class SaveData
{
public:
	static SaveData* instance;
	// 唯一のアクセス経路
	static SaveData* GetInstance()
	{
		if (instance == NULL)instance = new SaveData();
		return instance;
	}

	int map_open_flag[10][10][10]; //n個目のマップの(l,m)は行ったかどうか
	FILE *fp;
	int x_max[10];
	int z_max[10];
	int nummap;

private:
	// 生成やコピーを禁止する
	SaveData();
	SaveData(const SaveData& rhs);
	SaveData& operator=(const SaveData& rhs);
	~SaveData();
};

