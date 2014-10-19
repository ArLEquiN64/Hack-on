#include "Player.h"
#include "window.h"
#include "DxLib.h"

Player::Player(bool riaju) :HP(0), walkCount(0), credit(0) {
	RIAJU = riaju;
	for (int i = 0; i < 128; i++) {
		item[i] = 0;
	}
	for (int i = 0; i < 5; i++) {
		examRate[i] = 0;
	}
	w = new window(0, 420, 640, 60);
}

Player::~Player() {
}

int Player::getHP() {
	return HP;
}

int Player::getNowItem(int n) {
	return item[n];
}

int Player::getExamRate(int n) {
	return examRate[n];
}

void Player::addHP(int par) {
	HP += par;
	if (HP < 0) HP = 0;
	if (HP < 100)HP = 100;
}
void Player::addWalkCount(int par) {
	walkCount += par;
	if (HP < 0) HP = 0;
	if (HP < 100)HP = 100;
}

void Player::addItem(int Num, int vol) {
	item[Num] += vol;
	if (item[Num] < 0)item[Num] = 0;
	if (item[Num] > 99)item[Num] = 99;
}

void Player::addExamRate(int Num, int vol) {
	examRate[Num] += vol;
	if (examRate[Num] < 0) examRate[Num] = 0;
	if (examRate[Num] < 100)examRate[Num] = 100;
}

#pragma warning(disable:4996)

void Player::drawState() {
	char str[8][256];
	char* BOKU;
	BOKU = RIAJU ? "ƒŠƒA[" : "‚Ú‚Á‚¿";
	sprintf(str[0], "        ”æ˜J“x    :    %d %%            ŠŽ’PˆÊ  :    %d", HP, credit);
	sprintf(str[1], "        •à”@    :    %d •à            ‚Ú‚­‚Í %s", walkCount, BOKU);
	
	w->setString(str, 2);
	w->drawWindow();
}