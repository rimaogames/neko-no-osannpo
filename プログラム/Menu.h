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

   //�����̃O���t�B�b�N�n���h��
   int start1_gh; //�J�n�I�����W
   int start0_gh; //�J�n�D�F
   int config1_gh; //�ݒ�I�����W
   int config0_gh; //�����Ă��D�F
   int how1_gh;    //�����т����I�����W
   int how0_gh; //�����т����D�F

   int cursor[6];//�J�[�\��
   int NowSelect;//���I�𒆂̍���
   int count; //�J�E���g

   int nowselect_sound;//�I�𒆂̉��n���h��
   bool nowselectsound_flag; //nowselect_sound��炷���̃t���O
private:
	void Draw(); //�`��
public:
	Menu();
	void Initialize(); //������
	void Finalize();//�I���̏���
	void Update(); //�I�[�o�[���C�h
	void All();  //�I�[�o�[���C�h
};

