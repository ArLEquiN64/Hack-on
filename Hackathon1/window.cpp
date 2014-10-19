#include "window.h"
#include "DxLib.h"


window::window(int ix, int iy, int isizeX, int isizeY) {
	x = ix;
	y = iy;
	sizeX = isizeX;
	sizeY = isizeY;
	// �w��T�C�Y�̃A���t�@�`�����l���Ȃ��̕`��\�摜���쐬����
	handle = MakeScreen(sizeX, sizeY, TRUE);
	back = MakeScreen(sizeX, sizeY, TRUE);
	// �쐬�����摜��`��Ώۂɂ���
	SetDrawScreen(back);
	SetDrawBlendMode(DX_BLENDGRAPHTYPE_ALPHA, 192);
	DrawBox(0, 0, isizeX, isizeY, 0xFFFFFF, TRUE);
	SetDrawBlendMode(DX_BLENDGRAPHTYPE_NORMAL, 0);
	// �`��Ώۂ�\��ʂɂ���
	SetDrawScreen(DX_SCREEN_BACK);
}


window::~window() {
}

void window::drawWindow() {

	DrawGraph(x, y, back, TRUE);
	DrawGraph(x, y, handle, TRUE);	

}

void window::setString(char str[8][256],int l) {

	// �쐬�����摜��`��Ώۂɂ���
	SetDrawScreen(handle); 

	ClearDrawScreen();

	for (int i = 0; i < l; i++) {
		DrawString(0 + 8, 0 + 8 + 20 * i, str[i], 0x00000000);
	}

	// �`��Ώۂ�\��ʂɂ���
	SetDrawScreen(DX_SCREEN_BACK);

}