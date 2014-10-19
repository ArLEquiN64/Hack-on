#include "DxLib.h"
#include "Prologue.h"
#include "window.h"
#include"Key_Input.h"

Prologue::Prologue() :end(false){
	w = new window(0, 360, 640, 120);
	textHandle = FileRead_open("prologue.txt");
}


Prologue::~Prologue() {
}

void Prologue::Draw() {
	w->setString(dText, 3);
	w->drawWindow();
}
bool Prologue::RIAJU;
#pragma warning(disable:4996)
int Prologue::Reaction() {
	if (Key_Input::buff_time[KEY_INPUT_Z] % 40 == 1 || firstflag)
	{
		firstflag = 0;
		if (!FileRead_eof(textHandle)) {
			if (FileRead_gets(buf, 48 * 3 + 1, textHandle)) {
				for (int i = 0; i < 3; i++) {
					for (int j = 0; j < 48; j++) {
						dText[i][j] = buf[48 * i + j];
					}
				}
			}
			return 0;
		}
		else {
			FileRead_close(textHandle);
			strcpy(dText[0], "‹M•û‚ÍƒŠƒA[‚©@Y/N");
			end = true;
			return 0;
		}
	}

	if (end) {
		if (Key_Input::buff_time[KEY_INPUT_Y] % 40 == 1 || firstflag) {
			RIAJU = true;
			return 3;
		}
		if (Key_Input::buff_time[KEY_INPUT_N] % 40 == 1 || firstflag) {
			RIAJU = false;
			return 3;
		}
	}
}