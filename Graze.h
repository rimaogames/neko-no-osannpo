#pragma once


//グレイズの処理
class Graze
{
private:
	static int grazegh;//グレイズのグラフィックハンドル(staticで変数を共有)
	double x, y;//座標
	double rad;//飛び散る角度(ラジアン)
	int alpha;//α率
	double bigrate;//拡大率
	int count;//カウント
	bool doflag;//実行中かどうかのフラグ
private:
	void Move();//動かす
	void Draw();//描画
public:
	Graze();//コンストラクタ
	void Setflag(double x, double y);//座標設定とフラグを立てる
	bool Getflag();//フラグの今の状態を返す
	void All();	//実行
};

