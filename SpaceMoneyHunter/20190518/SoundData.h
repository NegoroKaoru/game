#ifndef __SOUND_H__
#define __SOUND_H__

#include <xaudio2.h>

#pragma comment(lib, "xaudio2.lib")

//----------
// 構造体
//----------
struct SoundData
{
	WAVEFORMATEX		format;		// WAVフォーマット
	BYTE				*pBuffer;	// サウンドデータ
	DWORD				bufSize;	// データサイズ
	IXAudio2SourceVoice	*pSource;	// XAudioソース
	XAUDIO2_BUFFER		xa2Buffer;	// XAudioバッファー
};

//----------
// プロトタイプ宣言
//----------
HRESULT InitSoundData(void);
void UninitSoundData(void);
void SetMasterVolume(float volume);

HRESULT CreateSound(const char *file, SoundData *pData, bool loop);
void ReleaseSound(SoundData *pData);

void PauseSound(const SoundData *pData);
void PlaySound(const SoundData *pData);
void StopSound(const SoundData *pData);

#endif // __SOUND_H__