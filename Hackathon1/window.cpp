#include "window.h"
#include "DxLib.h"


window::window(int ix, int iy, int isizeX, int isizeY) {
	x = ix;
	y = iy;
	sizeX = isizeX;
	sizeY = isizeY;
	// 指定サイズのアルファチャンネルなしの描画可能画像を作成する
	handle = MakeScreen(sizeX, sizeY, TRUE);
	back = MakeScreen(sizeX, sizeY, TRUE);
	// 作成した画像を描画対象にする
	SetDrawScreen(back);
	SetDrawBlendMode(DX_BLENDGRAPHTYPE_ALPHA, 192);
	DrawBox(0, 0, isizeX, isizeY, 0xFFFFFF, TRUE);
	SetDrawBlendMode(DX_BLENDGRAPHTYPE_NORMAL, 0);
	// 描画対象を表画面にする
	SetDrawScreen(DX_SCREEN_BACK);
}


window::~window() {
}

void window::drawWindow() {

	DrawGraph(x, y, back, TRUE);
	DrawGraph(x, y, handle, TRUE);	

}

void window::setString(char str[8][256],int l) {

	// 作成した画像を描画対象にする
	SetDrawScreen(handle); 

	ClearDrawScreen();

	for (int i = 0; i < l; i++) {
		DrawString(0 + 8, 0 + 8 + 20 * i, str[i], 0x00000000);
	}

	// 描画対象を表画面にする
	SetDrawScreen(DX_SCREEN_BACK);

}