#pragma once
#include "Config.h"
#include "Menu.h"
#include "Stop.h"
#include "Howto.h"
#include "SceneBase.h"
#include "define.h"
#include "Result.h"

//シーンの管理クラス
class SceneMgr :public SceneBase
{
private:
	static eScene Scene;
	static eScene NextScene;
    
	Menu* menu = 0;
	Config* config=0;
	Stop* stop=0;
	Howto* howto = 0;
	Result* result = 0;
	//サウンドハンドル
	int topsound;     //トップに戻る
	int gamestartsound;  //ゲーム開始
	int stopsound;  //一時停止
	int selectother_sound; //ゲーム開始以外を選んだ時の音

	//ハンドルをならすかどうかのフラグ
	bool topsound_flag;
	bool gamestartsound_flag;
	bool stopsound_flag;
	bool selectothersound_flag;

private:
	SceneMgr();  //２つのインスタンス持つの禁止（シングルトン）
	void SoundAll();
	void Initialize(eScene scene);
	void Finalize(eScene scene);
public:
	void Update(); //オーバーライド
	void All();   //オーバーライド
	void Loop(); //Mainで呼び出される実行関数
	void ChangeScene(eScene nextScene);  //次のシーンを引数のものにする
	static SceneMgr& Instance() {//クラス静的変数、自身のインスタンスを格納
		static SceneMgr scenemgr;//静的変数として宣言
		return scenemgr;
	}
};

