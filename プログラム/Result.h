#pragma once
#include "SceneBase.h"


//結果画面のクラス
class Result :public SceneBase
{
private:

    int result_sound;//次に行くときの音ハンドル
    int up_sound;//ハイスコア更新サウンドハンドル
    bool resound_flag;//次に行くときの音ハンドル　を鳴らすかフラグ
    bool upsound_flag;//ハイスコア更新サウンドハンドル　を鳴らすかフラグ

    int upgh;//はいすこあ更新文字
    int resultgh;//画面のグラフィックハンドル
    int g_number[10];//数字のグラフィックハンドル
    int nextgh;//次へ文字
    int endgh;//メニューへ文字

    int rescore;//スコア
    int regraze;//グレイズ
    int rehigh_score;//ハイスコア
    int count;//何回エンターキー押したか？
    bool endflag;//画面の表示が全て終わったかどうか


private:
    void Draw();//描画
    void SetResult();//結果をセットする
    void SoundAll();//音の処理
public:
    Result();
    void Initialize();//初期化
    void Finalize();//終了の処理
    void Update() ;//オーバーライド
    void All();//オーバーライド

};