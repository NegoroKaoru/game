//=============================================================================
//
// �T�E���h���� [sound.h]
// Author : AKIRA TANAKA
//
//=============================================================================
#ifndef _SOUND_H_
#define _SOUND_H_

#include "main.h"

#include <xaudio2.h>
// Windows7�̏ꍇ�͏�L���폜���Ĉȉ��ɒu������.
//#include <C:\Program Files (x86)\Microsoft DirectX SDK (June 2010)\Include\xaudio2.h>

//*****************************************************************************
// �T�E���h�t�@�C��
//*****************************************************************************
typedef enum
{
	SOUND_LABEL_BGM_OP = 0,				// �I�[�v�j���O
	SOUND_LABEL_BGM_STAGE1,				// �X�e�[�W�P
	SOUND_LABEL_BGM_STAGE2,				//�X�e�[�W�Q
	SOUND_LABEL_BGM_BOSS,				//�{�XBGM
	SOUND_LABEL_BGM_SHOP,				//�V���b�vBGM
	SOUND_LABEL_DEATH,					// �c�@�����鉹
	SOUND_LABEL_SE_DECIDE,				// ���艹
	SOUND_LABEL_SE_CANCEL,				// �L�����Z����
	SOUND_LABEL_SE_SELECT,				// �I����
	SOUND_LABEL_SE_SHOT,				// �e���ˉ�
	SOUND_LABEL_SE_LOCKON,				// ���b�N�I����
	SOUND_LABEL_SE_COIN,				// �q�b�g��
	SOUND_LABEL_SE_GUARD,				// �K�[�h��
	SOUND_LABEL_SE_EXPLOSION,			// ������
	SOUND_LABEL_SE_JUMP,				// �W�����v��
	SOUND_LABEL_SE_BUY,					//�V���b�v�Ŕ������i�����j
	SOUND_LABEL_SE_NOMONEY,			//�V���b�v�Ŕ������i�s�����j
	SOUND_LABEL_SE_BARRIERBREAK,		//�o���A�j��
	SOUND_LABEL_SE_CURSOL,				//�J�[�\��
	SOUND_LABEL_MAX,					// �o�^���̎����ݒ�
} SOUND_LABEL;

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT InitSound(HWND hWnd);
void UninitSound(void);

void PauseSound(SOUND_LABEL label);
HRESULT PlaySound(SOUND_LABEL label);

void StopSound(SOUND_LABEL label);
void StopSound(void);

void SetVolume(float fVol);

#endif
