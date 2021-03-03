#include "DirectX.h"
#include "main.h"
#include "polygon.h"
#include "Texture.h"
#include "title.h"

//==========================================
// マクロ定義
//==========================================
#define Title_TEX_PATH1 ("data/TEXTURE/tittle.png")
#define Title_TEX_PATH2 ("data/TEXTURE/pressEnter.png")
#define NUM_SPLITTITLE_X (4)
#define NUM_SPLITTITLE_Y (3)

//==========================================
// グローバル宣言
//==========================================
int g_fCnt;


//背景読込先
ID3D11ShaderResourceView* g_pTitle[3];

float g_spaceScroll = 0.0f;

HRESULT InitTitle(void)
{
	g_fCnt = 0;

	g_spaceScroll = 0.0f;

	CreateTextureFromFile(GetDevice(), Title_TEX_PATH1, &g_pTitle[0]);
	return (CreateTextureFromFile(GetDevice(), Title_TEX_PATH2, &g_pTitle[1]));
}
void UninitTitle(void)
{
	for (int i = 0; i < 3; i++)
	SAFE_RELEASE(g_pTitle[i]);
}
void UpdateTitle(void)
{
	//背景横移動速度
	g_spaceScroll -= 0.001f;
	g_fCnt++;
}
void DrawTitle(void)
{

	//TITLE
	SetPolygonSize(1200, 500);
	SetPolygonTexture(g_pTitle[0]);
	SetPolygonPos(0, 100);
	SetPolygonUV(0,1);
	SetPolygonFrameSize(1.0f, 1.0f);
	UpdatePolygon();
	DrawPolygon(GetDeviceContext());

	//PRESS ENTER
	SetPolygonSize(500, 100);
	SetPolygonTexture(g_pTitle[1]);
	SetPolygonPos(0, -200);
	SetPolygonUV(0, 1);
	SetPolygonFrameSize(1.0f, 1.0f);
	UpdatePolygon();
	DrawPolygon(GetDeviceContext());


}