#pragma once
#include "Player.h"
#include "Back.h"
#include "Enemy.h"
#include "Graze.h"
#include "Score.h"
#include "Item.h"
#include "Boss.h"
class Control
{
private:
	//�e�N���X�̐����i�|�C���^�j
	Player* player;
	Back* back;
	Enemy* enemy[ENEMY_NUM];
	Boss* boss;
	Graze* graze[GRAZE_NUM];
	Item*  item[ITEM_NUM];
	Score* score;
	ENEMY_DATA data[ENEMY_NUM];
	int sound_eshot;//�G�̃V���b�g�T�E���h�n���h��
	int sound_pshot;//player�̃V���b�g�T�E���h�n���h��
	int sound_pdamage;//player�̃_���[�W�T�E���h�n���h��
	int sound_edeath;//�G�̎��񂾉��̃T�E���h�n���h��
	int sound_graze;//�O���C�Y�̃T�E���h�n���h��
	int sound_item;//�A�C�e���擾���̃T�E���h�n���h��
	int bgm;//bgm�̃T�E���h�n���h��

	bool eshot_flag;//�G�V���b�g�̉����o�����̃t���O
	bool pshot_flag;//player�V���b�g�̉����o�����̃t���O
	bool pdamage_flag;//�G���_���[�W��H��������̉��t���O
	bool edeath_flag;//�G������ł邩�̉��t���O
	bool graze_flag;//�O���C�Y�����o�����̃t���O
	bool itemsound_flag;//�A�C�e���擾�����o�����̃t���O 
	

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
	int deathenemy_num;//���񂾓G�̓Y��
	double deathenemy_x, deathenemy_y;
	bool eefe_flag;//���S�G�t�F�N�g���o�����̃t���O(�G�j
	bool pefe_flag;//���S�G�t�F�N�g���o�����̃t���O(player)
	bool befe_flag;//���S�G�t�F�N�g���o�����̃t���O(Boss)

	bool end_flag;//�Q�[�����I�������
	bool game_over;//�Q�[���I�[�o�[��
	bool gameclear;//�Q�[���N���A

private:
	Control();//Main�ȊO��Enemy�N���X����C���X�^���X���擾����׃V���O���g���ɂ���
	~Control();
	void SoundAll();
	void SetenemyEffect(int i);
	void EFECTALL();
	void EnemyAllJudge();
	void BossAllJudge();
	//�~�`�̂����蔻��
	bool CircleJudge(double pcir, double ecir, double pcir_x, double ecir_x, double pcir_y, double ecir_y);
public:
	void All();
	void PlayerCoordinate(double *x, double *y);//player�̍��W���擾
	void EnemyCoordinate(int index, double* x, double* y);//�G�i�Y��index)�̍��W���擾
	void BossCoordinate(int index, double* x, double* y);//�G�i�Y��index)�̍��W���擾
	int GetHiscore();//�n�C�X�R�A���擾
	static Control& Instance() {//�N���X�ÓI�ϐ��A���g�̃C���X�^���X���i�[
		static Control control;//�ÓI�ϐ��Ƃ��Đ錾
		return control;
	}


};

