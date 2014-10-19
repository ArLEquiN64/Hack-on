#include "Scene.h"
#include"DxLib.h"

Scene::Scene()
{
	title = new Title;
	prologue = new Prologue;
	scene_now = title;
}


Scene::~Scene()
{
	
}


void Scene::Draw()
{
	scene_now->Draw();
}


int Scene::Reaction()
{
	int r = scene_now->Reaction();
	if (r)
	{
		ChangeScene(r);
	}
	return r;
}


void Scene::ChangeScene(int scene_number)
{
	switch (scene_number)
	{
	case 1:
		scene_now = title;
		break;
	case 2:
		scene_now = prologue;
		break;
	case 3:
		if (dungeon == NULL) { dungeon = new Dungeon; }
		scene_now = dungeon;
		break;
	case 4:
		break;
	default:
		break;
	}
}