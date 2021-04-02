#include "Control.h"
#include "define.h"
#include "InputKey.h"
#include "Config.h"
#include "SceneMgr.h"
#include "Menu.h"
#include <fstream>
#include<string>
#include <sstream>
using namespace std;


//�R���X�g���N�^�i�f�[�^�̓ǂݍ��݂������Č��Initialize�ŏ�����)
Control::Control() {

	//data������
	memset(data, 0, sizeof(data));

	//Enemy�N���X�̃f�[�^���N���X�̃C���X�^���X�ɓ����
	FILE* fp;//�t�@�C���|�C���^
	char buf[100];
	int s;
	int row = 0;
	int col = 1;
	bool flag = false;
	memset(buf, 0, sizeof(buf));
	//�ǂݎ���p�Ńt�@�C�����J����
	if ((fopen_s(&fp, "IMAGE/enemydata.csv", "r")) != 0) MSG("�G���[");

	while (fgetc(fp) != '\n') {};//1�s�ڂ͉������Ȃ�

	while (1) {//�ǂݎ��I���܂Ń��[�v

		while (1) {//1�̃f�[�^��ǂݎ��܂Ń��[�v

			s = fgetc(fp);//1���������ǂݎ��

			if (s == EOF) {//���������Ȃ�΃t���O�𗧂ĂĂ��̃��[�v�𔲂���
				flag = true;
				break;
			}

			if (s != ',' && s != '\n') {//�R���}����s�ɂȂ�܂�buf�ɕ���������
				strcat_s(buf, (const char*)&s);
			}
			else {//�R���}����s�Ȃ炱�̃��[�v�𔲂���
				break;
			}
		}
		if (flag)  break;//�t���O�������Ă���Ȃ�t�@�C���ǂݎ��I���

		// ���Abuf�ɂ�Excel�̃Z��1���̃f�[�^�������Ă�
		switch (col) {//������ځH
		case 1: data[row].type = atoi(buf); break;//atoi�ō��̍s��type�Ƀf�[�^�𐔒l�Ƃ��ē����
		case 2: data[row].shottype = atoi(buf); break;
		case 3:	data[row].move_pattern = atoi(buf); break;
		case 4: data[row].shot_pattern = atoi(buf); break;
		case 5: data[row].speed = atoi(buf); break;
		case 6:data[row].intime = atoi(buf); break;
		case 7:data[row].stoptime = atoi(buf); break;
		case 8:data[row].shottime = atoi(buf); break;
		case 9:data[row].outtime = atoi(buf); break;
		case 10:data[row].x = atoi(buf); break;
		case 11:data[row].y = atoi(buf); break;
		case 12:data[row].hp = atoi(buf); break;
		case 13:data[row].item = atoi(buf); break;
		}
		memset(buf, 0, sizeof(buf));//buf��������
		++col;//������炷
		if (s == '\n') {//�s���I�������
			col = 1;//���1��ڂɖ߂�
			++row;//�s�����炷
		}
	}
	//�G�N���X�����
	for (int i = 0; i < ENEMY_NUM; i++) {
		enemy[i] = new Enemy(data[i].type, data[i].shottype, data[i].move_pattern, data[i].shot_pattern, data[i].speed, data[i].intime, data[i].stoptime, data[i].shottime, data[i].outtime, data[i].x, data[i].y, data[i].hp, data[i].item);

	}
	
	//���C�u�����ŉ����t�@�C���ǂݍ���
	sound_eshot = LoadSoundMem("MUSIC/enemyshot.mp3");
	sound_pshot = LoadSoundMem("MUSIC/playershot.mp3");
	sound_pdamage = LoadSoundMem("MUSIC/playerdamage.mp3");
	sound_edeath = LoadSoundMem("MUSIC/enemydeath.mp3");
	sound_graze = LoadSoundMem("MUSIC/graze.mp3");
	sound_item = LoadSoundMem("MUSIC/item.mp3");
	sound_gameover = LoadSoundMem("MUSIC/gameover.ogg");
	sound_gameclear = LoadSoundMem("MUSIC/clear.ogg");
	bossbgm = LoadSoundMem("MUSIC/boss.ogg");


	//���C�u������player���S�G�t�F�N�g�ǂݍ���
	if (LoadDivGraph("IMAGE/pdeath_efe1.png", 8, 8, 1, 120, 120, pdeath_efegh) == -1) {
		MSG("�G���[����");
	}
	//���C�u������enemy���S�G�t�F�N�g�ǂݍ���
	if (LoadDivGraph("IMAGE/edeath_efe1.png", 10, 5, 2, 320, 320, edeath_efegh) == -1) {
		MSG("�G���[����");
	}
	eefewidth = 320;
	eefeheight = 320;
	//�G�t�F�N�g�摜�̑傫��
	pefewidth = 120;
	pefeheight = 120;
	eefewidth = 320;
	eefeheight = 320;
	deathenemy_x = 0; 
	deathenemy_y = 0;

	//���C�u�����ŉ摜�ǂݍ���
	gameovergh = LoadGraph("IMAGE/over1.png");
	backmenu = LoadGraph("IMAGE/over2.png");
	cleargh = LoadGraph("IMAGE/clear.png");
	title = LoadGraph("IMAGE/title.png");
	bgmgh = LoadGraph("IMAGE/bgm.png");
	image = LoadGraph("IMAGE/image.png");
	gamestartgh = LoadGraph("IMAGE/gamestart.png");
}


