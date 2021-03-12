#include "define.h"
#include "Control.h"
int game_count = 0;//ゲームのカウント

int hiscore=0;
typedef enum {
	Scene_Menu,    //メニュー画面
	Scene_Game,    //ゲーム画面
	Scene_Stop,
} eScene;
static int Scene = Scene_Menu;    //現在の画面(シーン)


void UpdateScene() {	
	if (CheckHitKey(KEY_INPUT_G) != 0) {
		Scene = Scene_Game;
		
	}
	if (Scene!=Scene_Stop && CheckHitKey(KEY_INPUT_M) != 0) {
		Scene = Scene_Menu;
	}
	if (Scene != Scene_Menu && CheckHitKey(KEY_INPUT_S) != 0) {
		Scene = Scene_Stop;
	}
}

//メニュー画面
void Menu() {

	DrawGraph(0, 0, LoadGraph("Top.png"), FALSE);
}

//ゲーム画面
void Game() {
	Control& control = Control::Instance();//インスタンスの参照
	control.All();
	hiscore = control.GetHiscore();
}
//一時停止画面
void Stop() {
	DrawGraph(0, 0, LoadGraph("stop.png"), FALSE);
}

int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {
	ChangeWindowMode(TRUE);//ゲーム画面を表示
	if (DxLib_Init() == -1) return -1;//DXライブラリの初期化
	SetDrawScreen(DX_SCREEN_BACK);//描画先を裏画面に


	while (!ProcessMessage()) {//ウィンドウが閉じるまで
		ClearDrawScreen();//描画画面の前の画像消す(裏画面)
		switch (Scene) {//現在のシーンにあった処理をする
		case Scene_Menu://現在のシーンがメニューなら
			Menu();//メニュー画面
			break;
		case Scene_Game://現在のシーンがゲームなら
			Game();//ゲーム画面
			break;
		case Scene_Stop://現在のシーンがゲームなら
			Stop();//ゲーム画面
			break;
		}
		UpdateScene();//シーンを更新する

		ScreenFlip();//表画面に転送
	}
	
	DxLib_End();
	return 0;
}