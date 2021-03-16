#pragma once
#include "DxLib.h"
#include <Windows.h>

//���b�Z�[�W�{�b�N�X
#define MSG(m){\
MessageBoxA(NULL,m, "���b�Z�[�W", MB_OK);}
//�v���C���[�̕����X�s�[�h
#define PLAYER_SPEED 4
//��ʃX�N���[���̃X�s�[�h
#define SCROOL_SPEED 2
//�v���C���[�̒e�̉�ʒ��̒e��
#define PLAYERSHOT_NUM 50
//�G�̐�
#define ENEMY_NUM 142
//�G�̒e�̐�
#define ENEMYSHOT_NUM 50
//�{�X�̒e�̐�
#define BOSSSHOT_NUM 300
//�{�X��HP
#define BOSS_HP 400
//�{�X�̏o������
#define BOSSTIME 7400
//�{�X�̉��ړ��̐U�ꕝ
#define BOSS_SHAKE 20;
//�O���C�Y�̐�
#define GRAZE_NUM 50
//�e�̑���
#define SHOT_SPEED 13
//��ʂ̑傫��
#define WIDTH 400
#define HEIGHT 480

//�����蔻��p�̒�`
#define PLAYER_RADIUS 4
#define ENEMY_RADIUS 10
#define BOSS_RADIUS 40
#define PLAYSHOT_RADIUS 4
#define ENESHOT1_RADIOUS 3
#define ENESHOT2_RADIOUS 3
#define ENESHOT3_RADIOUS 2
#define ENESHOT4_RADIOUS 2
//�O���C�Y�����蔻��p�̒�`
#define GRAZE_RADIUS 18
//�A�C�e���̓����蔻��p���a
#define ITEM_RADIOUS 20
//�A�C�e���̑���(���ʂɑ��݂���j
#define ITEM_NUM 30
//�X�R�A������x���W
#define SCORE_X 420
//����1�����̕��@17
#define NUMBER_LONG 17

struct SHOT {//�e�̍\����
	double x, y;//���W
	int shotgh;//�O���t�B�b�N�n���h��
	int width, height;//�摜�̑傫��
	bool flag;//�e�����˒����ۂ�
};
struct ENE_SHOT {//�G�̒e
	double x, y;//���W
	double rad; //�p�x���W�A��=�p�x*��/180
	int shotgh;//�O���t�B�b�N�n���h��
	int width, height;//�摜�̑傫��
	int pattern;//�e�̎��
	int speed;//�e�̎��
	bool flag;//�e�����˒����ۂ�
	bool graflag;//�O���C�Y����t���O�i�����������ǂ����j

};

struct ENEMY_DATA {
	int type;//�G�̎��
	int shottype;//�e�̎��
	int move_pattern;//�ړ��p�^�[��
	int shot_pattern;//�e�̃p�^�[��
	int speed;//�e�̃X�s�[�h
	int intime;//�o�����鎞��
	int stoptime;//��~����
	int shottime; //�e�𔭎˂��鎞��
	int outtime;//�A�҂��鎞��
	int x;//x���W
	int y;//y���W
	int hp;//HP
	int item;//�A�C�e��
};

enum class SCOREDATA {//�񋓌^
	HIGH_SCORE,  //�n�C�X�R�A
	SCORE,       //�X�R�A
	GRAZE_SCORE,//�O���C�Y
	LIFE,      //HP
	POWER      //�p���[
};




extern int game_count;//�Q�[�����n�܂��Ă��牽���[�v�ځH
extern int hiscore;//�S�̂ł̃n�C�X�R�A�́H