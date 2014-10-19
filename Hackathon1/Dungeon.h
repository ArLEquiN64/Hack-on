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
	int DrawSquare(float pos_x_lu, float pos_y_lu, float pos_z_lu, float pos_x_rd, float pos_y_rd, float pos_z_rd); //3d��Ԃɐ��l�p�`�������֐�
	//int kabe_handle;
	int DrawMap_c(unsigned char(*map_data)[10], int x_max, int z_max); //�}�b�v�̕`��B�[�x�o�b�t�@���Ȃ�
	void DrawMiniMap(); //�~�j�}�b�v�̕`��
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
	int state; //��Ԃ�\���ϐ��B1�őO�i���B2�ŉE�]��B3�ŋt�������B4�ō��]��B
	//5�ŉE���s�ړ��B6�ō����s�ړ��B7�ŃG���J�E���g�J�n�B8�Ō�ށB9�ň���߂�
	int revflag = 0; //��]���Ă���t���O�B�v����ɉ�]���̓G���J�E���g���Ȃ�����
	int time; //��Ԃɂ������Ă��鎞�Ԃ�ێ��B
	void Return_right(); //�E�]��
	void GoForward(); //�O�i
	void ReturnBack();
	void ReturnLeft();
	void GoRight();
	void GoLeft();
	void GoBack();
	int down_help = 0; //���{�^�����̃w���p�[
	int flaging = 0; //�֗��t���b�O
	static int floors; //���݂̊K�w
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
	int minimap_flag = 0; //0�Ŕ�\���A1�Œʏ�\���A2�őS�̕\��?
	char dungeon_name[50];
	void nfscanf_(const int line, const char* file, FILE* scan_target, const char* format_text, ...);
	Option* option;
	SaveData* savedata;
	
	void DrawEvent(); //�т�����}�[�N��`��
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
	void DrawExcra(int posx, int posy, int posz); //�т�����}�[�N��`��
	static bool menuflag;
	Menu* menu;
	Player* player;
};