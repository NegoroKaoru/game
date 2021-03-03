#include "life.h"
#include"polygon.h"
#include"Texture.h"
#include "character.h"

int g_pLifeSec;
int g_pLifeFrame;
ID3D11ShaderResourceView*
g_ppLifeTexture;


HRESULT InitpLife(void)
{
	g_pLifeSec = 0;
	g_pLifeFrame = 0;

	HRESULT hr;

	hr = CreateTextureFromFile(GetDevice(), "data/TEXTURE/player.png", &g_ppLifeTexture);
	return hr;

}
void UninitpLife(void)
{
	SAFE_RELEASE(g_ppLifeTexture);
}
void UpdatepLife(void)
{

}
void DrawpLife(void)
{
	CharacterInfo characterInfo = GetCharacterInfo();

	SetPolygonAlpha(1);
	SetPolygonAngle(0);
	SetPolygonTexture(g_ppLifeTexture);
	SetPolygonFrameSize(1.0f / 3, 1.0f / 2);
	SetPolygonSize(25, 50);


	int num = characterInfo.Life;
	float x = -620;
	float y = 320;

	do
	{
		if (num == 0)
			break;

		SetPolygonUV(0 / 3.0f, 2 / 2.0f);

		num -= 1;

		SetPolygonPos(x, y);

		//SetPolygonUV(//10‚ÌˆÊ
		//	((num / 10) % 10) / 10.0f, 0.0f);

		UpdatePolygon();
		DrawPolygon(GetDeviceContext());
		x += 40;
	} while (num > 0);
}

int GetpLife(void)
{
	return g_pLifeSec;
}

void SetpLife(int sec)
{
	g_pLifeSec = sec;
	g_pLifeFrame = 0;
}