#pragma once
#include "define.h"

//アイテムの処理
class Item
{
private:
	static int gh[2], sgh[2];//グラフィックハンドル
	int type;//どっちのタイプのアイテムか
	double x, y;//座標
	double pre_y;//yの値を保持する用の変数
	double rad;//ラジアン
	int count;//カウント
	bool fall_flag;//落下するフラグ
	bool do_flag;//出現中かどうかのフラグ
private:
	void Move();//動く
	void Draw();//描画
public:
	Item();
	void Setflag(double x, double y, int type);//フラグとアイテムの種類と初期位置の設定
	bool Getflag();//フラグを取得
	void DeleteItem();//Itemを消す
	void Get_Position(double* x, double* y);//Itemの座標を取得
	int GetType();//Itemの種類を取得
	void All();//実行

};

