#include "Enemy.h"
#include "define.h"
#include "Control.h"
#define _USE_MATH_DEFINES
#include <cmath>
#include <cstdlib> 
#include <ctime> 
#define RAD 180

Enemy::Enemy(int type, int shottype, int move_pattern, int shot_pattern, int speed, int intime, int stoptime, int shottime, int outtime, int x, int y, int hp, int item) {

	//引数をそれぞれに代入
	this->enemy_type = type;
	this->shot_type = shottype;
	this->move_pattern = move_pattern;
	this->shot_pattern = shot_pattern;
	this->intime = intime;
	this->stoptime = stoptime;
	this->shottime = shottime;
	this->outtime = outtime;
	this->x = x;
	this->y = y;
	this->hp = hp;
	this->item = item;


	//敵のタイプで読み込む画像を変える
	switch (enemy_type)
	{case 0:
		//ライブラリで画像読み込み
		LoadDivGraph("IMAGE/enemy.png", 3, 3, 1, 32, 32, enemygh);
		width = 32;
		height = 32;
		break;
	case 1:
		//ライブラリで画像読み込み
		LoadDivGraph("IMAGE/enemy2.png", 3, 3, 1, 32, 36, enemygh);
		width = 32;
		height = 36;
		break;
	case 2:
		//ライブラリで画像読み込み
		LoadDivGraph("IMAGE/enemy3.png", 3, 3, 1, 32, 32, enemygh);
		width = 32;
		height = 32;
		break;
	case 3:
		//ライブラリで画像読み込み
		LoadDivGraph("IMAGE/enemy4.png", 3, 3, 1, 32, 32, enemygh);
		width = 32;
		height = 32;
		break;
	default:
		break;
	}


	//弾のタイプで読み込む画像を変える
	int temp = 0;
	switch (shot_type) {
	case 0:
		//ライブラリで画像読み込み
		temp = LoadGraph("IMAGE/enemyshot1.png");
		break;
	case 1:
		//ライブラリで画像読み込み
		temp = LoadGraph("IMAGE/enemyshot2.png");
		break;
	case 2:
		//ライブラリで画像読み込み
		temp = LoadGraph("IMAGE/enemyshot3.png");
		break;
	case 3:
		//ライブラリで画像読み込み
		temp = LoadGraph("IMAGE/enemyshot4.png");
	default:
		break;
	}
	//ライブラリで弾の大崎を取得
	int w, h;
	GetGraphSize(temp, &w, &h);

	//弾初期化
	for (int i = 0; i < ENEMYSHOT_NUM; i++) {
		shot[i].flag = false;
		shot[i].height = h;
		shot[i].width = w;
		shot[i].shotgh = temp;
		shot[i].pattern = shot_pattern;
		shot[i].x = x;
		shot[i].y = y;
		shot[i].speed = speed;
		shot[i].rad = 0;
		shot[i].graflag = false;
	}

	//初期化
	count = 0;
	shotcount = 0;
	shotnumber = 0;
	rad = 0;
	deathflag = false;
	shotflag = false;
	endflag = false;
	soundshot = false;
}


//敵の動き
void Enemy::Move() {
	if (!deathflag) {//生きている時だけ処理
		switch (move_pattern) {//動きのパターンで処理を変える
		case 0://下に動いたら停止して上に戻る
		   //ゲームのループがinttime<game_count<stoptimeなら下に進む
			if (intime < game_count && game_count < stoptime) {
				y += 2;
			}
			else if (game_count > outtime) {//outtimeになったら上に進む
				y -= 2;
			}
			break;

		case 1://上から下に止まらずに動く
			//ゲームのループがinttime=game_countになったら下に進む
			if (intime <= game_count) {
				y += 2;
			}
			break;

		case 2://右下に移動
			 //ゲームのループがinttime=game_countなら下に進む
			if (intime <= game_count) {
				y += 2;
				if (count % 2 == 0) x += 2;
			}
			break;
		case 3://左下に移動
		//ゲームのループがinttime=game_countなら下に進む
			if (intime <= game_count) {
				y += 2;
				if (count % 2 == 0) x -= 2;
			}
			break;
		}
		if (game_count >= stoptime) {
			if (LocateCheck()) {//敵が画面外に行ったら死亡フラグをtrueに
				deathflag = true;
			}
		}
	}
}

