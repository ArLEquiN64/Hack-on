#include "Dungeon.h"
#include"Key_Input.h"
#include "Prologue.h"
#include<math.h>
#pragma warning(disable:4996)

#define PI    3.1415926535897932384626433832795f

int Dungeon::floors = 0;
bool Dungeon::menuflag = 0;

Dungeon::Dungeon()
{
	black = GetColor(0, 0, 0);
	yellow = GetColor(255, 255, 0);
	white = GetColor(255, 255, 255);
	blue = GetColor(0, 0, 255);

	SetTransColor(255, 255, 255); //���𓧉ߐF��
	yajirushi_h = LoadGraph("./dungeon/yajirushi.png");
	SetTransColor(0, 0, 0); //�ꉞ�߂�
	event_h = LoadGraph("./img/2bikkuri.bmp");

	if (yajirushi_h == -1)
	{
		DrawString(0, 0, "Error!", GetColor(255, 0, 0));
		WaitKey();
	}
	SetUseZBuffer3D(TRUE); //�[�x�X�e���V���o�b�t�@
	SetWriteZBuffer3D(TRUE); //�B���̂Ƃ���K�v�Ȃ��c�Ǝv������A����ʍs�̕ǂ��r�Ԃ邱�Ƃւ̑Ώ����ł���B��u�Â��Ȃ�͎̂d���Ȃ�?

	option = Option::GetInstance();
	savedata = SaveData::GetInstance();
	menu = Menu::GetInstance();
	player = new Player(Prologue::RIAJU);
	LoadDungeon(3);
}


Dungeon::~Dungeon()
{
}


void Dungeon::Draw()
{
		//�J�����̈ړ�
		//target_camera = VGet(pos_x * 100 + (muki % 2 ? (muki - 1 ? 0 : 100) : 50), y * 100 - 50, (pos_z * 100 + (muki % 2 ? 50 : (muki ? 0 : 100))));
		//player_camera = VGet(pos_x * 100 + (muki % 2 ? (muki - 1 ? 100 : 0) : 50), y * 100 - 50, (pos_z * 100 + (muki % 2 ? 50 : (muki ? 100 : 0))));
		SetCameraPositionAndTarget_UpVecY(player_camera, target_camera);

		//���C���`��
		DrawMap_c(map_data, x_max, z_max);
		DrawEvent();
		if (!menuflag)
		{
			//�~�j�}�b�v
			DrawMiniMap();
		}
		else
		{
			menu->Draw();
		}
		player->drawState();
}


int Dungeon::Reaction()
{
	if (!menuflag)
	{
		//�}�b�v�̓��j
		if (!(savedata->map_open_flag[floors - 1][pos_z][pos_x]))
		{
			savedata->map_open_flag[floors - 1][pos_z][pos_x] = 1;
		}

		if (!state)
		{

			if (Key_Input::buff_time[KEY_INPUT_LEFT]) //state�ŊǗ����Ă��邽��%X==1���K�v�Ȃ�
			{
				player->addWalkCount(1);
				state = 4;
			}
			else if (Key_Input::buff_time[KEY_INPUT_RIGHT])
			{
				player->addWalkCount(1);
				state = 2;
			}
			else if (Key_Input::buff_time[KEY_INPUT_DOWN])
			{
				player->addWalkCount(1);
				state = 3;
			}
			else if (Key_Input::buff_time[KEY_INPUT_A])
			{
				for (int i = 0; !i; i++) //�ׂ��ǂȂ�ړ����Ȃ�
				{
					if (muki == 0 && (map_data[pos_z][pos_x] & 8))
					{
						break;
					}
					if (muki == 1 && (map_data[pos_z][pos_x] & 1))
					{
						break;
					}
					if (muki == 2 && (map_data[pos_z][pos_x] & 2))
					{
						break;
					}
					if (muki == 3 && (map_data[pos_z][pos_x] & 4))
					{
						break;
					}
					state = 6;
				}
			}
			else if (Key_Input::buff_time[KEY_INPUT_D])
			{
				for (int i = 0; !i; i++) //�ׂ��ǂȂ�ړ����Ȃ�
				{
					if (muki == 0 && (map_data[pos_z][pos_x] & 2))
					{
						break;
					}
					if (muki == 1 && (map_data[pos_z][pos_x] & 4))
					{
						break;
					}
					if (muki == 2 && (map_data[pos_z][pos_x] & 8))
					{
						break;
					}
					if (muki == 3 && (map_data[pos_z][pos_x] & 1))
					{
						break;
					}
					state = 5;
				}
			}
			else if (Key_Input::buff_time[KEY_INPUT_UP])
			{
				player->addWalkCount(1);
				for (int i = 0; !i; i++)
				{
					if (muki == 0 && (map_data[pos_z][pos_x] & 1))
					{
						break;
					}
					if (muki == 1 && (map_data[pos_z][pos_x] & 2))
					{
						break;
					}
					if (muki == 2 && (map_data[pos_z][pos_x] & 4))
					{
						break;
					}
					if (muki == 3 && (map_data[pos_z][pos_x] & 8))
					{
						break;
					}
					state = 1;
				}
			}
			else if (Key_Input::buff_time[KEY_INPUT_X] == 1)
			{
				menuflag = 1;
				//minimap_flag = !minimap_flag; //����͕\��/��\���̂�
			}
		}

		if (state)
		{
			switch (state)
			{
			case 1: //�O�i
				GoForward();
				break;

				//�E�]��
			case 2:
				if (time < 50)
				{
					time += option->revolve_speed;
					Return_right();
				}
				else
				{
					time = 0;
					state = 0;
					revflag++;
				}
				break;

			case 3: //�������B2�{����2��E�]��
				ReturnBack();
				break;

				//���]��
			case 4:
				ReturnLeft();
				break;

				//D�{�^����������
			case 5:
				GoRight();
				break;

				//A�{�^����������
			case 6:
				GoLeft();
				break;

				//���
			case 8:
				GoBack();
				break;

			default:
				break;

			}
			//�����I������ꍇ�̃`�F�b�N
			if (!state)
			{
				if (!revflag)
				{
					state = 0;
				}
				else
				{
					revflag = 0;
				}
			}
		}
	}
	else
	{
		menu->Reaction();
	}
	return 0;
}


