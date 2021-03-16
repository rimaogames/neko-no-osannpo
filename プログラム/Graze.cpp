#include "define.h"
#include <time.h>
#include <cmath>
#include "Graze.h"


int Graze::grazegh = 0;//������

Graze::Graze() {

	if (grazegh == 0) {//�Ăяo���ꂽ����ɉ摜��ǂݍ���
		grazegh = LoadGraph("IMAGE/graze.png");
	}
	//������
	x = 0;
	y = 0;
	rad = 0;
	bigrate = 0;
	alpha = 255;
	doflag = false;
	count = 0;
	srand((unsigned)time(NULL));//�����̃V�[�h�����Ԃŏ�����
}


//�O���C�Y�̉摜�̓���
void Graze::Move() {

	//����Ɋp�x�ݒ�(��юU��e�̓����_���ɔ�юU��j
	if (count == 0) {
		rad = rand() % 628 / 100;
	}
	//���l�ő�255�A20�J�E���g��0�ɂȂ�悤��
	alpha = 255 - (255 / 20) * count;

	//�g�嗦�ő�1.0�A20�J�E���g��0�ɂȂ�悤��
	bigrate = 1.0 - 0.05 * count;

	bigrate = 1.0 - 0.05 * count;
	x += cos(rad) * 6;//rad�̕�����6�̃X�s�[�h�Ői��
	y += sin(rad) * 6;

	++count;

	if (count == 20) {
		count = 0;
		doflag = false;
	}


}

//�`��
void Graze::Draw(){
	//���C�u�����Ń��u�����h���[�h�ɐݒ�i�l��alpha)
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, alpha);
	//���C�u�����ō��W(x,y)�Ɋg�嗦bidtate�ŕ`��p�x1���W�A���ŉ摜grazeph��`��BTRUE�������x�L��
	DrawRotaGraph((int)x, (int)y, bigrate, 1, grazegh, TRUE);
	//���C�u�����Ń��[�h�����ɖ߂�
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

}

//���̎��s���邩�̃t���O��Ԃ�
bool Graze::Getflag() {
	return doflag;
}
//���W�ݒ�ƃt���O�𗧂Ă�
void Graze::Setflag(double x, double y) {
	this->x = x;//���W�ݒ�
	this->y = y;
	doflag = true;//�t���O�𗧂Ă�
}


//Control�ŌĂяo�����s�֐�
void Graze::All() {
	if (doflag==true) {//�t���O�������Ă���Ȃ�
		Move();//���������ā@
		Draw();//����
	 }
}



