#include "Back.h"
#include "define.h"

Back::Back():x(0),y(0) {
    backgh = LoadGraph("IMAGE/back.png");//�o�b�N�̔w�i��ǂݍ���
    backgh2 = LoadGraph("IMAGE/back2.png");//�o�b�N�i�E���j��ǂݍ���
}

void Back::Draw() {//�w�i������
    DrawGraph(x, y, backgh, FALSE);//�w�i������
    DrawGraph(x, y - HEIGHT, backgh, FALSE);//���ɗ����w�i��ǂݍ���

    if (y == HEIGHT)y = 0;

}
void Back::Draw2() {//�E�̔w�i������
    DrawGraph(WIDTH, 0, backgh2, FALSE);
}
void Back::Move() {
    y += SCROOL_SPEED;//�w�i����ɂ��炷
}
void Back::All() {//Control�ŌĂяo���i��)
    Draw();//�`��
    Move();//������
}

void Back::All2() {//Control�ŌĂяo��(�E)
    Draw2();//�`��
}
