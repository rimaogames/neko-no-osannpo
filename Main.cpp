#include "define.h"
#include "Menu.h"
int game_count = 0;//ゲームのカウント
int hiscore=0;//ハイスコア


//ウィンドウの作成とゲームのループ実行
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {
	ChangeWindowMode(TRUE);//ゲーム画面を表示
	if (DxLib_Init() == -1) return -1;//DXライブラリの初期化
	SetDrawScreen(DX_SCREEN_BACK);//ライブラリ、描画先を裏画面に

	Menu *menu = new Menu;

	while (!ProcessMessage()) {//ウィンドウが閉じるまで

	    ClearDrawScreen();//ライブラリ、描画画面の前の画像消す(裏画面)
		
	    menu->All();//メニューのALLを実行

		ScreenFlip();//ライブラリ、表画面に転送

	}
	
	DxLib_End();
	return 0;
}