#pragma once
#include "SceneBase.h"
class Stop :public SceneBase
{
private:
	int stopgraphgh; //グラフィックハンドル

public:
	Stop();
	~Stop();
	void Update();//更新（オーバーライド）
	void All();//実行（オーバーライド）
};