//�f�X�g���N�^�i�Q�[���v���C���ŋ����I�����ꂽ�ꍇ�͂�����delete����)
Control::~Control()
{
	if (now_game) {
		//�e�N���X�̉��
		delete player;
		delete back;
		//�O���C�Y�N���X�̉��
		for (int i = 0; i < GRAZE_NUM; ++i) {
			delete graze[i];
		}

		delete score;

		//�A�C�e���N���X�̉��
		for (int i = 0; i < ITEM_NUM; ++i) {
			delete item[i];
		}
		delete boss;
		for (int i = 0; i < ENEMY_NUM; i++) {
			if (enemy[i] != NULL) {//�܂����ł��ĂȂ�enemy����������delete
				delete enemy[i];
			}
		}
	}
}

//player�̈ʒu�������̃|�C���^�ɗ^����
void Control::PlayerCoordinate(double* x, double* y) {
	double tempx = 0, tempy = 0;

	player->GetCoordinate(&tempx, &tempy);//���W���擾

	*x = tempx;//x�ɗ^����
	*y = tempy;//y�ɗ^����
}

//enemy�̈ʒu�������̃|�C���^�ɗ^����
void Control::EnemyCoordinate(int index, double* x, double* y) {
	double tempx = 0, tempy = 0;

	enemy[index]->GetCoordinate(&tempx, &tempy);//�Y��index�̓G�̍��W���擾

	*x = tempx;//x�ɗ^����
	*y = tempy;//y�ɗ^����
}

////Boss�̈ʒu�������̃|�C���^�ɗ^����
void Control::BossCoordinate(int index, double* x, double* y) {
	double tempx = 0, tempy = 0;

	boss->GetCoordinate(&tempx, &tempy);//���W���擾

	*x = tempx;
	*y = tempy;
}

void Control::Update() {
	SceneMgr& scenemgr = SceneMgr::Instance();

	//�Q�[�����I����ĂȂ���
	if (!game_over && !gameclear) {
		if (InputKey::GetKeyPush(KEY_INPUT_M)) { //M�L�[��������Ă�����
			scenemgr.ChangeScene(eScene::Scene_Menu);//�V�[�������j���[�ɕύX
		}
		else
			if (InputKey::GetKeyPush(KEY_INPUT_S)) { //S�L�[��������Ă�����
				scenemgr.ChangeScene(eScene::Scene_Stop);//�V�[�������j���[�ɕύX
			}
	}

	//�Q�[�����I�����RETURN�������ꂽ��
	if ((game_over || gameclear) && InputKey::GetKeyPush(KEY_INPUT_RETURN)) {
		scenemgr.ChangeScene(eScene::Scene_Result);//�V�[�������ʉ�ʂɕύX
	}
}


