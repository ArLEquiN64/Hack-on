#pragma once
#include"DxLib.h"

class Menu
{

public:
	static Menu* instance;
	//// �B��̃A�N�Z�X�o�H
	static Menu* GetInstance()
	{
		if (instance == NULL)instance = new Menu();
		return instance;
	}

	void Draw();
	int Reaction();
	int WindowImage[40];
	int MenuNum = 0;
	int KeyCheck = 0;


private:
	Menu();
	Menu(const Menu& rhs);
	Menu& operator=(const Menu& rhs);
	~Menu(){};
};

