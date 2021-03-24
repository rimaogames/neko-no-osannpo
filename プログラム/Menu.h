#pragma once
#include "SceneBase.h"

//選択項目
typedef enum { //列挙型
	mGame,        //ゲーム開始 0
	mConfig,    //設定 1
	mHowto,      //遊び方　2
	mNum,        //本項目の数 3
} mScene;

//メニュー画面
class Menu :public SceneBase
{
private:
   int menugraph;//メニュー画面

   //文字のグラフィックハンドル
   int start1_gh; //開始オレンジ
   int start0_gh; //開始灰色
   int config1_gh; //設定オレンジ
   int config0_gh; //せってい灰色
   int how1_gh;    //あそびかたオレンジ
   int how0_gh; //あそびかた灰色

   int cursor[6];//カーソル
   int NowSelect;//今選択中の項目
   int count; //カウント

   int nowselect_sound;//選択中の音ハンドル
   bool nowselectsound_flag; //nowselect_soundを鳴らすかのフラグ
private:
	void Draw(); //描画
public:
	Menu();
	void Initialize(); //初期化
	void Finalize();//終了の処理
	void Update(); //オーバーライド
	void All();  //オーバーライド
};