//���[�v���Ŏ��s�����֐�
void Control::All() {

	//�T�E���h�t���O��������
	gameover_soundflag = false;
	gameclear_soundflag = false;
	eshot_flag = false;
	pshot_flag = false;
	edeath_flag = false;
	pdamage_flag = false;
	graze_flag = false;
	itemsound_flag = false;
	boss_soundflag = false;
	boss_soundflag = false;

	back->All();//��ɔw�i
	player->All();//�v���C���[�L����

	//�t���O�������Ă���Ȃ�T�E���h�t���O�𗧂Ă�
	if (player->GetSoundshot()) {
		pshot_flag = true;
	}


	if (!boss->GetFlag()) {//�܂�boss���Ȃ�
		for (int i = 0; i < ENEMY_NUM; i++) {
			if (enemy[i] != NULL) {//�C���X�^���X����������Ă���Ȃ��
				//�t���O�������Ă���Ȃ�T�E���h�t���O�𗧂Ă�
				if (enemy[i]->GetSoundshot() == true) {
					eshot_flag = true;
				}

				if (enemy[i]->All() == true) {//endflag=true�Ȃ��
					delete enemy[i];//�N���X����
					enemy[i] = NULL;
				}
			}

		}
		EnemyAllJudge();//�����蔻��̏������s��
	}
	else {//Boss�o��
		boss->All();
		//�t���O�������Ă���Ȃ�T�E���h�t���O�𗧂Ă�
		if (boss->GetSoundshot()) eshot_flag = true;
		//�����蔻��̏������s��
		BossAllJudge();
	}

	if (game_count == BOSSTIME) {//�{�X�̏o�����ԂɂȂ�����
		boss->SetFlag(true);   //�{�X�̐����t���O�𗧂Ă�
		boss_soundflag = true;  //�{�X��BGM�t���O�𗧂Ă�
	}

	//�O���C�Y�̕`��
	for (int i = 0; i < GRAZE_NUM; i++) {
		graze[i]->All();
	}
	//Item�̕`��
	for (int i = 0; i < ITEM_NUM; i++) {
		if (item[i]->Getflag()) item[i]->All();
	}

	if (player->GetLife() == 0) { //�v���C����HP=0 �Q�[���I�[�o�[�̃t���O
		game_over = true;
	}



	//�E���̉�ʂ̕`��
	back->All2();//�E�̔w�i�摜
	score->All();//�X�R�A

	//���C�u�����ŕ����̕`��
	DrawGraph(SCORE_X, 360, title, TRUE);//�^�C�g��
	DrawGraph(SCORE_X, 390, bgmgh, TRUE);//������
	DrawGraph(SCORE_X, 420, image, TRUE);//�Ăۂ�q��

	//�Q�[���I�����̏���
	if (game_over) {
		player->SetLiveFlag();
		DrawGraph(20, 100, gameovergh, TRUE);
		DrawGraph(20, 150, backmenu, TRUE);

		//�n�C�X�R�A�̍X�V
		int temp1 = 0, temp2 = 0;
		temp1 = score->GetScore(SCOREDATA::SCORE);
		temp2 = score->GetScore(SCOREDATA::HIGH_SCORE);
		if (temp2 <= temp1) {
			score->SetScore(SCOREDATA::HIGH_SCORE, temp1);
		}
	}
	else if (gameclear) {
		DrawGraph(20, 100, cleargh, TRUE);
		DrawGraph(20, 150, backmenu, TRUE);

		//�n�C�X�R�A�̍X�V
		int temp1 = 0, temp2 = 0;
		temp1 = score->GetScore(SCOREDATA::SCORE);
		temp2 = score->GetScore(SCOREDATA::HIGH_SCORE);
		if (temp2 <= temp1) {
			score->SetScore(SCOREDATA::HIGH_SCORE, temp1);
		}
	}

	//�G�t�F�N�g�̏���
	EFECTALL();

	//�T�E���h�̏���
	SoundAll();
	if (game_count < 40) {
		DrawGraph(100, 100, gamestartgh, TRUE);
	}
	
	
		//�Q�[���S�̂̃J�E���g�𑝂₷
		++game_count;
}



//�~�`�̓����蔻����s��
bool Control::CircleJudge(double pcir, double ecir, double pcir_x, double ecir_x, double pcir_y, double ecir_y) {
	double sum_radius = pcir + ecir;//���a�̍��v
	double x_length = pcir_x - ecir_x;
	double y_length = pcir_y - ecir_y;

	//�s�^�S���X�̒藝����player�ƓG�̋������~�`�̔��a�̍��v���Z�����true
	if (sum_radius * sum_radius >= (x_length * x_length) + (y_length * y_length)) {
		return true;
	}
	else {
		return false;
	}
}