#define nfscanf(scan_target, format_text, ...) nfscanf_(__LINE__,__FILE__,scan_target, format_text,__VA_ARGS__);
void Dungeon::nfscanf_(const int line, const char* file, FILE* scan_target, const char* format_text, ...)
{
	FILE* scanf_fp;
	int ret = 0;
	va_list args;

	scanf_fp = fopen("scanf_log.txt", "w");
	fprintf(scanf_fp, "%s\n�s:%d\n", file, line);
	fclose(scanf_fp);

	va_start(args, format_text);
	ret = vfscanf(scan_target, format_text, args);
	va_end(args);

}


int Dungeon::DrawSquare(float pos_x_lu, float pos_y_lu, float pos_z_lu, float pos_x_rd, float pos_y_rd, float pos_z_rd)
//����̍��W�ƉE���̍��W�����
{

	VERTEX3D Vertex[4];
	WORD Index[6];
	for (int i = 0; i < 4; i++)
	{
		Vertex[i].norm = VGet(0.0f, 0.0f, -1.0f);
		Vertex[i].dif = GetColorU8(255, 255, 255, 255);
		Vertex[i].spc = GetColorU8(0, 0, 0, 0);
		Vertex[i].su = 0.0f;
		Vertex[i].sv = 0.0f;
	}
	double t_z1 = pos_z_lu;
	double t_z2 = pos_z_rd;
	if (pos_y_lu == pos_y_rd) //�c�Ɖ��̏��������B�v�l��
	{
		double keep_z = t_z1;
		t_z1 = t_z2;
		t_z2 = keep_z;
	}

	// �Q�|���S�����̒��_�̃f�[�^���Z�b�g
	Vertex[0].pos = VGet(pos_x_lu, pos_y_lu, pos_z_lu); //����̓_
	Vertex[0].u = 0.0f;
	Vertex[0].v = 0.0f;

	Vertex[1].pos = VGet(pos_x_lu, pos_y_rd, t_z1); //�����̓_
	Vertex[1].u = 0.0f;
	Vertex[1].v = 1.0f;

	Vertex[2].pos = VGet(pos_x_rd, pos_y_lu, t_z2); //�E��̓_
	Vertex[2].u = 1.0f;
	Vertex[2].v = 0.0f;

	Vertex[3].pos = VGet(pos_x_rd, pos_y_rd, pos_z_rd); //�E���̓_
	Vertex[3].u = 1.0f;
	Vertex[3].v = 1.0f;

	Index[0] = 0;
	Index[1] = 1;
	Index[2] = 2;
	Index[3] = 3;
	Index[4] = 2;
	Index[5] = 1;

	return DrawPolygonIndexed3D(Vertex, 4, Index, 2, kabe_handle, FALSE);
}


