#include"DxLib.h"
#include"Scene.h"
#include"Key_Input.h"

// プログラムは WinMain から始まります
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
	LPSTR lpCmdLine, int nCmdShow)
{

	ChangeWindowMode(TRUE); // ウィンドウモードに設定
	SetMainWindowText("タンイトル"); //タイトルの指定。何にしよう
	SetDrawScreen(DX_SCREEN_BACK);
	//SetBackgroundColor(0, 0, 0); //背景の色変更5
	if (DxLib_Init() == -1)		// ＤＸライブラリ初期化処理
	{
		return -1;			// エラーが起きたら直ちに終了
	}
	Scene* scene = new Scene(); //現在の場面
	Key_Input* key_input=new Key_Input(); //キー入力用


	while (1) //メインループ
	{

		ClearDrawScreen(); //画面をクリア。描画処理はこれより後に書く
		key_input->KeyUpdate(); //キー入力
		if (scene->Reaction() == -1) //キー入力などによる情報の更新
		{
			break;
		}
		scene->Draw(); //現在の場面の描画

		ScreenFlip(); //裏と表の仲介役。描画処理よりも後に書く


		if (ProcessMessage()) //×クリック待ち
		{
			break;
		}
		if (CheckHitKey(KEY_INPUT_ESCAPE) == 1)  //Esc入力待ち
		{
			break;
		}
	}
	DxLib_End();				// ＤＸライブラリ使用の終了処理

	return 0;				// ソフトの終了 
}