#include "Boss.h"
#include "Control.h"
#define _USE_MATH_DEFINES
#include <cmath>
#define RAD 180

Boss::Boss() {
	//座標の初期位置
	x = 200;
	y = -100;
	pre_x = 200; 
	pre_y = -100;

	//ライブラリで画像読み込み
	bossgh[0] = LoadGraph("IMAGE/boss.png");
	bossgh[1] = LoadGraph("IMAGE/boss.png");

	shotgh[0] = LoadGraph("IMAGE/enemyshot3.png");
	shotgh[1] = LoadGraph("IMAGE/enemyshot2.png");
	shotgh[2] = LoadGraph("IMAGE/enemyshot4.png");

	//ライブラリで画像の大きさを取得
	GetGraphSize(shotgh[0], &w, &h);
	GetGraphSize(shotgh[1], &w1, &h1);
	GetGraphSize(shotgh[2], &w2, &h2);

	//弾shot構造体の初期化
	for (int i = 0; i < BOSSSHOT_NUM; i++) {
		shot[i].flag = false;
		shot[i].graflag = false;
		shot[i].shotgh = 0;
		shot[i].pattern = 0;
		shot[i].rad = 0;
		shot[i].height = 0;
		shot[i].width = 0;
		shot[i].x = 0;
		shot[i].y = 0;
		shot[i].speed = 0;
	}

    //初期化 
	rise = 2;  //振動の速さは2とする
	rise2 = 2;
	hp = BOSS_HP;
	pre_hp = BOSS_HP;
	angle = 0;
	move_pattern = 0;
	shot_pattern = 0;
	pre_move_pattern = 0;
	pre_shot_pattern = 0;
	shotcount = 0;
	move_x = 0;
	move_y = 180;//最初の移動距離は180とする
	waitcount = 0;
	wait = false;
	p3_state = 0;
	nodamage_flag = false;
	soundshot = false;
	live_flag = false;
	shot_flag = false;

}


//生存フラグをfにする
void Boss::SetFlag(bool f)
{
	live_flag = f;
}


//生存フラグを返す
bool Boss::GetFlag()
{
	return live_flag;
}

//移動
void Boss::Move() {

	switch (move_pattern) {//移動パターンで処理を変える
	case 0:
		Appear();//ボスの登場
		break;
	case 1:
		MovePattern1();//ふわふわ上下に運動する
		break;
	case 2:
		MovePattern2();//左右に動く
		break;
	case 3:
		MovePattern3();//三角形型に動く
		break;
	case 4:
		MoveDefalt();//デフォルト位置に戻る
		break;
	}
}


//出現
void Boss::Appear() {
	double temp;

	//角度を2°ずつ増やす
	angle += 2;
	//angleをラジアンに変えてsin値（0～1)を得る
	temp = sin(angle * M_PI / RAD);

	//上から移動するだけ＝xは変化無し
	x = 200;

	//座標ｙを計算　前のy座標 + sin値 *　目的地までのyの距離 
	y = pre_y + temp * move_y;

	if (angle == 90) {//90°まで行ったらpatter1の動きに進んで弾を打つ
		move_pattern = 1;
		angle = 0;
		shot_flag = true;
	}
}


//移動パターン1
void Boss::MovePattern1() {
	//角度を2°(-2°）ずつ増やす
	angle += rise;

	x = 200;

	//中心位置(80)＋sin値*振れ幅
	y = 80 + sin(angle * M_PI / RAD) * BOSS_SHAKE;

	if (angle == 90 || angle == -90) {
		rise = ~rise;//増加量反転
	}
}

//移動パターン2
void Boss::MovePattern2() {
	if (!wait) {
		x += rise2;
		if (x == 40) {//左端までいったら
			rise2 = 2;//反転
			wait = true;//停止フラグを立てる

		} else if( x==360) {//右端までいったら
			rise2 = -2; //反転
			wait = true; //停止フラグを立てる
		}
     }

	if (wait) {//10カウントだけ停止
		++waitcount;
		if (waitcount == 10) {
			wait = false;
			waitcount = 0;
		}
	}
}


//移動パターン3
void Boss::MovePattern3() {
	double temp;

	//角度を2°(-2°）ずつ増やす
	angle += 2;
	temp = sin(angle * M_PI / RAD);

	//座標を計算　前のx,y座標 + sin値 *　目的地までのx,yの距離 
	x = pre_x + temp * move_x;
	y = pre_y + temp * move_y;

	if (angle == 90) {//sin値＝１だから目的地まで移動したから目的地を変える
		if (p3_state == 0) {//左へ移動
			MoveInit(70, 80, 1);
		}
		else if (p3_state == 1) {//真ん中へ移動
			MoveInit(200, 160, 2);
		}
		else {
			MoveInit(330, 80, 0);//右へ移動
		}
	}
}


