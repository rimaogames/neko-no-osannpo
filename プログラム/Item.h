#pragma once
#include "define.h"

//�A�C�e���̏���
class Item
{
private:
	static int gh[2], sgh[2];//�O���t�B�b�N�n���h��
	int type;//�ǂ����̃^�C�v�̃A�C�e����
	double x, y;//���W
	double pre_y;//y�̒l��ێ�����p�̕ϐ�
	double rad;//���W�A��
	int count;//�J�E���g
	bool fall_flag;//��������t���O
	bool do_flag;//�o�������ǂ����̃t���O
private:
	void Move();//����
	void Draw();//�`��
public:
	Item();
	void Setflag(double x, double y, int type);//�t���O�ƃA�C�e���̎�ނƏ����ʒu�̐ݒ�
	bool Getflag();//�t���O���擾
	void DeleteItem();//Item������
	void Get_Position(double* x, double* y);//Item�̍��W���擾
	int GetType();//Item�̎�ނ��擾
	void All();//���s

};