int Dungeon::DrawMap_c(unsigned char(*map_data)[10], int x_max, int z_max)
{

	for (int z = 0; z < z_max; z++)
	{
		for (int x = 0; x < x_max; x++)
		{
			DrawSquare(x * 100, 0, (z + 1) * 100, (x + 1) * 100, 0, z * 100); //��
			DrawSquare(x * 100, 100, (z + 1) * 100, (x + 1) * 100, 100, z * 100); //�V��
		}
	}

	for (int z = 0; z < z_max; z++)
	{
		for (int x = 0; x < x_max; x++)
		{
			if ((map_data[z][x] & 1))
			{
				if (z >= z_max - 1) //�z��̊O�ɃA�N�Z�X���Ȃ��悤��
				{
					goto sugusoko1;
				}
				else if (pos_z > z && !(map_data[z + 1][x] & 4)) //����ʍs���l��
				{
				}
				else
				{
				sugusoko1:;
					DrawSquare(x * 100, 100, (z + 1) * 100, (x + 1) * 100, 0, (z + 1) * 100);
				}
			}
			if ((map_data[z][x] & 2))
			{
				if (x >= x_max - 1) //�z��̊O�ɃA�N�Z�X���Ȃ��悤��
				{
					goto sugusoko2;
				}
				else if (pos_x > x &&!(map_data[z][x + 1] & 8)) //����ʍs���l��
				{
				}
				else
				{
				sugusoko2:;
					DrawSquare((x + 1) * 100, 100, z * 100, (x + 1) * 100, 0, (z + 1) * 100);
				}
			}
			if ((map_data[z][x] & 4))
			{
				if (!z) //�z��̊O�ɃA�N�Z�X���Ȃ��悤��
				{
					goto sugusoko4;
				}
				else if (pos_z < z && !(map_data[z - 1][x] & 1)) //����ʍs���l��
				{
				}
				else
				{
				sugusoko4:;
					DrawSquare(x * 100, 100, z * 100, (x + 1) * 100, 0, z * 100);
				}
			}
			if ((map_data[z][x] & 8))
			{
				if (!x) //�z��̊O�ɃA�N�Z�X���Ȃ��悤��
				{
					goto sugusoko8;
				}
				else if (pos_x < x && !(map_data[z][x - 1] & 2)) //����ʍs���l��
				{
				}
				else
				{
				sugusoko8:;
					DrawSquare(x * 100, 100, (z + 1) * 100, x * 100, 0, z * 100);
				}
			}
		}
	}

	DrawFormatString(0, 0, GetColor(255, 0, 0), "x:%d,z:%d,%d", pos_x, pos_z, muki);
	if (1) //�f�o�b�O�p�R�[�h
	{
		for (int z = z_max - 1; z >= 0; --z)
		{
			for (int x = x_max - 1; x >= 0; --x)
			{
				DrawFormatString(20 * (x), 20 + 20 * (z_max + 1 - z), GetColor(255, 0, 0), "%d", savedata->map_open_flag[floors - 1][z][x]);
			}
		}
	}

	DrawFormatString(0, 100, GetColor(0, 0, 255), "t_x:%d,t_z:%d,p_x:%d,p_z:%d", (int)target_camera.x, (int)target_camera.z, (int)player_camera.x, (int)player_camera.z);

	return 0;
}


void Dungeon::Return_right()
{
	switch (muki)
	{
	case 0:
		target_camera.x += option->revolve_speed;
		//target_camera.z = (int)sqrt((double)(2500 - ((int)target_camera.x % 100 - 50)*((int)target_camera.x % 100 - 50))) + 50 + pos_z * 100;
		player_camera.x -= option->revolve_speed;
		//player_camera.z = 100 - (int)target_camera.z % 100 + pos_z * 100;
		target_camera.z -= option->revolve_speed;
		player_camera.z += option->revolve_speed;
		if (time >= 50)
		{
			target_camera.x -= time - 50;
			player_camera.x += time - 50;
			target_camera.z += time - 50;
			player_camera.z -= time - 50;
			muki++;
		}
		break;
	case 1:
		target_camera.x -= option->revolve_speed;
		player_camera.x += option->revolve_speed;
		target_camera.z -= option->revolve_speed;
		player_camera.z += option->revolve_speed;
		if (time >= 50)
		{
			target_camera.x += time - 50;
			player_camera.x -= time - 50;
			target_camera.z += time - 50;
			player_camera.z -= time - 50;
			muki++;
		}
		break;
	case 2:
		target_camera.x -= option->revolve_speed;
		player_camera.x += option->revolve_speed;
		target_camera.z += option->revolve_speed;
		player_camera.z -= option->revolve_speed;
		if (time >= 50)
		{
			target_camera.x += time - 50;
			player_camera.x -= time - 50;
			target_camera.z -= time - 50;
			player_camera.z += time - 50;
			muki++;
		}
		break;
	case 3:
		target_camera.x += option->revolve_speed;
		player_camera.x -= option->revolve_speed;
		target_camera.z += option->revolve_speed;
		player_camera.z -= option->revolve_speed;
		if (time >= 50)
		{
			target_camera.x -= time - 50;
			player_camera.x += time - 50;
			target_camera.z -= time - 50;
			player_camera.z += time - 50;
			muki -= muki;
		}
		break;
	default:
		break;
	}
}