//�G�̓����蔻��̏������s��
void Control::EnemyAllJudge() {
	double px, py, ex, ey;//�G��player�̒e�̍��W

	//player�̒e�ƓG�̓����蔻��

	for (int i = 0; i < PLAYERSHOT_NUM; i++) {//�e�̐������`�F�b�N
		if (player->GetshotCoordinate(i, &px, &py)) {//player�̒e����ʂɂ���Ȃ�΍��W������
			for (int s = 0; s < ENEMY_NUM; s++) {//�G�̐�����
				if (enemy[s] != NULL && !enemy[s]->GetDeathflag()) {//�Y��s��enemy��NULL����Ȃ����A����ł��Ȃ��A�A�҂��Ă��Ȃ�
					enemy[s]->GetCoordinate(&ex, &ey);//�G�̍��W��Ⴄ
					if (CircleJudge(PLAYSHOT_RADIUS, ENEMY_RADIUS, px, ex, py, ey)) {//�~�`�̓����蔻�肪true�Ȃ��
						enemy[s]->SetDeathflag();//���S�t���O�𗧂Ă�
						player->SetShotflag(i, false);//���������e�̃t���O��߂���
						edeath_flag = true;//�G���S���t���O
						eefe_flag = true;//�G�t�F�N�g�̃t���O�𗧂Ă�
						enemy[s]->GetCoordinate(&deathenemy_x, &deathenemy_y);//�G�̎��S�ʒu���擾
						score->SetScore(SCOREDATA::SCORE, 100);//���|������100point
						for (int j = 0; j < ITEM_NUM; j++) {//�A�C�e�����o��������
							if (!item[j]->Getflag()) {//�Y����j�̃A�C�e�����o�����Ă��Ȃ�
								item[j]->Setflag(ex, ey, enemy[s]->GetItem());//�A�C�e�����Z�b�g����
								break;
							}
						}
					}
				}
			}
		}

	}
	double  px2, py2, ex2, ey2;//Player�ƓG�̒e�̍��W
	bool dam_tempflag = false;//�_���[�W���󂯂���true
	bool gra_tempflag = false;//�O���C�Y�����������Ȃ�true
	//�G�̒e��player�̓����蔻��
	if (player->GetDamageflag() == false) {//���͐����Ă���_�ł��Ă��Ȃ�

		player->GetCoordinate(&px2, &py2);//player�̍��W������
		for (int i = 0; i < ENEMY_NUM; i++) {//�G�̐�����
			if (enemy[i] != NULL) {//�Y��i��enemy��NULL����Ȃ�(����łĂ��e�͎c���Ă邩��deathflag�͂���Ȃ��j
				for (int s = 0; s < ENEMYSHOT_NUM; s++) {
					if (enemy[i]->GetshotCoordinate(s, &ex2, &ey2)) {//�G�i�Y��)�̒e����ʂɂ���Ȃ�΍��W��Ⴄ
						switch (enemy[i]->GetShottype()) {//�e�̎�ނŕύX
						case 0://�e1
							//�����蔻��̑O�ɃO���C�Y������s��
							if (CircleJudge(GRAZE_RADIUS, ENESHOT1_RADIOUS, px2, ex2, py2, ey2)) { //�~�`�̓����蔻�肪true�Ȃ��
								gra_tempflag = true;
							}
							//�~�`�̓����蔻�肪true�Ȃ��
							if (CircleJudge(PLAYER_RADIUS, ENESHOT1_RADIOUS, px2, ex2, py2, ey2)) {//�~�`�̓����蔻�肪true�Ȃ��
								dam_tempflag = true;

							}
							break;
						case 1://�e2
							//�����蔻��̑O�ɃO���C�Y������s��
							if (CircleJudge(GRAZE_RADIUS, ENESHOT2_RADIOUS, px2, ex2, py2, ey2)) { //�~�`�̓����蔻�肪true�Ȃ��
								gra_tempflag = true;
							}
							//�~�`�̓����蔻�肪true�Ȃ��
							if (CircleJudge(PLAYER_RADIUS, ENESHOT2_RADIOUS, px2, ex2, py2, ey2)) {//�~�`�̓����蔻�肪true�Ȃ��
								dam_tempflag = true;

							}
							break;
						case 2://�e3
							//�����蔻��̑O�ɃO���C�Y������s��
							if (CircleJudge(GRAZE_RADIUS, ENESHOT3_RADIOUS, px2, ex2, py2, ey2)) {//�~�`�̓����蔻�肪true�Ȃ��
								gra_tempflag = true;
							}
							//�~�`�̓����蔻�肪true�Ȃ��
							if (CircleJudge(PLAYER_RADIUS, ENESHOT3_RADIOUS, px2, ex2, py2, ey2)) { //�~�`�̓����蔻�肪true�Ȃ��
								dam_tempflag = true;
							}
							break;
						case 3://�e3
						//�����蔻��̑O�ɃO���C�Y������s��
							if (CircleJudge(GRAZE_RADIUS, ENESHOT4_RADIOUS, px2, ex2, py2, ey2)) {//�~�`�̓����蔻�肪true�Ȃ��
								gra_tempflag = true;
							}
							//�~�`�̓����蔻�肪true�Ȃ��
							if (CircleJudge(PLAYER_RADIUS, ENESHOT4_RADIOUS, px2, ex2, py2, ey2)) { //�~�`�̓����蔻�肪true�Ȃ��
								dam_tempflag = true;
							}
							break;
						}
						if (gra_tempflag) {//�O���C�Y��������
							if (!enemy[i]->GetGrazeflag(s)) {//���̒e�̃t���O�������ĂȂ��Ȃ痧�Ă�
								enemy[i]->SetGrazeflag(s);
								//�t���O�������ĂȂ��O���C�Y�̃t���O�𗧂Ăč��W��ݒ�
								for (int j = 0; j < GRAZE_NUM; j++) {
									if (!graze[j]->Getflag()) {
										graze[j]->Setflag(px2, py2);
										break;//���[�v�𔲂���
									}
								}
								//�X�R�A�����Z
								score->SetScore(SCOREDATA::GRAZE_SCORE, 1);
								score->SetScore(SCOREDATA::SCORE, 10);
								graze_flag = true;//�O���C�Y�̉��t���O�𗧂Ă�
							}
							gra_tempflag = false;//�O���C�Y����t���O��߂�

						}

						if (dam_tempflag) {//�_���[�W��������
							player->SetDamageflag();//�_���[�W�t���O�𗧂Ă�
							enemy[i]->SetShotflag(s, false);//���������e�̃t���O��߂�
							pdamage_flag = true;//�_���[�W���t���O
							pefe_flag = true;//�_���[�W�G�t�F�N�g�t���O
							if (player->GetLife() == 0) gameover_soundflag = true;//�_���[�W���O�Ȃ�Q�[���I�[�o�[�̉��o��
							dam_tempflag = false;
						}
					}

				}
			}
		}
		//player�ƃA�C�e���̓����蔻��
		double ix, iy;//�A�C�e���̈ʒu���擾�p
		for (int i = 0; i < ITEM_NUM; i++) {
			if (item[i]->Getflag()) {//�t���O�������Ă���i�o�����j�A�C�e�����������
				item[i]->Get_Position(&ix, &iy);//���W���擾
				if (CircleJudge(PLAYER_RADIUS, ITEM_RADIOUS, px2, ix, py2, iy)) {//���肪true��������
					switch (item[i]->GetType()) {//�^�C�v�ŗN����
					case 0://�X�R�A�A�C�e��
						score->SetScore(SCOREDATA::SCORE, 500);//500�_���Z
						break;
					case 1://power�A�C�e��
						player->SetPower(1);
						score->SetScore(SCOREDATA::POWER, player->GetPower());//�p���[����
						break;
					}
					item[i]->DeleteItem();//�A�C�e������
					itemsound_flag = true;//�T�E���h�n���h�����Z�b�g
				}
			}
		}


	}//if(player�����͐����Ă���_�ł��Ă��Ȃ�)�̏I���


	//HP�̍X�V
	score->SetScore(SCOREDATA::LIFE, player->GetLife());
}

