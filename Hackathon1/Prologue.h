#pragma once
#include "SceneBase.h"

class window;

class Prologue :
	public SceneBase {
public:
	Prologue();
	~Prologue();

	void Draw();
	int Reaction();

	static bool RIAJU;

private:
	window* w;
	int textHandle;
	char dText[8][256];
	char buf[48 * 3];
	bool firstflag = 1;

	bool end;
};

