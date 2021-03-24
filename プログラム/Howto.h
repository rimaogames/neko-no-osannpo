#pragma once
#include "SceneBase.h"
class Howto :
    public SceneBase
{
private:
	int howgraphgh; //グラフィックハンドル

public:
	Howto();
	~Howto();
	void Update();//更新（オーバーライド）
	void All();//実行（オーバーライド）
};

