#include "define.h"
#include "SceneMgr.h"
#include "InputKey.h"
int game_count = 0;//�Q�[���̃J�E���g
int hiscore = 0;//�n�C�X�R�A


//���C�u�����ŃE�B���h�E�̍쐬�ƃQ�[���̃��[�v���s
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {
	ChangeWindowMode(TRUE);//���C�u�����ŃQ�[����ʂ�\��
	if (DxLib_Init() == -1) return -1;//DX���C�u�����̏�����
	SetDrawScreen(DX_SCREEN_BACK);//���C�u�����ŕ`���𗠉�ʂ�
	
	//SceneMgr�̎Q��
	SceneMgr& scenemgr = SceneMgr::Instance();

	//�L�[�̓��͊Ǘ��N���X�̃C���X�^���X
	InputKey input;

	while (!ProcessMessage()) {//�E�B���h�E������܂�

		//���C�u�����ŕ`���ʂ̑O�̉摜����(�����)
		ClearDrawScreen();

		//�L�[�̓��͏�Ԃ̍X�V
		input.Update_Keystate();

		//scenemgr�̃��[�v�֐������s
		scenemgr.Loop();

		//���C�u�����ŕ\��ʂɓ]��
		ScreenFlip();

	}

	DxLib_End(); //DX���C�u�����̏I������
	return 0;
}