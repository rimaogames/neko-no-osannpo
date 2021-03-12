#include "Player.h"
#include "define.h"

//�R���X�g���N�^
Player::Player()
{
	//player�摜�ǂݍ���
	if (LoadDivGraph("Player.png", 12, 3, 4, 32, 32, playergh) == -1){
 		MSG("�G���[����");
    }
	if (LoadDivGraph("player2.png", 12, 3, 4, 32, 32, playergh2) == -1) {
		MSG("�G���[����");
	}
	//player�摜�̑傫��
	width = 32;
	height = 32;

	//shot�摜�ǂݍ���
	int temp = LoadGraph("playershot.png");
	int w,h;
	GetGraphSize(temp, &w,&h);

	//������
	move = 1.0f;
	xcount = 0;
	ycount = 0;
	count = 0;
	ix = 0;
	iy = 0;
	result = 0;
	memset(shot, 0, sizeof(shot));
	live = true;
	damage = false;
	player_hp = 10;
	damcount = 0;
	power = 0;
	powerup_flag = false;

	//�����̈ʒu
	x = 180;
    y = 400;

	//shot�ɉ摜�ƃT�C�Y�����ď�����
	for (int i = 0; i < PLAYERSHOT_NUM; i++) {
		shot[i].shotgh = temp;
		shot[i].flag = false;
		shot[i].width = w;
		shot[i].height = h;
	}
}

