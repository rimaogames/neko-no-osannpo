#include "Boss2.h"
#include "Config.h"
#define _USE_MATH_DEFINES
#include <cmath>
#define RAD 180

Boss2::Boss2() {
	//���W�̏����ʒu
	x = 200;
	y = -100;
	pre_x = 200;
	pre_y = -100;

	//���C�u�����ŉ摜�ǂݍ���
	bossgh2[0] = LoadGraph("IMAGE/boss2.png");
	bossgh2[1] = LoadGraph("IMAGE/damageboss2.png");

	shotgh2[0] = LoadGraph("IMAGE/enemyshot3.png");
	shotgh2[1] = LoadGraph("IMAGE/enemyshot2.png");
	shotgh2[2] = LoadGraph("IMAGE/enemyshot4.png");

	//���C�u�����ŉ摜�̑傫�����擾
	GetGraphSize(shotgh2[0], &w, &h);
	GetGraphSize(shotgh2[1], &w1, &h1);
	GetGraphSize(shotgh2[2], &w2, &h2);

	//�eshot�\���̂̏�����
	for (int i = 0; i < BOSSSHOT_NUM; i++) {
		bshot[i].flag = false;
		bshot[i].graflag = false;
		bshot[i].shotgh = 0;
		bshot[i].pattern = 0;
		bshot[i].rad = 0;
		bshot[i].height = 0;
		bshot[i].width = 0;
		bshot[i].x = 0;
		bshot[i].y = 0;
		bshot[i].speed = 0;
	}

	//������ 
	rise = 2;  //�U���̑�����2�Ƃ���
	rise2 = 2;
	angle = 0;
	move_pattern = 0;
	shot_pattern = 0;
	pre_move_pattern = 0;
	pre_shot_pattern = 0;
	shotcount = 0;
	move_x = 0;
	move_y = 180;//�ŏ��̈ړ�������180�Ƃ���
	waitcount = 0;
	wait = false;
	p3_state = 0;
	nodamage_flag = false;
	soundshot = false;
	shot_flag = false;
	live_flag = false;
	//��Փx�Ń{�X�̗̑͂�ς���
	switch (Config::select_dif) {
	case Easy:
		hp = EBOSS_HP;
		pre_hp = EBOSS_HP;
		break;
	case Normal:
		hp = NBOSS_HP;
		pre_hp = NBOSS_HP;
		break;
	case Hard:
		hp = HBOSS_HP;
		pre_hp = HBOSS_HP;
		break;

	}

}
//�ړ�
void Boss2::Move() {

	switch (move_pattern) {//�ړ��p�^�[���ŏ�����ς���
	case 0:
		Appear();//�{�X�̓o��
		break;
	case 1:
		MovePattern1();//�ӂ�ӂ�㉺�ɉ^������
		break;
	case 2:
		MovePattern2();//���E�ɓ���
		break;
	case 3:
		MovePattern3();//�O�p�`�^�ɓ���
		break;
	case 4:
		MoveDefalt();//�f�t�H���g�ʒu�ɖ߂�
		break;
	}
}

//�ړ��p�^�[��1
void Boss2::MovePattern1() {
	//�p�x��2��(-2���j�����₷
	angle += rise;

	x = 200;

	//���S�ʒu(80)�{sin�l*�U�ꕝ
	y = 80 + sin(angle * M_PI / RAD) * BOSS_SHAKE;

	if (angle == 90 || angle == -90) {
		rise = ~rise;//�����ʔ��]
	}
}

//�ړ��p�^�[��2
void Boss2::MovePattern2() {
	if (!wait) {
		x += rise2;
		if (x == 40) {//���[�܂ł�������
			rise2 = 2;//���]
			wait = true;//��~�t���O�𗧂Ă�

		}
		else if (x == 360) {//�E�[�܂ł�������
			rise2 = -2; //���]
			wait = true; //��~�t���O�𗧂Ă�
		}
	}

	if (wait) {//10�J�E���g������~
		++waitcount;
		if (waitcount == 10) {
			wait = false;
			waitcount = 0;
		}
	}
}


