#pragma once
#include "SceneBase.h"
#include"DxLib.h"
#include"Option.h"
#include"SaveData.h"
#include"Menu.h"
#include"Player.h"

class Dungeon :
	public SceneBase
{
public:
	Dungeon();
	~Dungeon();
	void Draw();
	int Reaction();
	int DrawSquare(float pos_x_lu, float pos_y_lu, float pos_z_lu, float pos_x_rd, float pos_y_rd, float pos_z_rd); //3d空間に正四角形を書く関数
	//int kabe_handle;
	int DrawMap_c(unsigned char(*map_data)[10], int x_max, int z_max); //マップの描画。深度バッファしない
	void DrawMiniMap(); //ミニマップの描画
	FILE *fp;
	int kabe_handle;
	int pos_x;
	int pos_z;
	const int block_size = 100;
	int muki = 0; //0=U,1=R,2=D,3=L
	unsigned char map_data[10][10];
	int x_max = 0, z_max = 0;
	VECTOR target_camera;
	VECTOR player_camera;
	int y = 1;
	int state; //状態を表す変数。1で前進中。2で右転回。3で逆を向く。4で左転回。
	//5で右平行移動。6で左平行移動。7でエンカウント開始。8で後退。9で一歩戻る
	int revflag = 0; //回転しているフラグ。要するに回転時はエンカウントしないため
	int time; //状態にかかっている時間を保持。
	void Return_right(); //右転回
	void GoForward(); //前進
	void ReturnBack();
	void ReturnLeft();
	void GoRight();
	void GoLeft();
	void GoBack();
	int down_help = 0; //下ボタン時のヘルパー
	int flaging = 0; //便利フラッグ
	static int floors; //現在の階層
	int start_z = 0;
	int start_x = 0;
	void LoadDungeon(int floor);
	int black;
	int yellow;
	int white;
	int blue;
	int nowchoose = 0;
	int feel_flag;
	char kabe_name[100];
	unsigned char fog_r = 0;
	unsigned char fog_g = 0;
	unsigned char fog_b = 0;
	float fog_start = 0;
	float fog_goal = 0;
	int yajirushi_h;
	int minimap_flag = 0; //0で非表示、1で通常表示、2で全体表示?
	char dungeon_name[50];
	void nfscanf_(const int line, const char* file, FILE* scan_target, const char* format_text, ...);
	Option* option;
	SaveData* savedata;
	
	void DrawEvent(); //びっくりマークを描画
	typedef struct pos_
	{
		char x;
		char y;
	}pos;
	typedef struct event_
	{
		pos posxy;
		char evnumber;
	}ev;
	int event_h;
	ev events[10];
	void DrawExcra(int posx, int posy, int posz); //びっくりマークを描画
	static bool menuflag;
	Menu* menu;
	Player* player;
};