//���@�̈ړ��֐�
void Player::Move() {

	//�΂߈ړ��������瑬�x�𗎂Ƃ�
	if (CheckHitKey(KEY_INPUT_LEFT) || CheckHitKey(KEY_INPUT_RIGHT)) {
		if (CheckHitKey(KEY_INPUT_UP) || CheckHitKey(KEY_INPUT_DOWN)) {
			move = 0.71f;
		}
		else {
			move = 1.0f;
		}
	}else if (CheckHitKey(KEY_INPUT_UP) || CheckHitKey(KEY_INPUT_DOWN)) {
		move = 1.0f;
	}
	//�����ꂽ�{�^���ɍ��킹�Ĉړ�=4*�ړ��W��
	if (CheckHitKey(KEY_INPUT_LEFT))   x -= (int)PLAYER_SPEED * move;
	if (CheckHitKey(KEY_INPUT_RIGHT))  x += (int)PLAYER_SPEED * move;
	if (CheckHitKey(KEY_INPUT_UP))     y -= (int)PLAYER_SPEED * move;
	if (CheckHitKey(KEY_INPUT_DOWN))   y += (int)PLAYER_SPEED * move;

	//��ʂ̒[�ł͎~�܂�B
	if (x < width/2 )x = width/2;                    //x-width/2<0(�摜�̍��[��0����)�Ȃ�x-width/2=0
	if (x > WIDTH- width / 2)x = WIDTH - width / 2;     //x+width/2>390(�摜�̉E�[��390�𒴂���)�Ȃ�x+width/2=390
	if (y < height / 2)y = height / 2;               //y-height/2<0(�摜�̏オ0�����j�Ȃ�y-height/2=0
	if (y > HEIGHT - height / 2)y = HEIGHT - height / 2;   //y+height/2>480(�摜�̉���480�𒴂���j�Ȃ�y+height/2=480
	
	//���̕����L�[�������Ă���Ԃ͑Ή������J�E���^�𑝂₵�A���񐔕��J�E���^���������Ȃ�摜�����̓���̂��̂ɐ؂�ւ���
	if (CheckHitKey(KEY_INPUT_LEFT)){
		if(xcount<0) xcount=0;
		++xcount;
	}
	if (CheckHitKey(KEY_INPUT_RIGHT)) {
		if (xcount > 0) xcount = 0;
		--xcount;
	}
	if (CheckHitKey(KEY_INPUT_UP)) {
		if (ycount < 0) ycount = 0;
		++ycount;
	}
	if (CheckHitKey(KEY_INPUT_DOWN)) {
		if (ycount > 0) ycount = 0;
		--ycount;
	}
	//count����摜�̓Y�������߂�
	ix = abs(xcount) % 30 / 10;//|xcount|%30/10=0����29��10�Ŋ����0����܂ł̒l�𓾂�=10count���Ƃɉ摜��ς���
	iy = abs(ycount) % 30 / 10;//|ycount|%30/10

	//xcount>0�͍������B2�s�ڂ̐擪�Y���𑫂��B
	if (xcount > 0) {
		ix += 3;
		result = ix;//3~5
	}
	else if (xcount < 0) {//xcoount<0�͉E�����B3�s�ڂ̐擪�Y���𑫂��B
		ix += 6;
		result = ix;//6~8
	}

	//ycount>0�͏�����B4�s�ڂ̐擪�Y���𑫂��B
	if (ycount > 0) {
		iy += 9;
		result = iy;//9~11
	}
	else if (ycount < 0) {//ycount<0�͉������B�擪�Y����0�Ȃ̂ŉ������Ȃ��Ă悢�B
		//iy += 0;
		result = iy;
	}

	//�΂߈ړ��̎��͏�i���j������
	if (move == 0.71f) result = iy;

	//�L�[���͖����̎���count�����Z�b�g
	if (CheckHitKey(KEY_INPUT_LEFT) != 1 && CheckHitKey(KEY_INPUT_RIGHT) != 1) {
		xcount = 0;
	}
	if (CheckHitKey(KEY_INPUT_UP) != 1 && CheckHitKey(KEY_INPUT_DOWN) != 1) {
		ycount = 0;
	}

}
void Player::Shot(){

	int num = 0;
	soundshot = false;
	if (!damage) {//�_���[�W��H����ĂȂ����͑łĂ�
	//6���[�v���Ƃɔ��ˁi�L�[�����Ă���j
		//�L�[��������Ă��邩��4���[�v�Ɉ��
		if (CheckHitKey(KEY_INPUT_Z) && count % 4 == 0) {
			for (int i = 0; i < PLAYERSHOT_NUM; ++i) {
				if (shot[i].flag == false) {//���˂���Ă��Ȃ��e�𔭎˂�����
					if (power < 5) {//�p���[��5�����͕��ʂ̃V���b�g
						shot[i].flag = true;
						shot[i].x = x;
						shot[i].y = y;
						break;
					}else if (power >= 5) {
						if (num == 0) {
							shot[i].flag = true;
							shot[i].x = x;
							shot[i].y = y;
						}
						else if (num == 1) {
							shot[i].flag = true;
							shot[i].x = x+25;
							shot[i].y = y+10;
						}
						else if (num == 2) {
							shot[i].flag = true;
							shot[i].x = x - 25;
							shot[i].y =y+ 10;
						}
						++num;
						if (num == 3)break;
					}
				}
			}
			soundshot = true;//���̃t���O�𗧂Ă�
		}
	}
	//�e�̈ړ�������
	for (int i = 0; i < PLAYERSHOT_NUM;++i) {
		if (shot[i].flag) {//i�Ԗڂ̒e�����˂��Ă���
			shot[i].y -= SHOT_SPEED;//����14�ňړ�
			//��ʊO�ɂł���flag��߂�
			if (shot[i].y < 0) shot[i].flag = false;
		}
	}
}
void Player::Draw() {
	//shot�`��
	for (int i = 0; i<PLAYERSHOT_NUM;i++){
		if (shot[i].flag) {
			DrawGraph((int)shot[i].x-(int)shot[i].width/2,(int)shot[i].y-(int)shot[i].height/2, (int)shot[i].shotgh, TRUE);
		}
	}
	//�����Ă���̂Ȃ�Player�`��
	if (live && damage==false) {//���̓_���[�W��H����Ă��Ȃ�
		DrawGraph((int)x - width / 2, (int)y - height / 2, playergh[result], TRUE);//(x,y)���摜�̒��S�ɂȂ�悤��
	}
	else if (live && damage == true) {//�_���[�W��H����Ă��܂���
		if (damcount < 100) {//�_���[�W��H�����150���[�v���͓_��
			if (damcount % 2==0) {//�_���[�W�𕉂���2�J�E���g��1��
				SetDrawBlendMode(DX_BLENDMODE_ALPHA,0);//���u�����f�B���O��Pal��0�i0�ɋ߂�������)�Ŏw��
				DrawGraph((int)x - width / 2,(int)y - height/2, playergh[result],TRUE);//�ݒ肵�����[�h�ŕ`��
				SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);//�ݒ�����ɖ߂�
			}else {
				DrawGraph((int)x - width / 2, (int)y - height/2, playergh[result], TRUE);
			}
		}
		++damcount;
		if (damcount == 100) {
			damage = false;
			damcount = 0;
		}
	}
	if (live&&power >= 5) {
		DrawGraph((int)x + 23 - width / 2, (int)y +10 - height / 2, playergh2[result], TRUE);//(x,y)���摜�̒��S�ɂȂ�悤
		DrawGraph((int)x - 23 - width / 2, (int)y + 10 - height / 2, playergh2[result], TRUE);//(x,y)���摜�̒��S�ɂȂ�悤
	}
}
void Player::GetCoordinate(double* x, double* y) {
	*x = this->x;//�|�C���^��player��x���W��^����
	*y = this->y;//�|�C���^��player��y���W��^����

}
bool Player::GetSoundshot(){
	return soundshot;
}
void Player::SetShotflag(int index, bool flag) {
	shot[index].flag = flag;
  }
bool Player::GetshotCoordinate(int index, double* x, double* y) {
	if (shot[index].flag ) {
		*x = shot[index].x;//x���W
		*y = shot[index].y;//y���W
		return true;//��ʏ�ɂ��鎞��true��Ԃ�
	}else {
		return false;//��ʂɂȂ��Ȃ�false
	}
}
void Player::SetDamageflag(){
	damage = true;
	--player_hp;
}
bool Player::GetDamageflag() {
	return damage;
}
int Player::GetLife() {
	return player_hp;
}
void Player::SetPower(int a) {
	power += a;
	if (power > 10)power = 10;

	if (power > 5) {
		powerup_flag = true;
	}
	else if (power <= 5) {
		powerup_flag = false;
	}
}
int Player::GetPower() {
	return power;
}
void Player::SetLiveFlag() {
	live = false;
}
void Player::All() {
	
	Move();//�_���[�W�𕉂��ē_�ł��ĂȂ����͓�����
	Shot();
	Draw();
	++count;
}