#include "Menu.h"
#include "InputKey.h"
#include "SceneMgr.h"
#include "Control.h"
#include "DxLib.h"

//コンストラクタ
Menu::Menu() {
	//ライブラリで画像のロード
	menugraph = LoadGraph("IMAGE/Top.jpg");    
	if (LoadDivGraph("IMAGE/cursor.png", 6, 6, 1, 16, 30, cursor) == -1) {
		MSG("エラー発生");
	}
	start1_gh = LoadGraph("IMAGE/start.png");
	start0_gh = LoadGraph("IMAGE/notstart.png");
	config1_gh = LoadGraph("IMAGE/Co.png");
	config0_gh = LoadGraph("IMAGE/notcon.png");
	how1_gh = LoadGraph("IMAGE/how.png");
	how0_gh = LoadGraph("IMAGE/nothow.png");




	//他初期化
	count = 0;
	NowSelect = mGame; //最初はゲーム開始を選んでいる（値は0)

	//ライブラリで音データを読み込み
	nowselect_sound = LoadSoundMem("MUSIC/select.ogg");//選択中の音
	nowselectsound_flag = false;

}

//初期化
void Menu::Initialize() {


	//ライブラリで画像のロード
	menugraph = LoadGraph("IMAGE/Top.jpg");   
	start1_gh = LoadGraph("IMAGE/start.png");
	start0_gh = LoadGraph("IMAGE/notstart.png");
	config1_gh = LoadGraph("IMAGE/Co.png");
	config0_gh = LoadGraph("IMAGE/notcon.png");
	how1_gh = LoadGraph("IMAGE/how.png");
	how0_gh = LoadGraph("IMAGE/nothow.png");

	if (LoadDivGraph("IMAGE/cursor.png", 6, 6, 1, 16, 30, cursor) == -1) {
		MSG("エラー発生");
	}
	
	count = 0;
	NowSelect = mGame; //最初はゲーム開始を選んでいる（値は0)
	nowselectsound_flag = false;
}


//終了の処理
void Menu::Finalize() {
	//ライブラリで画像の消去
	DeleteGraph(menugraph);  
	DeleteGraph(cursor[5]);
	DeleteGraph(start1_gh);
	DeleteGraph(start0_gh);
	DeleteGraph(config0_gh);
	DeleteGraph(config1_gh);
	DeleteGraph(how1_gh);
	DeleteGraph(how0_gh);
}
//画面の更新
void Menu::Update() {
	//ScemeMgrの参照
	SceneMgr& scenemgr = SceneMgr::Instance();

	//下キーが押されたら
	if (InputKey::GetKeyPush(KEY_INPUT_DOWN)) {
		NowSelect = (NowSelect + 1) % mNum;//選択状態を一つ下げる
		nowselectsound_flag = true;//音フラグ立てる
	}
	//上キーが押されたら
	else if (InputKey::GetKeyPush(KEY_INPUT_UP)) {
		NowSelect = (NowSelect + (mNum-1)) % mNum;//選択状態を一つ上げる
		nowselectsound_flag = true;//音フラグ立てる
	}
	if (InputKey::GetKeyPush(KEY_INPUT_RETURN)) {
		//今選択しているものは？
		switch (NowSelect) {
		case mGame:
			scenemgr.ChangeScene(eScene::Scene_Game);//シーンをゲームに変更
			break;
		case mConfig:
			scenemgr.ChangeScene(eScene::Scene_Config); //シーンを設定画面に変更
			break;
			case mHowto:
			scenemgr.ChangeScene(eScene::Scene_Howto); //シーンを設定画面に変更
		default:
			break;
		}
	}

	//音フラグが立っている　かつ　音鳴らす設定ONなら音を鳴らす
	if (nowselectsound_flag&&Config::select_sound == ON)PlaySoundMem(nowselect_sound, DX_PLAYTYPE_BACK, TRUE);
}

void Menu::Draw() {
	//背景
	DrawGraph(0, 0, menugraph, FALSE);
	//文字

	switch (NowSelect) {
	case mGame:
		DrawGraph(200, 200, start1_gh, TRUE);
		DrawGraph(200, 300, config0_gh, TRUE);
		DrawGraph(200, 400, how0_gh, TRUE);
		break;
	case mConfig:
		DrawGraph(200, 200, start0_gh, TRUE);
		DrawGraph(200, 300, config1_gh, TRUE);
		DrawGraph(200, 400, how0_gh, TRUE);
		break;
	case mHowto:
		DrawGraph(200, 200, start0_gh, TRUE);
		DrawGraph(200, 300, config0_gh, TRUE);
		DrawGraph(200, 400, how1_gh, TRUE);
	default:
		break;
	}





	//カーソル
	int y = 200;
	switch (NowSelect) {
	case mGame:
		y = 200;
		break;
	case mConfig:
	    y = 300;
	    break;
	case mHowto:
		y = 400;
	default:
		break;
	}

	int number;
			number = count % 60 / 10;//0,1,2,3と動く
			DrawGraph(170, y+10, cursor[number], TRUE);//描画

}
void Menu::All() {
	nowselectsound_flag = false;
	Draw();
	count++;
} 