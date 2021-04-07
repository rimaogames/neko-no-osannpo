#include "Menu.h"
#include "InputKey.h"
#include "SceneMgr.h"
#include "Control.h"
#include "DxLib.h"
int Menu::stage = STAGE1;

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
	stage1gh = LoadGraph("IMAGE/stage1.png");
	stage2gh = LoadGraph("IMAGE/stage2.png");
	stage3gh = LoadGraph("IMAGE/stage3.png");
	notstage1gh = LoadGraph("IMAGE/nstage1.png");
	notstage2gh = LoadGraph("IMAGE/nstage2.png");
	notstage3gh = LoadGraph("IMAGE/nstage3.png");
	selectgh = LoadGraph("IMAGE/Top2.jpg");


	//��������
	count = 0;
	NowSelect = mGame; //�ŏ��̓Q�[���J�n��I��ł���i�l��0)
	//���C�u�����ŉ��f�[�^��ǂݍ���
	nowselect_sound = LoadSoundMem("MUSIC/select.ogg");//�I�𒆂̉�
	select_gamesound= LoadSoundMem("MUSIC/otherselect.ogg");
	nowselectsound_flag = false;
	select_stage = false;

}

//������
void Menu::Initialize() {


	//���C�u�����ŉ摜�̃��[�h
	menugraph = LoadGraph("IMAGE/Top.jpg");   
	selectgh= LoadGraph("IMAGE/Top2.jpg");
	start1_gh = LoadGraph("IMAGE/start.png");
	start0_gh = LoadGraph("IMAGE/notstart.png");
	config1_gh = LoadGraph("IMAGE/Co.png");
	config0_gh = LoadGraph("IMAGE/notcon.png");
	how1_gh = LoadGraph("IMAGE/how.png");
	how0_gh = LoadGraph("IMAGE/nothow.png");
	stage1gh= LoadGraph("IMAGE/stage1.png");
	stage2gh = LoadGraph("IMAGE/stage2.png");
	stage3gh = LoadGraph("IMAGE/stage3.png");
	notstage1gh = LoadGraph("IMAGE/nstage1.png");
	notstage2gh = LoadGraph("IMAGE/nstage2.png");
	notstage3gh = LoadGraph("IMAGE/nstage3.png");

	if (LoadDivGraph("IMAGE/cursor.png", 6, 6, 1, 16, 30, cursor) == -1) {
		MSG("�G���[����");
	}
	

	count = 0;
	NowSelect = mGame; //�ŏ��̓Q�[���J�n��I��ł���i�l��0)
	nowselectsound_flag = false;
	select_stage = false;
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
	if (!select_stage) {
		//���L�[�������ꂽ��
		if (InputKey::GetKeyPush(KEY_INPUT_DOWN)) {
			NowSelect = (NowSelect + 1) % mNum;//�I����Ԃ��������
			nowselectsound_flag = true;//���t���O���Ă�
		}
		//��L�[�������ꂽ��
		else if (InputKey::GetKeyPush(KEY_INPUT_UP)) {
			NowSelect = (NowSelect + (mNum - 1)) % mNum;//�I����Ԃ���グ��
			nowselectsound_flag = true;//���t���O���Ă�
		}
		if (InputKey::GetKeyPush(KEY_INPUT_RETURN)) {
			//���I�����Ă�����̂́H
			switch (NowSelect) {
			case mGame:
				select_stage = true;
				break;
			case mConfig:
				scenemgr.ChangeScene(eScene::Scene_Config); //�V�[����ݒ��ʂɕύX
				break;
			case mHowto:
				scenemgr.ChangeScene(eScene::Scene_Howto); //�V�[����ݒ��ʂɕύX
			default:
				break;
			}
			if (Config::select_sound == ON)PlaySoundMem(select_gamesound, DX_PLAYTYPE_BACK, TRUE);
		}


		//���t���O�������Ă���@���@���炷�ݒ�ON�Ȃ特��炷
		if (nowselectsound_flag && Config::select_sound == ON)PlaySoundMem(nowselect_sound, DX_PLAYTYPE_BACK, TRUE);


	}
	else if (select_stage == true && InputKey::GetKeyPush(KEY_INPUT_SPACE)) {
		select_stage = false;
	}
    else if (select_stage == true && InputKey::GetKeyPush(KEY_INPUT_RETURN)) {
		scenemgr.ChangeScene(eScene::Scene_Game);//�V�[�����Q�[���ɕύX
	}


	

}
void Menu::Select_Stage() {
	//���L�[�������ꂽ��
	if (InputKey::GetKeyPush(KEY_INPUT_DOWN)) {
		stage = (stage + 1) % sNum;//�I����Ԃ��������
		nowselectsound_flag = true;//���t���O���Ă�
	}
	//��L�[�������ꂽ��
	else if (InputKey::GetKeyPush(KEY_INPUT_UP)) {
		stage = (stage + (sNum - 1)) % sNum;//�I����Ԃ���グ��
		nowselectsound_flag = true;//���t���O���Ă�
	}

	//���t���O�������Ă���@���@���炷�ݒ�ON�Ȃ特��炷
	if (nowselectsound_flag && Config::select_sound == ON)PlaySoundMem(nowselect_sound, DX_PLAYTYPE_BACK, TRUE);
}


void Menu::Draw() {
	//�w�i
	if (!select_stage) {
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
		DrawGraph(170, y + 10, cursor[number], TRUE);//�`��



	}else if (select_stage) {

		DrawGraph(0, 0, selectgh, FALSE);

		switch (stage) {
		case STAGE1:
			DrawGraph(200, 100, stage1gh, TRUE);
			DrawGraph(200, 250, notstage2gh, TRUE);
			DrawGraph(200, 400, notstage3gh, TRUE);
			break;
		case STAGE2:
			DrawGraph(200, 100, notstage1gh, TRUE);
			DrawGraph(200, 250, stage2gh, TRUE);
			DrawGraph(200, 400, notstage3gh, TRUE);
			break;
		case STAGE3:
			DrawGraph(200, 100, notstage1gh, TRUE);
			DrawGraph(200, 250, notstage2gh, TRUE);
			DrawGraph(200, 400, stage3gh, TRUE);
			break;
		default:
			break;
		}
	}

}
void Menu::All() {
	nowselectsound_flag = false;
	Draw();

	if (select_stage) {
		Select_Stage();
	}
	count++;
} 