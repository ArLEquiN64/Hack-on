#pragma once
#include"DxLib.h"

class Option
{
public:
	static Option* instance;
	//// 唯一のアクセス経路
	static Option* GetInstance()
	{
		if (instance == NULL)instance = new Option();
		return instance;
	}

	int move_speed;
	int revolve_speed; //右or左を押した時の速さ
	void Draw();
	int Reaction();
	bool optionflag; //オプション画面描画フラグ
	int choosenow;
	int black;
	int white;
	int yellow;
	int blue;
	FILE *fp;
	char option_list[10][80];
	char option_explanation[10][120];
	int option_max;
	int bgm_bolume;
	int se_bolume;
	int battle_effect_flag;
	int keyconfigflag;
	int choosenow_keyconfig;
	int keyconfingflag;
	void DrawKey(int pos_x, int pos_y, int key); //与えられた数字に対してDXライブラリで割り当てられたキーの名前を描画
	unsigned char key_deside[15];
	unsigned char key_deside_temp[15];
	int pad_deside[15];
	int pad_deside_temp[15];
	FILE *key_name_fp;
	char key_name_list[10][15];
	int key_name_max;
	FILE *key_fp;
	int key_max;
	int GetKeyKwsk(); //押されたキーを1つだけ取得
private:
	// 生成やコピーを禁止する
	Option();
	Option(const Option& rhs);
	Option& operator=(const Option& rhs);
	~Option(){};
};