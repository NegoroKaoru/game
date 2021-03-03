//=============================================================================
//
// �T�E���h���� [sound.cpp]
// Author : AKIRA TANAKA
//
//=============================================================================
#define USE_SOUND
#include "sound.h"
#if (_WIN32_WINNT >= 0x0602)
#pragma comment(lib, "xaudio2.lib")
#endif

#include "SoundData.h"

//*****************************************************************************
// �p�����[�^�\���̒�`
//*****************************************************************************
typedef struct
{
	LPCTSTR	pFilename;		// �t�@�C����
	BYTE	nCntLoop;		// ���[�v�J�E���g
	SoundData sound;
} SOUNDPARAM;


// �e���f�ނ̃p�����[�^
SOUNDPARAM g_aParam[SOUND_LABEL_MAX] =
{
	{"data/BGM/op (online-audio-converter.com).wav", -1},		//�I�[�v�j���O
	{"data/BGM/stage1 (online-audio-converter.com).wav", -1},		// �X�e�[�W�P��BGM
	{ "data/BGM/stage2 (online-audio-converter.com).wav", -1 },		// �X�e�[�W2��BGM
	{ "data/BGM/boss.wav", -1 },									// �{�X��BGM
	{"data/BGM/shop (online-audio-converter.com).wav", -1},		//�V���b�vBGM
	{"data/SE/death.wav", 0},		//�c�@�����鉹
	{"data/SE/decide000.wav", 0},		// ���艹
	{"data/SE/cancel000.wav", 0},		// �L�����Z����
	{"data/SE/select000.wav", 0},		// �I����
	{"data/SE/shot000.wav", 0},		// �e���ˉ�
	{"data/SE/lockon000.wav", 0},		// ���b�N�I����
	{"data/SE/coin.wav", 0},			// �R�C����
	{"data/SE/guard000.wav", 0},		// �K�[�h��
	{"data/SE/explosion000.wav", 0},	// ������
	{"data/SE/jump000.wav", 0},		// �W�����v��
	{"data/SE/money.wav", 0},		// �V���b�v�Ŕ������i�����j
	{ "data/SE/cancel (online-audio-converter.com).wav", 0 },		//�V���b�v�Ŕ������i�����j
	{ "data/SE/barrierBreak.mp3", 0 },		//�o���A�j��
	{ "data/SE/cursor.wav", 0 },		//�J�[�\��
};

//=============================================================================
// ������
//=============================================================================
HRESULT InitSound(HWND hWnd)
{
#ifdef USE_SOUND
	HRESULT hr;

	hr = InitSoundData();

	// �T�E���h�f�[�^�̏�����
	for (int nCntSound = 0; nCntSound < SOUND_LABEL_MAX; nCntSound++)
	{
		CreateSound(g_aParam[nCntSound].pFilename, &g_aParam[nCntSound].sound, g_aParam[nCntSound].nCntLoop == -1);
	}
#endif

	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void UninitSound(void)
{
#ifdef USE_SOUND
	// �ꎞ��~
	for(int nCntSound = 0; nCntSound < SOUND_LABEL_MAX; nCntSound++)
	{
		// �ꎞ��~
		g_aParam[nCntSound].sound.pSource->Stop(0);
		ReleaseSound(&g_aParam[nCntSound].sound);
	}
	
	UninitSoundData();
#endif
}

//=============================================================================
// �Z�O�����g�ꎞ��~
//=============================================================================
void PauseSound(SOUND_LABEL label)
{
#ifdef USE_SOUND
	PauseSound(&g_aParam[label].sound);
#endif

}

//=============================================================================
// �Z�O�����g�Đ�(��~)
//=============================================================================
HRESULT PlaySound(SOUND_LABEL label)
{
#ifdef USE_SOUND
	PlaySound(&g_aParam[label].sound);
#endif

	return S_OK;
}

//=============================================================================
// �Z�O�����g��~
//=============================================================================
void StopSound(SOUND_LABEL label)
{
#ifdef USE_SOUND
	StopSound(&g_aParam[label].sound);
#endif
}

//=============================================================================
// �Z�O�����g��~
//=============================================================================
void StopSound(void)
{
#ifdef USE_SOUND
	// �ꎞ��~
	for(int nCntSound = 0; nCntSound < SOUND_LABEL_MAX; nCntSound++)
	{
		StopSound(&g_aParam[nCntSound].sound);
	}
#endif
}

// ���ʐݒ�
void SetVolume(float fVol)
{
	SetMasterVolume(fVol);
}
