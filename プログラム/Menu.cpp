#include "Menu.h"
#include "define.h"
#include "Control.h"


Menu::Menu() {

	//������
     restart_flag = false;//�Q�[����蒼���t���O
	 Scene = Scene_Menu;    //���݂̉��(�V�[��) �ŏ��̓��j���[���

	 //���C�u�����ŉ��Ł[���̓ǂݍ���
	 topsound=LoadSoundMem("MUSIC/bagtop.ogg");     //�g�b�v�ɖ߂�
	 gamestartsound=LoadSoundMem("MUSIC/start.ogg");//�Q�[���J�n
	 stopsound= LoadSoundMem("MUSIC/Stop.ogg");//�ꎞ��~

	 //�n���h�����Ȃ炷���ǂ����̃t���O
	 topsound_flag=false;
	 gamestartsound_flag=false;
	 stopsound_flag=false;
}

//��ʂ̍X�V
void Menu::UpdateScene() {
	if (CheckHitKey(KEY_INPUT_G) != 0) {
		if (Scene == Scene_Menu) {
			gamestartsound_flag = true;
		}
		else if (Scene == Scene_Stop) {
			stopsound_flag = true;
	 }
		Scene = Scene_Game;

	}else
	if (Scene !=Scene_Menu &&CheckHitKey(KEY_INPUT_M) != 0) {//��ʂ�menu�łȂ�����M�����ꂽ��
		topsound_flag = true;//menu��ʂɖ߂鉹�t���O�𗧂Ă�
		Scene = Scene_Menu;
	}else
	if (Scene ==Scene_Game && CheckHitKey(KEY_INPUT_S) != 0) {//��ʂ��Q�[���̎���S�����ꂽ��
		stopsound_flag = true;
		Scene = Scene_Stop;
	}
}

//���j���[���
void Menu::Top() {

	DrawGraph(0, 0, LoadGraph("IMAGE/Top.png"), FALSE);
	if (restart_flag == true) {
		Control& control = Control::Instance();//�C���X�^���X�̎Q��
		control.Restart();
		restart_flag = false;
	}
}
//�Q�[�����
void Menu::Game() {
	Control& control = Control::Instance();//�C���X�^���X�̎Q��
	control.All();
	hiscore = control.GetHiscore();
	restart_flag = true;
}
//�ꎞ��~���
void Menu::Stop() {
	DrawGraph(0, 0, LoadGraph("IMAGE/stop.png"), FALSE);
}

//���̏���
void Menu::SoundAll() {
	//���C�u�����ł��ꂼ��̃t���O�������Ă���Ȃ特���o��
	if (topsound_flag)PlaySoundMem(topsound, DX_PLAYTYPE_BACK, TRUE);
	if (gamestartsound_flag)PlaySoundMem(gamestartsound, DX_PLAYTYPE_BACK, TRUE);
	if (stopsound_flag)PlaySoundMem(stopsound, DX_PLAYTYPE_BACK, TRUE);

}

//���[�v���ŌĂяo�����֐�
void Menu::All(){
	topsound_flag = false;
	gamestartsound_flag = false;
	stopsound_flag = false;

		switch (Scene) {//���݂̃V�[���ɂ���������������
		case Scene_Menu://���݂̃V�[�������j���[�Ȃ�
			Top();//���j���[���
			break;
		case Scene_Game://���݂̃V�[�����Q�[���Ȃ�
			Game();//�Q�[�����
			break;
		case Scene_Stop://���݂̃V�[�����Q�[���Ȃ�
			Stop();//�Q�[�����
			break;
		}
		UpdateScene();//�V�[�����X�V����
		SoundAll();//���̏���
	}

