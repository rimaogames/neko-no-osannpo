#pragma once
#include "define.h"

//�L�[�p�b�h�̓��͂̊Ǘ��N���X
class InputKey
{
private:
	static char keybuf[KEY]; // �S�ẴL�[�̓��͏�Ԃ��i�[����ׂ̕ϐ�
	static int keyframe[KEY];  // �L�[�̓��͏�Ԋi�[�p�ϐ�
public:
	void Update_Keystate(); // �L�[�̓��͏�ԍX�V
	static bool GetKey(int KeyCode); //�����̃L�[�����͂��ꂽ���H
	static bool GetKeyPush(int KeyCode); //�����̃L�[�������ꂽ�u�Ԃł��邩(�I����ʂɎg���j
};

