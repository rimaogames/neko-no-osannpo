#include "Item.h"

int Item::gh[2] = { 0,0 };

int Item::sgh[2] = { 0,0 };
Item::Item() {
	//���C�u�����A����̂݉摜�ǂݍ���
	if (gh[0] == 0 && sgh[0] == 0) {
		gh[0] = LoadGraph("IMAGE/item1.png");
		gh[1] = LoadGraph("IMAGE/item2.png");
		sgh[0] = LoadGraph("IMAGE/item3.png");
		sgh[1] = LoadGraph("IMAGE/item4.png");

	}
	//������
	x = 0;
	y = 0;
	pre_y = 0;
	rad = 0;
	count = 0;
	type = 0;
	fall_flag = false;
	do_flag = false;

}

void Item::Move() {
	double temp;
	rad = 0.04 * count;//4rad=2�x����]
	++count;

	if (!fall_flag) {//�������ĂȂ������܂�Ă܂��͏�ɔ�ԁi�W�����v)
		temp = y;//�O���y�̒l��ۊ�

		//(���݂�y���W-�O���y���W)�����݂�Y���W�ɑ�������ɂP�𑫂�(�ړ��ʁj
		//��ɍs����y�̒l�͏������Ȃ遁(y-pre_y)�̓}�C�i�X�̒l
		y += (y - pre_y) + 1;
		pre_y = temp;//temp��O���y�̒l��ێ�����ϐ�pre_v��
		if ((y - pre_y) + 1 == 0) {//���_�܂ōs�����痎��
			fall_flag = true;
		}
	}else if(fall_flag) {
		y += 2.5;//����
	}
	if (y > 500)DeleteItem();//��ʊO�ɍs���������

}

void Item::Draw()
{//���C�u�����A(x,y)�Ɋg�嗦1.0�Ŋp�xrad(2�߂�0)��gh[type]��`��BTRUE=�����x�L��
	DrawRotaGraph(x, y, 1.0, rad, gh[type], TRUE);
	DrawRotaGraph(x, y, 1.0, 0, sgh[type], TRUE);
}

void Item::DeleteItem() {//�J�E���g�ƃt���O��������
	count =0;
	fall_flag = false;
	do_flag = false;
}

void Item::Setflag(double x, double y, int type) {
	//�l��ݒ�
	this->x = x;
	this->y = y;
	this->type = type;
	//pre_y(�O��y��ێ�����ϐ�)��y��^����.
	pre_y = y;
	this->y -= 6;//�n��6������ɍs���Ƃ���
	do_flag = true;//item�o���t���O�𗧂Ă�
}

bool Item::Getflag() {//�t���O���擾
	return do_flag;
}

void Item::Get_Position(double* x, double* y) {//���̍��W���擾
	*x= this->x;
	*y = this->y;
}

int Item::GetType() {//����Item�̃^�C�v���擾
	return type;
}

void Item::All() {//���̃N���X�ŌĂԎ��s�֐�
	Move();
	Draw();
}