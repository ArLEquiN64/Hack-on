#pragma once
class Key_Input //キーボードからの入力を受け取るクラス
{
public:
	Key_Input();
	~Key_Input();

	static char buff[256];
	static int buff_time[256]; //それぞれのキーの押し下時間
	int i;
	void KeyUpdate();
	int talkingflag; //話し中フラグ
	int JoyPadInput;
	int AnalogInputx;
	int AnalogInputy;
};