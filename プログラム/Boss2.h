#pragma once
#include "Boss.h"
#include "define.h"
#include "Control.h"

class Control;
class Boss2 :
    public Boss
{

private:
	//�O���t�B�b�N�n���h��
	int bossgh2[2];//boss
	int shotgh2[3];//�e
	int w, w1, w2, h, h1, h2;//�e�̉摜�̑傫���i�c���A����)��ێ�

private:
	void Move();//����
	void MovePattern1();//�ړ��p�^�[���P
	void MovePattern2();//�ړ��p�^�[���Q
	void MovePattern3();//�ړ��p�^�[���R
	void MoveDefalt();//�ړ��p�^�[���ω����邽�߃f�t�H���g�ʒu�ɖ߂�
	void Shot();//�e��ł�
	void Draw();//�`��
public:
	Boss2();//�R���X�g���N�^
	void All(); //���s
};

