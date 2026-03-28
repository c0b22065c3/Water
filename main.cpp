#include "DxLib.h"

#define SCREEN_WIDTH	640
#define SCREEN_HEIGHT	480

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	ChangeWindowMode(TRUE);	// ウィンドウモードに変更
	SetGraphMode(SCREEN_WIDTH, SCREEN_HEIGHT, 32);	// 解像度の設定
	SetMainWindowText("GameProject");	// ウィンドウのタイトルを変更

	if (DxLib_Init() == -1)	// DXライブラリ初期化処理
	{
		return -1;	// エラーが起きたら直ちに終了
	}

	// ゲームループ
	while (ProcessMessage() == 0)
	{
		// ------------------------------------
		// 描画処理
		// ------------------------------------
		ClearDrawScreen(); // 画面を焼き払う

		ScreenFlip(); // 過去を忘却

		clsDx(); // 簡易文字を抹殺
	}

	DxLib_End();	// DXライブラリ使用の終了処理

	return 0;	// ソフトの終了
}