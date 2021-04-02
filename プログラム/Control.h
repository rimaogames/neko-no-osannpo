#pragma once
#include "define.h"
#include "SceneBase.h"
#include "Player.h"
#include "Back.h"
#include "Enemy.h"
#include "Graze.h"
#include "Score.h"
#include "Item.h"
#include "Boss.h"


//ゲーム全体の処理
class Control:public SceneBase
{
private:
	//各クラスの生成（ポインタ）
	Player* player;
	Back* back;
	Enemy* enemy[ENEMY_NUM];
	Boss* boss;
	Graze* graze[GRAZE_NUM];
	Item* item[ITEM_NUM];
	Score* score;
	ENEMY_DATA data[ENEMY_NUM];
	int sound_eshot;//敵のショットサウンドハンドル
	int sound_pshot;//playerのショットサウンドハンドル
	int sound_pdamage;//playerのダメージサウンドハンドル
	int sound_edeath;//敵の死んだ音のサウンドハンドル
	int sound_graze;//グレイズのサウンドハンドル
	int sound_item;//アイテム取得音のサウンドハンドル
	int sound_gameover;//ゲームオーバーのサウンドハンドル
	int sound_gameclear;//ゲームクリアのサウンドハンドル
	int bgm;//bgmのサウンドハンドル
	int bossbgm;//boss曲のサウンドハンドル


	bool eshot_flag;//敵ショットの音を出すかのフラグ
	bool pshot_flag;//playerショットの音を出すかのフラグ
	bool pdamage_flag;//敵がダメージを食らったかの音フラグ
	bool edeath_flag;//敵が死んでるかの音フラグ
	bool graze_flag;//グレイズ音を出すかのフラグ
	bool itemsound_flag;//アイテム取得音を出すかのフラグ 
	bool gameover_soundflag;//ゲームオーバーの音を出すかのフラグ
	bool gameclear_soundflag;//ゲームクリアの音を出すかのフラグ
	bool boss_soundflag;//ボス曲を流すかのフラグ

	int edeath_efegh[10];//死亡時エフェクト画像ハンドル(敵）
	int eefewidth, eefeheight;//敵死亡エフェクト画像大きさ
	int pdeath_efegh[8];//死亡時エフェクト画像ハンドル(player）
	int pefewidth, pefeheight;//player死亡エフェクト画像大きさ
	int eefecount, pefecount;//死んでからのカウント(敵、player)
	//クレジット関係の画像ハンドル
	int title;//タイトル
	int bgmgh;//音楽
	int image;//画像

	int gameovergh;//ゲームオーバーの画像
	int cleargh;//ゲームクリアの画像
	int backmenu;//メニューに戻る案内画像
	int gamestartgh;//ゲームスタート文字の画像



	int deathenemy_num;//死んだ敵の添字
	double deathenemy_x, deathenemy_y; //敵の死亡場所を取得用の変数
	bool eefe_flag;//死亡エフェクトを出すかのフラグ(敵）
	bool pefe_flag;//死亡エフェクトを出すかのフラグ(player)
	bool befe_flag;//死亡エフェクトを出すかのフラグ(Boss)

	int FirstBossHP; //ボスの初期体力を保持する関数

	bool now_game;//ゲームをプレイ中か
	bool end_flag;//ゲームが終わったか
	bool game_over;//ゲームオーバーか
	bool gameclear;//ゲームクリア


private:
	Control();//コンストラクタ（シングルトンパターン)
	~Control();//デストラクタ
	void SoundAll();
	void EFECTALL();
	void EnemyAllJudge();
	void BossAllJudge();
	//円形のあたり判定
	bool CircleJudge(double pcir, double ecir, double pcir_x, double ecir_x, double pcir_y, double ecir_y);
public:
	void Update();
	void Initialize();
	void Finalize();
	void All();//Menuで呼び出す関数(オーバーライド）
	void PlayerCoordinate(double* x, double* y);//playerの座標を取得
	void EnemyCoordinate(int index, double* x, double* y);//敵（添字index)の座標を取得
	void BossCoordinate(int index, double* x, double* y);//敵（添字index)の座標を取得
	void GetResult(int* x, int* y,int* z);//最終結果を取得
	int GetHiscore();//ハイスコアを取得
	static Control& Instance() {//クラス静的変数、自身のインスタンスを格納
		static Control control;//静的変数として宣言
		return control;
	}


};

