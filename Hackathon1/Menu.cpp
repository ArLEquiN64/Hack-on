#include "Menu.h"
#include"Key_Input.h"
#include"Dungeon.h"

#define ChipWIDHT 16
#define ChipHEIGHT 16
Menu* Menu::instance;

Menu::Menu()
{
	MenuNum = 0;
	KeyCheck = 0;
	LoadDivGraph("img/WindowMaterial.png", 40, 8, 5, 16, 16, WindowImage);


}

void Menu::Draw()
{
	for (int n = 0; n < 160; n++)
	{
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, 150);
		DrawGraph(n % 10 * ChipWIDHT, n / 10 * ChipHEIGHT, WindowImage[1], TRUE);
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

		if (n == 0)
		{
			DrawGraph(n % 10 * ChipWIDHT, n / 10 * ChipHEIGHT, WindowImage[4], TRUE);
		}
		else if (n == 9)
		{
			DrawGraph(n % 10 * ChipWIDHT, n / 10 * ChipHEIGHT, WindowImage[7], TRUE);
		}
		else if (n == 150)
		{
			DrawGraph(n % 10 * ChipWIDHT, n / 10 * ChipHEIGHT, WindowImage[28], TRUE);
		}
		else if (n == 159)
		{
			DrawGraph(n % 10 * ChipWIDHT, n / 10 * ChipHEIGHT, WindowImage[31], TRUE);
		}
		else if (n % 10 == 0)
		{
			if (n / 10 % 2 == 0){
				DrawGraph(n % 10 * ChipWIDHT, n / 10 * ChipHEIGHT, WindowImage[20], TRUE);
			}
			else
			{
				DrawGraph(n % 10 * ChipWIDHT, n / 10 * ChipHEIGHT, WindowImage[12], TRUE);
			}
		}
		else if (n % 10 == 9)
		{
			if (n / 10 % 2 == 0)
			{
				DrawGraph(n % 10 * ChipWIDHT, n / 10 * ChipHEIGHT, WindowImage[23], TRUE);
			}
			else
			{
				DrawGraph(n % 10 * ChipWIDHT, n / 10 * ChipHEIGHT, WindowImage[15], TRUE);
			}
		}
		else if (n < 10)
		{
			if (n % 2 == 0)
			{
				DrawGraph(n % 10 * ChipWIDHT, n / 10 * ChipHEIGHT, WindowImage[6], TRUE);
			}
			else
			{
				DrawGraph(n % 10 * ChipWIDHT, n / 10 * ChipHEIGHT, WindowImage[5], TRUE);
			}
		}
		else if (n > 150)
		{
			if (n % 2 == 0)
			{
				DrawGraph(n % 10 * ChipWIDHT, n / 10 * ChipHEIGHT, WindowImage[30], TRUE);
			}
			else
			{
				DrawGraph(n % 10 * ChipWIDHT, n / 10 * ChipHEIGHT, WindowImage[29], TRUE);
			}
		}
	}
	DrawGraph(ChipWIDHT * 1, ChipHEIGHT*(MenuNum * 2 + 1), WindowImage[34], TRUE);

	//以下、メニュー項目を描画
	DrawString(ChipWIDHT * 2, ChipHEIGHT * 1, "ステータス", GetColor(255, 255, 255));
	DrawString(ChipWIDHT * 2, ChipHEIGHT * 3, "アイテム", GetColor(255, 255, 255));
	DrawString(ChipWIDHT * 2, ChipHEIGHT * 5, "ヒント", GetColor(255, 255, 255));
	DrawString(ChipWIDHT * 2, ChipHEIGHT * 7, "オプション", GetColor(255, 255, 255));
	DrawString(ChipWIDHT * 2, ChipHEIGHT * 9, "ゲームを終了", GetColor(255, 255, 255));
	DrawString(ChipWIDHT * 2, ChipHEIGHT * 11, "タイトルへ", GetColor(255, 255, 255));
	DrawString(ChipWIDHT * 2, ChipHEIGHT * 13, "戻る", GetColor(255, 255, 255));


}

int Menu::Reaction()
{
	if (Key_Input::buff_time[KEY_INPUT_DOWN] % 40 == 1)
	{
		MenuNum++;
	}
	if (Key_Input::buff_time[KEY_INPUT_UP] % 40 == 1)
	{
		MenuNum--;
	}
	if (MenuNum < 0){
		MenuNum = 6;
	}
	if (MenuNum>6){
		MenuNum = 0;
	}
	if (Key_Input::buff_time[KEY_INPUT_X] == 1)
	{
		Dungeon::menuflag = 0;
	}
	if (Key_Input::buff_time[KEY_INPUT_Z] == 1 && MenuNum == 6)
	{
		Dungeon::menuflag = 0;
	}

	return 0;
}