#include "input.h"

//=== マクロ・定数定義 ===
#define KEY_REPEAT_WAIT	(20)

//=== グローバル変数宣言 ===
BYTE g_KeyInput[256];
BYTE g_KeyPrevInput[256];
BYTE g_KeyRepeatCount[256];

HRESULT InitInput(void)
{
	return S_OK;
}
void UninitInput(void)
{

}
void UpdateInput(void)
{
	//windowsメッセージからとってくる為、微小なラグが発生する可能性がある
	//bool ks = (GetKeyState(VK_LEFT) & 0x8000) > 0; 

	//関数が呼ばれた時点のキー入力
	//bool aks = (GetAsyncKeyState(VK_LEFT) & 0x8000) > 0;

	//一度に全部取ってくる
	//BYTE key[256];
	//GetKeyboardState(key);
	//if ((key[VK_LEFT] & 0x80) > 0){	}
	
	//前のキー入力
	memcpy(g_KeyPrevInput, g_KeyInput,
		sizeof(g_KeyPrevInput));
	//今のキー入力
	GetKeyboardState(g_KeyInput);	//取ってこれなかったらfalseが返ってきたりする

	//リピートのカウント
	for (int i = 0; i < 256; i++)
	{
		if (IsPressInput(i)) {
			if (g_KeyRepeatCount[i] <= KEY_REPEAT_WAIT)
			g_KeyRepeatCount[i]++;

		}
		else
			g_KeyRepeatCount[i] = 0;
	}

}

bool IsPressInput(BYTE nVertKey)
{
	return (g_KeyInput[nVertKey] & 0x80) > 0;
}
bool IsTriggerInput(BYTE nVertKey)
{
//(前 ^今) & 今
	return
		((g_KeyPrevInput[nVertKey] ^ g_KeyInput[nVertKey]) &
		g_KeyInput[nVertKey] & 0x80) > 0;
}
bool IsReleaseInput(BYTE nVertKey)
{
	//(前 ^今) & 前
	return
		((g_KeyPrevInput[nVertKey] ^ g_KeyInput[nVertKey]) &
		g_KeyPrevInput[nVertKey] & 0x80) > 0;
}
bool IsRepeatInput(BYTE nVertKey)
{
	if (g_KeyRepeatCount[nVertKey] == 1) 
		return true;
	else if (g_KeyRepeatCount[nVertKey] > KEY_REPEAT_WAIT) 
		return true;
	return false;
}