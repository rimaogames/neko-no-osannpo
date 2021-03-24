#pragma once
#include "define.h"

//�v���C���̏���
class Player {
private:
	//x,y���W
	double x, y;
	//x������y�����̃J�E���g��
	int xcount, ycount;

	//�摜�̕�
	int width;//��
	int height;//�c

	//�O���t�B�b�N�n���h��(�������ɕۑ������摜�̎��ʔԍ�)���i�[����z��
	int playergh[12];
	int playergh2[12];

	//�ړ��W��
	float move;

	//playergh�̔z��̓Y����
	int ix, iy, result;

	//�e
	SHOT shot[PLAYERSHOT_NUM];

	//�e�̃J�E���g
	int count;

	//�e�̃p���[
	int power;

	//�V���b�g�����Ȃ������ǂ���
	bool soundshot;

	//�����֌W
	bool live;//�����Ă��邩�ǂ����@
	bool damage;//�_���[�W�𕉂�����
	int  player_hp;//HP
	int  damcount; //�_���[�W���̃J�E���g


	bool powerup_flag;
private:
	void Move();
	void Draw();
	void Shot();
public:
	Player();//�R���X�g���N�^
	void GetCoordinate(double* x, double* y);//player�̍��W��Ԃ�
	void SetShotflag(int index, bool flag);//�Y��index��shot��flag�ɂ���
	bool GetshotCoordinate(int index, double* x, double* y);//��ʂɂ���player�̒e�̍��W��Ԃ�
	bool GetSoundshot();//�����Ȃ�t���O��Ԃ�
	void SetDamageflag();//�_���[�W�𕉂������̃t���O��true�ɐݒ�
	bool GetDamageflag();//�_���[�W�𕉂������̃t���O���擾
	void SetLiveFlag();//���񂾃t���O
	int  GetLife();//����HP���擾
	void SetPower(int a);//power��a�𑫂�
	int  GetPower();//�p���[���擾
	void All();
};



