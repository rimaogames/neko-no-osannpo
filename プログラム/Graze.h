#pragma once


//�O���C�Y�̏���
class Graze
{
private:
	static int grazegh;//�O���C�Y�̃O���t�B�b�N�n���h��(static�ŕϐ������L)
	double x, y;//���W
	double rad;//��юU��p�x(���W�A��)
	int alpha;//����
	double bigrate;//�g�嗦
	int count;//�J�E���g
	bool doflag;//���s�����ǂ����̃t���O
private:
	void Move();//������
	void Draw();//�`��
public:
	Graze();//�R���X�g���N�^
	void Setflag(double x, double y);//���W�ݒ�ƃt���O�𗧂Ă�
	bool Getflag();//�t���O�̍��̏�Ԃ�Ԃ�
	void All();	//���s
};

