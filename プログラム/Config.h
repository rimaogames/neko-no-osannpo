#pragma once
#include "SceneBase.h"
//�I������
typedef enum { //�񋓌^
	cDif,        //��Փx 0
	cBGM,    //BGM�ݒ� 1
	cSound,      //���ʉ��@2
	cBack,        //���j���[��ʂɖ߂�@3
	cNum,        //�{���ڂ̐� 4
} cScene;


//�ݒ��ʃN���X
class Config :public SceneBase
{
private:
	int cursor[6];//�J�[�\���̃O���t�B�b�N�n���h��
	int enemy[3];//�L�����N�^�[�i�G�j�̃O���t�B�b�N�n���h��
    //�����̃O���t�B�b�N�n���h��
	int ongh;//����
	int offgh;//����
	int easygh;//���񂽂�
	int normalgh;//�ӂ�
	int hardgh;//�ނ�������
	int exp_dif;//�Ȃ񂢂ǐ���
	int exp_bgm;//BGM����
	int exp_sound;//���ʉ�����
	int exp_menu;//���j���[����

	int count; //�J�E���g
	bool do_set; //�ݒ肷�鍀�ڂ�I�񂾂�
	int NowSelect; //���I�����Ă��鍀��
	//�摜�n���h���i�[�p�ϐ�
	 int configimage;

	 int nowselect_sound;//�I�𒆂̉��n���h��
	 int selectother_sound; //Back�ȊO��I�񂾎���ݒ�����߂����̉�
	 bool nowselectsound_flag; //nowselect_sound��炷���̃t���O
	 bool selectothersound_flag;
public:
	static int select_dif;  //���I�����Ă����Փx
	static int select_bgm;  //���I�����Ă���BGM�ݒ�
	static int select_sound;  //���I�����Ă�����ʉ��ݒ�
private:
	void Draw();//�`��
	void SoundAll(); //���̏���
	void Select_Dif(); //��Փx�ݒ�
	void Setting_BGM(); //BGM�ݒ�
	void Setting_Sound(); //���ʉ��ݒ�
	void Select_cScene(); //�ݒ荀�ڂ�I��
public:
	Config();
	void Initialize();  //������
	void Finalize(); //�I���̏���
	void Update();//�X�V�i�I�[�o�[���C�h)
	void All();//���s(�I�[�o�[���C�h�j
};

