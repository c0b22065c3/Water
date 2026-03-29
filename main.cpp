#include "DxLib.h"

#include "stdio.h"
#include "time.h"

#define SCREEN_WIDTH	640
#define SCREEN_HEIGHT	480

// 時間
int startTime;					// ゲーム開始時間
int nowTime;					// 現在の時間
int oldTime;					// ひとつ前の時間

// キーボード情報
char keyState[256];		// キーボード情報
char oldKeyState[256];	// ひとつ前のキーボード情報

// 水を飲んだカウント
int waterCount = 0;

// 変数を一時的に格納する為の変数
int integer = 0;
float floating = 0.0f;
char msg[64] = "";

// テキストファイルに書き込み
void SaveText(char *data)
{
	FILE* fp;
	
	fopen_s(&fp, "SaveData.txt", "a");
	fprintf(fp, data);
	fclose(fp);
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	ChangeWindowMode(TRUE);	// ウィンドウモードに変更
	SetGraphMode(SCREEN_WIDTH, SCREEN_HEIGHT, 32);	// 解像度の設定
	SetMainWindowText("Water");	// ウィンドウのタイトルを変更

	// 現在時刻を格納するよう変数
	DATEDATA Date;

	if (DxLib_Init() == -1)	// DXライブラリ初期化処理
	{
		return -1;	// エラーが起きたら直ちに終了
	}

	// ひとつ前のキーボード情報を初期化
	for (int key = 0; key < 256; key++)
	{
		oldKeyState[key] = 0;
	}

	// ゲーム開始時間を得る
	startTime = GetNowCount();

	// ゲームループ
	while (ProcessMessage() == 0)
	{
		// ------------------------------------
		// 前処理
		// ------------------------------------

		// 現在時刻を得る
		GetDateTime(&Date);

		// ゲーム開始からの経過時間を更新
		nowTime = GetNowCount() - startTime;

		// 現在のキーボード情報を更新
		GetHitKeyStateAll(keyState);

		// SPACEキーで水を飲んだ回数を加算してテキストに保存する
		if (keyState[KEY_INPUT_SPACE] == 1 && oldKeyState[KEY_INPUT_SPACE] == 0)
		{
			waterCount++;
			sprintf_s(msg, "%d/%d/%d %d:%d:%d 水を飲んだ！ %d杯目\n", Date.Year, Date.Mon, Date.Day, Date.Hour, Date.Min, Date.Sec, waterCount);
			SaveText(msg);
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
		if (keyState[KEY_INPUT_Q] == 1 && oldKeyState[KEY_INPUT_Q] == 0)
		{
			break;
		}

		// キーボード情報を保存
		for (int key = 0; key < 256; key++)
		{
			oldKeyState[key] = keyState[key];
		}

		// 時間を保存
		oldTime = nowTime;

		ScreenFlip(); // 過去を忘却

		clsDx(); // 簡易文字を抹殺
	}

	DxLib_End();	// DXライブラリ使用の終了処理

	return 0;	// ソフトの終了
}