//デフォルト位置に動く
void Boss::MoveDefalt() {
	double temp;

	angle += 2;

	temp = sin(angle * M_PI / 180);

	x = pre_x + temp * move_x;
	y = pre_y + temp * move_y;

	if (angle == 90) {//sin値＝１だから目的地まで移動したから目的地を変える
		SetMovepattern(pre_move_pattern + 1);
		SetShotpattern(pre_shot_pattern + 1);
		nodamage_flag= false;

		if (move_pattern == 3)MoveInit(200, 160, 2);
	}

}

//angle,pre_x,pre_y,move_x,move_yを設定
void Boss::SetDamage() {
	//前回の座標をセット
	pre_x = x;
	pre_y = y;
	//現在位置から目的地までの距離
	move_x = 200 - x;
	move_y = 80 - y;

	angle = 0;

	nodamage_flag = true;

	//デフォルト位置に戻るからパターン4に進む
	SetMovepattern(4);
	SetShotpattern(3);

}


//移動パターンを変更
void Boss::SetMovepattern(int pattern) {
	pre_move_pattern = move_pattern;//現在の移動パターンをpre_move_patternに与える
	move_pattern = pattern;//パターン変更
}


//弾パターンを変更
void Boss::SetShotpattern(int pattern) {
	pre_shot_pattern = shot_pattern;//現在の弾パターンをpre_move_patternに与える
	shot_pattern = pattern;//パターン変更
}


//移動目的地変更
void Boss::MoveInit(double ix, double iy, int state) {
	//現在の座標を代入
	pre_x = this->x;
	pre_y = this->y;
	//目的地までの移動きょり
	move_x = ix - this->x;
	move_y = iy - this->y;
	//角度の初期化と次の目的地を与える
	angle = 0;
	p3_state = state;

}


//弾を打つ
void Boss::Shot() {
	int index = 0;//空いている弾の添字
	int shotnum=0; //弾を打ってからのカウント
	static double rad;//角度（ラジアン）弾の発射時に使用
	bool scount_flag = false;//shotcountを初期化するかどうか
	double px, py; //playerの座標を保持する変数


	//Controlクラスの参照
	Control &control = Control::Instance();

		soundshot = false;

		if (nodamage_flag) {//ダメージが一定数食らったらshotcountを0に戻す
			scount_flag = true;
		}
		
			control.PlayerCoordinate(&px, &py);//プレイヤの位置を取得

			if (shotcount == 0)rad = std::atan2(py - y, px - x);//弾の打ち始めに角度（ラジアン）を計算

			switch (shot_pattern) {
			case 0://放射状に10ループに1回25発打つ
				if (shotcount % 10 == 0) {//プレイヤーの周り（前後30度）に4ループに1初打つ
					while ((index = ShotSearch()) != -1) {//弾の準備
						shot[index].pattern = 0;
						shot[index].shotgh = shotgh[2];
						shot[index].width = w2;
						shot[index].height = h2;
						shot[index].speed = 4;
						//プレイヤーの位置+360度の範囲で30方向に打つ
						shot[index].rad = atan2(py - y, px - x) + ((double)shotnum * 12 * M_PI / RAD);//360÷30=12
						++shotnum;
						if (shotnum == 30)break;
						soundshot = true;//弾を打つ音を鳴らすフラグを立てる
					}
				}
				break;
			case 1://プレイヤーの周りに弾を定期的に打つ
				if (shotcount % 10 == 0 && shotcount <= 40) {//ル-プカウント0,6,12,18の4回打つ
					while ((index = ShotSearch()) != -1) {//空きがある弾の添字を取得する(-1の時は弾の空きがない）
						shot[index].pattern = 1;
						shot[index].shotgh = shotgh[0];
						shot[index].width = w;
						shot[index].height = h;
						shot[index].speed = 6;
						//一回に6発打つ

						if (shotnum == 0) {//プレイヤーの位置から30度左
							shot[index].rad = rad - (30 * M_PI / RAD);
						}
						else if (shotnum == 1) {//プレイヤーの位置から15度左
							shot[index].rad = rad - (15 * M_PI / RAD);
						}
						else if (shotnum == 2) {//プレイヤーの位置
							shot[index].rad = rad;
						}
						else if (shotnum == 3) {//プレイヤーの位置から15度右
							shot[index].rad = rad + (15 * M_PI / RAD);
						}
						else if (shotnum == 4) {//プレイヤーの位置から30度右
							shot[index].rad = rad + (30 * M_PI / RAD);
						}



						soundshot = true;//弾を打つ音を鳴らすフラグを立てる

						++shotnum;
						if (shotnum == 5)break;
					}
				}

				break;
			case 2://プレイヤーの周り（前後30度）に4ループに1初打つ
				if (shotcount % 4 == 0) {
					if ((index = ShotSearch()) != -1) {
						shot[index].pattern = 2;
						shot[index].shotgh = shotgh[1];
						shot[index].width = w1;
						shot[index].height = h1;
						shot[index].speed = 5;
						//プレイヤーの位置＋(-30～30の範囲の乱数)度
						shot[index].rad = atan2(py - y, px - x) + (double)(rand() % 61-30) * M_PI / RAD;

						soundshot = true;//弾を打つ音を鳴らすフラグを立てる
					}
				}
				break;

			default:
				break;
			}



			for (int i = 0; i < BOSSSHOT_NUM; i++) {
				if (shot[i].flag == true) {//フラグが立っているならば弾を移動させる
					switch (shot[i].pattern) {
					case 0:
						shot[i].x += shot[i].speed * cos(shot[i].rad);
						shot[i].y += shot[i].speed * sin(shot[i].rad);
						break;

					case 1://playerに向かって発射
						shot[i].x += shot[i].speed * cos(shot[i].rad);
						shot[i].y += shot[i].speed * sin(shot[i].rad);

						if (!scount_flag && shotcount == 60) scount_flag = true;//打ったら60までは待機してcountを戻す
						break;
					case 2:
						shot[i].x += shot[i].speed * cos(shot[i].rad);
						shot[i].y += shot[i].speed * sin(shot[i].rad);

						break;

					default:
						break;
					}

					if (ShotLocateCheck(i))shot[i].flag = false;
				}
			}

			++shotcount;

			if (scount_flag)shotcount = 0;//フラグが立っているならは0にする
		
		
	
}


