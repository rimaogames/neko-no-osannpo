#pragma once
#include "define.h"

//�E�ɕ`�悷��n�C�X�R�A�A�X�R�A�A�O���C�Y�AHP�A�p���[�̏���
class Score
{
private:
	int g_highscore, g_score, g_graze, g_hp, g_power;//�{�[�h�̃O���t�B�b�N�n���h��
	int g_number[10];//�����̃O���t�B�b�N�n���h��
	int high_score;//�n�C�X�R�A
	int score;//���̃X�R�A
	int graze_score;//�O���C�Y�̃X�R�A
	int life;//���C�t
	int power;
private:
	void Draw();//�l�`��
public:
	Score();//�R���X�g���N�^
	void SetScore(SCOREDATA data, int a);//�X�R�A�̂����Ă�(�w�肵��SCOREDATA��a�𑫂��j(life�̎���life=a�ɐݒ�)
	int GetScore(SCOREDATA data);//�X�R�A�̎擾
	void All();//���s
};

