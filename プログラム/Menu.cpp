#include "Menu.h"
#include "define.h"
#include "Control.h"


Menu::Menu() {

	//初期化
     restart_flag = false;//ゲームやり直しフラグ
	 Scene = Scene_Menu;    //現在の画面(シーン) 最初はメニュー画面

	 //ライブラリで音でーたの読み込み
	 topsound=LoadSoundMem("MUSIC/bagtop.ogg");     //トップに戻る
	 gamestartsound=LoadSoundMem("MUSIC/start.ogg");//ゲーム開始
	 stopsound= LoadSoundMem("MUSIC/Stop.ogg");//一時停止

	 //ハンドルをならすかどうかのフラグ
	 topsound_flag=false;
	 gamestartsound_flag=false;
	 stopsound_flag=false;
}

//画面の更新
void Menu::UpdateScene() {
	if (CheckHitKey(KEY_INPUT_G) != 0) {
		if (Scene == Scene_Menu) {
			gamestartsound_flag = true;
		}
		else if (Scene == Scene_Stop) {
			stopsound_flag = true;
	 }
		Scene = Scene_Game;

	}else
	if (Scene !=Scene_Menu &&CheckHitKey(KEY_INPUT_M) != 0) {//画面がmenuでない時にMおされたら
		topsound_flag = true;//menu画面に戻る音フラグを立てる
		Scene = Scene_Menu;
	}else
	if (Scene ==Scene_Game && CheckHitKey(KEY_INPUT_S) != 0) {//画面がゲームの時にSおされたら
		stopsound_flag = true;
		Scene = Scene_Stop;
	}
}

//メニュー画面
void Menu::Top() {

	DrawGraph(0, 0, LoadGraph("IMAGE/Top.png"), FALSE);
	if (restart_flag == true) {
		Control& control = Control::Instance();//インスタンスの参照
		control.Restart();
		restart_flag = false;
	}
}
//ゲーム画面
void Menu::Game() {
	Control& control = Control::Instance();//インスタンスの参照
	control.All();
	hiscore = control.GetHiscore();
	restart_flag = true;
}
//一時停止画面
void Menu::Stop() {
	DrawGraph(0, 0, LoadGraph("IMAGE/stop.png"), FALSE);
}

//音の処理
void Menu::SoundAll() {
	//ライブラリでそれぞれのフラグが立っているなら音を出す
	if (topsound_flag)PlaySoundMem(topsound, DX_PLAYTYPE_BACK, TRUE);
	if (gamestartsound_flag)PlaySoundMem(gamestartsound, DX_PLAYTYPE_BACK, TRUE);
	if (stopsound_flag)PlaySoundMem(stopsound, DX_PLAYTYPE_BACK, TRUE);

}

//ループ内で呼び出される関数
void Menu::All(){
	topsound_flag = false;
	gamestartsound_flag = false;
	stopsound_flag = false;

		switch (Scene) {//現在のシーンにあった処理をする
		case Scene_Menu://現在のシーンがメニューなら
			Top();//メニュー画面
			break;
		case Scene_Game://現在のシーンがゲームなら
			Game();//ゲーム画面
			break;
		case Scene_Stop://現在のシーンがゲームなら
			Stop();//ゲーム画面
			break;
		}
		UpdateScene();//シーンを更新する
		SoundAll();//音の処理
	}

