#include "InputKey.h"
#include "define.h"

char InputKey::keybuf[KEY] = { 0 };
int InputKey::keyframe[KEY] = { 0 };

// �L�[�̓��͏�ԍX�V
void InputKey::Update_Keystate() {

	// ���C�u�����őS�ẴL�[�̓��͏�Ԃ𓾂�
	GetHitKeyStateAll(keybuf);

	//�L�[�̎�ނ���
	for (int i = 0; i < KEY; i++) {

		//������Ă���
		if (keybuf[i] == 1) {
			//������Ă���Ȃ�J�E���g����
			keyframe[i]++;
		}
		//������Ă��Ȃ�
		else if (keybuf[i] == 0) {
			//0�ɂ���
			keyframe[i] = 0;
		}
	}
	
}

//�����̃L�[�������ꂽ�H
bool InputKey::GetKey(int KeyCode) {
	return keyframe[KeyCode] > 0;
}

//�����̃L�[�������ꂽ�������n�߂��H
bool InputKey::GetKeyPush(int KeyCode) {
	return keyframe[KeyCode] == 1;
}