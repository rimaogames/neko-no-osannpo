#include "Back.h"
#include "define.h"

Back::Back():x(0),y(0) {
    backgh = LoadGraph("back.png");//ƒoƒbƒN‚Ì”wŒi‚ğ“Ç‚İ‚İ
    backgh2 = LoadGraph("back2.png");//ƒoƒbƒNi‰E‘¤j‚ğ“Ç‚İ‚İ
}

void Back::Draw() {//”wŒi‚ğ‘‚­
    DrawGraph(x, y, backgh, FALSE);//”wŒi‚ğ‘‚­
    DrawGraph(x, y - HEIGHT, backgh, FALSE);//Ÿ‚É—¬‚ê‚é”wŒi‚ğ“Ç‚İ‚İ

    if (y == HEIGHT)y = 0;

}
void Back::Draw2() {//‰E‚Ì”wŒi‚ğ‘‚­
    DrawGraph(WIDTH, 0, backgh2, FALSE);
}
void Back::Move() {
    y += SCROOL_SPEED;//”wŒi‚ğã‚É‚¸‚ç‚·
}
void Back::All() {
    Draw();
    Move();
}

void Back::All2() {
    Draw2();
}