//�{�X�̓����蔻��̏���
void Control::BossAllJudge() {
	double px, py, bx, by;//Boss�̒e��player�̍��W
	int boss_hp;//Boss��HP
	int item_number = 0;//Boss���o���A�C�e��
	int setix, setiy;//�A�C�e���̍��W��ݒ肷��p�ϐ�

	//player�̒e�ƓG�̓����蔻��
	if (!boss->GetNodamageFlag()) {//�{�X�͍��͖��G�ł͂Ȃ�
		for (int i = 0; i < PLAYERSHOT_NUM; i++) {//�e�̐������`�F�b�N
			if (player->GetshotCoordinate(i, &px, &py)) {//player�̒e����ʂɂ���Ȃ�΍��W������
				if (boss->GetFlag()) {//boss�������Ă���
					boss->GetCoordinate(&bx, &by);//boss�̍��W��Ⴄ
					if (CircleJudge(PLAYSHOT_RADIUS, BOSS_RADIUS, px, bx, py, by)) {//�~�`�̓����蔻�肪true�Ȃ��
						boss_hp = boss->SetHP(1);
						player->SetShotflag(i, false);//���������e�̃t���O��߂���
						score->SetScore(SCOREDATA::SCORE, 50);//���100point


						if (FirstBossHP * 2 / 3 >= boss_hp && boss->GetPreHP() > FirstBossHP * 2 / 3) {//HP��2/3�ɂȂ���

							befe_flag = true;//�_���[�W�G�t�F�N�g�t���O
							edeath_flag = true;//�e�����艹�t���O
							score->SetScore(SCOREDATA::SCORE, 5000);//5000point
							for (int j = 0; j < ITEM_NUM; j++) {//�A�C�e�����o��������
								if (!item[j]->Getflag()) {//�Y����j�̃A�C�e�����o�����Ă��Ȃ�
									setix = (rand() % 151 - 75) + bx;
									setiy = (rand() % 151 - 75) + by;
									item[j]->Setflag(setix, setiy, 0);//�X�R�A�A�C�e�����Z�b�g����
									++item_number;
									if (item_number == 7)break;//�A�C�e��7�R�o������I���
								}
							}
							boss->SetDamage();
						}
						else if (FirstBossHP * 1 / 3 >= boss_hp && boss->GetPreHP() > FirstBossHP * 1 / 3) {//HP��1/3�ɂȂ���
							befe_flag = true;//�_���[�W�G�t�F�N�g�t���O
							edeath_flag = true;//�e�����艹�t���O
							score->SetScore(SCOREDATA::SCORE, 5000);//5000point
							for (int j = 0; j < ITEM_NUM; j++) {//�A�C�e�����o��������
								if (!item[j]->Getflag()) {//�Y����j�̃A�C�e�����o�����Ă��Ȃ�
									setix = (rand() % 151 - 75) + bx;
									setiy = (rand() % 151 - 75) + by;
									item[j]->Setflag(setix, setiy, 0);//�X�R�A�A�C�e�����Z�b�g����
									++item_number;
									if (item_number == 7)break;//�A�C�e��7�R�o������I���
								}
							}
							boss->SetDamage();
						}
						else if (boss_hp < 0) {//hp��0�ɂȂ�����
							gameclear = true;
							boss->SetFlag(false);//�G���S
							befe_flag = true;//�_���[�W�G�t�F�N�g�t���O
							edeath_flag = true;//�e�����艹�t���O
							gameclear_soundflag = true;
							score->SetScore(SCOREDATA::SCORE, 10000);//10000point
							for (int j = 0; j < ITEM_NUM; j++) {//�A�C�e�����o��������
								if (!item[j]->Getflag()) {//�Y����j�̃A�C�e�����o�����Ă��Ȃ�
									setix = (rand() % 151 - 75) + bx;
									setiy = (rand() % 151 - 75) + by;
									item[j]->Setflag(setix, setiy, 0);//�X�R�A�A�C�e�����Z�b�g����
									++item_number;
									if (item_number == 15)break;//�A�C�e��15�R�o������I���
								}
							}
						}
					}
				}
			}
		}
	}

	double  px2, py2, bx2, by2;//Boss�̒e��Player�̍��W
	int shot_pattern;
	bool dam_tempflag = false;//�_���[�W���󂯂���true
	bool gra_tempflag = false;//�O���C�Y�����������Ȃ�true

	//Boss�̒e��player�̓����蔻��
	if (player->GetDamageflag() == false) {//���͐����Ă���_�ł��Ă��Ȃ�

		player->GetCoordinate(&px2, &py2);//player�̍��W������
		for (int s = 0; s < BOSSSHOT_NUM; s++) {//boss1�̒e�̐�����
			if (boss->GetshotCoordinate(s, &bx2, &by2, &shot_pattern)) {
				;
				switch (shot_pattern) {//bss�̒e�̎�ނŕύX(boss�͒e�̎��=�ł����̎�ނ�����type�łȂ�pattern�ōς�)
				case 0://�e1
					//�����蔻��̑O�ɃO���C�Y������s��
					if (CircleJudge(GRAZE_RADIUS, ENESHOT1_RADIOUS, px2, bx2, py2, by2)) { //�~�`�̓����蔻�肪true�Ȃ��
						gra_tempflag = true;
					}
					//�~�`�̓����蔻�肪true�Ȃ��
					if (CircleJudge(PLAYER_RADIUS, ENESHOT1_RADIOUS, px2, bx2, py2, by2)) {//�~�`�̓����蔻�肪true�Ȃ��
						dam_tempflag = true;

					}
					break;
				case 1://�e2
					//�����蔻��̑O�ɃO���C�Y������s��
					if (CircleJudge(GRAZE_RADIUS, ENESHOT2_RADIOUS, px2, bx2, py2, by2)) { //�~�`�̓����蔻�肪true�Ȃ��
						gra_tempflag = true;
					}
					//�~�`�̓����蔻�肪true�Ȃ��
					if (CircleJudge(PLAYER_RADIUS, ENESHOT1_RADIOUS, px2, bx2, py2, by2)) {//�~�`�̓����蔻�肪true�Ȃ��
						dam_tempflag = true;

					}
					break;
				case 2://�e3
					//�����蔻��̑O�ɃO���C�Y������s��
					if (CircleJudge(GRAZE_RADIUS, ENESHOT2_RADIOUS, px2, bx2, py2, by2)) {//�~�`�̓����蔻�肪true�Ȃ��
						gra_tempflag = true;
					}
					//�~�`�̓����蔻�肪true�Ȃ��
					if (CircleJudge(PLAYER_RADIUS, ENESHOT3_RADIOUS, px2, bx2, py2, by2)) { //�~�`�̓����蔻�肪true�Ȃ��
						dam_tempflag = true;
					}
					break;
				}
				if (gra_tempflag) {//�O���C�Y��������
					if (!boss->GetGrazeflag(s)) {//���̒e�̃t���O�������ĂȂ��Ȃ痧�Ă�
						boss->SetGrazeflag(s);
						//�t���O�������ĂȂ��O���C�Y�̃t���O�𗧂Ăč��W��ݒ�
						for (int j = 0; j < GRAZE_NUM; j++) {
							if (!graze[j]->Getflag()) {
								graze[j]->Setflag(px2, py2);
								break;//���[�v�𔲂���
							}
						}
						//�X�R�A�����Z
						score->SetScore(SCOREDATA::GRAZE_SCORE, 1);
						score->SetScore(SCOREDATA::SCORE, 10);
						graze_flag = true;//�O���C�Y�̉��t���O�𗧂Ă�
					}
					gra_tempflag = false;//�O���C�Y����t���O��߂�

				}

				if (dam_tempflag) {//�_���[�W��������
					player->SetDamageflag();//�_���[�W�t���O�𗧂Ă�
					boss->SetShotflag(s, false);//���������e�̃t���O��߂�
					pdamage_flag = true;//�_���[�W���t���O
					pefe_flag = true;//�_���[�W�G�t�F�N�g�t���O
					if (player->GetLife() == 0) gameover_soundflag = true;//�_���[�W���O�Ȃ�Q�[���I�[�o�[�̉��o��
					dam_tempflag = false;
					break;//���̒e�͔��肷��K�v�͂Ȃ����甲����
				}
			}

		}

		//player�ƃA�C�e���̓����蔻��
		double ix, iy;//�A�C�e���̈ʒu���擾�p
		for (int i = 0; i < ITEM_NUM; i++) {
			if (item[i]->Getflag()) {//�t���O�������Ă���i�o�����j�A�C�e�����������
				item[i]->Get_Position(&ix, &iy);//���W���擾
				if (CircleJudge(PLAYER_RADIUS, ITEM_RADIOUS, px2, ix, py2, iy)) {//���肪true��������
					switch (item[i]->GetType()) {//�^�C�v�ŗN����
					case 0://�X�R�A�A�C�e��
						score->SetScore(SCOREDATA::SCORE, 500);//500�_���Z
						break;
					case 1://power�A�C�e��
						player->SetPower(1);
						score->SetScore(SCOREDATA::POWER, player->GetPower());//�p���[����
						break;
					}
					item[i]->DeleteItem();//�A�C�e������
					itemsound_flag = true;//�T�E���h�n���h�����Z�b�g
				}
			}
		}

	}//if(player�����͐����Ă���_�ł��Ă��Ȃ�)�̏I���


	//HP�̍X�V
	score->SetScore(SCOREDATA::LIFE, player->GetLife());
}

