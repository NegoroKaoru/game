#ifndef __SOUND_H__
#define __SOUND_H__

#include <xaudio2.h>

#pragma comment(lib, "xaudio2.lib")

//----------
// �\����
//----------
struct SoundData
{
	WAVEFORMATEX		format;		// WAV�t�H�[�}�b�g
	BYTE				*pBuffer;	// �T�E���h�f�[�^
	DWORD				bufSize;	// �f�[�^�T�C�Y
	IXAudio2SourceVoice	*pSource;	// XAudio�\�[�X
	XAUDIO2_BUFFER		xa2Buffer;	// XAudio�o�b�t�@�[
};

//----------
// �v���g�^�C�v�錾
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