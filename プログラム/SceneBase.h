#pragma once
//抽象クラス(それぞれの画面は次の事ができる）
class SceneBase 
{
public: 
    virtual void Update() = 0;        //更新処理
    virtual void All()=0;            //実行処理
};

