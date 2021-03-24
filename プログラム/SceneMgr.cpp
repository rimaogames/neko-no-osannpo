#include "SceneMgr.h"
#include "Control.h"
#include "define.h"

//最初はメニュー画面にする
eScene SceneMgr::NextScene = eScene::Scene_None;
eScene SceneMgr::Scene = eScene::Scene_Menu;

//コンストラクタ
SceneMgr::SceneMgr() {
    //インスタンス
    menu = new Menu;
    config = new Config;
    result = new Result;
    //ライブラリで音データの読み込み
    topsound = LoadSoundMem("MUSIC/bagtop.ogg");     //トップに戻る
    gamestartsound = LoadSoundMem("MUSIC/start.ogg");//ゲーム開始
    stopsound = LoadSoundMem("MUSIC/Stop.ogg");//一時停止
    selectother_sound = LoadSoundMem("MUSIC/otherselect.ogg"); //ゲーム開始以外の項目選択
    //ハンドルをならすかどうかのフラグ初期化
    topsound_flag = false;
    gamestartsound_flag = false;
    stopsound_flag = false;
    selectothersound_flag = false;

}

//初期化
void SceneMgr::Initialize(eScene scene) {
    //Controlクラスの参照
    Control& control = Control::Instance();

    switch (scene) {          //シーンによって処理を分岐

    case eScene::Scene_Menu:       //指定画面がメニュー画面なら
        menu->Initialize();                 //メニュー画面の初期化処理をする
        break;
    case eScene::Scene_Game:       //指定画面がゲーム画面なら
        control.Initialize();           //ゲーム画面の初期化処理をする             
        break;
    case eScene::Scene_Config:     //指定画面が設定画面なら
        config->Initialize();          //設定画面の初期化処理をする
        break;
    case eScene::Scene_Howto:     //指定画面が遊び方画面なら
        howto = new Howto;          //遊び方画面の初期化処理をする
        break;
    case eScene::Scene_Stop:     //指定画面が一時停止画面なら
        stop = new Stop;          //一時停止画面の初期化処理をする
        break;
    case eScene::Scene_Result:
        result->Initialize();
        break;
    default:
        break;
    }
}
//終了の処理
void SceneMgr::Finalize(eScene scene) {
    //Controlクラスの参照
    Control& control = Control::Instance();
    switch (scene) {          //シーンによって処理を分岐
    case eScene::Scene_Menu:     //指定画面がメニュー画面なら
        menu->Finalize() ;                //メニュー画面の終了の処理をする
        break;
    case eScene::Scene_Game:    //指定画面がゲーム画面なら
        control.Finalize();         //ゲーム画面の終了の処理
        break;
    case eScene::Scene_Config:  //指定画面が設定画面なら
        config->Finalize();            //設定画面の終了の処理
        break;
    case eScene::Scene_Howto:  //指定画面が遊び方画面なら
        delete howto;             //遊び方画面の終了の処理
        break;  
    case eScene::Scene_Stop:  //指定画面が一時停止画面なら
        delete stop;             //一時停止画面の終了の処理
         break;
    case eScene::Scene_Result:  //指定画面が結果画面なら
        result->Finalize();             //結果画面の終了の処理
        break;
    default:
        break;

    }
}
//次のシーンを引数のシーンに設定(他クラスから呼び出される)
void SceneMgr::ChangeScene(eScene scene) {
    //次のシーンに引数のシーン入れる
    NextScene = scene;

    //音のフラグを立てる
    if (scene == eScene::Scene_Stop) {
        stopsound_flag = true;
    }
    if (scene == eScene::Scene_Menu) {
        topsound_flag = true;
    }
    if (scene == eScene::Scene_Game) {
        gamestartsound_flag = true;
    }
    if (scene == eScene::Scene_Howto || scene == eScene::Scene_Config|| scene == eScene::Scene_Result) {
        selectothersound_flag = true;
    }
}

//音の処理
void SceneMgr::SoundAll() {
    //ライブラリでそれぞれのフラグが立っているなら音を出す
    if (topsound_flag)PlaySoundMem(topsound, DX_PLAYTYPE_BACK, TRUE);
    if (gamestartsound_flag)PlaySoundMem(gamestartsound, DX_PLAYTYPE_BACK, TRUE);
    if (stopsound_flag)PlaySoundMem(stopsound, DX_PLAYTYPE_BACK, TRUE);
    if (selectothersound_flag)PlaySoundMem(selectother_sound, DX_PLAYTYPE_BACK, TRUE);

}

