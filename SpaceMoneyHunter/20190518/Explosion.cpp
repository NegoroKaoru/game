#include "Explosion.h"
#include "polygon.h"
#include "Texture.h"

//=== マクロ・定数定義 ===
#define MAX_EXPLOSION_NUM (10)
#define SPLIT_IMAGE_HORIZONTAL (8)
#define SPLIT_IMAGE_VERTICAL (2)
#define SPLIT_IMAGE_NUM (SPLIT_IMAGE_HORIZONTAL * SPLIT_IMAGE_VERTICAL)

//=== 構造体定義 ===
typedef struct {
	float x;
	float y;
	int texAnimeCount;
	bool bUse;	//使用中か
}ExplosionInfo;

//=== グローバル変数宣言 ===
ExplosionInfo g_ExplosionInfo[MAX_EXPLOSION_NUM];
ID3D11ShaderResourceView* g_pTexExplosion;

HRESULT InitExplosion(void)
{
	for (int i = 0; i < MAX_EXPLOSION_NUM; i++)
	{
		g_ExplosionInfo[i].x = 0;
		g_ExplosionInfo[i].y = 0;
		g_ExplosionInfo[i].texAnimeCount = 0;
		g_ExplosionInfo[i].bUse = false;
	}
	return (CreateTextureFromFile(GetDevice(), "data/TEXTURE/explosion.png", &g_pTexExplosion));
}
void UninitExplosion(void)
{
	SAFE_RELEASE(g_pTexExplosion);
}
void UpdateExplosion(void)
{
	for (int i = 0; i < MAX_EXPLOSION_NUM; i++)
	{
		if (!g_ExplosionInfo[i].bUse) continue;
		g_ExplosionInfo[i].texAnimeCount++;
		if (g_ExplosionInfo[i].texAnimeCount >= SPLIT_IMAGE_NUM)
		{
			g_ExplosionInfo[i].texAnimeCount = 0;
			g_ExplosionInfo[i].bUse = false;
		}
	}
}
void DrawExplosion(void)
{
	for (int i = 0; i < MAX_EXPLOSION_NUM; i++)
	{
		if (!g_ExplosionInfo[i].bUse) continue;
		SetPolygonSize(300, 300);
		SetPolygonTexture(g_pTexExplosion);
		SetPolygonPos(g_ExplosionInfo[i].x, g_ExplosionInfo[i].y);
		SetPolygonFrameSize(1.0f / SPLIT_IMAGE_HORIZONTAL, 1.0f / SPLIT_IMAGE_VERTICAL);
		SetPolygonUV(
			g_ExplosionInfo[i].texAnimeCount % SPLIT_IMAGE_HORIZONTAL / (float)SPLIT_IMAGE_HORIZONTAL,
			g_ExplosionInfo[i].texAnimeCount / SPLIT_IMAGE_HORIZONTAL / (float)SPLIT_IMAGE_VERTICAL
			);
		UpdatePolygon();
		DrawPolygon(GetDeviceContext());
	}
}
bool SetExplosion(float x, float y)
{
	for (int i = 0; i < MAX_EXPLOSION_NUM; i++)
	{
		if (g_ExplosionInfo[i].bUse) continue;
		g_ExplosionInfo[i].bUse = true;
		g_ExplosionInfo[i].texAnimeCount = 0;
		g_ExplosionInfo[i].x = x;
		g_ExplosionInfo[i].y = y;
		return true; //つくれたよ
	}
	return false; //だめでした
}