//


//�G�t�F�N�g�̏���
void Control::EFECTALL() {
	int temp1, temp2;
	double px, py, bx, by;


	//���ꂼ��̃t���O�������Ă���Ȃ�
	if (eefe_flag) {
		temp1 = eefecount;

		//���C�u�����ŕ`��
		DrawGraph((int)deathenemy_x - eefewidth / 2, (int)deathenemy_y - eefeheight / 2, edeath_efegh[temp1], TRUE);
		++eefecount;
		if (eefecount == 10) { eefecount = 0; eefe_flag = false; }
	}

	if (pefe_flag) {
		player->GetCoordinate(&px, &py);
		temp2 = pefecount % 40 / 5;

		//���C�u�����ŕ`��
		DrawGraph((int)px - pefewidth / 2, (int)py - pefeheight / 2, pdeath_efegh[temp2], TRUE);
		++pefecount;
		if (pefecount == 40) { pefecount = 0; pefe_flag = false; }
	}
	if (befe_flag) {
		boss->GetCoordinate(&bx, &by);
		temp1 = eefecount;

		//���C�u�����ŕ`��
		DrawGraph((int)bx - eefewidth / 2, (int)bx - eefeheight / 2, edeath_efegh[temp1], TRUE);
		++eefecount;
		if (eefecount == 10) { eefecount = 0; befe_flag = false; }
	}
}


