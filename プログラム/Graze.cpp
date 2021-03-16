#include "define.h"
#include <time.h>
#include <cmath>
#include "Graze.h"


int Graze::grazegh = 0;//初期化

Graze::Graze() {

	if (grazegh == 0) {//呼び出された初回に画像を読み込む
		grazegh = LoadGraph("IMAGE/graze.png");
	}
	//初期化
	x = 0;
	y = 0;
	rad = 0;
	bigrate = 0;
	alpha = 255;
	doflag = false;
	count = 0;
	srand((unsigned)time(NULL));//乱数のシードを時間で初期化
}


//グレイズの画像の動き
void Graze::Move() {

	//初回に角度設定(飛び散る弾はランダムに飛び散る）
	if (count == 0) {
		rad = rand() % 628 / 100;
	}
	//α値最大255、20カウントで0になるように
	alpha = 255 - (255 / 20) * count;

	//拡大率最大1.0、20カウントで0になるように
	bigrate = 1.0 - 0.05 * count;

	bigrate = 1.0 - 0.05 * count;
	x += cos(rad) * 6;//radの方向に6のスピードで進む
	y += sin(rad) * 6;

	++count;

	if (count == 20) {
		count = 0;
		doflag = false;
	}


}

//描画
void Graze::Draw(){
	//ライブラリでαブレンドモードに設定（値はalpha)
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, alpha);
	//ライブラリで座標(x,y)に拡大率bidtateで描画角度1ラジアンで画像grazephを描画。TRUE＝透明度有効
	DrawRotaGraph((int)x, (int)y, bigrate, 1, grazegh, TRUE);
	//ライブラリでモードを元に戻す
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

}

//今の実行するかのフラグを返す
bool Graze::Getflag() {
	return doflag;
}
//座標設定とフラグを立てる
void Graze::Setflag(double x, double y) {
	this->x = x;//座標設定
	this->y = y;
	doflag = true;//フラグを立てる
}


//Controlで呼び出す実行関数
void Graze::All() {
	if (doflag==true) {//フラグが立っているなら
		Move();//うごかして　
		Draw();//書く
	 }
}



