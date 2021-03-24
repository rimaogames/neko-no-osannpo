#include "Player.h"
#include "define.h"
#include "InputKey.h"
#include "Config.h"
//コンストラクタ
Player::Player()
{
	//ライブラリでplayer画像読み込み
	if (LoadDivGraph("IMAGE/Player.png", 12, 3, 4, 32, 32, playergh) == -1) {
		MSG("エラー発生");
	}
	if (LoadDivGraph("IMAGE/player2.png", 12, 3, 4, 32, 32, playergh2) == -1) {
		MSG("エラー発生");
	}
	//player画像の大きさ
	width = 32;
	height = 32;

	//ライブラリでshot画像読み込み
	int temp = LoadGraph("IMAGE/playershot.png");
	int w, h;
	GetGraphSize(temp, &w, &h);

	//初期化
	move = 1.0f;
	xcount = 0;
	ycount = 0;
	count = 0;
	ix = 0;
	iy = 0;
	result = 0;
	memset(shot, 0, sizeof(shot));
	live = true;
	damage = false;
	damcount = 0;
	power = 0;
	powerup_flag = false;

	//初期の位置
	x = 180;
	y = 400;

	//shotに画像とサイズを入れて初期化
	for (int i = 0; i < PLAYERSHOT_NUM; i++) {
		shot[i].shotgh = temp;
		shot[i].flag = false;
		shot[i].width = w;
		shot[i].height = h;
	}
	
	switch (Config::select_dif) {
	case Easy:
		player_hp = EPLAY_HP;
		break;
	case Normal:
		player_hp = NPLAY_HP;
		break;
	case Hard:
		player_hp = HPLAY_HP;
		break;
	default:
		break;

	}


}

//自機の移動関数
void Player::Move() {

	//斜め移動だったら速度を落とす
	if (InputKey::GetKey(KEY_INPUT_LEFT) || InputKey::GetKey(KEY_INPUT_RIGHT)) {
		if (InputKey::GetKey(KEY_INPUT_UP) || InputKey::GetKey(KEY_INPUT_DOWN)) {
			move = 0.71f;
		}
		else {
			move = 1.0f;
		}
	}
	else if (InputKey::GetKey(KEY_INPUT_UP) || InputKey::GetKey(KEY_INPUT_DOWN)) {
		move = 1.0f;
	}


	//押されたボタンに合わせて移動=4*移動係数
	if (InputKey::GetKey(KEY_INPUT_LEFT))   x -= (double)PLAYER_SPEED * move;
	if (InputKey::GetKey(KEY_INPUT_RIGHT))  x += (double)PLAYER_SPEED * move;
	if (InputKey::GetKey(KEY_INPUT_UP))     y -= (double)PLAYER_SPEED * move;
	if (InputKey::GetKey(KEY_INPUT_DOWN))   y += (double)PLAYER_SPEED * move;

	//画面の端では止まる。
	if (x < width / 2)x = width / 2;                    //x-width/2<0(画像の左端が0未満)ならx-width/2=0
	if (x > WIDTH - width / 2)x = WIDTH - width / 2;     //x+width/2>390(画像の右端が390を超える)ならx+width/2=390
	if (y < height / 2)y = height / 2;               //y-height/2<0(画像の上が0未満）ならy-height/2=0
	if (y > HEIGHT - height / 2)y = HEIGHT - height / 2;   //y+height/2>480(画像の下が480を超える）ならy+height/2=480

	//その方向キーを押している間は対応したカウンタを増やし、一定回数分カウンタが増えたなら画像を次の動作のものに切り替える
	if (InputKey::GetKey(KEY_INPUT_LEFT)) {
		if (xcount < 0) xcount = 0;
		++xcount;
	}
	if (InputKey::GetKey(KEY_INPUT_RIGHT)) {
		if (xcount > 0) xcount = 0;
		--xcount;
	}
	if (InputKey::GetKey(KEY_INPUT_UP)) {
		if (ycount < 0) ycount = 0;
		++ycount;
	}
	if (InputKey::GetKey(KEY_INPUT_DOWN)) {
		if (ycount > 0) ycount = 0;
		--ycount;
	}
	//countから画像の添字を決める
	ix = abs(xcount) % 30 / 10;//|xcount|%30/10=0から29を10で割ると0からまでの値を得る=10countごとに画像を変える
	iy = abs(ycount) % 30 / 10;//|ycount|%30/10

	//xcount>0は左向き。2行目の先頭添字を足す。
	if (xcount > 0) {
		ix += 3;
		result = ix;//3~5
	}
	else if (xcount < 0) {//xcoount<0は右向き。3行目の先頭添字を足す。
		ix += 6;
		result = ix;//6~8
	}

	//ycount>0は上向き。4行目の先頭添字を足す。
	if (ycount > 0) {
		iy += 9;
		result = iy;//9~11
	}
	else if (ycount < 0) {//ycount<0は下向き。先頭添字は0なので何もしなくてよい。
		//iy += 0;
		result = iy;
	}

	//斜め移動の時は上（下）を向く
	if (move == 0.71f) result = iy;

	//キー入力無しの時はcountをリセット
	if (InputKey::GetKey(KEY_INPUT_LEFT) != 1 && InputKey::GetKey(KEY_INPUT_RIGHT) != 1) {
		xcount = 0;
	}
	if (InputKey::GetKey(KEY_INPUT_UP) != 1 && InputKey::GetKey(KEY_INPUT_DOWN) != 1) {
		ycount = 0;
	}

}

