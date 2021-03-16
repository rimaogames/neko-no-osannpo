#include "Boss.h"
#include "Control.h"
#define _USE_MATH_DEFINES
#include <cmath>
#define RAD 180

Boss::Boss() {
	//���W�̏����ʒu
	x = 200;
	y = -100;
	pre_x = 200; 
	pre_y = -100;

	//���C�u�����ŉ摜�ǂݍ���
	bossgh[0] = LoadGraph("IMAGE/boss.png");
	bossgh[1] = LoadGraph("IMAGE/boss.png");

	shotgh[0] = LoadGraph("IMAGE/enemyshot3.png");
	shotgh[1] = LoadGraph("IMAGE/enemyshot2.png");
	shotgh[2] = LoadGraph("IMAGE/enemyshot4.png");

	//���C�u�����ŉ摜�̑傫�����擾
	GetGraphSize(shotgh[0], &w, &h);
	GetGraphSize(shotgh[1], &w1, &h1);
	GetGraphSize(shotgh[2], &w2, &h2);

	//�eshot�\���̂̏�����
	for (int i = 0; i < BOSSSHOT_NUM; i++) {
		shot[i].flag = false;
		shot[i].graflag = false;
		shot[i].shotgh = 0;
		shot[i].pattern = 0;
		shot[i].rad = 0;
		shot[i].height = 0;
		shot[i].width = 0;
		shot[i].x = 0;
		shot[i].y = 0;
		shot[i].speed = 0;
	}

    //������ 
	rise = 2;  //�U���̑�����2�Ƃ���
	rise2 = 2;
	hp = BOSS_HP;
	pre_hp = BOSS_HP;
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
	live_flag = false;
	shot_flag = false;

}


//�����t���O��f�ɂ���
void Boss::SetFlag(bool f)
{
	live_flag = f;
}


//�����t���O��Ԃ�
bool Boss::GetFlag()
{
	return live_flag;
}

