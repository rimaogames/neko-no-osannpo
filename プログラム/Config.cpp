#include "Config.h"
#include "define.h"
#include "InputKey.h"
#include "SceneMgr.h"
#include "DxLib.h"

int Config::select_dif =Normal;
int Config::select_bgm = ON;
int Config::select_sound = ON;
//�R���X�g���N�^
Config::Config() {
	//���C�u�����ŉ��f�[�^��ǂݍ���
	nowselect_sound = LoadSoundMem("MUSIC/select.ogg");//�I�𒆂̉�
	selectother_sound=LoadSoundMem("MUSIC/otherselect.ogg"); //Back�ȊO�̍��ڑI���܂��͐ݒ�̌���

	//�T�E���h�t���O�̏�����
	nowselectsound_flag = false;
	selectothersound_flag = false;
}

//������
void Config::Initialize(){

	//���C�u�����ŉ摜��ǂݍ���
	if (LoadDivGraph("IMAGE/cursor.png", 6, 6, 1, 16, 30, cursor) == -1) {
		MSG("�G���[����");
	}
	//���C�u�����ŉ摜�ǂݍ���
	if (LoadDivGraph("IMAGE/enemy3.png", 3, 3, 1, 32, 32, enemy) == -1) {
		MSG("�G���[����");
	}

	ongh = LoadGraph("IMAGE/on.png");
	offgh = LoadGraph("IMAGE/off.png");
	easygh = LoadGraph("IMAGE/easy.png");
	normalgh = LoadGraph("IMAGE/normal.png");
	hardgh = LoadGraph("IMAGE/hard.png");
	exp_dif = LoadGraph("IMAGE/exp_dif.png");
	exp_bgm = LoadGraph("IMAGE/exp_bgm.png");
	exp_sound = LoadGraph("IMAGE/exp_sound.png");
	exp_menu = LoadGraph("IMAGE/exp_menu.png");

	count = 0;
	//���C�u�����ŉ��f�[�^��ǂݍ���
	configimage = LoadGraph("IMAGE/config.png");

	//��������
	NowSelect = cDif;
	do_set = false;
	nowselectsound_flag = false;
	selectothersound_flag = false;
}


//�I���̏���
 void Config::Finalize() {
	 //���C�u�����ŉ摜���̂Ă�
	DeleteGraph( configimage);
	DeleteGraph(ongh);
	DeleteGraph(offgh);
	DeleteGraph(easygh);
	DeleteGraph(normalgh);
	DeleteGraph(hardgh);
	DeleteGraph(exp_dif);
	DeleteGraph(exp_bgm);
	DeleteGraph(exp_sound);
	DeleteGraph(exp_menu);
	DeleteGraph(cursor[5]);
	DeleteGraph(enemy[2]);
}

 void Config::Select_cScene() {
	 //���L�[�������ꂽ��
	 if (InputKey::GetKeyPush(KEY_INPUT_DOWN)) {
		 NowSelect = (NowSelect + 1) % cNum;//�I����Ԃ��������
		 nowselectsound_flag = true;//���t���O���Ă�
	 }
	 //��L�[�������ꂽ��
	 else if (InputKey::GetKeyPush(KEY_INPUT_UP)) {
		 NowSelect = (NowSelect + (cNum - 1)) % cNum;//�I����Ԃ���グ��
		 nowselectsound_flag = true;//���t���O���Ă�
	 }
	 if (InputKey::GetKeyPush(KEY_INPUT_RETURN)) {
		if(NowSelect!=cBack){
			selectothersound_flag = true;//���艹�t���O���Ă�
			do_set = true;
		 }
	 }
 }

 void Config::Select_Dif() {
	 //���L�[�������ꂽ��
	 if (InputKey::GetKeyPush(KEY_INPUT_DOWN)) {
		 select_dif = (select_dif + 1) % dNum;//�I����Ԃ��������
		 nowselectsound_flag = true;//���t���O���Ă�
	 }
	 //��L�[�������ꂽ��
	 else if (InputKey::GetKeyPush(KEY_INPUT_UP)) {
		 select_dif = (select_dif + (dNum - 1)) % dNum;//�I����Ԃ���グ��
		 nowselectsound_flag = true;//���t���O���Ă�
	 }
	 if (InputKey::GetKeyPush(KEY_INPUT_RETURN)) {
		 selectothersound_flag = true;//���艹�t���O���Ă�
		 do_set = false; //�ݒ荀�ڂ��甲����
		 return;
	 }
 }
 void Config::Setting_BGM() {
	 //���L�[�������ꂽ��
	 if (InputKey::GetKeyPush(KEY_INPUT_DOWN)) {
		 select_bgm = (select_bgm + 1) %muNUM;//�I����Ԃ��������
		 nowselectsound_flag = true;//���t���O���Ă�
	 }
	 //��L�[�������ꂽ��
	 else if (InputKey::GetKeyPush(KEY_INPUT_UP)) {
		 select_bgm = (select_bgm + (muNUM - 1)) % muNUM;//�I����Ԃ���グ��
		 nowselectsound_flag = true;//���t���O���Ă�
	 }
	 if (InputKey::GetKeyPush(KEY_INPUT_RETURN)) {
		 selectothersound_flag = true;//���艹�t���O���Ă�
		 do_set = false;//�ݒ荀�ڂ��甲����
		 return;
	 }
 }
 void Config::Setting_Sound() {
	 //���L�[�������ꂽ��
	 if (InputKey::GetKeyPush(KEY_INPUT_DOWN)) {
		 select_sound = (select_sound + 1) % muNUM;//�I����Ԃ��������
		nowselectsound_flag = true;//���t���O���Ă�
	 }
	 //��L�[�������ꂽ��
	 else if (InputKey::GetKeyPush(KEY_INPUT_UP)) {
		 select_sound = (select_sound + (muNUM - 1)) % muNUM;//�I����Ԃ���グ��
		 nowselectsound_flag = true;//���t���O���Ă�
	 }
	 if (InputKey::GetKeyPush(KEY_INPUT_RETURN)) {
		 selectothersound_flag = true;//���艹�t���O���Ă�
		 do_set = false;//�ݒ荀�ڂ��甲����
		 return;
	 }
 }

