#include "SaveData.h"
#include<stdio.h>
#include"DxLib.h"

SaveData* SaveData::instance;

SaveData::SaveData()
{
	for (int i = 0; i < 10; i++)
	{
		for (int i2 = 0; i2 < 10; i2++)
		{
			for (int i3 = 0; i3 < 10; i3++)
			{
				map_open_flag[i][i2][i3] = 0;
			}
		}
	}
}


SaveData::~SaveData()
{
}