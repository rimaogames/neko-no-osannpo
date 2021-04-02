#pragma once
#include "SceneBase.h"

//�I������
typedef enum { //�񋓌^
	mGame,        //�Q�[���J�n 0
	mConfig,    //�ݒ� 1
	mHowto,      //�V�ѕ��@2
	mNum,        //�{���ڂ̐� 3
} mScene;

//���j���[���
class Menu :public SceneBase
{
private:
   int menugraph;//���j���[���
   int selectgh; //���ā[���I�����

   //�����̃O���t�B�b�N�n���h��
   int start1_gh; //�J�n�I�����W
   int start0_gh; //�J�n�D�F
   int config1_gh; //�ݒ�I�����W
   int config0_gh; //�����Ă��D�F
   int how1_gh;    //�����т����I�����W
   int how0_gh; //�����т����D�F
   int stage1gh; //���ā[���P��
   int stage2gh;
   int stage3gh;
   int notstage1gh; //���ā[���Q�D�F
   int notstage2gh;
   int notstage3gh;

   int cursor[6];//�J�[�\��
   int NowSelect;//���I�𒆂̍���
   int count; //�J�E����

   int nowselect_sound;//�I�𒆂̉��n���h��
   bool nowselectsound_flag; //nowselect_sound��炷���̃t���O
   int select_gamesound; //�Q�[���X�^�[�g��I�񂾎��ɖ炷���y�̃n���h��
   bool select_stage; //���̓X�e�[�W�I����ʂ�
public:
   static int stage; //�I�񂾃X�e�[�W

private:
	void Draw(); //�`��
	void Select_Stage();
public:
	Menu();
	void Initialize(); //������
	void Finalize();//�I���̏���
	void Update(); //�I�[�o�[���C�h
	void All();  //�I�[�o�[���C�h
};

