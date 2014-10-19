#include"DxLib.h"
#include"Scene.h"
#include"Key_Input.h"

// �v���O������ WinMain ����n�܂�܂�
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
	LPSTR lpCmdLine, int nCmdShow)
{

	ChangeWindowMode(TRUE); // �E�B���h�E���[�h�ɐݒ�
	SetMainWindowText("�^���C�g��"); //�^�C�g���̎w��B���ɂ��悤
	SetDrawScreen(DX_SCREEN_BACK);
	//SetBackgroundColor(0, 0, 0); //�w�i�̐F�ύX5
	if (DxLib_Init() == -1)		// �c�w���C�u��������������
	{
		return -1;			// �G���[���N�����璼���ɏI��
	}
	Scene* scene = new Scene(); //���݂̏��
	Key_Input* key_input=new Key_Input(); //�L�[���͗p


	while (1) //���C�����[�v
	{

		ClearDrawScreen(); //��ʂ��N���A�B�`�揈���͂������ɏ���
		key_input->KeyUpdate(); //�L�[����
		if (scene->Reaction() == -1) //�L�[���͂Ȃǂɂ����̍X�V
		{
			break;
		}
		scene->Draw(); //���݂̏�ʂ̕`��

		ScreenFlip(); //���ƕ\�̒�����B�`�揈��������ɏ���


		if (ProcessMessage()) //�~�N���b�N�҂�
		{
			break;
		}
		if (CheckHitKey(KEY_INPUT_ESCAPE) == 1)  //Esc���͑҂�
		{
			break;
		}
	}
	DxLib_End();				// �c�w���C�u�����g�p�̏I������

	return 0;				// �\�t�g�̏I�� 
}