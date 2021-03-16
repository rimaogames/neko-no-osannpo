#pragma once
class Back
{
private: 
	double x, y;//座標
	int backgh,backgh2;//グラフィックハンドル
private:
	void Draw();//ゲーム画面左の背景の描画
	void Draw2();//ゲーム画面右の背景の描画
	void Move();//背景の移動
public:
	Back();//コンストラクタ
	void All();//Controlで呼び出す（左背景）関数
	void All2();//Controlで呼び出す（右背景）関数

};

