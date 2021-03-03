//=============================================================================
//
// サウンド処理 [sound.cpp]
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
// パラメータ構造体定義
//*****************************************************************************
typedef struct
{
	LPCTSTR	pFilename;		// ファイル名
	BYTE	nCntLoop;		// ループカウント
	SoundData sound;
} SOUNDPARAM;


// 各音素材のパラメータ
SOUNDPARAM g_aParam[SOUND_LABEL_MAX] =
{
	{"data/BGM/op (online-audio-converter.com).wav", -1},		//オープニング
	{"data/BGM/stage1 (online-audio-converter.com).wav", -1},		// ステージ１のBGM
	{ "data/BGM/stage2 (online-audio-converter.com).wav", -1 },		// ステージ2のBGM
	{ "data/BGM/boss.wav", -1 },									// ボスのBGM
	{"data/BGM/shop (online-audio-converter.com).wav", -1},		//ショップBGM
	{"data/SE/death.wav", 0},		//残機が減る音
	{"data/SE/decide000.wav", 0},		// 決定音
	{"data/SE/cancel000.wav", 0},		// キャンセル音
	{"data/SE/select000.wav", 0},		// 選択音
	{"data/SE/shot000.wav", 0},		// 弾発射音
	{"data/SE/lockon000.wav", 0},		// ロックオン音
	{"data/SE/coin.wav", 0},			// コイン音
	{"data/SE/guard000.wav", 0},		// ガード音
	{"data/SE/explosion000.wav", 0},	// 爆発音
	{"data/SE/jump000.wav", 0},		// ジャンプ音
	{"data/SE/money.wav", 0},		// ショップで買い物（成功）
	{ "data/SE/cancel (online-audio-converter.com).wav", 0 },		//ショップで買い物（完売）
	{ "data/SE/barrierBreak.mp3", 0 },		//バリア破壊
	{ "data/SE/cursor.wav", 0 },		//カーソル
};

//=============================================================================
// 初期化
//=============================================================================
HRESULT InitSound(HWND hWnd)
{
#ifdef USE_SOUND
	HRESULT hr;

	hr = InitSoundData();

	// サウンドデータの初期化
	for (int nCntSound = 0; nCntSound < SOUND_LABEL_MAX; nCntSound++)
	{
		CreateSound(g_aParam[nCntSound].pFilename, &g_aParam[nCntSound].sound, g_aParam[nCntSound].nCntLoop == -1);
	}
#endif

	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void UninitSound(void)
{
#ifdef USE_SOUND
	// 一時停止
	for(int nCntSound = 0; nCntSound < SOUND_LABEL_MAX; nCntSound++)
	{
		// 一時停止
		g_aParam[nCntSound].sound.pSource->Stop(0);
		ReleaseSound(&g_aParam[nCntSound].sound);
	}
	
	UninitSoundData();
#endif
}

//=============================================================================
// セグメント一時停止
//=============================================================================
void PauseSound(SOUND_LABEL label)
{
#ifdef USE_SOUND
	PauseSound(&g_aParam[label].sound);
#endif

}

//=============================================================================
// セグメント再生(停止)
//=============================================================================
HRESULT PlaySound(SOUND_LABEL label)
{
#ifdef USE_SOUND
	PlaySound(&g_aParam[label].sound);
#endif

	return S_OK;
}

//=============================================================================
// セグメント停止
//=============================================================================
void StopSound(SOUND_LABEL label)
{
#ifdef USE_SOUND
	StopSound(&g_aParam[label].sound);
#endif
}

//=============================================================================
// セグメント停止
//=============================================================================
void StopSound(void)
{
#ifdef USE_SOUND
	// 一時停止
	for(int nCntSound = 0; nCntSound < SOUND_LABEL_MAX; nCntSound++)
	{
		StopSound(&g_aParam[nCntSound].sound);
	}
#endif
}

// 音量設定
void SetVolume(float fVol)
{
	SetMasterVolume(fVol);
}
