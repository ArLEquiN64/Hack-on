#include "Key_Input.h"
#include<DxLib.h>

char Key_Input::buff[256];
int Key_Input::buff_time[256];

Key_Input::Key_Input()
{
}


Key_Input::~Key_Input()
{
}


void Key_Input::KeyUpdate()
{
	GetHitKeyStateAll(buff);

	//パッド入力をキー入力に変換する
	if (GetJoypadNum())
	{
		if (1) //Xboxコントローラーでない
		{
			JoyPadInput = GetJoypadInputState(DX_INPUT_PAD1);
			GetJoypadAnalogInput(&AnalogInputx, &AnalogInputy, DX_INPUT_PAD1);
			if ((JoyPadInput&PAD_INPUT_UP) || AnalogInputy > 100)
			{
				buff[KEY_INPUT_UP] = 1;
			}
			if ((JoyPadInput&PAD_INPUT_RIGHT) || AnalogInputx < -100)
			{
				buff[KEY_INPUT_RIGHT] = 1;
			}
			if ((JoyPadInput&PAD_INPUT_DOWN) || AnalogInputy < -100)
			{
				buff[KEY_INPUT_DOWN] = 1;
			}
			if ((JoyPadInput&PAD_INPUT_LEFT) || AnalogInputx > 100)
			{
				buff[KEY_INPUT_LEFT] = 1;
			}
			if (JoyPadInput&PAD_INPUT_3)
			{
				buff[KEY_INPUT_Z] = 1;
			}
			if (JoyPadInput&PAD_INPUT_1)
			{
				buff[KEY_INPUT_X] = 1;
			}
			if (JoyPadInput&PAD_INPUT_5)
			{
				buff[KEY_INPUT_A] = 1;
			}
			if (JoyPadInput&PAD_INPUT_6)
			{
				buff[KEY_INPUT_D] = 1;
			}

		}
		else
		{
			//GetJoypadXInputState();
		}
	}
	i = 0;


	//使ってないキーの消去
	/*if (options->keyconfingflag) //キーコンフィグ中ではない
	{
	}
	else
	{
		while (i < 256)
		{
			if (buff[i])
			{
				for (int n = 0; n < options->key_max; n++)
				{
					if (i == options->key_deside[n])
					{
						break;
					}
					if (n == options->key_max - 1)
					{
						buff[i] = 0;
					}
				}
			}
			i++;
		}

		i = 0;

		//キーコンフィグによるキーの変換
		if (buff[options->key_deside[0]]) //↑キー
		{
			buff[options->key_deside[0]] = 0;
			buff[KEY_INPUT_UP] = 1;
		}
		else if (buff[options->key_deside[1]]) //→キー
		{
			buff[options->key_deside[1]] = 0;
			buff[KEY_INPUT_RIGHT] = 1;
		}
		else if (buff[options->key_deside[2]]) //↓キー
		{
			buff[options->key_deside[2]] = 0;
			buff[KEY_INPUT_DOWN] = 1;
		}
		else if (buff[options->key_deside[3]]) //←キー
		{
			buff[options->key_deside[3]] = 0;
			buff[KEY_INPUT_LEFT] = 1;
		}
		else if (buff[options->key_deside[4]]) //Aキー
		{
			buff[options->key_deside[4]] = 0;
			buff[KEY_INPUT_A] = 1;
		}
		else if (buff[options->key_deside[5]]) //Dキー
		{
			buff[options->key_deside[5]] = 0;
			buff[KEY_INPUT_D] = 1;
		}
		else if (buff[options->key_deside[6]]) //Zキー
		{
			buff[options->key_deside[6]] = 0;
			buff[KEY_INPUT_Z] = 1;
		}
		else if (buff[options->key_deside[7]]) //Xキー
		{
			buff[options->key_deside[7]] = 0;
			buff[KEY_INPUT_X] = 1;
		}
	}
	*/

	while (i < 256) //押し下時間を調べる
	{
		if (buff[i])
		{
			buff_time[i]++;
		}
		else
		{
			buff_time[i] = 0;
		}
		i++;
	}


	/*if (Flags::talkflag) //会話中は決定キーのみ
	{
	if (buff[KEY_INPUT_Z])
	{
	talkingflag++;
	}
	for (int i = 0; i < 256; i++)
	{
	buff[i] = 0;
	}
	if (talkingflag)
	{
	buff[KEY_INPUT_Z] = 1;
	talkingflag = 0;
	}
	}*/
}