void Dungeon::GoForward()
{
	time += option->move_speed;
	if (time >= 60 && !flaging) //����ʍs�̎��ɕǂ������Ă��܂��̂ŉ��}���u
	{
		flaging++;
		switch (muki)
		{
		case 0:
			pos_z++;
			break;
		case 1:
			pos_x++;
			break;
		case 2:
			pos_z--;
			break;
		case 3:
			pos_x--;
			break;
		default:
			break;
		}
	}
	if (time < 100)
	{
		switch (muki)
		{
		case 0:
			target_camera.z += option->move_speed;
			player_camera.z += option->move_speed;
			break;
		case 1:
			target_camera.x += option->move_speed;
			player_camera.x += option->move_speed;
			break;
		case 2:
			target_camera.z -= option->move_speed;
			player_camera.z -= option->move_speed;
			break;
		case 3:
			target_camera.x -= option->move_speed;
			player_camera.x -= option->move_speed;
			break;
		default:
			DrawString(0, 0, "Error! Dungeon.cpp have missing muki.", GetColor(255, 0, 0));
			WaitKey();
			break;
		}
	}
	else
	{
		switch (muki)
		{
		case 0:
			target_camera.z = pos_z * 100 + 100;
			player_camera.z = pos_z * 100;
			break;
		case 1:
			target_camera.x = pos_x * 100 + 100;
			player_camera.x = pos_x * 100;
			break;
		case 2:
			target_camera.z = pos_z * 100;
			player_camera.z = pos_z * 100 + 100;
			break;
		case 3:
			target_camera.x = pos_x * 100;
			player_camera.x = pos_x * 100 + 100;
			break;
		default:
			DrawString(0, 0, "Error! Dungeon.cpp have missing muki.", GetColor(255, 0, 0));
			WaitKey();
			break;
		}
		flaging = 0;
		state = 0;
		time = 0;
	}
}


