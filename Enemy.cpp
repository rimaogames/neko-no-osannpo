#include "Enemy.h"
#include "define.h"
#include "Control.h"
#define _USE_MATH_DEFINES
#include <cmath>
#include <cstdlib> 
#include <ctime> 
#define RAD 180

Enemy::Enemy(int type, int shottype, int move_pattern, int shot_pattern, int speed, int intime, int stoptime, int shottime, int outtime, int x, int y, int hp, int item) {

	//���������ꂼ��ɑ��
	this->enemy_type = type;
	this->shot_type = shottype;
	this->move_pattern = move_pattern;
	this->shot_pattern = shot_pattern;
	this->intime = intime;
	this->stoptime = stoptime;
	this->shottime = shottime;
	this->outtime = outtime;
	this->x = x;
	this->y = y;
	this->hp = hp;
	this->item = item;

	if (enemy_type == 0) {
		LoadDivGraph("enemy.png", 3, 3, 1, 32, 32, enemygh);
		width = 32;
		height = 32;
    }

	int temp = 0;
	switch (shot_type) {
	case 0:
		temp = LoadGraph("enemyshot1.png");
		break;
	case 1:
		temp = LoadGraph("enemyshot2.png");
		break;
	case 2:
		temp = LoadGraph("enemyshot3.png");
		break;
	}
	int w, h;
	GetGraphSize(temp, &w, &h);

	//�e������
	for (int i = 0; i < ENEMYSHOT_NUM; i++) {
		shot[i].flag = false;
		shot[i].height = h;
		shot[i].width = w;
		shot[i].shotgh = temp;
		shot[i].pattern = shot_pattern;
		shot[i].x = x;
		shot[i].y = y;
		shot[i].speed = speed;
		shot[i].rad = 0;
		shot[i].graflag = false;
	}

	//������
	count = 0;
	shotcount = 0;
	shotnumber = 0;
	rad = 0;
	deathflag = false;
	shotflag = false;
	endflag = false;
}

void Enemy::Move() {
	if (!deathflag) {//�����Ă��鎞��������
		switch (move_pattern) {//�����̃p�^�[���ŏ�����ς���
		case 0://���ɓ��������~���ď�ɖ߂�
		   //�Q�[���̃��[�v��inttime<game_count<stoptime�Ȃ牺�ɐi��
			if (intime < game_count && game_count < stoptime) {
				y += 2;
			}
			else if (game_count > outtime) {//outtime�ɂȂ������ɐi��
				y -= 2;
			}
			break;

		case 1://�ォ�牺�Ɏ~�܂炸�ɓ���
			//�Q�[���̃��[�v��inttime=game_count�ɂȂ����牺�ɐi��
			if (intime <= game_count) {
				y += 2;
			}
			break;

		case 2://�E���Ɉړ�
			 //�Q�[���̃��[�v��inttime=game_count�Ȃ牺�ɐi��
			if (intime <= game_count) {
				y += 2;
				if (count % 2 == 0) x += 2;
			}
			break;
		case 3://�����Ɉړ�
		//�Q�[���̃��[�v��inttime=game_count�Ȃ牺�ɐi��
			if (intime <= game_count) {
				y += 2;
				if (count % 2 == 0) x -= 2;
			}
			break;
		}
		if (game_count >= stoptime) {
			if (LocateCheck()) {//�G����ʊO�ɍs�����玀�S�t���O��true��
				deathflag = true;
			}
		}
	}
}
bool Enemy::LocateCheck() {
		if (x < -20 || x> 400 || y < -20 || y>500) {
			return true;
		}
		else {
			return false;
		}
	}
