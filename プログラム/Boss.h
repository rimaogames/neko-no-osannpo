#pragma once
#include "define.h"

//ラスボスの処理
class Boss
{
private:
	//座標
	double x, y;
	//直前の座標を保持する変数
	double pre_x, pre_y;
	//グラフィックハンドル
	int bossgh[2];//boss
	int shotgh[3];//弾
	int w, w1, w2, h, h1, h2;//弾の画像の大きさ（縦幅、横幅)を保持
	//HP
	int hp;
	//1つ前のHP
	int pre_hp;
	//移動パターン
	int move_pattern;
	//弾のパターン
	int shot_pattern;
	//1つ前の移動パターン
	int pre_move_pattern;
	//１つ前の弾のパターン
	int pre_shot_pattern;
	//弾を打つかどうかのフラグ
	bool shot_flag;
	//弾の構造体
	ENE_SHOT shot[BOSSSHOT_NUM];
	//弾の打っている間のカウント
	int shotcount;
	//合計角度
	int angle;
	//増加量(sin波に使う)  サインを取得するための角度
	int rise;
	//移動パターン2の時の増加量(sin波に使う) 位相が1フレームに変化する量
	int rise2;
	int waitcount;//停止カウント
	bool wait;//停止フラグ
	//次の移動場所までの距離
	double move_x, move_y;
	//移動パターン3で使う三角形のどの頂点へ移動するのかを示す変数
	int p3_state;
	//ダメージを負わないフラグ(攻撃パターン変化時）
	bool nodamage_flag;
	//弾を打つ音を鳴らすかのフラグ
	bool soundshot;
	//生きているかどうかのフラグ
	bool live_flag;
private:
	void Move();//動く
	void Appear();//出現
	void MovePattern1();//移動パターン１
	void MovePattern2();//移動パターン２
	void MovePattern3();//移動パターン３
	void MoveDefalt();//移動パターン変化するためデフォルト位置に戻る
	void MoveInit(double x, double y, int state);//移動の目的地の変更
	void SetMovepattern(int pattern);//移動パターン変更
	void SetShotpattern(int pattern);//ショットパターン変更
	void Shot();//弾を打つ
	bool ShotLocateCheck(int i);//弾が画面外にあるか
	int ShotSearch();//フラグが立っていない弾を設定しその添字を返す
	void Draw();//描画
public:
	Boss();//コンストラクタ
	void SetFlag(bool a);//フラグを立てる
	bool GetFlag();//フラグを取得
	bool GetNodamageFlag();//無敵時間かどうかのフラグを取得
	int GetPreHP();//１つ前のHPを返す
	void SetDamage();//angle,pre_x,pre_y,move_x,move_yを設定
	void GetCoordinate(double* x, double* y);//Bossの座標を取得
	int SetHP(int damage);//BossのHPをセット
	void SetShotflag(int index, bool flag);//添字がindexのshotを指定したflagにする
	bool GetSoundshot();//サウンドフラグを取得
	bool GetshotCoordinate(int index, double* x, double* y, int* pattern);//画面にある敵の弾の座標とtypeを取得(enemyクラスの同名の関数にpatternを加えた)
	void SetGrazeflag(int index);//添え字indexの弾のグレイズ判定フラグを立てる
	bool GetGrazeflag(int index);//添え字indexの弾のグレイズ判定フラグを返す
	void All();//実行（Controlで呼び出す)

};

