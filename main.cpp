#include "DxLib.h"

#define SCREEN_WIDTH	640
#define SCREEN_HEIGHT	480

// キーボード情報
char keyState[256];		// キーボード情報
char oldKeyState[256];	// ひとつ前のキーボード情報

int waterCount = 0;

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	ChangeWindowMode(TRUE);	// ウィンドウモードに変更
	SetGraphMode(SCREEN_WIDTH, SCREEN_HEIGHT, 32);	// 解像度の設定
	SetMainWindowText("Water");	// ウィンドウのタイトルを変更

	if (DxLib_Init() == -1)	// DXライブラリ初期化処理
	{
		return -1;	// エラーが起きたら直ちに終了
	}

	// ひとつ前のキーボード情報を初期化
	for (int key = 0; key < 256; key++)
	{
		oldKeyState[key] = 0;
	}

	// ゲームループ
	while (ProcessMessage() == 0)
	{
		// ------------------------------------
		// 前処理
		// ------------------------------------

		// 現在のキーボード情報を更新
		GetHitKeyStateAll(keyState);

		// SPACEキーで飲んだ水のカウントをプラスする
		if (keyState[KEY_INPUT_SPACE] == 1 && oldKeyState[KEY_INPUT_SPACE] == 0)
		{
			waterCount++;
		}

		// DELETEキーで飲んだ水のカウントをマイナスする
		if (keyState[KEY_INPUT_DELETE] == 1 && oldKeyState[KEY_INPUT_DELETE] == 0)
		{
			waterCount--;
		}

		printfDx("WaterCount:%d\n", waterCount);

		// ------------------------------------
		// 描画処理
		// ------------------------------------
		ClearDrawScreen(); // 画面を焼き払う

		// ------------------------------------
		// 後処理
		// ------------------------------------


		// Qキーで終了
		if (keyState[KEY_INPUT_Q] == 1 && oldKeyState[KEY_INPUT_Q] == 0) break;

		// キーボード情報を保存
		for (int key = 0; key < 256; key++)
		{
			oldKeyState[key] = keyState[key];
		}

		ScreenFlip(); // 過去を忘却

		clsDx(); // 簡易文字を抹殺
	}

	DxLib_End();	// DXライブラリ使用の終了処理

	return 0;	// ソフトの終了
}