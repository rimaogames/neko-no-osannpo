#include "Item.h"

int Item::gh[2] = { 0,0 };

int Item::sgh[2] = { 0,0 };
Item::Item() {
	//ライブラリ、初回のみ画像読み込み
	if (gh[0] == 0 && sgh[0] == 0) {
		gh[0] = LoadGraph("IMAGE/item1.png");
		gh[1] = LoadGraph("IMAGE/item2.png");
		sgh[0] = LoadGraph("IMAGE/item3.png");
		sgh[1] = LoadGraph("IMAGE/item4.png");

	}
	//初期化
	x = 0;
	y = 0;
	pre_y = 0;
	rad = 0;
	count = 0;
	type = 0;
	fall_flag = false;
	do_flag = false;

}

void Item::Move() {
	double temp;
	rad = 0.04 * count;//4rad=2度ずつ回転
	++count;

	if (!fall_flag) {//落下してない＝生まれてまずは上に飛ぶ（ジャンプ)
		temp = y;//前回のyの値を保管

		//(現在のy座標-前回のy座標)を現在のY座標に足した後に１を足す(移動量）
		//上に行く＝yの値は小さくなる＝(y-pre_y)はマイナスの値
		y += (y - pre_y) + 1;
		pre_y = temp;//tempを前回のyの値を保持する変数pre_vへ
		if ((y - pre_y) + 1 == 0) {//頂点まで行ったら落下
			fall_flag = true;
		}
	}else if(fall_flag) {
		y += 2.5;//落下
	}
	if (y > 500)DeleteItem();//画面外に行ったら消す

}

void Item::Draw()
{//ライブラリ、(x,y)に拡大率1.0で角度rad(2つめは0)でgh[type]を描画。TRUE=透明度有効
	DrawRotaGraph(x, y, 1.0, rad, gh[type], TRUE);
	DrawRotaGraph(x, y, 1.0, 0, sgh[type], TRUE);
}

void Item::DeleteItem() {//カウントとフラグを初期化
	count =0;
	fall_flag = false;
	do_flag = false;
}

void Item::Setflag(double x, double y, int type) {
	//値を設定
	this->x = x;
	this->y = y;
	this->type = type;
	//pre_y(前のyを保持する変数)にyを与える.
	pre_y = y;
	this->y -= 6;//始め6だけ上に行くとする
	do_flag = true;//item出現フラグを立てる
}

bool Item::Getflag() {//フラグを取得
	return do_flag;
}

void Item::Get_Position(double* x, double* y) {//今の座標を取得
	*x= this->x;
	*y = this->y;
}

int Item::GetType() {//今のItemのタイプを取得
	return type;
}

void Item::All() {//他のクラスで呼ぶ実行関数
	Move();
	Draw();
}