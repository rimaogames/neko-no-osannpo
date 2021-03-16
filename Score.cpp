#include "Score.h"
#include "define.h"
#include <string>
Score::Score() {

	//���C�u�����ŉ摜�ǂݍ���
	g_highscore = LoadGraph("IMAGE/highscore.png");
	g_score = LoadGraph("IMAGE/score.png");
	g_graze = LoadGraph("IMAGE/b_graze.png");
	g_hp = LoadGraph("IMAGE/HP.png");
	g_power = LoadGraph("IMAGE/power.png");
	LoadDivGraph("IMAGE/number.png",10,10,1,17,29,g_number);
	
	//������
	high_score = 0;
	score = 0;
	graze_score = 0;
	life = 0;
	power = 0;
}

//�`��
void Score::Draw() {
	char buf[100];
	memset(buf, 0, sizeof(buf));

	int h_num,s_num,g_num,l_num,p_num;//�n�C�X�R�A�A�X�R�A�A�O���C�Y�Alife,power�̕�����������p
	//���C�u�����A���W(�����P,�����Q)�Ɉ����R�������B�����S���摜�̓����x��L���ɂ��邩�ǂ���
	DrawGraph(SCORE_X, 10,g_highscore, TRUE);
	DrawGraph(SCORE_X, 90, g_score, TRUE);
	DrawGraph(SCORE_X, 170, g_graze, TRUE);
	DrawGraph(SCORE_X, 240, g_hp, TRUE);
	DrawGraph(SCORE_X, 300, g_power, TRUE);

	h_num = sprintf_s(buf, "%d", high_score);//buf�Ƀn�C�X�R�A������Bnum�ɂ͕�����������
	for (int i = 0; i < h_num; i++) {
		//���C�u�����Œl�̏����n�߂�SOCRE_X+20�B��y���W45�ɐ������L���B
		//buf�ɂ�1�o�C�g���������i�[����Ă���Bg_number[buf[i]-0]�Ő�����buf[i]-���擾
		DrawGraph((SCORE_X + 20) + (i * NUMBER_LONG), 45, g_number[buf[i] - '0'], TRUE);
	}
	//�ȉ����l

	s_num = sprintf_s(buf, "%d", score);//buf�ɃX�R�A������Bs_num�ɂ͕�����������
	for (int i = 0; i < s_num; i++) {
		//
		DrawGraph((SCORE_X + 20) + (i * NUMBER_LONG), 125, g_number[buf[i] - '0'], TRUE);
	}

	g_num = sprintf_s(buf, "%d", graze_score);//buf�ɃO���C�Y������Bg_num�ɂ͕�����������
	for (int i = 0; i < g_num; i++) {
		DrawGraph((SCORE_X + 20) + (i * NUMBER_LONG), 200, g_number[buf[i] - '0'], TRUE);
	}

	l_num = sprintf_s(buf, "%d", life);//buf��life������Bl_num�ɂ͕�����������
	for (int i = 0; i < l_num; i++) {
		DrawGraph((SCORE_X +20)+ (i * NUMBER_LONG), 270, g_number[buf[i] - '0'], TRUE);
	}

		p_num = sprintf_s(buf, "%d", power);//buf��power������Bp_num�ɂ͕�����������
	for (int i = 0; i < p_num; i++) {
		DrawGraph((SCORE_X + 20) + (i * NUMBER_LONG), 330, g_number[buf[i] - '0'], TRUE);
	}



}
//�����̎�ނ̒l��ݒ�
void Score::SetScore(SCOREDATA data, int a) {//�w�肵��SCOREDATA��a�𑫂�
	switch (data) {//data�̓��e�ŕς���
	case SCOREDATA::HIGH_SCORE://�n�C�X�R�A�ݒ�
		high_score = a;
		break;
	case SCOREDATA::SCORE://�X�R�A�ݒ�
		score += a;
		break;
	case SCOREDATA::GRAZE_SCORE://�O���C�Y�X�R�A�ݒ�
		graze_score += a;
		break;
	case SCOREDATA::LIFE:
		life  = a;//life��a�̒l�ɐݒ�
		if (life < 0)life = 0;
		break;
	case SCOREDATA::POWER:
		power = a;
	}
}

//�����̎�ނ̒l���擾
int Score::GetScore(SCOREDATA data) {
	switch (data) {
	case SCOREDATA::HIGH_SCORE:
		return high_score;
		break;
	case SCOREDATA::SCORE:
		return score ;
		break;
	case SCOREDATA::GRAZE_SCORE:
		return graze_score;
		break;
	case SCOREDATA::LIFE:
		return life;
		break;
	case SCOREDATA::POWER:
		return power;
		break;
	}

	//���Ă͂܂�Ȃ��Ȃ�-1
	return -1;
}

//control�ŌĂяo�������s�֐�
void Score::All() {
	Draw();
}