//敵は画面内にいるのか
bool Enemy::LocateCheck() {
		if (x < -20 || x> 400 || y < -20 || y>500) {
			return true;
		}
		else {
			return false;
		}
	}


//弾の処理
void Enemy::Shot() {
	 
	//Controlクラスの参照
	Control &control = Control::Instance();
	double px, py;//playerの座標を保持する関数

	//ゲームのループが発射の時刻になったらフラグを立てる
	if (shottime == game_count) shotflag = true;
	
	if (shotflag == true) {//フラグが立っているならば

		soundshot = false;//ショット音フラグをfalseにする

		if (deathflag == false) {//敵が生きている時には弾を発射する準備の処理

			control.PlayerCoordinate(&px,&py);//Playerの位置情報取得
			//始めにplayerと敵の座標から逆正接（単位はラジアン）を求める。
			if (shotcount == 0){
				rad = std::atan2(py - y, px - x);
			}
			switch (shot_pattern) {//弾のパターンで分岐して弾のセットを行う
			case 0: //「10ループごとに1回発射を10発行う(まっすぐ)
				if (shotcount <= 90 && shotcount % 10 == 0) {
					for (int i = 0; i < ENEMYSHOT_NUM; i++) {//フラグが立っていない
						if (shot[i].flag == false) {
							shot[i].flag = true;
							shot[i].x = x;//敵の今の位置
							shot[i].y = y;
							shot[i].rad = rad;// std::atan2(py - y, px - x);
							break;//一発セットしたらbreak
						}
					}
					soundshot = true;//フラグ立てる
				}
				break;
			case 1://playerに向かって9ループに1回発射を10回行う
				if (shotcount <= 81 && shotcount % 9 == 0) {
					for (int i = 0; i < ENEMYSHOT_NUM; i++) {
						if (shot[i].flag == false) {
							shot[i].flag = true;
							shot[i].x = x;//敵の今の位置
							shot[i].y = y;
							shot[i].rad = rad;//std::atan2(py - y, px - x);
							break;//一発セットしたらbreak
						}
					}
					soundshot = true;//フラグ立てる
				}
				break;
			case 2: //10ループに1回発射を５回。3方向に打つ
				if (shotcount <= 40 && shotcount % 10 == 0) {
					for (int i = 0; i < ENEMYSHOT_NUM; i++) {
						if (shot[i].flag == false) {
							shot[i].flag = true;
							shot[i].x = x;
							shot[i].y = y;
							if (shotnumber == 0) {//左よりの方向に
								shot[i].rad = std::atan2(py - y, px - x) - (15 * M_PI / RAD);//10度左に
							}
							else if (shotnumber == 1) {//playerに向かって
								shot[i].rad = std::atan2(py - y, px - x);
							}
							else if (shotnumber == 2) {//右よりの方向に
								shot[i].rad = std::atan2(py - y, px - x) + (15 * M_PI / RAD);//10度右に
							}
							++shotnumber;
							if (shotnumber == 3) {
								shotnumber = 0;
								break;
							}
						}

					}
					soundshot = true;//フラグ立てる
				}
				break;
			case 3://5ループに1回乱射
				if (shotcount % 5 == 0) {
					for (int i = 0; i < ENEMYSHOT_NUM; i++) {
						if (shot[i].flag == false) {
							shot[i].flag = true;
							shot[i].x = x;
							shot[i].y = y;

							//始めに乱数初期化
							if (shotnumber == 0) std::srand((unsigned)time(NULL));//seedの初期化は時間で
							//角度を変える為にatan2で毎度計算する。playerの左右60度の範囲で乱射させる
							shot[i].rad = atan2(py - y, px - x) - (60 * M_PI / RAD) + ((rand() % 120) * M_PI / RAD);
							++shotnumber;
							break;
						}
					}
					soundshot = true;//フラグ立てる
				}

				break;
			}
		}
		//フラグが立っている弾の数
		int shot_flagnum = 0;

		for (int i = 0; i < ENEMYSHOT_NUM; i++) {
			if (shot[i].flag == true) {//フラグが立っているならば弾を移動させる
				switch (shot[i].pattern) {
				case 0://下に発射
					shot[i].y += shot[i].speed;//弾が移動
					break;
				case 1://playerに向かって発射
					shot[i].x += shot[i].speed * cos(shot[i].rad);
					shot[i].y += shot[i].speed * sin(shot[i].rad);
					break;
				case 2://playerに向かって発射
					shot[i].x += shot[i].speed * cos(shot[i].rad);
					shot[i].y += shot[i].speed * sin(shot[i].rad);
					break;
				case 3://playerに向かって発射
					shot[i].x += shot[i].speed * cos(shot[i].rad);
					shot[i].y += shot[i].speed * sin(shot[i].rad);
					break;
				}

				//弾が画面外
				if (ShotLocateCheck(i) == true) {
					shot[i].flag = false;//フラグを戻す
					continue;//shot_numを追加しない
				}
				++shot_flagnum;//発射中の弾を数える
			}
		}

		//発射中の弾がなくdeathflagが立っている
		if (shot_flagnum == 0 && deathflag == true) {
			endflag = true;
		}

		++shotcount;//弾発射中のループカウント


	}
}