void Dungeon::ReturnBack()
{
	option->revolve_speed *= 2;
	switch (muki)
	{
	case 0:
		/*if (time < 50)
		{
		time += option->revolve_speed;
		Return_right();
		}
		else
		{
		time = 0;
		down_help++;
		if (down_help>1) //�E�]���2��Ăяo��
		{
		state = 0;
		down_help = 0;
		}
		}*/
		/*if (time < 100)
		{
		time += 1;
		target_camera.z -= 1;
		player_camera.z += 1;
		if (time > 100)
		{
		target_camera.z += time - 100;
		player_camera.z -= time - 100;
		}
		}
		else
		{
		time = 0;
		state = 0;
		}*/
		if (time < 100)
		{
			if (time < 50)
			{
				time += option->revolve_speed;
				target_camera.x += option->revolve_speed;
				player_camera.x -= option->revolve_speed;
				target_camera.z = (int)sqrt((double)(2500 - ((int)target_camera.x % 100 - 50)*((int)target_camera.x % 100 - 50))) + 50 + pos_z * 100;
				player_camera.z = 100 - (int)target_camera.z % 100 + pos_z * 100;
				if (time >= 50)
				{
					target_camera.x -= time - 50;
					player_camera.x += time - 50;
					target_camera.z = pos_z * 100 + 50;
					player_camera.z = pos_z * 100 + 50;
					time = 50;
				}
			}
			else
			{
				time += option->revolve_speed;
				target_camera.x -= option->revolve_speed;
				player_camera.x += option->revolve_speed;
				target_camera.z = -(int)sqrt((double)(2500 - ((int)target_camera.x % 100 - 50)*((int)target_camera.x % 100 - 50))) + 50 + pos_z * 100;
				player_camera.z = 100 - (int)target_camera.z % 100 + pos_z * 100;
				if (time >= 100)
				{
					target_camera.x += time - 100;
					player_camera.x -= time - 100;
					target_camera.z = pos_z * 100;
					player_camera.z = pos_z * 100 + 100;
				}

			}
		}
		else
		{
			time = 0;
			state = 0;
			muki = 2;
		}
		break;

	case 1: //�E����
		if (time < 100)
		{
			if (time < 50)
			{
				time += option->revolve_speed;
				target_camera.x -= option->revolve_speed;
				player_camera.x += option->revolve_speed;
				target_camera.z = -(int)sqrt((double)(2500 - ((int)target_camera.x % 100 - 50)*((int)target_camera.x % 100 - 50))) + 50 + pos_z * 100;
				player_camera.z = 100 - (int)target_camera.z % 100 + pos_z * 100;
				if (time >= 50)
				{
					target_camera.x += time - 50;
					player_camera.x -= time - 50;
					target_camera.z = pos_z * 100;
					player_camera.z = pos_z * 100 + 100;
					time = 50;
				}
			}
			else
			{
				time += option->revolve_speed;
				target_camera.x -= option->revolve_speed;
				player_camera.x += option->revolve_speed;
				target_camera.z = -(int)sqrt((double)(2500 - ((int)target_camera.x % 100 - 50)*((int)target_camera.x % 100 - 50))) + 50 + pos_z * 100;
				player_camera.z = 100 - (int)target_camera.z % 100 + pos_z * 100;
				if (time >= 100)
				{
					target_camera.x += time - 100;
					player_camera.x -= time - 100;
					target_camera.z = pos_z * 100 + 50;
					player_camera.z = pos_z * 100 + 50;
				}

			}
		}
		else
		{
			time = 0;
			state = 0;
			muki = 3;
		}
		break;

	case 2: //������
		if (time < 100)
		{
			if (time < 50)
			{
				time += option->revolve_speed;
				target_camera.x -= option->revolve_speed;
				player_camera.x += option->revolve_speed;
				target_camera.z = -(int)sqrt((double)(2500 - ((int)target_camera.x % 100 - 50)*((int)target_camera.x % 100 - 50))) + 50 + pos_z * 100;
				player_camera.z = 100 - (int)target_camera.z % 100 + pos_z * 100;
				if (time >= 50)
				{
					target_camera.x += time - 50;
					player_camera.x -= time - 50;
					target_camera.z = pos_z * 100;
					player_camera.z = pos_z * 100 + 100;
					time = 50;
				}
			}
			else
			{
				time += option->revolve_speed;
				target_camera.x += option->revolve_speed;
				player_camera.x -= option->revolve_speed;
				target_camera.z = (int)sqrt((double)(2500 - ((int)target_camera.x % 100 - 50)*((int)target_camera.x % 100 - 50))) + 50 + pos_z * 100;
				player_camera.z = 100 - (int)target_camera.z % 100 + pos_z * 100;
				if (time >= 100)
				{
					target_camera.x -= time - 100;
					player_camera.x += time - 100;
					target_camera.z = pos_z * 100 + 100;
					player_camera.z = pos_z * 100;
				}

			}
		}
		else
		{
			time = 0;
			state = 0;
			muki = 0;
		}
		break;

	case 3: //�����E
		if (time < 100)
		{
			if (time < 50)
			{
				time += option->revolve_speed;
				target_camera.x += option->revolve_speed;
				player_camera.x -= option->revolve_speed;
				target_camera.z = (int)sqrt((double)(2500 - ((int)target_camera.x % 100 - 50)*((int)target_camera.x % 100 - 50))) + 50 + pos_z * 100;
				player_camera.z = 100 - (int)target_camera.z % 100 + pos_z * 100;
				if (time >= 50)
				{
					target_camera.x -= time - 50;
					player_camera.x += time - 50;
					target_camera.z = pos_z * 100 + 100;
					player_camera.z = pos_z * 100;
					time = 50;
				}
			}
			else
			{
				time += option->revolve_speed;
				target_camera.x += option->revolve_speed;
				player_camera.x -= option->revolve_speed;
				target_camera.z = (int)sqrt((double)(2500 - ((int)target_camera.x % 100 - 50)*((int)target_camera.x % 100 - 50))) + 50 + pos_z * 100;
				player_camera.z = 100 - (int)target_camera.z % 100 + pos_z * 100;
				if (time >= 100)
				{
					target_camera.x -= time - 100;
					player_camera.x += time - 100;
					target_camera.z = pos_z * 100 + 50;
					player_camera.z = pos_z * 100 + 50;
				}

			}
		}
		else
		{
			time = 0;
			state = 0;
			muki = 1;
		}
		break;
	}

	if (!revflag)
	{
		revflag++;
	}
	option->revolve_speed /= 2;
}


