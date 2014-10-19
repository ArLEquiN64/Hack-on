#include "Title.h"
#include"DxLib.h"

Title::Title()
{

	TitleGraph = LoadGraph("img/BG14a_80.jpg");
	LoadDivGraph("img/numicon.png", 4, 4, 1, 16, 16, numicon);
	LoadDivGraph("img/WindowFrame.png", 16, 4, 4, 16, 16, WindowFrame);
	LineNum = 0;
	SetTransColor(255, 255, 255);
	title_h = LoadGraph("img/title.png");
	SetTransColor(0, 0, 0);
}


Title::~Title()
{
}


void Title::Draw()
{
	DrawGraph(0, 0, TitleGraph, TRUE);

	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 150);
	DrawBox(252, 292, 358, 388, GetColor(200, 150, 50), TRUE);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
	for (int n = 0; n < 42; n++)
	{
		if (n == 0)
		{
			DrawGraph(252, 292, WindowFrame[0], TRUE);
		}
		else if (n == 6)
		{
			DrawGraph(348, 292, WindowFrame[3], TRUE);
		}
		else if (n == 35)
		{
			DrawGraph(252, 372, WindowFrame[12], TRUE);
		}
		else if (n == 41)
		{
			DrawGraph(348, 372, WindowFrame[15], TRUE);
		}
		else if (n % 7 == 0)
		{
			if (n / 7 % 2 == 0)
			{
				DrawGraph(252 + n % 7 * 16, 292 + n / 7 * 16, WindowFrame[8], TRUE);
			}
			else
			{
				DrawGraph(252 + n % 7 * 16, 292 + n / 7 * 16, WindowFrame[4], TRUE);
			}
		}
		else if (n % 7 == 6)
		{
			if (n / 7 % 2 == 0)
			{
				DrawGraph(252 + n % 7 * 16, 292 + n / 7 * 16, WindowFrame[11], TRUE);
			}
			else
			{
				DrawGraph(252 + n % 7 * 16, 292 + n / 7 * 16, WindowFrame[7], TRUE);
			}
		}
		else if (n < 7)
		{
			if (n % 2 == 0)
			{
				DrawGraph(252 + n % 7 * 16, 292 + n / 7 * 16, WindowFrame[2], TRUE);
			}
			else
			{
				DrawGraph(252 + n % 7 * 16, 292 + n / 7 * 16, WindowFrame[1], TRUE);
			}
		}
		else if (n > 35)
		{
			if (n % 2 == 0)
			{
				DrawGraph(252 + n % 7 * 16, 292 + n / 7 * 16, WindowFrame[14], TRUE);
			}
			else
			{
				DrawGraph(252 + n % 7 * 16, 292 + n / 7 * 16, WindowFrame[13], TRUE);
			}
		}
		/*DrawGraph(252 + n % 6 * 16, 292 + n / 6 * 16, WindowFrame[1], TRUE);*/
	}
	SetFontSize(18);
	DrawString(290, 305, "START", GetColor(255, 255, 255));
	DrawString(285, 333, "OPTION", GetColor(255, 255, 255));
	DrawString(298, 358, "END", GetColor(255, 255, 255));
	DrawGraph(265, LineNum * 26 + 305, numicon[2], TRUE);
	
	DrawRotaGraph(320,160,0.6,0.0, title_h, 1);
}

int Title::Reaction()
{
	if (Key_Input::buff_time[KEY_INPUT_DOWN] % 40 == 1)
	{
		LineNum++;
	}
	if (Key_Input::buff_time[KEY_INPUT_UP] % 40 == 1)
	{
		LineNum--;
	}
	if (LineNum < 0){
		LineNum = 2;
	}
	if (LineNum>2){
		LineNum = 0;
	}
	if (Key_Input::buff[KEY_INPUT_Z] || Key_Input::buff_time[KEY_INPUT_RETURN])
	{
		if (LineNum == 0)
		{
			return 2;
		}
		if (LineNum == 2)
		{
			return -1;
		}
	}
	return 0;
}