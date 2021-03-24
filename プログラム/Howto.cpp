#include "Howto.h"
#include "define.h"
#include "InputKey.h"
#include "SceneMgr.h"

Howto::Howto() {

	howgraphgh = LoadGraph("IMAGE/howto.png");    //���C�u�����ŉ摜�̃��[�h
}
Howto::~Howto() {
	DeleteGraph(howgraphgh);
}
void Howto::Update() {

	//SceneMgr�N���X�̎Q��
	SceneMgr& scenemgr = SceneMgr::Instance();
	if (InputKey::GetKeyPush(KEY_INPUT_RETURN)) {
		scenemgr.ChangeScene(eScene::Scene_Menu);//�V�[�������j���[�ɕύX
	}
}

void Howto::All() {
	DrawGraph(0, 0, howgraphgh, FALSE);
}
