#include "InputKey.h"
#include "define.h"

char InputKey::keybuf[KEY] = { 0 };
int InputKey::keyframe[KEY] = { 0 };

// キーの入力状態更新
void InputKey::Update_Keystate() {

	// ライブラリで全てのキーの入力状態を得る
	GetHitKeyStateAll(keybuf);

	//キーの種類だけ
	for (int i = 0; i < KEY; i++) {

		//押されている
		if (keybuf[i] == 1) {
			//押されているならカウントする
			keyframe[i]++;
		}
		//押されていない
		else if (keybuf[i] == 0) {
			//0にする
			keyframe[i] = 0;
		}
	}
	
}

//引数のキーが押された？
bool InputKey::GetKey(int KeyCode) {
	return keyframe[KeyCode] > 0;
}

//引数のキーが押された＆押し始めか？
bool InputKey::GetKeyPush(int KeyCode) {
	return keyframe[KeyCode] == 1;
}