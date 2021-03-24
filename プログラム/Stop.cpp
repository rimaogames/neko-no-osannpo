#include "Stop.h"
#include "InputKey.h"
#include "define.h"
#include "SceneMgr.h"
#include "Control.h"
Stop::Stop() {
	stopgraphgh = LoadGraph("IMAGE/stop.png");    //�摜�̃��[�h
}
Stop::~Stop() {
	DeleteGraph(stopgraphgh);
}

//��ʂ̍X�V
void Stop::Update() {

	//SceneMgr�N���X�̎Q��
	SceneMgr& scenemgr = SceneMgr::Instance();
	//S�������ꂽ��
	if (InputKey::GetKeyPush(KEY_INPUT_S) != 0) {
		scenemgr.ChangeScene(eScene::Scene_Game);//�V�[�����Q�[���ɕύX�i�ĊJ�j
	}else
		//M�������ꂽ��
	if(	InputKey::GetKeyPush(KEY_INPUT_M) != 0) {
		scenemgr.ChangeScene(eScene::Scene_Menu);//�V�[�������j���[�ɕύX
	}
}

//���s
void Stop::All() {
	DrawGraph(0, 0, stopgraphgh,FALSE);//�`��
}