//画面の更新
void SceneMgr::Update() {

    //今はゲーム画面で次にいくのが一時停止画面か結果画面ならば(今のシーンを終了させない）
    if (NextScene == eScene::Scene_Stop || NextScene==eScene::Scene_Result) {

        //今のシーンに次の予定のシーンを入れる
        Scene = NextScene;
        //予定のシーンは初期化しておく
        NextScene = eScene::Scene_None;
        //今のシーン（予定されていたシーン）を初期化させる
        Initialize(Scene);
    }
    //一時停止画面からゲーム画面に行くならば（次のシーンを初期化させない）
    else if (Scene == eScene::Scene_Stop && NextScene == eScene::Scene_Game) {
        //今の画面は終了する
        Finalize(Scene);
        //画面は入れ替え
        Scene = NextScene;
        //予定のシーンは初期化
        NextScene = eScene::Scene_None;
    }
    //一時停止画面(or結果画面）からメニューにいくのなら(共にゲームも初期化）
    else if ((Scene == eScene::Scene_Stop|| Scene==eScene::Scene_Result) && NextScene == eScene::Scene_Menu) {
        //今の画面は終了する
        Finalize(Scene);
        Finalize(eScene::Scene_Game);
        //画面は入れ替え
        Scene = NextScene;
        //予定のシーンは初期化
        NextScene = eScene::Scene_None;
        //今のシーン（予定されていたシーン）を初期化させる
        Initialize(Scene);


    }
    //他の場合の画面移動ならば
    else if (NextScene != eScene::Scene_None) {
        //今の画面は終了する
            Finalize(Scene);
            //画面は入れ替え
            Scene = NextScene;
            //予定のシーンは初期化
            NextScene = eScene::Scene_None;
            //今のシーン（予定されていたシーン）を初期化させる
            Initialize(Scene);
    }
  
    //Controlクラスの参照
    Control& control = Control::Instance();

    //画面が更新する命令が下るか見る
    switch (Scene) {       //シーンによって処理を分岐
    case eScene::Scene_Menu:    //現在の画面がメニューなら
        menu->Update();            //メニュー画面の更新関数
        break;//以下略
    case eScene::Scene_Game:    //現在の画面がゲームなら
        control.Update();          //ゲーム画面の更新関数
        break;
    case eScene::Scene_Config:  //現在の画面が設定なら
        config->Update();          //設定の更新関数
        break;
    case eScene::Scene_Howto:  //現在の画面が遊び方説明なら
        howto->Update();           //遊び方の更新関数
        break;
    case eScene::Scene_Stop:     //現在の画面が一時停止画面なら
        stop->Update();            //一時停止の更新関数
        break;
    case eScene::Scene_Result:     //現在の画面が結果画面なら
        result->Update();            //結果の更新関数
        break;
    default:
        break;

    }

}


//内容の実行
void SceneMgr::All() {
    //Controlクラスの参照
    Control& control = Control::Instance();


    switch (Scene) {      //シーンによって処理を分岐
    case eScene::Scene_Menu:   //現在の画面がメニュー画面なら
        menu->All();              //メニュー画面の処理をする
        break;//以下略
    case eScene::Scene_Game: //現在の画面がゲーム画面なら
        control.All();            //ゲームの処理をする
        break;
    case eScene::Scene_Config:   //現在の画面が設定画面なら
        config->All();             //設定の処理をする
        break;
    case eScene::Scene_Howto:    //現在の画面が遊び方画面なら
        howto->All();              //遊び方画面の処理をする
        break;
    case eScene::Scene_Stop: //現在の画面が一時停止画面なら
        stop->All();             //一時停止の処理をする
        break;
    case eScene::Scene_Result: //現在の画面が結果画面なら
        result->All();             //結果の処理をする
        break;
    }
}

//Mainで呼び出される関数
void SceneMgr::Loop() {
    //サウンドフラグを初期化
    topsound_flag = false;
    gamestartsound_flag = false;
    stopsound_flag = false;
    selectothersound_flag = false;

    //更新
    Update();
    //実行
    All();
    //音を出す
    if(Config::select_sound==ON) SoundAll();
}