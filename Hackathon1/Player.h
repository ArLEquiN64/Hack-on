#pragma once

class window;

class Player {
public:
	Player(bool RIAJU);
	~Player();

	int getHP();
	int getNowItem(int itemNum);
	int getExamRate(int examNum);
	bool getRIAJU();
	int getWalkCount();
	int getCredit();

	void addHP(int par);
	void addItem(int itemNum, int par);
	void addExamRate(int examNum, int par);
	void addWalkCount(int par);
	void addCredit(int par);

	void drawState();

private:
	bool RIAJU;
	int HP;
	int item[128];
	int examRate[5];
	int walkCount;
	int credit;

	window* w;
};