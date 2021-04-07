#include "Boss2.h"
#include "Config.h"
#define _USE_MATH_DEFINES
#include <cmath>
#define RAD 180

Boss2::Boss2() {
	//座標の初期位置
	x = 200;
	y = -100;
	pre_x = 200;
	pre_y = -100;

	//ライブラリで画像読み込み
	bossgh2[0] = LoadGraph("IMAGE/boss2.png");
	bossgh2[1] = LoadGraph("IMAGE/damageboss2.png");

	shotgh2[0] = LoadGraph("IMAGE/enemyshot3.png");
	shotgh2[1] = LoadGraph("IMAGE/enemyshot2.png");
	shotgh2[2] = LoadGraph("IMAGE/enemyshot4.png");

	//ライブラリで画像の大きさを取得
	GetGraphSize(shotgh2[0], &w, &h);
	GetGraphSize(shotgh2[1], &w1, &h1);
	GetGraphSize(shotgh2[2], &w2, &h2);

	//弾shot構造体の初期化
	for (int i = 0; i < BOSSSHOT_NUM; i++) {
		bshot[i].flag = false;
		bshot[i].graflag = false;
		bshot[i].shotgh = 0;
		bshot[i].pattern = 0;
		bshot[i].rad = 0;
		bshot[i].height = 0;
		bshot[i].width = 0;
		bshot[i].x = 0;
		bshot[i].y = 0;
		bshot[i].speed = 0;
	}

	//初期化 
	rise = 2;  //振動の速さは2とする
	rise2 = 2;
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
	shot_flag = false;
	live_flag = false;
	//難易度でボスの体力を変える
	switch (Config::select_dif) {
	case Easy:
		hp = EBOSS_HP;
		pre_hp = EBOSS_HP;
		break;
	case Normal:
		hp = NBOSS_HP;
		pre_hp = NBOSS_HP;
		break;
	case Hard:
		hp = HBOSS_HP;
		pre_hp = HBOSS_HP;
		break;

	}

}
//移動
void Boss2::Move() {

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

//移動パターン1
void Boss2::MovePattern1() {
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
void Boss2::MovePattern2() {
	if (!wait) {
		x += rise2;
		if (x == 40) {//左端までいったら
			rise2 = 2;//反転
			wait = true;//停止フラグを立てる

		}
		else if (x == 360) {//右端までいったら
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
void Boss2::MovePattern3() {
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
void Boss2::MoveDefalt() {
	double temp;

	angle += 2;

	temp = sin(angle * M_PI / 180);

	x = pre_x + temp * move_x;
	y = pre_y + temp * move_y;

	if (angle == 90) {//sin値＝１だから目的地まで移動したから目的地を変える
		SetMovepattern(pre_move_pattern + 1);
		SetShotpattern(pre_shot_pattern + 1);
		nodamage_flag = false;

		if (move_pattern == 3)MoveInit(200, 160, 2);
	}
}

//弾を打つ
void Boss2::Shot() {
	int index = 0;//空いている弾の添字
	int shotnum = 0; //弾を打ってからのカウント
	static double rad;//角度（ラジアン）弾の発射時に使用
	bool scount_flag = false;//shotcountを初期化するかどうか
	double px, py; //playerの座標を保持する変数


	//Controlクラスの参照
	Control& control = Control::Instance();

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
				bshot[index].pattern = 0;
				bshot[index].shotgh = shotgh2[2];
				bshot[index].width = w2;
				bshot[index].height = h2;
				bshot[index].speed = 4;
				//プレイヤーの位置+360度の範囲で30方向に打つ
				bshot[index].rad = atan2(py - y, px - x) + ((double)shotnum * 12 * M_PI / RAD);//360÷30=12
				++shotnum;
				if (shotnum == 30)break;
				soundshot = true;//弾を打つ音を鳴らすフラグを立てる
			}
		}
		break;
	case 1://プレイヤーの周りに弾を定期的に打つ
		if (shotcount % 10 == 0 && shotcount <= 40) {//ル-プカウント0,6,12,18の4回打つ
			while ((index = ShotSearch()) != -1) {//空きがある弾の添字を取得する(-1の時は弾の空きがない）
				bshot[index].pattern = 1;
				bshot[index].shotgh = shotgh2[0];
				bshot[index].width = w;
				bshot[index].height = h;
				bshot[index].speed = 6;
				//一回に6発打つ

				if (shotnum == 0) {//プレイヤーの位置から30度左
					bshot[index].rad = rad - (30 * M_PI / RAD);
				}
				else if (shotnum == 1) {//プレイヤーの位置から15度左
					bshot[index].rad = rad - (15 * M_PI / RAD);
				}
				else if (shotnum == 2) {//プレイヤーの位置
					bshot[index].rad = rad;
				}
				else if (shotnum == 3) {//プレイヤーの位置から15度右
					bshot[index].rad = rad + (15 * M_PI / RAD);
				}
				else if (shotnum == 4) {//プレイヤーの位置から30度右
					bshot[index].rad = rad + (30 * M_PI / RAD);
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
				bshot[index].pattern = 2;
				bshot[index].shotgh = shotgh2[1];
				bshot[index].width = w1;
				bshot[index].height = h1;
				bshot[index].speed = 5;
				//プレイヤーの位置＋(-30～30の範囲の乱数)度
				bshot[index].rad = atan2(py - y, px - x) + (double)(rand() % 61 - 30) * M_PI / RAD;

				soundshot = true;//弾を打つ音を鳴らすフラグを立てる
			}
		}
		break;

	default:
		break;
	}



	for (int i = 0; i < BOSSSHOT_NUM; i++) {
		if (bshot[i].flag == true) {//フラグが立っているならば弾を移動させる
			switch (bshot[i].pattern) {
			case 0:
				bshot[i].x += bshot[i].speed * cos(bshot[i].rad);
				bshot[i].y += bshot[i].speed * sin(bshot[i].rad);
				break;

			case 1://playerに向かって発射
				bshot[i].x += bshot[i].speed * cos(bshot[i].rad);
				bshot[i].y += bshot[i].speed * sin(bshot[i].rad);

				if (!scount_flag && shotcount == 60) scount_flag = true;//打ったら60までは待機してcountを戻す
				break;
			case 2:
				bshot[i].x += bshot[i].speed * cos(bshot[i].rad);
				bshot[i].y += bshot[i].speed * sin(bshot[i].rad);

				break;

			default:
				break;
			}

			if (ShotLocateCheck(i))bshot[i].flag = false;
		}
	}

	++shotcount;

	if (scount_flag)shotcount = 0;//フラグが立っているならは0にする



}

//描画
void Boss2::Draw() {
	//弾の描画
	for (int i = 0; i < BOSSSHOT_NUM; i++) {
		//フラグが立っている弾は描画。ライブラリで描画
		if (bshot[i].flag) DrawRotaGraph((int)bshot[i].x, (int)bshot[i].y, 1.0, bshot[i].rad + 90 * M_PI / 180, bshot[i].shotgh, TRUE);
	}

	if (live_flag) {//生きている
		//Bossの描画
		if (nodamage_flag) {//ライブラリで無敵状態は明るく描画
			DrawRotaGraph(x, y, 1.0, 0, bossgh2[1], TRUE);
		}
		else {//ライブラリでボスの描画
			DrawRotaGraph(x, y, 1.0, 0, bossgh2[0], TRUE);
		}

	}
}

//Controlで呼び出す関数
void Boss2::All() {
	Move();//動く

	if (shot_flag)Shot();//フラグが立っている弾は書く
	Draw();
}