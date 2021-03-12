#include "define.h"
#include "Control.h"
int game_count = 0;//�Q�[���̃J�E���g

int hiscore=0;
typedef enum {
	Scene_Menu,    //���j���[���
	Scene_Game,    //�Q�[�����
	Scene_Stop,
} eScene;
static int Scene = Scene_Menu;    //���݂̉��(�V�[��)


void UpdateScene() {	
	if (CheckHitKey(KEY_INPUT_G) != 0) {
		Scene = Scene_Game;
		
	}
	if (Scene!=Scene_Stop && CheckHitKey(KEY_INPUT_M) != 0) {
		Scene = Scene_Menu;
	}
	if (Scene != Scene_Menu && CheckHitKey(KEY_INPUT_S) != 0) {
		Scene = Scene_Stop;
	}
}

//���j���[���
void Menu() {

	DrawGraph(0, 0, LoadGraph("Top.png"), FALSE);
}

//�Q�[�����
void Game() {
	Control& control = Control::Instance();//�C���X�^���X�̎Q��
	control.All();
	hiscore = control.GetHiscore();
}
//�ꎞ��~���
void Stop() {
	DrawGraph(0, 0, LoadGraph("stop.png"), FALSE);
}

int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {
	ChangeWindowMode(TRUE);//�Q�[����ʂ�\��
	if (DxLib_Init() == -1) return -1;//DX���C�u�����̏�����
	SetDrawScreen(DX_SCREEN_BACK);//�`���𗠉�ʂ�


	while (!ProcessMessage()) {//�E�B���h�E������܂�
		ClearDrawScreen();//�`���ʂ̑O�̉摜����(�����)
		switch (Scene) {//���݂̃V�[���ɂ���������������
		case Scene_Menu://���݂̃V�[�������j���[�Ȃ�
			Menu();//���j���[���
			break;
		case Scene_Game://���݂̃V�[�����Q�[���Ȃ�
			Game();//�Q�[�����
			break;
		case Scene_Stop://���݂̃V�[�����Q�[���Ȃ�
			Stop();//�Q�[�����
			break;
		}
		UpdateScene();//�V�[�����X�V����

		ScreenFlip();//�\��ʂɓ]��
	}
	
	DxLib_End();
	return 0;
}