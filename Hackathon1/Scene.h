#pragma once
#include"Title.h"
#include"SceneBase.h"
#include"Dungeon.h"
#include"Prologue.h"

class Scene
{
public:
	Scene();
	~Scene();
	void Draw();
	int Reaction();
	SceneBase* scene_now;
	Title* title;
	Dungeon* dungeon;
	void ChangeScene(int scene_number);
	Prologue* prologue;
};