//�ړ��p�^�[��3
void Boss2::MovePattern3() {
	double temp;

	//�p�x��2��(-2���j�����₷
	angle += 2;
	temp = sin(angle * M_PI / RAD);

	//���W���v�Z�@�O��x,y���W + sin�l *�@�ړI�n�܂ł�x,y�̋��� 
	x = pre_x + temp * move_x;
	y = pre_y + temp * move_y;

	if (angle == 90) {//sin�l���P������ړI�n�܂ňړ���������ړI�n��ς���
		if (p3_state == 0) {//���ֈړ�
			MoveInit(70, 80, 1);
		}
		else if (p3_state == 1) {//�^�񒆂ֈړ�
			MoveInit(200, 160, 2);
		}
		else {
			MoveInit(330, 80, 0);//�E�ֈړ�
		}
	}
}
//�f�t�H���g�ʒu�ɓ���
void Boss2::MoveDefalt() {
	double temp;

	angle += 2;

	temp = sin(angle * M_PI / 180);

	x = pre_x + temp * move_x;
	y = pre_y + temp * move_y;

	if (angle == 90) {//sin�l���P������ړI�n�܂ňړ���������ړI�n��ς���
		SetMovepattern(pre_move_pattern + 1);
		SetShotpattern(pre_shot_pattern + 1);
		nodamage_flag = false;

		if (move_pattern == 3)MoveInit(200, 160, 2);
	}
}

