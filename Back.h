#pragma once
class Back
{
private: 
	double x, y;//座標
	int backgh,backgh2;//グラフィックハンドル
private:
	void Draw();
	void Draw2();
	void Move();
public:
	Back();//コンストラクタ
	void All();
	void All2();

};

