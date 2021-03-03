#include "input.h"

//=== �}�N���E�萔��` ===
#define KEY_REPEAT_WAIT	(20)

//=== �O���[�o���ϐ��錾 ===
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
	//windows���b�Z�[�W����Ƃ��Ă���ׁA�����ȃ��O����������\��������
	//bool ks = (GetKeyState(VK_LEFT) & 0x8000) > 0; 

	//�֐����Ă΂ꂽ���_�̃L�[����
	//bool aks = (GetAsyncKeyState(VK_LEFT) & 0x8000) > 0;

	//��x�ɑS������Ă���
	//BYTE key[256];
	//GetKeyboardState(key);
	//if ((key[VK_LEFT] & 0x80) > 0){	}
	
	//�O�̃L�[����
	memcpy(g_KeyPrevInput, g_KeyInput,
		sizeof(g_KeyPrevInput));
	//���̃L�[����
	GetKeyboardState(g_KeyInput);	//����Ă���Ȃ�������false���Ԃ��Ă����肷��

	//���s�[�g�̃J�E���g
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
//(�O ^��) & ��
	return
		((g_KeyPrevInput[nVertKey] ^ g_KeyInput[nVertKey]) &
		g_KeyInput[nVertKey] & 0x80) > 0;
}
bool IsReleaseInput(BYTE nVertKey)
{
	//(�O ^��) & �O
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