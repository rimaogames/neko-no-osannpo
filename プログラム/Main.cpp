#include "define.h"
#include "Menu.h"
int game_count = 0;//�Q�[���̃J�E���g
int hiscore=0;//�n�C�X�R�A


//�E�B���h�E�̍쐬�ƃQ�[���̃��[�v���s
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {
	ChangeWindowMode(TRUE);//�Q�[����ʂ�\��
	if (DxLib_Init() == -1) return -1;//DX���C�u�����̏�����
	SetDrawScreen(DX_SCREEN_BACK);//���C�u�����A�`���𗠉�ʂ�

	Menu *menu = new Menu;

	while (!ProcessMessage()) {//�E�B���h�E������܂�

	    ClearDrawScreen();//���C�u�����A�`���ʂ̑O�̉摜����(�����)
		
	    menu->All();//���j���[��ALL�����s

		ScreenFlip();//���C�u�����A�\��ʂɓ]��

	}
	
	DxLib_End();
	return 0;
}