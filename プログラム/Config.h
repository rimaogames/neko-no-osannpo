#pragma once
#include "SceneBase.h"
//選択項目
typedef enum { //列挙型
	cDif,        //難易度 0
	cBGM,    //BGM設定 1
	cSound,      //効果音　2
	cBack,        //メニュー画面に戻る　3
	cNum,        //本項目の数 4
} cScene;


//設定画面クラス
class Config :public SceneBase
{
private:
	int cursor[6];//カーソルのグラフィックハンドル
	int enemy[3];//キャラクター（敵）のグラフィックハンドル
    //文字のグラフィックハンドル
	int ongh;//おん
	int offgh;//おふ
	int easygh;//かんたん
	int normalgh;//ふつう
	int hardgh;//むずかしい
	int exp_dif;//なんいど説明
	int exp_bgm;//BGM説明
	int exp_sound;//効果音説明
	int exp_menu;//メニュー説明

	int count; //カウント
	bool do_set; //設定する項目を選んだか
	int NowSelect; //今選択している項目
	//画像ハンドル格納用変数
	 int configimage;

	 int nowselect_sound;//選択中の音ハンドル
	 int selectother_sound; //Back以外を選んだ時や設定を決めた時の音
	 bool nowselectsound_flag; //nowselect_soundを鳴らすかのフラグ
	 bool selectothersound_flag;
public:
	static int select_dif;  //今選択している難易度
	static int select_bgm;  //今選択しているBGM設定
	static int select_sound;  //今選択している効果音設定
private:
	void Draw();//描画
	void SoundAll(); //音の処理
	void Select_Dif(); //難易度設定
	void Setting_BGM(); //BGM設定
	void Setting_Sound(); //効果音設定
	void Select_cScene(); //設定項目を選ぶ
public:
	Config();
	void Initialize();  //初期化
	void Finalize(); //終了の処理
	void Update();//更新（オーバーライド)
	void All();//実行(オーバーライド）
};

