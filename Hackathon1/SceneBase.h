#pragma once
class SceneBase
{
public:
	SceneBase();
	~SceneBase();
	virtual void Draw() = 0;
	virtual int Reaction() = 0;
};