//�n�C�X�R�A��Ԃ�
int Control::GetHiscore() {
	return score->GetScore(SCOREDATA::HIGH_SCORE);
}

//���̏���
void Control::SoundAll() {

	if (Config::select_sound == ON) {
		//���C�u������if�̃t���O���������Ȃ�������̉����f�[�^���o�b�N�O���E���h�Đ�
		if (pshot_flag) PlaySoundMem(sound_pshot, DX_PLAYTYPE_BACK, TRUE);
		if (!game_over && eshot_flag) PlaySoundMem(sound_eshot, DX_PLAYTYPE_BACK, TRUE);
		if (pdamage_flag)PlaySoundMem(sound_pdamage, DX_PLAYTYPE_BACK, TRUE);
		if (edeath_flag)PlaySoundMem(sound_edeath, DX_PLAYTYPE_BACK, TRUE);
		if (graze_flag)PlaySoundMem(sound_graze, DX_PLAYTYPE_BACK, TRUE);
		if (itemsound_flag)PlaySoundMem(sound_item, DX_PLAYTYPE_BACK, TRUE);
		if (gameover_soundflag)PlaySoundMem(sound_gameover, DX_PLAYTYPE_BACK, TRUE);
		if (gameclear_soundflag)PlaySoundMem(sound_gameclear, DX_PLAYTYPE_BACK, TRUE);
	}
	if (Config::select_bgm == ON) {
		if (game_count == 0)PlaySoundMem(bgm, DX_PLAYTYPE_LOOP, TRUE);
		if (gameclear || game_over || boss_soundflag)StopSoundMem(bgm);
		if (boss_soundflag) PlaySoundMem(bossbgm, DX_PLAYTYPE_LOOP, TRUE);
			if (gameclear || game_over)StopSoundMem(bossbgm);
	}
}