//�ړ�
void Boss::Move() {

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


//�o��
void Boss::Appear() {
	double temp;

	//�p�x��2�������₷
	angle += 2;
	//angle�����W�A���ɕς���sin�l�i0�`1)�𓾂�
	temp = sin(angle * M_PI / RAD);

	//�ォ��ړ����邾����x�͕ω�����
	x = 200;

	//���W�����v�Z�@�O��y���W + sin�l *�@�ړI�n�܂ł�y�̋��� 
	y = pre_y + temp * move_y;

	if (angle == 90) {//90���܂ōs������patter1�̓����ɐi��Œe��ł�
		move_pattern = 1;
		angle = 0;
		shot_flag = true;
	}
}


//�ړ��p�^�[��1
void Boss::MovePattern1() {
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
void Boss::MovePattern2() {
	if (!wait) {
		x += rise2;
		if (x == 40) {//���[�܂ł�������
			rise2 = 2;//���]
			wait = true;//��~�t���O�𗧂Ă�

		} else if( x==360) {//�E�[�܂ł�������
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
void Boss::MovePattern3() {
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
void Boss::MoveDefalt() {
	double temp;

	angle += 2;

	temp = sin(angle * M_PI / 180);

	x = pre_x + temp * move_x;
	y = pre_y + temp * move_y;

	if (angle == 90) {//sin�l���P������ړI�n�܂ňړ���������ړI�n��ς���
		SetMovepattern(pre_move_pattern + 1);
		SetShotpattern(pre_shot_pattern + 1);
		nodamage_flag= false;

		if (move_pattern == 3)MoveInit(200, 160, 2);
	}

}

//angle,pre_x,pre_y,move_x,move_y��ݒ�
void Boss::SetDamage() {
	//�O��̍��W���Z�b�g
	pre_x = x;
	pre_y = y;
	//���݈ʒu����ړI�n�܂ł̋���
	move_x = 200 - x;
	move_y = 80 - y;

	angle = 0;

	nodamage_flag = true;

	//�f�t�H���g�ʒu�ɖ߂邩��p�^�[��4�ɐi��
	SetMovepattern(4);
	SetShotpattern(3);

}


//�ړ��p�^�[����ύX
void Boss::SetMovepattern(int pattern) {
	pre_move_pattern = move_pattern;//���݂̈ړ��p�^�[����pre_move_pattern�ɗ^����
	move_pattern = pattern;//�p�^�[���ύX
}


//�e�p�^�[����ύX
void Boss::SetShotpattern(int pattern) {
	pre_shot_pattern = shot_pattern;//���݂̒e�p�^�[����pre_move_pattern�ɗ^����
	shot_pattern = pattern;//�p�^�[���ύX
}


//�ړ��ړI�n�ύX
void Boss::MoveInit(double ix, double iy, int state) {
	//���݂̍��W����
	pre_x = this->x;
	pre_y = this->y;
	//�ړI�n�܂ł̈ړ������
	move_x = ix - this->x;
	move_y = iy - this->y;
	//�p�x�̏������Ǝ��̖ړI�n��^����
	angle = 0;
	p3_state = state;

}


//�e��ł�
void Boss::Shot() {
	int index = 0;//�󂢂Ă���e�̓Y��
	int shotnum=0; //�e��ł��Ă���̃J�E���g
	static double rad;//�p�x�i���W�A���j�e�̔��ˎ��Ɏg�p
	bool scount_flag = false;//shotcount�����������邩�ǂ���
	double px, py; //player�̍��W��ێ�����ϐ�


	//Control�N���X�̎Q��
	Control &control = Control::Instance();

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
						shot[index].pattern = 0;
						shot[index].shotgh = shotgh[2];
						shot[index].width = w2;
						shot[index].height = h2;
						shot[index].speed = 4;
						//�v���C���[�̈ʒu+360�x�͈̔͂�30�����ɑł�
						shot[index].rad = atan2(py - y, px - x) + ((double)shotnum * 12 * M_PI / RAD);//360��30=12
						++shotnum;
						if (shotnum == 30)break;
						soundshot = true;//�e��ł���炷�t���O�𗧂Ă�
					}
				}
				break;
			case 1://�v���C���[�̎���ɒe�����I�ɑł�
				if (shotcount % 10 == 0 && shotcount <= 40) {//��-�v�J�E���g0,6,12,18��4��ł�
					while ((index = ShotSearch()) != -1) {//�󂫂�����e�̓Y�����擾����(-1�̎��͒e�̋󂫂��Ȃ��j
						shot[index].pattern = 1;
						shot[index].shotgh = shotgh[0];
						shot[index].width = w;
						shot[index].height = h;
						shot[index].speed = 6;
						//����6���ł�

						if (shotnum == 0) {//�v���C���[�̈ʒu����30�x��
							shot[index].rad = rad - (30 * M_PI / RAD);
						}
						else if (shotnum == 1) {//�v���C���[�̈ʒu����15�x��
							shot[index].rad = rad - (15 * M_PI / RAD);
						}
						else if (shotnum == 2) {//�v���C���[�̈ʒu
							shot[index].rad = rad;
						}
						else if (shotnum == 3) {//�v���C���[�̈ʒu����15�x�E
							shot[index].rad = rad + (15 * M_PI / RAD);
						}
						else if (shotnum == 4) {//�v���C���[�̈ʒu����30�x�E
							shot[index].rad = rad + (30 * M_PI / RAD);
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
						shot[index].pattern = 2;
						shot[index].shotgh = shotgh[1];
						shot[index].width = w1;
						shot[index].height = h1;
						shot[index].speed = 5;
						//�v���C���[�̈ʒu�{(-30�`30�͈̗̔͂���)�x
						shot[index].rad = atan2(py - y, px - x) + (double)(rand() % 61-30) * M_PI / RAD;

						soundshot = true;//�e��ł���炷�t���O�𗧂Ă�
					}
				}
				break;

			default:
				break;
			}



			for (int i = 0; i < BOSSSHOT_NUM; i++) {
				if (shot[i].flag == true) {//�t���O�������Ă���Ȃ�Βe���ړ�������
					switch (shot[i].pattern) {
					case 0:
						shot[i].x += shot[i].speed * cos(shot[i].rad);
						shot[i].y += shot[i].speed * sin(shot[i].rad);
						break;

					case 1://player�Ɍ������Ĕ���
						shot[i].x += shot[i].speed * cos(shot[i].rad);
						shot[i].y += shot[i].speed * sin(shot[i].rad);

						if (!scount_flag && shotcount == 60) scount_flag = true;//�ł�����60�܂ł͑ҋ@����count��߂�
						break;
					case 2:
						shot[i].x += shot[i].speed * cos(shot[i].rad);
						shot[i].y += shot[i].speed * sin(shot[i].rad);

						break;

					default:
						break;
					}

					if (ShotLocateCheck(i))shot[i].flag = false;
				}
			}

			++shotcount;

			if (scount_flag)shotcount = 0;//�t���O�������Ă���Ȃ��0�ɂ���
		
		
	
}


//�e�̍\���̂̂Ȃ��ŋ󂫂�����Y������Ԃ�
int Boss::ShotSearch() { 
	bool do_setting = false;//�ݒ���������i���݋󂫂̒e������̂��j
	int i;
	for (i = 0; i < BOSSSHOT_NUM; i++) {
		if (!shot[i].flag) {//�t���O�������Ă��Ȃ��e���������
			shot[i].flag = true;//�t���O���Ă�
			shot[i].x = x;
			shot[i].y = y;
			do_setting = true;
			break;
		}
	}
    if (!do_setting) {//�ݒ�����ĂȂ��Ȃ��
			i=-1;//-1��Ԃ��悤�ɂ���
	}
			return i;//�ݒ肵���Y����or�󂫂��Ȃ��Ȃ�-1��Ԃ�
		
}

//�e����ʓ��ɂ���H
bool Boss::ShotLocateCheck(int i) {
	if (shot[i].x < -10 || shot[i].x>420 || shot[i].y < -10 || shot[i].y>490) {
		return true;
	}
	else {
		return false;
	}
}

//�e�̈ʒu���|�C���^�ɗ^����i�����H���s�H��Ԃ��j
bool Boss::GetshotCoordinate(int index, double* x, double* y, int* pattern) {
	if (shot[index].flag == true) {
		*x = shot[index].x;
		*y = shot[index].y;
		*pattern = shot[index].pattern;
		return true;
	}
	else {
		return false;
	}
}


//Boss�̈ʒu���|�C���^�ɗ^����
void Boss::GetCoordinate(double* x, double* y) {
		*x = this->x;//�|�C���^��Boss��x���W��^����
		*y = this->y;//�|�C���^��Boss��y���W��^����

	}

//Boss��HP�̐ݒ�
int Boss::SetHP(int damage) {


	//hp����damage������ĕԂ�
	pre_hp = hp;
	hp -=damage;

	return hp;
}


//�P�O�̂g�o��Ԃ�
int Boss::GetPreHP() {
	return pre_hp;
}

//���ܖ��G���Ԃ���Ԃ�
bool Boss::GetNodamageFlag() {
	return nodamage_flag;
}


//�O���C�Y�̃t���O��Ԃ�
bool Boss::GetGrazeflag(int index) {
	return shot[index].graflag;
}


//�O���C�Y�̃t���O(�O���C�Y���肪�ʂ����j��Ԃ�
void Boss::SetGrazeflag(int index) {
	shot[index].graflag = true;
}

//�Y����index�̒e�̏o�����t���O��flag�ɂ���
void Boss::SetShotflag(int index, bool flag) {
	shot[index].flag = flag;
}
//�e��ł��Ƃ�炷���ǂ����̃t���O��Ԃ�
bool Boss::GetSoundshot() {
	return soundshot;
}

//�`��
void Boss::Draw() {
	//�e�̕`��
	for (int i = 0; i < BOSSSHOT_NUM; i++) {
		//�t���O�������Ă���e�͕`��B���C�u�����ŕ`��
		if (shot[i].flag) DrawRotaGraph((int)shot[i].x, (int)shot[i].y, 1.0, shot[i].rad + 90 * M_PI / 180, shot[i].shotgh, TRUE);
	}

	if (live_flag) {//�����Ă���
		//Boss�̕`��
		if (nodamage_flag) {//���C�u�����Ŗ��G��Ԃ͖��邭�`��
			DrawRotaGraph(x, y, 1.0, 0, bossgh[1], TRUE);
		}
		else {//���C�u�����Ń{�X�̕`��
			DrawRotaGraph(x, y, 1.0, 0, bossgh[0], TRUE);
		}

	}
}

//Control�ŌĂяo���֐�
void Boss::All() {
	Move();//����

	if (shot_flag)Shot();//�t���O�������Ă���e�͏���
	Draw();
}