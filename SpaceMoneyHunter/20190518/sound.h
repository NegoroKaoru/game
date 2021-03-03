//=============================================================================
//
// サウンド処理 [sound.h]
// Author : AKIRA TANAKA
//
//=============================================================================
#ifndef _SOUND_H_
#define _SOUND_H_

#include "main.h"

#include <xaudio2.h>
// Windows7の場合は上記を削除して以下に置き換え.
//#include <C:\Program Files (x86)\Microsoft DirectX SDK (June 2010)\Include\xaudio2.h>

//*****************************************************************************
// サウンドファイル
//*****************************************************************************
typedef enum
{
	SOUND_LABEL_BGM_OP = 0,				// オープニング
	SOUND_LABEL_BGM_STAGE1,				// ステージ１
	SOUND_LABEL_BGM_STAGE2,				//ステージ２
	SOUND_LABEL_BGM_BOSS,				//ボスBGM
	SOUND_LABEL_BGM_SHOP,				//ショップBGM
	SOUND_LABEL_DEATH,					// 残機が減る音
	SOUND_LABEL_SE_DECIDE,				// 決定音
	SOUND_LABEL_SE_CANCEL,				// キャンセル音
	SOUND_LABEL_SE_SELECT,				// 選択音
	SOUND_LABEL_SE_SHOT,				// 弾発射音
	SOUND_LABEL_SE_LOCKON,				// ロックオン音
	SOUND_LABEL_SE_COIN,				// ヒット音
	SOUND_LABEL_SE_GUARD,				// ガード音
	SOUND_LABEL_SE_EXPLOSION,			// 爆発音
	SOUND_LABEL_SE_JUMP,				// ジャンプ音
	SOUND_LABEL_SE_BUY,					//ショップで買い物（成功）
	SOUND_LABEL_SE_NOMONEY,			//ショップで買い物（不成立）
	SOUND_LABEL_SE_BARRIERBREAK,		//バリア破壊
	SOUND_LABEL_SE_CURSOL,				//カーソル
	SOUND_LABEL_MAX,					// 登録数の自動設定
} SOUND_LABEL;

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
HRESULT InitSound(HWND hWnd);
void UninitSound(void);

void PauseSound(SOUND_LABEL label);
HRESULT PlaySound(SOUND_LABEL label);

void StopSound(SOUND_LABEL label);
void StopSound(void);

void SetVolume(float fVol);

#endif
