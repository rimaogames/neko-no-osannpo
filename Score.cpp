#include "Score.h"
#include "define.h"
#include <string>
Score::Score() {

	//ライブラリで画像読み込み
	g_highscore = LoadGraph("IMAGE/highscore.png");
	g_score = LoadGraph("IMAGE/score.png");
	g_graze = LoadGraph("IMAGE/b_graze.png");
	g_hp = LoadGraph("IMAGE/HP.png");
	g_power = LoadGraph("IMAGE/power.png");
	LoadDivGraph("IMAGE/number.png",10,10,1,17,29,g_number);
	
	//初期化
	high_score = 0;
	score = 0;
	graze_score = 0;
	life = 0;
	power = 0;
}

//描画
void Score::Draw() {
	char buf[100];
	memset(buf, 0, sizeof(buf));

	int h_num,s_num,g_num,l_num,p_num;//ハイスコア、スコア、グレイズ、life,powerの文字数を入れる用
	//ライブラリ、座標(引数１,引数２)に引数３を書く。引数４＝画像の透明度を有効にするかどうか
	DrawGraph(SCORE_X, 10,g_highscore, TRUE);
	DrawGraph(SCORE_X, 90, g_score, TRUE);
	DrawGraph(SCORE_X, 170, g_graze, TRUE);
	DrawGraph(SCORE_X, 240, g_hp, TRUE);
	DrawGraph(SCORE_X, 300, g_power, TRUE);

	h_num = sprintf_s(buf, "%d", high_score);//bufにハイスコアを入れる。numには文字数が入る
	for (int i = 0; i < h_num; i++) {
		//ライブラリで値の書き始めはSOCRE_X+20。にy座標45に数字を記入。
		//bufには1バイトずつ数字が格納されている。g_number[buf[i]-0]で数字のbuf[i]-を取得
		DrawGraph((SCORE_X + 20) + (i * NUMBER_LONG), 45, g_number[buf[i] - '0'], TRUE);
	}
	//以下同様

	s_num = sprintf_s(buf, "%d", score);//bufにスコアを入れる。s_numには文字数が入る
	for (int i = 0; i < s_num; i++) {
		//
		DrawGraph((SCORE_X + 20) + (i * NUMBER_LONG), 125, g_number[buf[i] - '0'], TRUE);
	}

	g_num = sprintf_s(buf, "%d", graze_score);//bufにグレイズを入れる。g_numには文字数が入る
	for (int i = 0; i < g_num; i++) {
		DrawGraph((SCORE_X + 20) + (i * NUMBER_LONG), 200, g_number[buf[i] - '0'], TRUE);
	}

	l_num = sprintf_s(buf, "%d", life);//bufにlifeを入れる。l_numには文字数が入る
	for (int i = 0; i < l_num; i++) {
		DrawGraph((SCORE_X +20)+ (i * NUMBER_LONG), 270, g_number[buf[i] - '0'], TRUE);
	}

		p_num = sprintf_s(buf, "%d", power);//bufにpowerを入れる。p_numには文字数が入る
	for (int i = 0; i < p_num; i++) {
		DrawGraph((SCORE_X + 20) + (i * NUMBER_LONG), 330, g_number[buf[i] - '0'], TRUE);
	}



}
//引数の種類の値を設定
void Score::SetScore(SCOREDATA data, int a) {//指定したSCOREDATAにaを足す
	switch (data) {//dataの内容で変える
	case SCOREDATA::HIGH_SCORE://ハイスコア設定
		high_score = a;
		break;
	case SCOREDATA::SCORE://スコア設定
		score += a;
		break;
	case SCOREDATA::GRAZE_SCORE://グレイズスコア設定
		graze_score += a;
		break;
	case SCOREDATA::LIFE:
		life  = a;//lifeをaの値に設定
		if (life < 0)life = 0;
		break;
	case SCOREDATA::POWER:
		power = a;
	}
}

//引数の種類の値を取得
int Score::GetScore(SCOREDATA data) {
	switch (data) {
	case SCOREDATA::HIGH_SCORE:
		return high_score;
		break;
	case SCOREDATA::SCORE:
		return score ;
		break;
	case SCOREDATA::GRAZE_SCORE:
		return graze_score;
		break;
	case SCOREDATA::LIFE:
		return life;
		break;
	case SCOREDATA::POWER:
		return power;
		break;
	}

	//当てはまらないなら-1
	return -1;
}

//controlで呼び出される実行関数
void Score::All() {
	Draw();
}