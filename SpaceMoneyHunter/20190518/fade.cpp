//=============================================================================
//
// �t�F�[�h���� [fade.cpp]
// Author : HIROHIKO HAMAYA
//
//=============================================================================
#include "fade.h"
#include "polygon.h"
#include "sound.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define	FADE_RATE		(0.02f)		// �t�F�[�h�W��
#define FADE_RED		0.0f
#define FADE_GREEN		0.0f
#define FADE_BLUE		0.0f

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
// (�Ȃ�)

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
static float			g_fAlpha = 1.0f;
static FADE				g_fade = FADE_IN;

//=============================================================================
// ����������
//=============================================================================
HRESULT InitFade(void)
{
	g_fAlpha = 1.0f;
	g_fade = FADE_IN;

	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void UninitFade(void)
{
	// (�������Ȃ�)
}

//=============================================================================
// �X�V����
//=============================================================================
void UpdateFade(void)
{

	if(g_fade != FADE_NONE) {
		// �t�F�[�h������
		if(g_fade == FADE_OUT) {
			// �t�F�[�h�A�E�g����
			g_fAlpha += FADE_RATE;		// ���l�����Z���ĉ�ʂ������Ă���
			if (g_fAlpha >= 1.0f) {
				// �t�F�[�h�C�������ɐ؂�ւ�
				g_fAlpha = 1.0f;
				SetFade(FADE_IN);

			}
			// �{�����[�����t�F�[�h�A�E�g
			SetVolume(1.0f - g_fAlpha);
		} else if (g_fade == FADE_IN) {
			// �t�F�[�h�C������
			g_fAlpha -= FADE_RATE;		// ���l�����Z���ĉ�ʂ𕂂��オ�点��
			if(g_fAlpha <= 0.0f) {
				// �t�F�[�h�����I��
				g_fAlpha = 0.0f;
				SetFade(FADE_NONE);
			}
			// �{�����[�����t�F�[�h�C��
			SetVolume(1.0f - g_fAlpha);
		}
	}
}

//=============================================================================
// �^�C�g�����
//=============================================================================
void DrawFade(void)
{
		ID3D11DeviceContext* pDeviceContext = GetDeviceContext();

		SetPolygonTexture(nullptr);
		SetPolygonSize(SCREEN_X, SCREEN_Y);
		SetPolygonPos(0.0f, 0.0f);
		SetPolygonFrameSize(1.0f, 1.0f);
		SetPolygonUV(0.0f, 0.0f);
		SetPolygonColor(FADE_RED, FADE_GREEN, FADE_BLUE);
		SetPolygonAlpha(g_fAlpha);

		DrawPolygon(pDeviceContext);

		SetPolygonColor(1.0f, 1.0f, 1.0f);
		SetPolygonAlpha(1.0f);

}

//=============================================================================
// �t�F�[�h�̏�Ԑݒ�
//=============================================================================
void SetFade(FADE fade)
{
	g_fade = fade;
}

//=============================================================================
// �t�F�[�h�̏�Ԏ擾
//=============================================================================
FADE GetFade(void)
{
	return g_fade;
}