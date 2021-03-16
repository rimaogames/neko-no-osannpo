#include "Back.h"
#include "define.h"

Back::Back():x(0),y(0) {
    backgh = LoadGraph("IMAGE/back.png");//バックの背景を読み込み
    backgh2 = LoadGraph("IMAGE/back2.png");//バック（右側）を読み込み
}

void Back::Draw() {//背景を書く
    DrawGraph(x, y, backgh, FALSE);//背景を書く
    DrawGraph(x, y - HEIGHT, backgh, FALSE);//次に流れる背景を読み込み

    if (y == HEIGHT)y = 0;

}
void Back::Draw2() {//右の背景を書く
    DrawGraph(WIDTH, 0, backgh2, FALSE);
}
void Back::Move() {
    y += SCROOL_SPEED;//背景を上にずらす
}
void Back::All() {//Controlで呼び出す（左)
    Draw();//描画
    Move();//動かす
}

void Back::All2() {//Controlで呼び出す(右)
    Draw2();//描画
}
