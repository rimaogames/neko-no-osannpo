#pragma once
#include "Boss.h"
#include "define.h"
#include "Control.h"

class Control;
class Boss2 :
    public Boss
{

private:
	//グラフィックハンドル
	int bossgh2[2];//boss
	int shotgh2[3];//弾
	int w, w1, w2, h, h1, h2;//弾の画像の大きさ（縦幅、横幅)を保持

private:
	void Move();//動く
	void MovePattern1();//移動パターン１
	void MovePattern2();//移動パターン２
	void MovePattern3();//移動パターン３
	void MoveDefalt();//移動パターン変化するためデフォルト位置に戻る
	void Shot();//弾を打つ
	void Draw();//描画
public:
	Boss2();//コンストラクタ
	void All(); //実行
};