//弾の処理
void Player::Shot() {

	int num = 0;  //弾がレベルアップした時に使う変数
	soundshot = false;   //音フラグ



	if (!damage) {//ダメージを食らってない時は打てる
	//6ループごとに発射（キー押している）
		//キーが押されているかつ4ループに一回
		if (InputKey::GetKey(KEY_INPUT_Z) && count % 4 == 0) {
			for (int i = 0; i < PLAYERSHOT_NUM; ++i) {
				if (shot[i].flag == false) {//発射されていない弾を発射させる
					if (power < 5) {//パワーが5未満は普通のショット
						shot[i].flag = true;
						shot[i].x = x;
						shot[i].y = y;
						break;
					}
					else if (power >= 5) {   //レベルアップした時のショットはplayerから左右に25だけ離れた場所からも弾が発射
						if (num == 0) {
							shot[i].flag = true;
							shot[i].x = x;
							shot[i].y = y;
						}
						else if (num == 1) {
							shot[i].flag = true;
							shot[i].x = x + 25;
							shot[i].y = y + 10;
						}
						else if (num == 2) {
							shot[i].flag = true;
							shot[i].x = x - 25;
							shot[i].y = y + 10;
						}
						++num;
						if (num == 3)break;
					}
				}
			}
			soundshot = true;//音のフラグを立てる
		}
	}
	//弾の移動を処理
	for (int i = 0; i < PLAYERSHOT_NUM; ++i) {
		if (shot[i].flag) {//i番目の弾が発射している
			shot[i].y -= SHOT_SPEED;//速さ14で移動
			//画面外にでたらflagを戻す
			if (shot[i].y < 0) shot[i].flag = false;
		}
	}
}

//描画
void Player::Draw() {

	//shot描画
	for (int i = 0; i < PLAYERSHOT_NUM; i++) {
		if (shot[i].flag) {
			//ライブラリで描画
			DrawGraph((int)shot[i].x - (int)shot[i].width / 2, (int)shot[i].y - (int)shot[i].height / 2, (int)shot[i].shotgh, TRUE);
		}
	}
	//生きているのならPlayer描画
	if (live && damage == false) {//今はダメージを食らっていない
		//ライブラリで(x,y)が画像の中心になるように描画
		DrawGraph((int)x - width / 2, (int)y - height / 2, playergh[result], TRUE);
	}
	else if (live && damage == true) {//ダメージを食らってしまった
		if (damcount < 100) {//ダメージを食らって150ループ中は点滅
			if (damcount % 2 == 0) {//ダメージを負って2カウントに1回

				//ライブラリでαブレンディングでPalを0（0に近い程透明)で指定
				SetDrawBlendMode(DX_BLENDMODE_ALPHA, 0);
				//ライブラリで設定したモードで描画
				DrawGraph((int)x - width / 2, (int)y - height / 2, playergh[result], TRUE);
				// ライブラリで設定を元に戻す
				SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
			}
			else {
				//ライブラリで描画
				DrawGraph((int)x - width / 2, (int)y - height / 2, playergh[result], TRUE);
			}
		}
		++damcount;
		if (damcount == 100) {//無敵時間は100ループだけ
			damage = false;
			damcount = 0;
		}
	}
	//生きていて弾がパワーアップしているなら左右に分身を描画
	if (live && power >= 5) {
		DrawGraph((int)x + 23 - width / 2, (int)y + 10 - height / 2, playergh2[result], TRUE);//ライブラリで(x,y)が画像の中心になるよう描画
		DrawGraph((int)x - 23 - width / 2, (int)y + 10 - height / 2, playergh2[result], TRUE);//ライブラリで(x,y)が画像の中心になるよう描画
	}
}

//プレイヤの位置を引数のポインタに与える
void Player::GetCoordinate(double* x, double* y) {
	*x = this->x;//ポインタにplayerのx座標を与える
	*y = this->y;//ポインタにplayerのy座標を与える

}

//弾を打つ音を出すかのフラグを返す
bool Player::GetSoundshot() {
	return soundshot;
}

//添え字indexの弾が打たれたかのフラグをflagにする
void Player::SetShotflag(int index, bool flag) {
	shot[index].flag = flag;
}

//添え字indexの弾の位置を引数のポインタに与える
bool Player::GetshotCoordinate(int index, double* x, double* y) {
	if (shot[index].flag) {
		*x = shot[index].x;//x座標
		*y = shot[index].y;//y座標
		return true;//画面上にある時はtrueを返す
	}
	else {
		return false;//画面にないならfalse
	}
}

//ダメージを負ったらのフラグを立ててプレイヤのHPを1減らす
void Player::SetDamageflag() {
	damage = true;
	--player_hp;
}

//ダメージを負ったかのフラグを返す
bool Player::GetDamageflag() {
	return damage;
}

//HPを返す
int Player::GetLife() {
	return player_hp;
}

//パワーの処理
void Player::SetPower(int a) {
	power += a;  //引数の値分パワーアップ（10以上は増えない）
	if (power > 10)power = 10;

	if (power > 5) {  //パワーが５よりあるなら弾をパワーアップ
		powerup_flag = true;
	}
	else if (power <= 5) {
		powerup_flag = false;
	}
}

//パワーを返す
int Player::GetPower() {
	return power;
}

//生きているかのフラグを返す
void Player::SetLiveFlag() {
	live = false;
}

//Controlで呼び出される実行関数
void Player::All() {

	Move();//ダメージを負って点滅してない時は動ける
	Shot();
	Draw();
	++count;
}