#pragma once
#include "define.h"


//�G�̏���
class Enemy
{
private:
	double x, y;//���W
	int enemygh[3];//�O���t�B�b�N�n���h��
	int width, height;//�摜�̃T�C�Y
	int intime, stoptime, outtime;//�G�̏o�����郋�[�v��ێ�
	int shottime;//�e�̔��˂��鎞��
	int count;//�o�����Ă���Ԃ̃J�E���g
	int enemy_type; //�G�̎��
	int shot_type; //�e�̎��
	int move_pattern; //�ړ��̎��
	int shot_pattern;//�e�̃p�^�[��
	int hp;//�G�̗̑�
	int item;//�G�̃A�C�e��
	ENE_SHOT shot[ENEMYSHOT_NUM];//�e�̍\����
	bool shotflag;//�e���łĂ邩
	int shotcount; //�e��ł��Ă���̃J�E���g
	int shotnumber;//���˂����e�̐�
	double rad;//�p�x�i���W�A���j�e�̔��ˎ��Ɏg�p
	bool deathflag;//�G���S
	bool endflag;//�G���A��
	bool soundshot;//�����Ȃ�����
private:
	void Move();
	void Shot();
	void Draw();
	bool LocateCheck();
	bool ShotLocateCheck(int i);
public:
	void GetCoordinate(double* x, double* y);
	bool GetSoundshot();//���̃t���O��Ԃ�
	void SetShotflag(int index, bool flag);//�Y����index��shot���w�肵��flag�ɂ���
	bool GetshotCoordinate(int index, double* x, double* y);//��ʂɂ���G�̒e�̍��W���擾
	int GetEnemytype();//�G�̒e�̎�ނ��擾
	int GetShottype();//�G�̒e�̎�ނ��擾
	int GetItem();//Item�̎�ނ��擾
	bool GetDeathflag();//���S�t���O��Ԃ�
	void SetDeathflag();//���S�t���O�𗧂Ă�
	void SetGrazeflag(int index);//�Y����index�̒e�̃O���C�Y����t���O�𗧂Ă�
	bool GetGrazeflag(int index);//�Y����index�̒e�̃O���C�Y����t���O��Ԃ�
	//�R���X�g���N�^�œG�̃p�^�[�����ꊇ�Ō��߂�悤�Ɂi�G�摜�A�G��ށA�ړ��p�^�[���A���W�A�o���J�n�A��~�A�A�ҁA�e�摜�A�e��ށA�e�p�^�[���A�e���ˎ��ԁA�e�����j
	Enemy(int type, int shottype, int move_pattern, int shot_pattern, int speed, int intime, int stoptime, int shottime, int outtime, int x, int y, int hp, int item);
	bool All();
};

