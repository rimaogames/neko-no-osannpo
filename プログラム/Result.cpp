#include "Result.h"
#include "define.h"
#include "InputKey.h"
#include "SceneMgr.h"
#include "Control.h"
//結果画面

//コンストラクタで音の読み込みだけ行って後はinitializeで
Result::Result() {
	//ライブラリで音の読み込み
	result_sound = LoadSoundMem("MUSIC/result.ogg");
	up_sound = LoadSoundMem("MUSIC/up.ogg");

}



//初期化
void Result::Initialize() {
	//ライブラリで画像の読み込み
	LoadDivGraph("IMAGE/number.png", 10, 10, 1, 17, 29, g_number);
	resultgh = LoadGraph("IMAGE/result.png");
	upgh = LoadGraph("IMAGE/up.png");
	nextgh = LoadGraph("IMAGE/next.png");
	endgh = LoadGraph("IMAGE/end.png");

    //結果をセット
	SetResult();
    //他初期化
	count = 0;
	endflag = false;
	resound_flag = false;
	upsound_flag = false;

	//コントロールの参照
	Control& control = Control::Instance();
	//ハイスコアを書き換え
	hiscore = control.GetHiscore();
}

//終了の処理
void Result::Finalize() {
	DeleteGraph(g_number[9]);
	DeleteGraph(resultgh);
	DeleteGraph(upgh);
	DeleteGraph(nextgh);
	DeleteGraph(endgh);
}

//結果をセット
void Result::SetResult() {
	int temp1, temp2, temp3;
	Control& control = Control::Instance();
	control.GetResult(&temp1,&temp2, &temp3);

	rescore = temp1;
	regraze = temp2;
	rehigh_score = temp3;
	
}

//描画
void Result::Draw() {
	DrawGraph(0, 0, resultgh, FALSE);
	char buf[100];
	memset(buf, 0, sizeof(buf));
	int h_num = 0, s_num = 0, g_num = 0;


	//エンターキーを押したらカウントを増やす
	if (count < 2&& InputKey::GetKeyPush(KEY_INPUT_RETURN) != 0) {
		resound_flag = true;//サウンドフラグを立てる
		count++;
	}
	//3回目はハイスコア更新かどうかでどっちの音を鳴らすか変える
	else if (count == 2 && InputKey::GetKeyPush(KEY_INPUT_RETURN) != 0) {
		count++;
		//ハイスコア更新
		if (rescore ==rehigh_score) {
			upsound_flag = true;
		}
		//ハイスコア更新してない
		else {
			resound_flag = true;
		}
	}
	if (count == 3)endflag = true;

	if (count > 0) {
		g_num = sprintf_s(buf, "%d", regraze);//bufにグレイズを入れる。numには文字数が入る
		for (int i = 0; i < g_num; i++) {
			//ライブラリで値の書き始めはSOCRE_X+20。にy座標45に数字を記入。
			//bufには1バイトずつ数字が格納されている。g_number[buf[i]-0]で数字のbuf[i]-を取得
			DrawGraph((SCORE_X + 20) + (i * NUMBER_LONG), 130, g_number[buf[i] - '0'], TRUE);
		}
	}
	if (count > 1) {
		s_num = sprintf_s(buf, "%d", rescore);//bufにスコアを入れる。numには文字数が入る
		for (int i = 0; i < s_num; i++) {
			//ライブラリで値の書き始めはSOCRE_X+20。にy座標45に数字を記入。
			//bufには1バイトずつ数字が格納されている。g_number[buf[i]-0]で数字のbuf[i]-を取得
			DrawGraph((SCORE_X + 20) + (i * NUMBER_LONG), 215, g_number[buf[i] - '0'], TRUE);
		}
	}
	if (count > 2) {
		h_num = sprintf_s(buf, "%d", rehigh_score);//bufにハイスコアを入れる。numには文字数が入る
		for (int i = 0; i < h_num; i++) {
			//ライブラリで値の書き始めはSOCRE_X+20。にy座標45に数字を記入。
			//bufには1バイトずつ数字が格納されている。g_number[buf[i]-0]で数字のbuf[i]-を取得
			DrawGraph((SCORE_X + 20) + (i * NUMBER_LONG), 300, g_number[buf[i] - '0'], TRUE);


			//ハイスコア更新ならハイスコア更新という文字を書く
			if (rescore == rehigh_score) {
				DrawGraph(100, 350, upgh, TRUE);
			}
		}
	}

	//最後以外は[次へ]文字を書く
	if (count < 3) {
		DrawGraph(440, 420, nextgh, TRUE);
	}
	//最後は[戻る]文字を書く
	else if (count >= 3) {
		DrawGraph(440, 420, endgh, TRUE);
	}
}
	//音の処理
void Result::SoundAll() {
	//ライブラリで音を鳴らす
	if (resound_flag)PlaySoundMem(result_sound, DX_PLAYTYPE_BACK,TRUE);
	if (upsound_flag)PlaySoundMem(up_sound, DX_PLAYTYPE_BACK,TRUE);
}

//画面の更新
void Result::Update() {
	//SceneMgrクラスの参照
	SceneMgr& scenemgr = SceneMgr::Instance();
	//表示が終了してGが押されたら
	if (endflag && InputKey::GetKeyPush(KEY_INPUT_RETURN) != 0) {
		scenemgr.ChangeScene(eScene::Scene_Menu);//シーンをゲームに変更（再開）
	}


}

//実行
void Result::All() {
	//サウンドフラグを初期化
	resound_flag = false;
	upsound_flag=false;

	//描画
	Draw();
	//設定で効果音を鳴らす設定なら音を鳴らす
	if (Config::select_sound == ON)SoundAll();
}
