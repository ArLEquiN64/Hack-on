#pragma once
#include "SceneBase.h"
#include "Key_Input.h"

class Title :
	public SceneBase
{
public:
	Title();
	~Title();
	void Draw();
	int Reaction();
	int LineNum = 0;
	int TitleGraph, numicon[4], WindowFrame[16];
	int title_h;
};