//�e��ł�
void Boss2::Shot() {
	int index = 0;//�󂢂Ă���e�̓Y��
	int shotnum = 0; //�e��ł��Ă���̃J�E���g
	static double rad;//�p�x�i���W�A���j�e�̔��ˎ��Ɏg�p
	bool scount_flag = false;//shotcount�����������邩�ǂ���
	double px, py; //player�̍��W��ێ�����ϐ�


	//Control�N���X�̎Q��
	Control& control = Control::Instance();

	soundshot = false;

	if (nodamage_flag) {//�_���[�W����萔�H�������shotcount��0�ɖ߂�
		scount_flag = true;
	}

	control.PlayerCoordinate(&px, &py);//�v���C���̈ʒu���擾

	if (shotcount == 0)rad = std::atan2(py - y, px - x);//�e�̑ł��n�߂Ɋp�x�i���W�A���j���v�Z

	switch (shot_pattern) {
	case 0://���ˏ��10���[�v��1��25���ł�
		if (shotcount % 10 == 0) {//�v���C���[�̎���i�O��30�x�j��4���[�v��1���ł�
			while ((index = ShotSearch()) != -1) {//�e�̏���
				bshot[index].pattern = 0;
				bshot[index].shotgh = shotgh2[2];
				bshot[index].width = w2;
				bshot[index].height = h2;
				bshot[index].speed = 4;
				//�v���C���[�̈ʒu+360�x�͈̔͂�30�����ɑł�
				bshot[index].rad = atan2(py - y, px - x) + ((double)shotnum * 12 * M_PI / RAD);//360��30=12
				++shotnum;
				if (shotnum == 30)break;
				soundshot = true;//�e��ł���炷�t���O�𗧂Ă�
			}
		}
		break;
	case 1://�v���C���[�̎���ɒe�����I�ɑł�
		if (shotcount % 10 == 0 && shotcount <= 40) {//��-�v�J�E���g0,6,12,18��4��ł�
			while ((index = ShotSearch()) != -1) {//�󂫂�����e�̓Y�����擾����(-1�̎��͒e�̋󂫂��Ȃ��j
				bshot[index].pattern = 1;
				bshot[index].shotgh = shotgh2[0];
				bshot[index].width = w;
				bshot[index].height = h;
				bshot[index].speed = 6;
				//����6���ł�

				if (shotnum == 0) {//�v���C���[�̈ʒu����30�x��
					bshot[index].rad = rad - (30 * M_PI / RAD);
				}
				else if (shotnum == 1) {//�v���C���[�̈ʒu����15�x��
					bshot[index].rad = rad - (15 * M_PI / RAD);
				}
				else if (shotnum == 2) {//�v���C���[�̈ʒu
					bshot[index].rad = rad;
				}
				else if (shotnum == 3) {//�v���C���[�̈ʒu����15�x�E
					bshot[index].rad = rad + (15 * M_PI / RAD);
				}
				else if (shotnum == 4) {//�v���C���[�̈ʒu����30�x�E
					bshot[index].rad = rad + (30 * M_PI / RAD);
				}



				soundshot = true;//�e��ł���炷�t���O�𗧂Ă�

				++shotnum;
				if (shotnum == 5)break;
			}
		}

		break;
	case 2://�v���C���[�̎���i�O��30�x�j��4���[�v��1���ł�
		if (shotcount % 4 == 0) {
			if ((index = ShotSearch()) != -1) {
				bshot[index].pattern = 2;
				bshot[index].shotgh = shotgh2[1];
				bshot[index].width = w1;
				bshot[index].height = h1;
				bshot[index].speed = 5;
				//�v���C���[�̈ʒu�{(-30�`30�͈̗̔͂���)�x
				bshot[index].rad = atan2(py - y, px - x) + (double)(rand() % 61 - 30) * M_PI / RAD;

				soundshot = true;//�e��ł���炷�t���O�𗧂Ă�
			}
		}
		break;

	default:
		break;
	}



	for (int i = 0; i < BOSSSHOT_NUM; i++) {
		if (bshot[i].flag == true) {//�t���O�������Ă���Ȃ�Βe���ړ�������
			switch (bshot[i].pattern) {
			case 0:
				bshot[i].x += bshot[i].speed * cos(bshot[i].rad);
				bshot[i].y += bshot[i].speed * sin(bshot[i].rad);
				break;

			case 1://player�Ɍ������Ĕ���
				bshot[i].x += bshot[i].speed * cos(bshot[i].rad);
				bshot[i].y += bshot[i].speed * sin(bshot[i].rad);

				if (!scount_flag && shotcount == 60) scount_flag = true;//�ł�����60�܂ł͑ҋ@����count��߂�
				break;
			case 2:
				bshot[i].x += bshot[i].speed * cos(bshot[i].rad);
				bshot[i].y += bshot[i].speed * sin(bshot[i].rad);

				break;

			default:
				break;
			}

			if (ShotLocateCheck(i))bshot[i].flag = false;
		}
	}

	++shotcount;

	if (scount_flag)shotcount = 0;//�t���O�������Ă���Ȃ��0�ɂ���



}

//�`��
void Boss2::Draw() {
	//�e�̕`��
	for (int i = 0; i < BOSSSHOT_NUM; i++) {
		//�t���O�������Ă���e�͕`��B���C�u�����ŕ`��
		if (bshot[i].flag) DrawRotaGraph((int)bshot[i].x, (int)bshot[i].y, 1.0, bshot[i].rad + 90 * M_PI / 180, bshot[i].shotgh, TRUE);
	}

	if (live_flag) {//�����Ă���
		//Boss�̕`��
		if (nodamage_flag) {//���C�u�����Ŗ��G��Ԃ͖��邭�`��
			DrawRotaGraph(x, y, 1.0, 0, bossgh2[1], TRUE);
		}
		else {//���C�u�����Ń{�X�̕`��
			DrawRotaGraph(x, y, 1.0, 0, bossgh2[0], TRUE);
		}

	}
}

//Control�ŌĂяo���֐�
void Boss2::All() {
	Move();//����

	if (shot_flag)Shot();//�t���O�������Ă���e�͏���
	Draw();
}