void Dungeon::ReturnLeft()
{
	if (time < 50)
	{
		time += option->revolve_speed;
		switch (muki)
		{
		case 0:
			target_camera.x -= option->revolve_speed;
			player_camera.x += option->revolve_speed;
			target_camera.z -= option->revolve_speed;
			player_camera.z += option->revolve_speed;
			if (time >= 50)
			{
				target_camera.x += time - 50;
				player_camera.x -= time - 50;
				target_camera.z += time - 50;
				player_camera.z -= time - 50;
				muki = 3;
			}
			break;
		case 1:
			target_camera.x -= option->revolve_speed;
			player_camera.x += option->revolve_speed;
			target_camera.z += option->revolve_speed;
			player_camera.z -= option->revolve_speed;
			if (time >= 50)
			{
				target_camera.x += time - 50;
				player_camera.x -= time - 50;
				target_camera.z -= time - 50;
				player_camera.z += time - 50;
				muki--;
			}
			break;
		case 2:
			target_camera.x += option->revolve_speed;
			player_camera.x -= option->revolve_speed;
			target_camera.z += option->revolve_speed;
			player_camera.z -= option->revolve_speed;
			if (time >= 50)
			{
				target_camera.x -= time - 50;
				player_camera.x += time - 50;
				target_camera.z -= time - 50;
				player_camera.z += time - 50;
				muki--;
			}
			break;
		case 3:
			target_camera.x += option->revolve_speed;
			player_camera.x -= option->revolve_speed;
			target_camera.z -= option->revolve_speed;
			player_camera.z += option->revolve_speed;
			if (time >= 50)
			{
				target_camera.x -= time - 50;
				player_camera.x += time - 50;
				target_camera.z += time - 50;
				player_camera.z -= time - 50;
				muki--;
			}
			break;
		default:
			break;
		}
	}
	else
	{
		time = 0;
		state = 0;
	}

	if (!revflag)
	{
		revflag++;
	}
}


void Dungeon::GoRight()
{
	time += option->move_speed;
	if (time < 100)
	{
		switch (muki)
		{
		case 0: //�����
			target_camera.x += option->move_speed;
			player_camera.x += option->move_speed;
			if (time >= 50 && !flaging) //�����ňړ����邱�Ƃɂ��ǂ̌����������������Ȃ�̂�h��
			{
				pos_x++;
				flaging++;
			}
			break;
		case 1:
			target_camera.z -= option->move_speed;
			player_camera.z -= option->move_speed;
			if (time >= 50 && !flaging)
			{
				pos_z--;
				flaging++;
			}
			break;
		case 2:
			target_camera.x -= option->move_speed;
			player_camera.x -= option->move_speed;
			if (time >= 50 && !flaging)
			{
				pos_x--;
				flaging++;
			}
			break;
		case 3:
			target_camera.z += option->move_speed;
			player_camera.z += option->move_speed;
			if (time >= 50 && !flaging)
			{
				pos_z++;
				flaging++;
			}
			break;
		default:
			break;
		}
	}
	else
	{
		if (muki % 2) //�E�����������Ă���
		{
			target_camera.z = pos_z * 100 + 50;
			player_camera.z = pos_z * 100 + 50;
		}
		else
		{
			target_camera.x = pos_x * 100 + 50;
			player_camera.x = pos_x * 100 + 50;
		}
		flaging = 0;
		time = 0;
		state = 0;
	}
}


void Dungeon::GoLeft()
{
	time += option->move_speed;
	if (time < 100)
	{
		switch (muki)
		{
		case 0:
			target_camera.x -= option->move_speed;
			player_camera.x -= option->move_speed;
			if (time >= 50 && !flaging)
			{
				pos_x--;
				flaging++;
			}
			break;

		case 1:
			target_camera.z += option->move_speed;
			player_camera.z += option->move_speed;
			if (time >= 50 && !flaging)
			{
				pos_z++;
				flaging++;
			}
			break;

		case 2:
			target_camera.x += option->move_speed;
			player_camera.x += option->move_speed;
			if (time >= 50 && !flaging)
			{
				pos_x++;
				flaging++;
			}
			break;

		case 3:
			target_camera.z -= option->move_speed;
			player_camera.z -= option->move_speed;
			if (time >= 50 && !flaging)
			{
				pos_z--;
				flaging++;
			}
			break;

		default:
			break;
		}
	}
	else
	{
		if (muki % 2) //�E�����������Ă���
		{
			target_camera.z = pos_z * 100 + 50;
			player_camera.z = pos_z * 100 + 50;
		}
		else
		{
			target_camera.x = pos_x * 100 + 50;
			player_camera.x = pos_x * 100 + 50;
		}
		flaging = 0;
		time = 0;
		state = 0;
	}
}


