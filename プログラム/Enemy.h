#pragma once
#include "define.h"


//敵の処理
class Enemy
{
private:
	double x, y;//座標
	int enemygh[3];//グラフィックハンドル
	int width, height;//画像のサイズ
	int intime, stoptime, outtime;//敵の出現するループを保持
	int shottime;//弾の発射する時刻
	int count;//出現している間のカウント
	int enemy_type; //敵の種類
	int shot_type; //弾の種類
	int move_pattern; //移動の種類
	int shot_pattern;//弾のパターン
	int hp;//敵の体力
	int item;//敵のアイテム
	ENE_SHOT shot[ENEMYSHOT_NUM];//弾の構造体
	bool shotflag;//弾が打てるか
	int shotcount; //弾を打ってからのカウント
	int shotnumber;//発射した弾の数
	double rad;//角度（ラジアン）弾の発射時に使用
	bool deathflag;//敵死亡
	bool endflag;//敵が帰還
	bool soundshot;//音がなったか
private:
	void Move();
	void Shot();
	void Draw();
	bool LocateCheck();
	bool ShotLocateCheck(int i);
public:
	void GetCoordinate(double* x, double* y);
	bool GetSoundshot();//音のフラグを返す
	void SetShotflag(int index, bool flag);//添字がindexのshotを指定したflagにする
	bool GetshotCoordinate(int index, double* x, double* y);//画面にある敵の弾の座標を取得
	int GetEnemytype();//敵の弾の種類を取得
	int GetShottype();//敵の弾の種類を取得
	int GetItem();//Itemの種類を取得
	bool GetDeathflag();//死亡フラグを返す
	void SetDeathflag();//死亡フラグを立てる
	void SetGrazeflag(int index);//添え字indexの弾のグレイズ判定フラグを立てる
	bool GetGrazeflag(int index);//添え字indexの弾のグレイズ判定フラグを返す
	//コンストラクタで敵のパターンを一括で決めるように（敵画像、敵種類、移動パターン、座標、出現開始、停止、帰還、弾画像、弾種類、弾パターン、弾発射時間、弾速さ）
	Enemy(int type, int shottype, int move_pattern, int shot_pattern, int speed, int intime, int stoptime, int shottime, int outtime, int x, int y, int hp, int item);
	bool All();
};

