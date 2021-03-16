#pragma once
#include "DxLib.h"
#include <Windows.h>

//メッセージボックス
#define MSG(m){\
MessageBoxA(NULL,m, "メッセージ", MB_OK);}
//プレイヤーの歩くスピード
#define PLAYER_SPEED 4
//画面スクロールのスピード
#define SCROOL_SPEED 2
//プレイヤーの弾の画面中の弾数
#define PLAYERSHOT_NUM 50
//敵の数
#define ENEMY_NUM 142
//敵の弾の数
#define ENEMYSHOT_NUM 50
//ボスの弾の数
#define BOSSSHOT_NUM 300
//ボスのHP
#define BOSS_HP 400
//ボスの出現時間
#define BOSSTIME 7400
//ボスの横移動の振れ幅
#define BOSS_SHAKE 20;
//グレイズの数
#define GRAZE_NUM 50
//弾の速さ
#define SHOT_SPEED 13
//画面の大きさ
#define WIDTH 400
#define HEIGHT 480

//当たり判定用の定義
#define PLAYER_RADIUS 4
#define ENEMY_RADIUS 10
#define BOSS_RADIUS 40
#define PLAYSHOT_RADIUS 4
#define ENESHOT1_RADIOUS 3
#define ENESHOT2_RADIOUS 3
#define ENESHOT3_RADIOUS 2
#define ENESHOT4_RADIOUS 2
//グレイズ当たり判定用の定義
#define GRAZE_RADIUS 18
//アイテムの当たり判定用半径
#define ITEM_RADIOUS 20
//アイテムの総数(一画面に存在する）
#define ITEM_NUM 30
//スコアを書くx座標
#define SCORE_X 420
//数字1文字の幅　17
#define NUMBER_LONG 17

struct SHOT {//弾の構造体
	double x, y;//座標
	int shotgh;//グラフィックハンドル
	int width, height;//画像の大きさ
	bool flag;//弾が発射中が否か
};
struct ENE_SHOT {//敵の弾
	double x, y;//座標
	double rad; //角度ラジアン=角度*π/180
	int shotgh;//グラフィックハンドル
	int width, height;//画像の大きさ
	int pattern;//弾の種類
	int speed;//弾の種類
	bool flag;//弾が発射中が否か
	bool graflag;//グレイズ判定フラグ（かすったかどうか）

};

struct ENEMY_DATA {
	int type;//敵の種類
	int shottype;//弾の種類
	int move_pattern;//移動パターン
	int shot_pattern;//弾のパターン
	int speed;//弾のスピード
	int intime;//出現する時刻
	int stoptime;//停止時間
	int shottime; //弾を発射する時刻
	int outtime;//帰還する時刻
	int x;//x座標
	int y;//y座標
	int hp;//HP
	int item;//アイテム
};

enum class SCOREDATA {//列挙型
	HIGH_SCORE,  //ハイスコア
	SCORE,       //スコア
	GRAZE_SCORE,//グレイズ
	LIFE,      //HP
	POWER      //パワー
};




extern int game_count;//ゲームが始まってから何ループ目？
extern int hiscore;//全体でのハイスコアは？