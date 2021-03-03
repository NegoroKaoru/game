#include "DirectX.h"
#include "main.h"
#include "polygon.h"
#include "Texture.h"
#include "background.h"

//==========================================
// �}�N����`
//==========================================
#define BG_TEX_PATH ("data/TEXTURE/�F��.png")
#define NUM_SPLITBG_X (4)
#define NUM_SPLITBG_Y (3)

//�w�i�Ǎ���
ID3D11ShaderResourceView* g_pBackground;

float g_backScroll = 0.0f;

HRESULT InitBG(void)
{
	g_backScroll = 0.0f;
	
	return (CreateTextureFromFile(GetDevice(), BG_TEX_PATH, &g_pBackground));
}
void UninitBG(void)
{
	SAFE_RELEASE(g_pBackground);
}
void UpdateBG(void)
{
	//�w�i���ړ����x
	g_backScroll -= 0.001f;
}
void DrawBG(void)
{
	//�w�i�`��
	SetPolygonSize(SCREEN_X, SCREEN_Y);
	SetPolygonTexture(g_pBackground);
	SetPolygonPos(0, 0);
	SetPolygonUV(0, g_backScroll);
	SetPolygonFrameSize(1.0f, 1.0f);
	UpdatePolygon();
	DrawPolygon(GetDeviceContext());
}