void Dungeon::GoBack()
{
	time += option->move_speed;
	if (time < 100)
	{
		switch (muki)
		{
		case 0:
			target_camera.z -= option->move_speed;
			player_camera.z -= option->move_speed;
			break;
		case 1:
			target_camera.x -= option->move_speed;
			player_camera.x -= option->move_speed;
			break;
		case 2:
			target_camera.z += option->move_speed;
			player_camera.z += option->move_speed;
			break;
		case 3:
			target_camera.x += option->move_speed;
			player_camera.x += option->move_speed;
			break;
		default:
			DrawString(0, 0, "Error! Dungeon.cpp have missing muki.", GetColor(255, 0, 0));
			WaitKey();
			break;
		}
	}
	else
	{
		//����
		switch (muki)
		{
		case 0:
			pos_z--;
			target_camera.z = pos_z * 100 + 100;
			player_camera.z = pos_z * 100;
			break;
		case 1:
			pos_x--;
			target_camera.x = pos_x * 100 + 100;
			player_camera.x = pos_x * 100;
			break;
		case 2:
			pos_z++;
			target_camera.z = pos_z * 100;
			player_camera.z = pos_z * 100 + 100;
			break;
		case 3:
			pos_x++;
			target_camera.x = pos_x * 100;
			player_camera.x = pos_x * 100 + 100;
			break;
		default:
			DrawString(0, 0, "Error! Dungeon.cpp have missing muki.", GetColor(255, 0, 0));
			WaitKey();
			break;
		}
		flaging = 0;
		state = 0;
		time = 0;
	}
}


void Dungeon::LoadDungeon(int floor) //�s���\��̊K�w�̏���ǂݍ��ނ�������
{
	switch (floor)
	{
	case 1:
		fp = fopen("./dungeon/dungeon1/floor1/map.cns", "r");
		strcpy(dungeon_name, "dungeon1/floor1");
		break;
	case 2:
		fp = fopen("./dungeon/dungeon1/floor2/map.cns", "r");
		strcpy(dungeon_name, "dungeon1/floor2");
		break;
	case 3:
		fp = fopen("./dungeon/dungeon1/floor3/map.cns", "r");
		strcpy(dungeon_name, "dungeon1/floor3");
		break;
	}
	floors = floor;

	//GraphFilter(kabe_handle, DX_GRAPH_FILTER_GAUSS, 32, 55600);

	if (fp == NULL) //�G���[�`�F�b�N
	{
		DrawString(0, 0, "Error!", GetColor(255, 0, 0));
		WaitKey();
	}

	fscanf(fp, "%d,%d", &x_max, &z_max);
	for (int i = 0; i < z_max; i++)
	{
		for (int i2 = 0; i2 < x_max; i2++)
		{
			fscanf(fp, "%d,", &map_data[i][i2]);
			//fscanf(fp, "%c");
		}
	}
	fscanf(fp, "%d,%d", &start_x, &start_z);
	fscanf(fp, "%d", &feel_flag);
	fscanf(fp, "%s", kabe_name);
	fscanf(fp, "%d,%d,%d", &fog_r, &fog_g, &fog_b);
	fscanf(fp, "%f,%f", &fog_start, &fog_goal);

	SetTransColor(255, 255, 255); //���𓧉ߐF��
	kabe_handle = LoadGraph(kabe_name);
	SetTransColor(0, 0, 0); //�ꉞ�߂�


	if (kabe_handle == -1) //�G���[�`�F�b�N
	{
		DrawString(0, 0, "Error!", GetColor(255, 0, 0));
		WaitKey();
	}

	if (feel_flag)
	{
		int keep = 0;
		for (int i = 0; i < z_max / 2; i++)
		{
			for (int i2 = 0; i2 < x_max; i2++)
			{
				keep = map_data[i][i2];
				map_data[i][i2] = map_data[z_max - i - 1][i2];
				map_data[z_max - i - 1][i2] = keep;
			}
		}
	}

	//���̏�����
	pos_x = start_x;
	pos_z = start_z;
	state = 0;
	time = 0;
	muki = 0;
	nowchoose = 0;
	state = 0;
	minimap_flag = 1;

	//�J�����̏�����
	target_camera = VGet(pos_x * 100 + 50, 50, pos_z * 100 + 100);
	player_camera = VGet(pos_x * 100 + 50, 50, pos_z * 100);

	//�t�H�O�̐ݒ�
	SetFogEnable(TRUE);
	SetFogColor(fog_r, fog_g, fog_b);
	SetFogStartEnd(fog_start, fog_goal);

}