//敵の死亡したフラグを立てる
void Enemy::SetDeathflag() {
	deathflag = true;
}

//敵が死んだかのフラグを返す
bool Enemy::GetDeathflag() {
	return deathflag;
}

//弾を打つ音を出すかのフラグを返す
bool Enemy::GetSoundshot() {
	return soundshot;
}

//弾が画面内にある？
bool Enemy::ShotLocateCheck(int i) {
	if (shot[i].x < -10 || shot[i].x>420 || shot[i].y < -10 || shot[i].y>490) {
		return true;
	}
	else {
		return false;
	}
}

//敵と弾の描画
void Enemy::Draw() {

	//弾描画
	for (int i = 0; i < ENEMYSHOT_NUM; i++) {
		if (shot[i].flag) {
			if (shot_type == 0 || shot_type == 2) {//ライブラリで0と2の弾はそのまま（(x,y)が画像の中心になるように）
				DrawGraph((int)shot[i].x - shot[i].width / 2, (int)shot[i].y - shot[i].height / 2, shot[i].shotgh, TRUE);
			}
			else if (shot_type == 1 || shot_type == 3) {//ライブラリでrad+90度回転させて描画
				DrawRotaGraph((int)shot[i].x, (int)shot[i].y, 1.0, shot[i].rad + (90 * M_PI / RAD), shot[i].shotgh, TRUE);

			}
		}
	}

	//敵描画
	int number;

	if (deathflag == false) {//敵が死んでいない
		number = count % 40 / 10;//0,1,2,3と動く
		if (number == 3)number = 1;//0,1,2,1と動くようにする
		//ライブラリで描画
		DrawGraph((int)x-width/2, (int)y-height/2, enemygh[number], TRUE);//描画
	}
}

//敵の位置を引数に与える
void Enemy::GetCoordinate(double* x, double* y) {
	*x = this->x;//ポインタに敵のx座標を与える
	*y = this->y;//ポインタに敵のy座標を与える

}

//敵の位置を引数に与える
bool Enemy::GetshotCoordinate(int index, double* x, double* y) {
	if (shot[index].flag) {
		*x = shot[index].x;//x座標
		*y = shot[index].y;//y座標
		return true;//画面上にある時はtrueを返す
	}
	else {
		return false;//画面にないならfalse
	}
}

//添え字indexの弾が発射されたかのフラグをflagにする
void Enemy::SetShotflag(int index, bool flag) {
	shot[index].flag = flag;
}

//敵のタイプを返す
int Enemy::GetEnemytype() {
	return enemy_type;
}

//弾のタイプを返す
int Enemy::GetShottype() {
	return shot_type;
}

//アイテムの種類を返す
int Enemy::GetItem() {
	return item;
}

//添字indexのグレイズ判定フラグを立てる
void Enemy::SetGrazeflag(int index) {
	shot[index].graflag = true;
}


//添字indexのグレイズ判定フラグを返す
bool Enemy::GetGrazeflag(int index) {
	return shot[index].graflag;
}

//全体の処理をする関数
bool Enemy::All() {
	Move();
	Shot();
	Draw();
	++count;

	return endflag;
}
