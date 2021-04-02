#pragma once
#include "define.h"
#include "SceneBase.h"
#include "Player.h"
#include "Back.h"
#include "Enemy.h"
#include "Graze.h"
#include "Score.h"
#include "Item.h"
#include "Boss.h"


//�Q�[���S�̂̏���
class Control:public SceneBase
{
private:
	//�e�N���X�̐����i�|�C���^�j
	Player* player;
	Back* back;
	Enemy* enemy[ENEMY_NUM];
	Boss* boss;
	Graze* graze[GRAZE_NUM];
	Item* item[ITEM_NUM];
	Score* score;
	ENEMY_DATA data[ENEMY_NUM];
	int sound_eshot;//�G�̃V���b�g�T�E���h�n���h��
	int sound_pshot;//player�̃V���b�g�T�E���h�n���h��
	int sound_pdamage;//player�̃_���[�W�T�E���h�n���h��
	int sound_edeath;//�G�̎��񂾉��̃T�E���h�n���h��
	int sound_graze;//�O���C�Y�̃T�E���h�n���h��
	int sound_item;//�A�C�e���擾���̃T�E���h�n���h��
	int sound_gameover;//�Q�[���I�[�o�[�̃T�E���h�n���h��
	int sound_gameclear;//�Q�[���N���A�̃T�E���h�n���h��
	int bgm;//bgm�̃T�E���h�n���h��
	int bossbgm;//boss�Ȃ̃T�E���h�n���h��


	bool eshot_flag;//�G�V���b�g�̉����o�����̃t���O
	bool pshot_flag;//player�V���b�g�̉����o�����̃t���O
	bool pdamage_flag;//�G���_���[�W��H��������̉��t���O
	bool edeath_flag;//�G������ł邩�̉��t���O
	bool graze_flag;//�O���C�Y�����o�����̃t���O
	bool itemsound_flag;//�A�C�e���擾�����o�����̃t���O 
	bool gameover_soundflag;//�Q�[���I�[�o�[�̉����o�����̃t���O
	bool gameclear_soundflag;//�Q�[���N���A�̉����o�����̃t���O
	bool boss_soundflag;//�{�X�Ȃ𗬂����̃t���O

	int edeath_efegh[10];//���S���G�t�F�N�g�摜�n���h��(�G�j
	int eefewidth, eefeheight;//�G���S�G�t�F�N�g�摜�傫��
	int pdeath_efegh[8];//���S���G�t�F�N�g�摜�n���h��(player�j
	int pefewidth, pefeheight;//player���S�G�t�F�N�g�摜�傫��
	int eefecount, pefecount;//����ł���̃J�E���g(�G�Aplayer)
	//�N���W�b�g�֌W�̉摜�n���h��
	int title;//�^�C�g��
	int bgmgh;//���y
	int image;//�摜

	int gameovergh;//�Q�[���I�[�o�[�̉摜
	int cleargh;//�Q�[���N���A�̉摜
	int backmenu;//���j���[�ɖ߂�ē��摜
	int gamestartgh;//�Q�[���X�^�[�g�����̉摜



	int deathenemy_num;//���񂾓G�̓Y��
	double deathenemy_x, deathenemy_y; //�G�̎��S�ꏊ���擾�p�̕ϐ�
	bool eefe_flag;//���S�G�t�F�N�g���o�����̃t���O(�G�j
	bool pefe_flag;//���S�G�t�F�N�g���o�����̃t���O(player)
	bool befe_flag;//���S�G�t�F�N�g���o�����̃t���O(Boss)

	int FirstBossHP; //�{�X�̏����̗͂�ێ�����֐�

	bool now_game;//�Q�[�����v���C����
	bool end_flag;//�Q�[�����I�������
	bool game_over;//�Q�[���I�[�o�[��
	bool gameclear;//�Q�[���N���A


private:
	Control();//�R���X�g���N�^�i�V���O���g���p�^�[��)
	~Control();//�f�X�g���N�^
	void SoundAll();
	void EFECTALL();
	void EnemyAllJudge();
	void BossAllJudge();
	//�~�`�̂����蔻��
	bool CircleJudge(double pcir, double ecir, double pcir_x, double ecir_x, double pcir_y, double ecir_y);
public:
	void Update();
	void Initialize();
	void Finalize();
	void All();//Menu�ŌĂяo���֐�(�I�[�o�[���C�h�j
	void PlayerCoordinate(double* x, double* y);//player�̍��W���擾
	void EnemyCoordinate(int index, double* x, double* y);//�G�i�Y��index)�̍��W���擾
	void BossCoordinate(int index, double* x, double* y);//�G�i�Y��index)�̍��W���擾
	void GetResult(int* x, int* y,int* z);//�ŏI���ʂ��擾
	int GetHiscore();//�n�C�X�R�A���擾
	static Control& Instance() {//�N���X�ÓI�ϐ��A���g�̃C���X�^���X���i�[
		static Control control;//�ÓI�ϐ��Ƃ��Đ錾
		return control;
	}


};

