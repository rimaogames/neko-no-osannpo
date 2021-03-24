#include "Menu.h"
#include "InputKey.h"
#include "SceneMgr.h"
#include "Control.h"
#include "DxLib.h"

//�R���X�g���N�^
Menu::Menu() {
	//���C�u�����ŉ摜�̃��[�h
	menugraph = LoadGraph("IMAGE/Top.jpg");    
	if (LoadDivGraph("IMAGE/cursor.png", 6, 6, 1, 16, 30, cursor) == -1) {
		MSG("�G���[����");
	}
	start1_gh = LoadGraph("IMAGE/start.png");
	start0_gh = LoadGraph("IMAGE/notstart.png");
	config1_gh = LoadGraph("IMAGE/Co.png");
	config0_gh = LoadGraph("IMAGE/notcon.png");
	how1_gh = LoadGraph("IMAGE/how.png");
	how0_gh = LoadGraph("IMAGE/nothow.png");




	//��������
	count = 0;
	NowSelect = mGame; //�ŏ��̓Q�[���J�n��I��ł���i�l��0)

	//���C�u�����ŉ��f�[�^��ǂݍ���
	nowselect_sound = LoadSoundMem("MUSIC/select.ogg");//�I�𒆂̉�
	nowselectsound_flag = false;

}

//������
void Menu::Initialize() {


	//���C�u�����ŉ摜�̃��[�h
	menugraph = LoadGraph("IMAGE/Top.jpg");   
	start1_gh = LoadGraph("IMAGE/start.png");
	start0_gh = LoadGraph("IMAGE/notstart.png");
	config1_gh = LoadGraph("IMAGE/Co.png");
	config0_gh = LoadGraph("IMAGE/notcon.png");
	how1_gh = LoadGraph("IMAGE/how.png");
	how0_gh = LoadGraph("IMAGE/nothow.png");

	if (LoadDivGraph("IMAGE/cursor.png", 6, 6, 1, 16, 30, cursor) == -1) {
		MSG("�G���[����");
	}
	
	count = 0;
	NowSelect = mGame; //�ŏ��̓Q�[���J�n��I��ł���i�l��0)
	nowselectsound_flag = false;
}


//�I���̏���
void Menu::Finalize() {
	//���C�u�����ŉ摜�̏���
	DeleteGraph(menugraph);  
	DeleteGraph(cursor[5]);
	DeleteGraph(start1_gh);
	DeleteGraph(start0_gh);
	DeleteGraph(config0_gh);
	DeleteGraph(config1_gh);
	DeleteGraph(how1_gh);
	DeleteGraph(how0_gh);
}
//��ʂ̍X�V
void Menu::Update() {
	//ScemeMgr�̎Q��
	SceneMgr& scenemgr = SceneMgr::Instance();

	//���L�[�������ꂽ��
	if (InputKey::GetKeyPush(KEY_INPUT_DOWN)) {
		NowSelect = (NowSelect + 1) % mNum;//�I����Ԃ��������
		nowselectsound_flag = true;//���t���O���Ă�
	}
	//��L�[�������ꂽ��
	else if (InputKey::GetKeyPush(KEY_INPUT_UP)) {
		NowSelect = (NowSelect + (mNum-1)) % mNum;//�I����Ԃ���グ��
		nowselectsound_flag = true;//���t���O���Ă�
	}
	if (InputKey::GetKeyPush(KEY_INPUT_RETURN)) {
		//���I�����Ă�����̂́H
		switch (NowSelect) {
		case mGame:
			scenemgr.ChangeScene(eScene::Scene_Game);//�V�[�����Q�[���ɕύX
			break;
		case mConfig:
			scenemgr.ChangeScene(eScene::Scene_Config); //�V�[����ݒ��ʂɕύX
			break;
			case mHowto:
			scenemgr.ChangeScene(eScene::Scene_Howto); //�V�[����ݒ��ʂɕύX
		default:
			break;
		}
	}

	//���t���O�������Ă���@���@���炷�ݒ�ON�Ȃ特��炷
	if (nowselectsound_flag&&Config::select_sound == ON)PlaySoundMem(nowselect_sound, DX_PLAYTYPE_BACK, TRUE);
}

void Menu::Draw() {
	//�w�i
	DrawGraph(0, 0, menugraph, FALSE);
	//����

	switch (NowSelect) {
	case mGame:
		DrawGraph(200, 200, start1_gh, TRUE);
		DrawGraph(200, 300, config0_gh, TRUE);
		DrawGraph(200, 400, how0_gh, TRUE);
		break;
	case mConfig:
		DrawGraph(200, 200, start0_gh, TRUE);
		DrawGraph(200, 300, config1_gh, TRUE);
		DrawGraph(200, 400, how0_gh, TRUE);
		break;
	case mHowto:
		DrawGraph(200, 200, start0_gh, TRUE);
		DrawGraph(200, 300, config0_gh, TRUE);
		DrawGraph(200, 400, how1_gh, TRUE);
	default:
		break;
	}





	//�J�[�\��
	int y = 200;
	switch (NowSelect) {
	case mGame:
		y = 200;
		break;
	case mConfig:
	    y = 300;
	    break;
	case mHowto:
		y = 400;
	default:
		break;
	}

	int number;
			number = count % 60 / 10;//0,1,2,3�Ɠ���
			DrawGraph(170, y+10, cursor[number], TRUE);//�`��

}
void Menu::All() {
	nowselectsound_flag = false;
	Draw();
	count++;
} 