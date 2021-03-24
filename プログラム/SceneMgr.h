#pragma once
#include "Config.h"
#include "Menu.h"
#include "Stop.h"
#include "Howto.h"
#include "SceneBase.h"
#include "define.h"
#include "Result.h"

//�V�[���̊Ǘ��N���X
class SceneMgr :public SceneBase
{
private:
	static eScene Scene;
	static eScene NextScene;
    
	Menu* menu = 0;
	Config* config=0;
	Stop* stop=0;
	Howto* howto = 0;
	Result* result = 0;
	//�T�E���h�n���h��
	int topsound;     //�g�b�v�ɖ߂�
	int gamestartsound;  //�Q�[���J�n
	int stopsound;  //�ꎞ��~
	int selectother_sound; //�Q�[���J�n�ȊO��I�񂾎��̉�

	//�n���h�����Ȃ炷���ǂ����̃t���O
	bool topsound_flag;
	bool gamestartsound_flag;
	bool stopsound_flag;
	bool selectothersound_flag;

private:
	SceneMgr();  //�Q�̃C���X�^���X���̋֎~�i�V���O���g���j
	void SoundAll();
	void Initialize(eScene scene);
	void Finalize(eScene scene);
public:
	void Update(); //�I�[�o�[���C�h
	void All();   //�I�[�o�[���C�h
	void Loop(); //Main�ŌĂяo�������s�֐�
	void ChangeScene(eScene nextScene);  //���̃V�[���������̂��̂ɂ���
	static SceneMgr& Instance() {//�N���X�ÓI�ϐ��A���g�̃C���X�^���X���i�[
		static SceneMgr scenemgr;//�ÓI�ϐ��Ƃ��Đ錾
		return scenemgr;
	}
};

