#include "Player.h"
#include "define.h"

//コンストラクタ
Player::Player()
{
	//player画像読み込み
	if (LoadDivGraph("IMAGE/Player.png", 12, 3, 4, 32, 32, playergh) == -1){
 		MSG("エラー発生");
    }
	if (LoadDivGraph("IMAGE/player2.png", 12, 3, 4, 32, 32, playergh2) == -1) {
		MSG("エラー発生");
	}
	//player画像の大きさ
	width = 32;
	height = 32;

	//shot画像読み込み
	int temp = LoadGraph("IMAGE/playershot.png");
	int w,h;
	GetGraphSize(temp, &w,&h);

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
	player_hp = 10;
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
}

//自機の移動関数
void Player::Move() {

	//斜め移動だったら速度を落とす
	if (CheckHitKey(KEY_INPUT_LEFT) || CheckHitKey(KEY_INPUT_RIGHT)) {
		if (CheckHitKey(KEY_INPUT_UP) || CheckHitKey(KEY_INPUT_DOWN)) {
			move = 0.71f;
		}
		else {
			move = 1.0f;
		}
	}else if (CheckHitKey(KEY_INPUT_UP) || CheckHitKey(KEY_INPUT_DOWN)) {
		move = 1.0f;
	}
	//押されたボタンに合わせて移動=4*移動係数
	if (CheckHitKey(KEY_INPUT_LEFT))   x -= (int)PLAYER_SPEED * move;
	if (CheckHitKey(KEY_INPUT_RIGHT))  x += (int)PLAYER_SPEED * move;
	if (CheckHitKey(KEY_INPUT_UP))     y -= (int)PLAYER_SPEED * move;
	if (CheckHitKey(KEY_INPUT_DOWN))   y += (int)PLAYER_SPEED * move;

	//画面の端では止まる。
	if (x < width/2 )x = width/2;                    //x-width/2<0(画像の左端が0未満)ならx-width/2=0
	if (x > WIDTH- width / 2)x = WIDTH - width / 2;     //x+width/2>390(画像の右端が390を超える)ならx+width/2=390
	if (y < height / 2)y = height / 2;               //y-height/2<0(画像の上が0未満）ならy-height/2=0
	if (y > HEIGHT - height / 2)y = HEIGHT - height / 2;   //y+height/2>480(画像の下が480を超える）ならy+height/2=480
	
	//その方向キーを押している間は対応したカウンタを増やし、一定回数分カウンタが増えたなら画像を次の動作のものに切り替える
	if (CheckHitKey(KEY_INPUT_LEFT)){
		if(xcount<0) xcount=0;
		++xcount;
	}
	if (CheckHitKey(KEY_INPUT_RIGHT)) {
		if (xcount > 0) xcount = 0;
		--xcount;
	}
	if (CheckHitKey(KEY_INPUT_UP)) {
		if (ycount < 0) ycount = 0;
		++ycount;
	}
	if (CheckHitKey(KEY_INPUT_DOWN)) {
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
	if (CheckHitKey(KEY_INPUT_LEFT) != 1 && CheckHitKey(KEY_INPUT_RIGHT) != 1) {
		xcount = 0;
	}
	if (CheckHitKey(KEY_INPUT_UP) != 1 && CheckHitKey(KEY_INPUT_DOWN) != 1) {
		ycount = 0;
	}

}
void Player::Shot(){

	int num = 0;
	soundshot = false;
	if (!damage) {//ダメージを食らってない時は打てる
	//6ループごとに発射（キー押している）
		//キーが押されているかつ4ループに一回
		if (CheckHitKey(KEY_INPUT_Z) && count % 4 == 0) {
			for (int i = 0; i < PLAYERSHOT_NUM; ++i) {
				if (shot[i].flag == false) {//発射されていない弾を発射させる
					if (power < 5) {//パワーが5未満は普通のショット
						shot[i].flag = true;
						shot[i].x = x;
						shot[i].y = y;
						break;
					}else if (power >= 5) {
						if (num == 0) {
							shot[i].flag = true;
							shot[i].x = x;
							shot[i].y = y;
						}
						else if (num == 1) {
							shot[i].flag = true;
							shot[i].x = x+25;
							shot[i].y = y+10;
						}
						else if (num == 2) {
							shot[i].flag = true;
							shot[i].x = x - 25;
							shot[i].y =y+ 10;
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
	for (int i = 0; i < PLAYERSHOT_NUM;++i) {
		if (shot[i].flag) {//i番目の弾が発射している
			shot[i].y -= SHOT_SPEED;//速さ14で移動
			//画面外にでたらflagを戻す
			if (shot[i].y < 0) shot[i].flag = false;
		}
	}
}
void Player::Draw() {
	//shot描画
	for (int i = 0; i<PLAYERSHOT_NUM;i++){
		if (shot[i].flag) {
			DrawGraph((int)shot[i].x-(int)shot[i].width/2,(int)shot[i].y-(int)shot[i].height/2, (int)shot[i].shotgh, TRUE);
		}
	}
	//生きているのならPlayer描画
	if (live && damage==false) {//今はダメージを食らっていない
		DrawGraph((int)x - width / 2, (int)y - height / 2, playergh[result], TRUE);//(x,y)が画像の中心になるように
	}
	else if (live && damage == true) {//ダメージを食らってしまった
		if (damcount < 100) {//ダメージを食らって150ループ中は点滅
			if (damcount % 2==0) {//ダメージを負って2カウントに1回
				SetDrawBlendMode(DX_BLENDMODE_ALPHA,0);//αブレンディングでPalを0（0に近い程透明)で指定
				DrawGraph((int)x - width / 2,(int)y - height/2, playergh[result],TRUE);//設定したモードで描画
				SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);//設定を元に戻す
			}else {
				DrawGraph((int)x - width / 2, (int)y - height/2, playergh[result], TRUE);
			}
		}
		++damcount;
		if (damcount == 100) {
			damage = false;
			damcount = 0;
		}
	}
	if (live&&power >= 5) {
		DrawGraph((int)x + 23 - width / 2, (int)y +10 - height / 2, playergh2[result], TRUE);//(x,y)が画像の中心になるよう
		DrawGraph((int)x - 23 - width / 2, (int)y + 10 - height / 2, playergh2[result], TRUE);//(x,y)が画像の中心になるよう
	}
}
void Player::GetCoordinate(double* x, double* y) {
	*x = this->x;//ポインタにplayerのx座標を与える
	*y = this->y;//ポインタにplayerのy座標を与える

}
bool Player::GetSoundshot(){
	return soundshot;
}
void Player::SetShotflag(int index, bool flag) {
	shot[index].flag = flag;
  }
bool Player::GetshotCoordinate(int index, double* x, double* y) {
	if (shot[index].flag ) {
		*x = shot[index].x;//x座標
		*y = shot[index].y;//y座標
		return true;//画面上にある時はtrueを返す
	}else {
		return false;//画面にないならfalse
	}
}
void Player::SetDamageflag(){
	damage = true;
	--player_hp;
}
bool Player::GetDamageflag() {
	return damage;
}
int Player::GetLife() {
	return player_hp;
}
void Player::SetPower(int a) {
	power += a;
	if (power > 10)power = 10;

	if (power > 5) {
		powerup_flag = true;
	}
	else if (power <= 5) {
		powerup_flag = false;
	}
}
int Player::GetPower() {
	return power;
}
void Player::SetLiveFlag() {
	live = false;
}
void Player::All() {
	
	Move();//ダメージを負って点滅してない時は動ける
	Shot();
	Draw();
	++count;
}