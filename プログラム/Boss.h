#pragma once
#include "define.h"

//���X�{�X�̏���
class Boss
{
private:
	//���W
	double x, y;
	//���O�̍��W��ێ�����ϐ�
	double pre_x, pre_y;
	//�O���t�B�b�N�n���h��
	int bossgh[2];//boss
	int shotgh[3];//�e
	int w, w1, w2, h, h1, h2;//�e�̉摜�̑傫���i�c���A����)��ێ�
	//HP
	int hp;
	//1�O��HP
	int pre_hp;
	//�ړ��p�^�[��
	int move_pattern;
	//�e�̃p�^�[��
	int shot_pattern;
	//1�O�̈ړ��p�^�[��
	int pre_move_pattern;
	//�P�O�̒e�̃p�^�[��
	int pre_shot_pattern;
	//�e��ł��ǂ����̃t���O
	bool shot_flag;
	//�e�̍\����
	ENE_SHOT shot[BOSSSHOT_NUM];
	//�e�̑ł��Ă���Ԃ̃J�E���g
	int shotcount;
	//���v�p�x
	int angle;
	//������(sin�g�Ɏg��)  �T�C�����擾���邽�߂̊p�x
	int rise;
	//�ړ��p�^�[��2�̎��̑�����(sin�g�Ɏg��) �ʑ���1�t���[���ɕω������
	int rise2;
	int waitcount;//��~�J�E���g
	bool wait;//��~�t���O
	//���̈ړ��ꏊ�܂ł̋���
	double move_x, move_y;
	//�ړ��p�^�[��3�Ŏg���O�p�`�̂ǂ̒��_�ֈړ�����̂��������ϐ�
	int p3_state;
	//�_���[�W�𕉂�Ȃ��t���O(�U���p�^�[���ω����j
	bool nodamage_flag;
	//�e��ł���炷���̃t���O
	bool soundshot;
	//�����Ă��邩�ǂ����̃t���O
	bool live_flag;
private:
	void Move();//����
	void Appear();//�o��
	void MovePattern1();//�ړ��p�^�[���P
	void MovePattern2();//�ړ��p�^�[���Q
	void MovePattern3();//�ړ��p�^�[���R
	void MoveDefalt();//�ړ��p�^�[���ω����邽�߃f�t�H���g�ʒu�ɖ߂�
	void MoveInit(double x, double y, int state);//�ړ��̖ړI�n�̕ύX
	void SetMovepattern(int pattern);//�ړ��p�^�[���ύX
	void SetShotpattern(int pattern);//�V���b�g�p�^�[���ύX
	void Shot();//�e��ł�
	bool ShotLocateCheck(int i);//�e����ʊO�ɂ��邩
	int ShotSearch();//�t���O�������Ă��Ȃ��e��ݒ肵���̓Y����Ԃ�
	void Draw();//�`��
public:
	Boss();//�R���X�g���N�^
	void SetFlag(bool a);//�t���O�𗧂Ă�
	bool GetFlag();//�t���O���擾
	bool GetNodamageFlag();//���G���Ԃ��ǂ����̃t���O���擾
	int GetPreHP();//�P�O��HP��Ԃ�
	void SetDamage();//angle,pre_x,pre_y,move_x,move_y��ݒ�
	void GetCoordinate(double* x, double* y);//Boss�̍��W���擾
	int SetHP(int damage);//Boss��HP���Z�b�g
	void SetShotflag(int index, bool flag);//�Y����index��shot���w�肵��flag�ɂ���
	bool GetSoundshot();//�T�E���h�t���O���擾
	bool GetshotCoordinate(int index, double* x, double* y, int* pattern);//��ʂɂ���G�̒e�̍��W��type���擾(enemy�N���X�̓����̊֐���pattern��������)
	void SetGrazeflag(int index);//�Y����index�̒e�̃O���C�Y����t���O�𗧂Ă�
	bool GetGrazeflag(int index);//�Y����index�̒e�̃O���C�Y����t���O��Ԃ�
	void All();//���s�iControl�ŌĂяo��)

};