//弾の構造体のなかで空きがある添え字を返す
int Boss::ShotSearch() { 
	bool do_setting = false;//設定をしたか（現在空きの弾があるのか）
	int i;
	for (i = 0; i < BOSSSHOT_NUM; i++) {
		if (!shot[i].flag) {//フラグが立っていない弾が会ったら
			shot[i].flag = true;//フラグ立てる
			shot[i].x = x;
			shot[i].y = y;
			do_setting = true;
			break;
		}
	}
    if (!do_setting) {//設定をしてないならば
			i=-1;//-1を返すようにする
	}
			return i;//設定した添え字or空きがないなら-1を返す
		
}

//弾が画面内にある？
bool Boss::ShotLocateCheck(int i) {
	if (shot[i].x < -10 || shot[i].x>420 || shot[i].y < -10 || shot[i].y>490) {
		return true;
	}
	else {
		return false;
	}
}

//弾の位置をポインタに与える（成功？失敗？を返す）
bool Boss::GetshotCoordinate(int index, double* x, double* y, int* pattern) {
	if (shot[index].flag == true) {
		*x = shot[index].x;
		*y = shot[index].y;
		*pattern = shot[index].pattern;
		return true;
	}
	else {
		return false;
	}
}


//Bossの位置をポインタに与える
void Boss::GetCoordinate(double* x, double* y) {
		*x = this->x;//ポインタにBossのx座標を与える
		*y = this->y;//ポインタにBossのy座標を与える

	}

//BossのHPの設定
int Boss::SetHP(int damage) {


	//hpからdamageを削って返す
	pre_hp = hp;
	hp -=damage;

	return hp;
}


//１つ前のＨＰを返す
int Boss::GetPreHP() {
	return pre_hp;
}

//今ま無敵時間かを返す
bool Boss::GetNodamageFlag() {
	return nodamage_flag;
}


//グレイズのフラグを返す
bool Boss::GetGrazeflag(int index) {
	return shot[index].graflag;
}


//グレイズのフラグ(グレイズ判定が通った）を返す
void Boss::SetGrazeflag(int index) {
	shot[index].graflag = true;
}

//添え字indexの弾の出現中フラグをflagにする
void Boss::SetShotflag(int index, bool flag) {
	shot[index].flag = flag;
}
//弾を打つおとを鳴らすかどうかのフラグを返す
bool Boss::GetSoundshot() {
	return soundshot;
}

//描画
void Boss::Draw() {
	//弾の描画
	for (int i = 0; i < BOSSSHOT_NUM; i++) {
		//フラグが立っている弾は描画。ライブラリで描画
		if (shot[i].flag) DrawRotaGraph((int)shot[i].x, (int)shot[i].y, 1.0, shot[i].rad + 90 * M_PI / 180, shot[i].shotgh, TRUE);
	}

	if (live_flag) {//生きている
		//Bossの描画
		if (nodamage_flag) {//ライブラリで無敵状態は明るく描画
			DrawRotaGraph(x, y, 1.0, 0, bossgh[1], TRUE);
		}
		else {//ライブラリでボスの描画
			DrawRotaGraph(x, y, 1.0, 0, bossgh[0], TRUE);
		}

	}
}

//Controlで呼び出す関数
void Boss::All() {
	Move();//動く

	if (shot_flag)Shot();//フラグが立っている弾は書く
	Draw();
}