#pragma once

typedef enum {      //列挙型
	Scene_Menu,    //メニュー画面
	Scene_Game,    //ゲーム画面
	Scene_Stop,    //一時停止画面
} eScene;


//画面の処理
class Menu
{
private:
	//現在の画面(シーン)
	int Scene;
	//ゲームやり直しフラグ
	bool restart_flag;
	//サウンドハンドル
	int topsound;     //トップに戻る
	int gamestartsound;  //ゲーム開始
	int stopsound;  //一時停止
	//ハンドルをならすかどうかのフラグ
	bool topsound_flag;
	bool gamestartsound_flag;
	bool stopsound_flag;

private:
	void SoundAll();//画面移動の時の音の処理
    void UpdateScene();//画面の更新
	void Top();//メニュー画面
    void Game();//ゲーム画面
	void Stop();//一時停止画面
public:
	Menu();//コンストラクタ
	void  All();//Mainで呼び出す関数
};