void Enemy::Shot() {
	 
	//Control�N���X�̎Q��
	Control &control = Control::Instance();
	double px, py;//player�̍��W��ێ�����֐�

	//�Q�[���̃��[�v�����˂̎����ɂȂ�����t���O�𗧂Ă�
	if (shottime == game_count) shotflag = true;
	
	if (shotflag == true) {//�t���O�������Ă���Ȃ��

		soundshot = false;//�V���b�g���t���O��false�ɂ���

		if (deathflag == false) {//�G�������Ă��鎞�ɂ͒e�𔭎˂��鏀���̏���

			control.PlayerCoordinate(&px,&py);//Player�̈ʒu���擾
			//�n�߂�player�ƓG�̍��W����t���ځi�P�ʂ̓��W�A���j�����߂�B
			if (shotcount == 0){
				rad = std::atan2(py - y, px - x);
			}
			switch (shot_pattern) {//�e�̃p�^�[���ŕ��򂵂Ēe�̃Z�b�g���s��
			case 0: //�u10���[�v���Ƃ�1�񔭎˂�10���s��(�܂�����)
				if (shotcount <= 90 && shotcount % 10 == 0) {
					for (int i = 0; i < ENEMYSHOT_NUM; i++) {//�t���O�������Ă��Ȃ�
						if (shot[i].flag == false) {
							shot[i].flag = true;
							shot[i].x = x;//�G�̍��̈ʒu
							shot[i].y = y;
							shot[i].rad = rad;// std::atan2(py - y, px - x);
							break;//�ꔭ�Z�b�g������break
						}
					}
					soundshot = true;//�t���O���Ă�
				}
				break;
			case 1://player�Ɍ�������9���[�v��1�񔭎˂�10��s��
				if (shotcount <= 81 && shotcount % 9 == 0) {
					for (int i = 0; i < ENEMYSHOT_NUM; i++) {
						if (shot[i].flag == false) {
							shot[i].flag = true;
							shot[i].x = x;//�G�̍��̈ʒu
							shot[i].y = y;
							shot[i].rad = rad;//std::atan2(py - y, px - x);
							break;//�ꔭ�Z�b�g������break
						}
					}
					soundshot = true;//�t���O���Ă�
				}
				break;
			case 2: //10���[�v��1�񔭎˂��T��B3�����ɑł�
				if (shotcount <= 40 && shotcount % 10 == 0) {
					for (int i = 0; i < ENEMYSHOT_NUM; i++) {
						if (shot[i].flag == false) {
							shot[i].flag = true;
							shot[i].x = x;
							shot[i].y = y;
							if (shotnumber == 0) {//�����̕�����
								shot[i].rad = std::atan2(py - y, px - x) - (15 * M_PI / RAD);//10�x����
							}
							else if (shotnumber == 1) {//player�Ɍ�������
								shot[i].rad = std::atan2(py - y, px - x);
							}
							else if (shotnumber == 2) {//�E���̕�����
								shot[i].rad = std::atan2(py - y, px - x) + (15 * M_PI / RAD);//10�x�E��
							}
							++shotnumber;
							if (shotnumber == 3) {
								shotnumber = 0;
								break;
							}
						}

					}
					soundshot = true;//�t���O���Ă�
				}
				break;
			case 3://5���[�v��1�񗐎�
				if (shotcount % 5 == 0) {
					for (int i = 0; i < ENEMYSHOT_NUM; i++) {
						if (shot[i].flag == false) {
							shot[i].flag = true;
							shot[i].x = x;
							shot[i].y = y;

							//�n�߂ɗ���������
							if (shotnumber == 0) std::srand((unsigned)time(NULL));//seed�̏������͎��Ԃ�
							//�p�x��ς���ׂ�atan2�Ŗ��x�v�Z����Bplayer�̍��E60�x�͈̔͂ŗ��˂�����
							shot[i].rad = atan2(py - y, px - x) - (60 * M_PI / RAD) + ((rand() % 120) * M_PI / RAD);
							++shotnumber;
							break;
						}
					}
					soundshot = true;//�t���O���Ă�
				}

				break;
			}
		}
		//�t���O�������Ă���e�̐�
		int shot_flagnum = 0;

		for (int i = 0; i < ENEMYSHOT_NUM; i++) {
			if (shot[i].flag == true) {//�t���O�������Ă���Ȃ�Βe���ړ�������
				switch (shot[i].pattern) {
				case 0://���ɔ���
					shot[i].y += shot[i].speed;//�e���ړ�
					break;
				case 1://player�Ɍ������Ĕ���
					shot[i].x += shot[i].speed * cos(shot[i].rad);
					shot[i].y += shot[i].speed * sin(shot[i].rad);
					break;
				case 2://player�Ɍ������Ĕ���
					shot[i].x += shot[i].speed * cos(shot[i].rad);
					shot[i].y += shot[i].speed * sin(shot[i].rad);
					break;
				case 3://player�Ɍ������Ĕ���
					shot[i].x += shot[i].speed * cos(shot[i].rad);
					shot[i].y += shot[i].speed * sin(shot[i].rad);
					break;
				}

				//�e����ʊO
				if (ShotLocateCheck(i) == true) {
					shot[i].flag = false;//�t���O��߂�
					continue;//shot_num��ǉ����Ȃ�
				}
				++shot_flagnum;//���˒��̒e�𐔂���
			}
		}

		//���˒��̒e���Ȃ�deathflag�������Ă���
		if (shot_flagnum == 0 && deathflag == true) {
			endflag = true;
		}

		++shotcount;//�e���˒��̃��[�v�J�E���g


	}
}
void Enemy::SetDeathflag() {
	deathflag = true;
}
bool Enemy::GetDeathflag() {
	return deathflag;
}
bool Enemy::GetSoundshot() {
	return soundshot;
}
bool Enemy::ShotLocateCheck(int i) {//�e����ʓ��ɂ���H
	if (shot[i].x < -10 || shot[i].x>420 || shot[i].y < -10 || shot[i].y>490) {
		return true;
	}
	else {
		return false;
	}
}
void Enemy::Draw() {

	//�e�`��
	for (int i = 0; i < ENEMYSHOT_NUM; i++) {
		if (shot[i].flag) {
			if (shot_type == 0 || shot_type == 2) {//0��2�̒e�͂��̂܂܁i(x,y)���摜�̒��S�ɂȂ�悤�Ɂj
				DrawGraph((int)shot[i].x - shot[i].width / 2, (int)shot[i].y - shot[i].height / 2, shot[i].shotgh, TRUE);
			}
			else if (shot_type == 1 || shot_type == 3) {//rad+90�x��]�����ĕ`��
				DrawRotaGraph((int)shot[i].x, (int)shot[i].y, 1.0, shot[i].rad + (90 * M_PI / RAD), shot[i].shotgh, TRUE);

			}
		}
	}

	//�G�`��
	int number;

	if (deathflag == false) {//�G������ł��Ȃ�
		number = count % 40 / 10;//0,1,2,3�Ɠ���
		if (number == 3)number = 1;//0,1,2,1�Ɠ����悤�ɂ���

		DrawGraph((int)x-width/2, (int)y-height/2, enemygh[number], TRUE);//�`��
	}
}
void Enemy::GetCoordinate(double* x, double* y) {
	*x = this->x;//�|�C���^�ɓG��x���W��^����
	*y = this->y;//�|�C���^�ɓG��y���W��^����

}
bool Enemy::GetshotCoordinate(int index, double* x, double* y) {
	if (shot[index].flag) {
		*x = shot[index].x;//x���W
		*y = shot[index].y;//y���W
		return true;//��ʏ�ɂ��鎞��true��Ԃ�
	}
	else {
		return false;//��ʂɂȂ��Ȃ�false
	}
}
void Enemy::SetShotflag(int index, bool flag) {
	shot[index].flag = flag;
}

int Enemy::GetEnemytype() {
	return enemy_type;
}
int Enemy::GetShottype() {
	return shot_type;
}
int Enemy::GetItem() {
	return item;
}
void Enemy::SetGrazeflag(int index) {
	shot[index].graflag = true;//�Y��index�̃O���C�Y����t���O�𗧂Ă�
}

bool Enemy::GetGrazeflag(int index) {
	return shot[index].graflag;//�Y��index�̃O���C�Y����t���O��Ԃ�
}
bool Enemy::All() {
	Move();
	Shot();
	Draw();
	++count;

	return endflag;
}