//���ʂ������ɓn��
void Control::GetResult(int* x, int* y,int *z) {
	*x = score->GetScore(SCOREDATA::SCORE);
	*y = score->GetScore(SCOREDATA::GRAZE_SCORE);
	*z = score->GetScore(SCOREDATA::HIGH_SCORE);
}

//������
void Control::Initialize() {
	//�C���X�^���X�̍Đ���
	player = new Player;
	back = new Back;
	score = new Score;
	boss = new Boss;

	for (int i = 0; i < GRAZE_NUM; i++) {
		graze[i] = new Graze;
	}
	for (int i = 0; i < ITEM_NUM; i++) {
		item[i] = new Item;
	}
	for (int i = 0; i < ENEMY_NUM; i++) {
		enemy[i] = new Enemy(data[i].type, data[i].shottype, data[i].move_pattern, data[i].shot_pattern, data[i].speed, data[i].intime, data[i].stoptime, data[i].shottime, data[i].outtime, data[i].x, data[i].y, data[i].hp, data[i].item);

	}
	//�����t���O������
	eshot_flag = false;
	pshot_flag = false;
	pdamage_flag = false;
	edeath_flag = false;
	graze_flag = false;
	itemsound_flag = false;
	gameover_soundflag = false;
	gameclear_soundflag = false;
	//��������
	end_flag = false;
	game_over = false;
	gameclear = false;
	deathenemy_num = 0;
	eefe_flag = false;
	pefe_flag = false;
	befe_flag = false;
	now_game = true;
	eefecount = 0;
	pefecount = 0;
	deathenemy_x = 0;
	deathenemy_y = 0;



	//�{�X�̏����̗͂�ݒ�
	switch(Config::select_dif) {
	case Easy:
		FirstBossHP = EBOSS_HP;
		break;
	case Normal:
		FirstBossHP = NBOSS_HP;
		break;
	case Hard:
		FirstBossHP = HBOSS_HP;
		break;
	default:
		break;
	}

	//�n�C�X�R�A���X�V����
	//switch (Menu::stage) {
	//case STAGE1:
		score->SetScore(SCOREDATA::HIGH_SCORE, hiscore);
		//break;
	/*case STAGE2:
		score->SetScore(SCOREDATA::HIGH_SCORE, hiscore2);
		break;
	case STAGE3:
		score->SetScore(SCOREDATA::HIGH_SCORE, hiscore3);
		break;
	}*/

	switch (Menu::stage) {
	case STAGE1:
		bgm = LoadSoundMem("MUSIC/bgm.ogg");
		break;
	case STAGE2:
		bgm = LoadSoundMem("MUSIC/bgm3.ogg");
		break;
	case STAGE3:
		bgm = LoadSoundMem("MUSIC/bgm2.ogg");
		break;
	default:
		break;
	}



}

//�Q�[���̏I������
void Control::Finalize() {

	//���[�v�J�E���g�̏�����
	game_count = 0;
	//�e�N���X�̉��
	delete player;
	delete back;
	//�O���C�Y�N���X�̉��
	for (int i = 0; i < GRAZE_NUM; ++i) {
		delete graze[i];
	}
	delete score;

	//�A�C�e���N���X�̉��
	for (int i = 0; i < ITEM_NUM; ++i) {
		delete item[i];
	}
	delete boss;
	for (int i = 0; i < ENEMY_NUM; i++) {
		if (enemy[i] != NULL) {//�܂����ł��ĂȂ�enemy����������delete
			delete enemy[i];
		}
	}


	now_game = false;

	StopSoundMem(bgm);
	StopSoundMem(bossbgm);
}

