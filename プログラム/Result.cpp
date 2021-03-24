#include "Result.h"
#include "define.h"
#include "InputKey.h"
#include "SceneMgr.h"
#include "Control.h"
//���ʉ��

//�R���X�g���N�^�ŉ��̓ǂݍ��݂����s���Č��initialize��
Result::Result() {
	//���C�u�����ŉ��̓ǂݍ���
	result_sound = LoadSoundMem("MUSIC/result.ogg");
	up_sound = LoadSoundMem("MUSIC/up.ogg");

}



//������
void Result::Initialize() {
	//���C�u�����ŉ摜�̓ǂݍ���
	LoadDivGraph("IMAGE/number.png", 10, 10, 1, 17, 29, g_number);
	resultgh = LoadGraph("IMAGE/result.png");
	upgh = LoadGraph("IMAGE/up.png");
	nextgh = LoadGraph("IMAGE/next.png");
	endgh = LoadGraph("IMAGE/end.png");

    //���ʂ��Z�b�g
	SetResult();
    //��������
	count = 0;
	endflag = false;
	resound_flag = false;
	upsound_flag = false;

	//�R���g���[���̎Q��
	Control& control = Control::Instance();
	//�n�C�X�R�A����������
	hiscore = control.GetHiscore();
}

//�I���̏���
void Result::Finalize() {
	DeleteGraph(g_number[9]);
	DeleteGraph(resultgh);
	DeleteGraph(upgh);
	DeleteGraph(nextgh);
	DeleteGraph(endgh);
}

//���ʂ��Z�b�g
void Result::SetResult() {
	int temp1, temp2, temp3;
	Control& control = Control::Instance();
	control.GetResult(&temp1,&temp2, &temp3);

	rescore = temp1;
	regraze = temp2;
	rehigh_score = temp3;
	
}

//�`��
void Result::Draw() {
	DrawGraph(0, 0, resultgh, FALSE);
	char buf[100];
	memset(buf, 0, sizeof(buf));
	int h_num = 0, s_num = 0, g_num = 0;


	//�G���^�[�L�[����������J�E���g�𑝂₷
	if (count < 2&& InputKey::GetKeyPush(KEY_INPUT_RETURN) != 0) {
		resound_flag = true;//�T�E���h�t���O�𗧂Ă�
		count++;
	}
	//3��ڂ̓n�C�X�R�A�X�V���ǂ����łǂ����̉���炷���ς���
	else if (count == 2 && InputKey::GetKeyPush(KEY_INPUT_RETURN) != 0) {
		count++;
		//�n�C�X�R�A�X�V
		if (rescore ==rehigh_score) {
			upsound_flag = true;
		}
		//�n�C�X�R�A�X�V���ĂȂ�
		else {
			resound_flag = true;
		}
	}
	if (count == 3)endflag = true;

	if (count > 0) {
		g_num = sprintf_s(buf, "%d", regraze);//buf�ɃO���C�Y������Bnum�ɂ͕�����������
		for (int i = 0; i < g_num; i++) {
			//���C�u�����Œl�̏����n�߂�SOCRE_X+20�B��y���W45�ɐ������L���B
			//buf�ɂ�1�o�C�g���������i�[����Ă���Bg_number[buf[i]-0]�Ő�����buf[i]-���擾
			DrawGraph((SCORE_X + 20) + (i * NUMBER_LONG), 130, g_number[buf[i] - '0'], TRUE);
		}
	}
	if (count > 1) {
		s_num = sprintf_s(buf, "%d", rescore);//buf�ɃX�R�A������Bnum�ɂ͕�����������
		for (int i = 0; i < s_num; i++) {
			//���C�u�����Œl�̏����n�߂�SOCRE_X+20�B��y���W45�ɐ������L���B
			//buf�ɂ�1�o�C�g���������i�[����Ă���Bg_number[buf[i]-0]�Ő�����buf[i]-���擾
			DrawGraph((SCORE_X + 20) + (i * NUMBER_LONG), 215, g_number[buf[i] - '0'], TRUE);
		}
	}
	if (count > 2) {
		h_num = sprintf_s(buf, "%d", rehigh_score);//buf�Ƀn�C�X�R�A������Bnum�ɂ͕�����������
		for (int i = 0; i < h_num; i++) {
			//���C�u�����Œl�̏����n�߂�SOCRE_X+20�B��y���W45�ɐ������L���B
			//buf�ɂ�1�o�C�g���������i�[����Ă���Bg_number[buf[i]-0]�Ő�����buf[i]-���擾
			DrawGraph((SCORE_X + 20) + (i * NUMBER_LONG), 300, g_number[buf[i] - '0'], TRUE);


			//�n�C�X�R�A�X�V�Ȃ�n�C�X�R�A�X�V�Ƃ�������������
			if (rescore == rehigh_score) {
				DrawGraph(100, 350, upgh, TRUE);
			}
		}
	}

	//�Ō�ȊO��[����]����������
	if (count < 3) {
		DrawGraph(440, 420, nextgh, TRUE);
	}
	//�Ō��[�߂�]����������
	else if (count >= 3) {
		DrawGraph(440, 420, endgh, TRUE);
	}
}
	//���̏���
void Result::SoundAll() {
	//���C�u�����ŉ���炷
	if (resound_flag)PlaySoundMem(result_sound, DX_PLAYTYPE_BACK,TRUE);
	if (upsound_flag)PlaySoundMem(up_sound, DX_PLAYTYPE_BACK,TRUE);
}

//��ʂ̍X�V
void Result::Update() {
	//SceneMgr�N���X�̎Q��
	SceneMgr& scenemgr = SceneMgr::Instance();
	//�\�����I������G�������ꂽ��
	if (endflag && InputKey::GetKeyPush(KEY_INPUT_RETURN) != 0) {
		scenemgr.ChangeScene(eScene::Scene_Menu);//�V�[�����Q�[���ɕύX�i�ĊJ�j
	}


}

//���s
void Result::All() {
	//�T�E���h�t���O��������
	resound_flag = false;
	upsound_flag=false;

	//�`��
	Draw();
	//�ݒ�Ō��ʉ���炷�ݒ�Ȃ特��炷
	if (Config::select_sound == ON)SoundAll();
}