void Dungeon::DrawMiniMap()
{
	if (minimap_flag)
	{
		//���n
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, 72); //����
		for (int z = 0; z < z_max; z++)
		{
			for (int x = 0; x < x_max; x++)
			{
				DrawBox(640 - (x_max - x + 1) * 20, 280 - z * 20, 640 - (x_max - x) * 20, 280 - (z + 1) * 20, white, FALSE);
			}
		}
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, 212); //����
		DrawBox(640 - (x_max + 1) * 20, 279, 640 - 20, 279 - z_max * 20, black, TRUE);
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0); //���ɖ߂�


		for (int z = 0; z < z_max; z++)
		{
			for (int x = 0; x < x_max; x++)
			{
				if (savedata->map_open_flag[floors - 1][z][x])
				{
					if (map_data[z][x] & 1)
					{
						DrawLine(640 - (x_max - x + 1) * 20, 280 - (z + 1) * 20, 640 - (x_max - x) * 20, 280 - (z + 1) * 20, white);
						if (z < z_max - 1) //�z��̊O�ɃA�N�Z�X���Ȃ��悤��
						{
							if (!(map_data[z + 1][x] & 4) && savedata->map_open_flag[floors - 1][z + 1][x]) //����ʍs�Ŋ��ɓ��j�ς݂̏ꍇ
							{
								DrawString(640 - (x_max - x + 1) * 20 + 3, 280 - (z + 1) * 20 - 10, "��", white);
							}
						}
					}
					if (map_data[z][x] & 2)
					{
						DrawLine(640 - (x_max - x) * 20, 280 - z * 20, 640 - (x_max - x) * 20, 280 - (z + 1) * 20, white);
						if (x < x_max - 1) //�z��̊O�ɃA�N�Z�X���Ȃ��悤��
						{
							if (!(map_data[z][x + 1] & 8) && savedata->map_open_flag[floors - 1][z][x + 1]) //����ʍs�Ŋ��ɓ��j�ς݂̏ꍇ
							{
								DrawString(640 - (x_max - x) * 20 - 10, 280 - (z + 1) * 20 + 3, "��", white);
							}
						}
					}
					if (map_data[z][x] & 4)
					{
						DrawLine(640 - (x_max - x + 1) * 20, 280 - z * 20, 640 - (x_max - x) * 20, 280 - z * 20, white);
						if (z > 0) //�z��̊O�ɃA�N�Z�X���Ȃ��悤��
						{
							if (!(map_data[z - 1][x] & 1) && savedata->map_open_flag[floors - 1][z - 1][x]) //����ʍs�Ŋ��ɓ��j�ς݂̏ꍇ
							{
								DrawString(640 - (x_max - x + 1) * 20 + 3, 280 - z * 20 - 10, "��", white);
							}
						}
					}
					if (map_data[z][x] & 8)
					{
						DrawLine(640 - (x_max - x + 1) * 20, 280 - z * 20, 640 - (x_max - x + 1) * 20, 280 - (z + 1) * 20, white);
						if (x > 0) //�z��̊O�ɃA�N�Z�X���Ȃ��悤��
						{
							if (!(map_data[z][x - 1] & 2) && savedata->map_open_flag[floors - 1][z][x - 1]) //����ʍs�Ŋ��ɓ��j�ς݂̏ꍇ
							{
								DrawString(640 - (x_max - x + 1) * 20 - 10, 280 - (z + 1) * 20 + 3, "��", white);
							}
						}
					}
					SetDrawBlendMode(DX_BLENDMODE_ALPHA, 72); //����
					DrawBox(640 - (x_max - x + 1) * 20, 280 - z * 20, 640 - (x_max - x) * 20, 280 - (z + 1) * 20, blue, TRUE); //������
					SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0); //���ɖ߂�
				}
			}
		}

		DrawRotaGraph(640 - (x_max - pos_x) * 20 - 10, 280 - (pos_z + 1) * 20 + 10, 20.0 / 128.0, muki * PI / 2.0, yajirushi_h, TRUE);
	}
}


void Dungeon::DrawEvent()
{
	DrawBillboard3D(VGet(150,50,150), 0.5f, 0.5f, 50.0, 0.0f, event_h, 0);
}


void Dungeon::DrawExcra(int posx, int posy, int posz)
{
	DrawSquare(posx*100+50, 0, posz+50, posx*100+50, 100, posz+50);
}