void Config::Update() {

	//ScemeMgr�̎Q��
	SceneMgr& scenemgr = SceneMgr::Instance();
	if (NowSelect == cBack && InputKey::GetKeyPush(KEY_INPUT_RETURN)) {
		scenemgr.ChangeScene(eScene::Scene_Menu);//�V�[�������j���[�ɕύX
	}

	
}

void Config::Draw() {
	DrawGraph(0, 0, configimage, FALSE);
	int y = 100;
	switch (NowSelect) {
	case cDif:
		y = 110;
		break;
	case cBGM:
		y = 170;
		break;
	case cSound:
		y = 230;
		break;
	case cBack:
		y = 300;
		break;
	default:
		break;
	}
	int number;
	number = count % 60 / 10;//0,1,2,3�Ɠ���
	DrawGraph(50, y, cursor[number], TRUE);//�`��


	switch (NowSelect) {
	case cDif:
		DrawGraph(80, 350, exp_dif, TRUE);
		break;
	case cBGM:
		DrawGraph(80, 350, exp_bgm, TRUE);
		break;
	case cSound:
		DrawGraph(80, 350, exp_sound, TRUE);
		break;
	case cBack:
		DrawGraph(80, 350, exp_menu, TRUE);
	default:
		break;
	}





	switch (select_dif) {
	case Easy:
		DrawGraph(400, 100, easygh, TRUE);
		break;
	case Normal:
		DrawGraph(400, 100, normalgh, TRUE);
		break;
	case Hard:
		DrawGraph(400, 100, hardgh, TRUE);
		break;
	default:
		break;
	}

	if (select_bgm == ON) {
		DrawGraph(400, 165, ongh, TRUE);
	} else if(select_bgm==OFF){
		DrawGraph(400, 165, offgh, TRUE);
		
	}
	if (select_sound == ON) {
		DrawGraph(400, 230, ongh, TRUE);
	}
	else if (select_sound == OFF) {
		DrawGraph(400, 230, offgh, TRUE);

	}

	int number2;
	number2 = count % 40 / 10;//0,1,2,3�Ɠ���
	if (number2 == 3)number2 = 1;//0,1,2,1�Ɠ����悤�ɂ���
	//���C�u�����ŕ`��
	DrawGraph( 480, 430, enemy[number2], TRUE);//�`��
}



void Config::SoundAll() {
	if (select_sound == ON) {
		if(nowselectsound_flag)PlaySoundMem(nowselect_sound, DX_PLAYTYPE_BACK, TRUE);
		if (selectothersound_flag)PlaySoundMem(selectother_sound, DX_PLAYTYPE_BACK, TRUE);
	}
}
void Config::All() {
	nowselectsound_flag = false;
	selectothersound_flag = false;
	if (do_set == false) {
		Select_cScene();
	}
	else if (do_set == true) {
		switch (NowSelect) {
		case cDif:
			Select_Dif();
			break;
		case cBGM:
			Setting_BGM();
			break;
		case cSound:
			Setting_Sound();
			break;
		default:
			break;

		}
	}
	Draw();
	SoundAll();
	
	count++;
}