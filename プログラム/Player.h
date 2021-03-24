#pragma once
#include "define.h"

//プレイヤの処理
class Player {
private:
	//x,y座標
	double x, y;
	//x方向とy方向のカウント数
	int xcount, ycount;

	//画像の幅
	int width;//横
	int height;//縦

	//グラフィックハンドル(メモリに保存した画像の識別番号)を格納する配列
	int playergh[12];
	int playergh2[12];

	//移動係数
	float move;

	//playerghの配列の添え字
	int ix, iy, result;

	//弾
	SHOT shot[PLAYERSHOT_NUM];

	//弾のカウント
	int count;

	//弾のパワー
	int power;

	//ショット音がなったかどうか
	bool soundshot;

	//生死関係
	bool live;//生きているかどうか　
	bool damage;//ダメージを負ったか
	int  player_hp;//HP
	int  damcount; //ダメージ中のカウント


	bool powerup_flag;
private:
	void Move();
	void Draw();
	void Shot();
public:
	Player();//コンストラクタ
	void GetCoordinate(double* x, double* y);//playerの座標を返す
	void SetShotflag(int index, bool flag);//添字indexのshotをflagにする
	bool GetshotCoordinate(int index, double* x, double* y);//画面にあるplayerの弾の座標を返す
	bool GetSoundshot();//音がなるフラグを返す
	void SetDamageflag();//ダメージを負ったかのフラグをtrueに設定
	bool GetDamageflag();//ダメージを負ったかのフラグを取得
	void SetLiveFlag();//死んだフラグ
	int  GetLife();//今のHPを取得
	void SetPower(int a);//powerにaを足す
	int  GetPower();//パワーを取得
	void All();
};



