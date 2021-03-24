#pragma once
#include "define.h"

//キーパッドの入力の管理クラス
class InputKey
{
private:
	static char keybuf[KEY]; // 全てのキーの入力状態を格納する為の変数
	static int keyframe[KEY];  // キーの入力状態格納用変数
public:
	void Update_Keystate(); // キーの入力状態更新
	static bool GetKey(int KeyCode); //引数のキーが入力されたか？
	static bool GetKeyPush(int KeyCode); //引数のキーが押された瞬間であるか(選択画面に使う）
};

