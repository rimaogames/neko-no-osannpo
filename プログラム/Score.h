#pragma once
#include "define.h"

//右に描画するハイスコア、スコア、グレイズ、HP、パワーの処理
class Score
{
private:
	int g_highscore, g_score, g_graze, g_hp, g_power;//ボードのグラフィックハンドル
	int g_number[10];//数字のグラフィックハンドル
	int high_score;//ハイスコア
	int score;//今のスコア
	int graze_score;//グレイズのスコア
	int life;//ライフ
	int power;
private:
	void Draw();//値描画
public:
	Score();//コンストラクタ
	void SetScore(SCOREDATA data, int a);//スコアのせってい(指定したSCOREDATAにaを足す）(lifeの時はlife=aに設定)
	int GetScore(SCOREDATA data);//スコアの取得
	void All();//実行
};

