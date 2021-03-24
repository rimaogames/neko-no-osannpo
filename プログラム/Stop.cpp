#include "Stop.h"
#include "InputKey.h"
#include "define.h"
#include "SceneMgr.h"
#include "Control.h"
Stop::Stop() {
	stopgraphgh = LoadGraph("IMAGE/stop.png");    //画像のロード
}
Stop::~Stop() {
	DeleteGraph(stopgraphgh);
}

//画面の更新
void Stop::Update() {

	//SceneMgrクラスの参照
	SceneMgr& scenemgr = SceneMgr::Instance();
	//Sが押されたら
	if (InputKey::GetKeyPush(KEY_INPUT_S) != 0) {
		scenemgr.ChangeScene(eScene::Scene_Game);//シーンをゲームに変更（再開）
	}else
		//Mがおされたら
	if(	InputKey::GetKeyPush(KEY_INPUT_M) != 0) {
		scenemgr.ChangeScene(eScene::Scene_Menu);//シーンをメニューに変更
	}
}

//実行
void Stop::All() {
	DrawGraph(0, 0, stopgraphgh,FALSE);//描画
}