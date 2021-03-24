#include "define.h"
#include "SceneMgr.h"
#include "InputKey.h"
int game_count = 0;//ゲームのカウント
int hiscore = 0;//ハイスコア


//ライブラリでウィンドウの作成とゲームのループ実行
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {
	ChangeWindowMode(TRUE);//ライブラリでゲーム画面を表示
	if (DxLib_Init() == -1) return -1;//DXライブラリの初期化
	SetDrawScreen(DX_SCREEN_BACK);//ライブラリで描画先を裏画面に
	
	//SceneMgrの参照
	SceneMgr& scenemgr = SceneMgr::Instance();

	//キーの入力管理クラスのインスタンス
	InputKey input;

	while (!ProcessMessage()) {//ウィンドウが閉じるまで

		//ライブラリで描画画面の前の画像消す(裏画面)
		ClearDrawScreen();

		//キーの入力状態の更新
		input.Update_Keystate();

		//scenemgrのループ関数を実行
		scenemgr.Loop();

		//ライブラリで表画面に転送
		ScreenFlip();

	}

	DxLib_End(); //DXライブラリの終了処理
	return 0;
}