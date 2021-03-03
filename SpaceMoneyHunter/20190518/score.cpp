#include "score.h"
#include"polygon.h"
#include"Texture.h"



int g_ScoreSec;

int g_scoreFrame;
ID3D11ShaderResourceView*
g_pScoreTexture;


HRESULT InitScore(void)
{
	//‰Šú‚ÌƒXƒRƒA
	 g_ScoreSec =   0;
	 g_scoreFrame = 0;

	 HRESULT hr;

	hr =  CreateTextureFromFile(GetDevice(), "data/TEXTURE/number.png", &g_pScoreTexture);
	 return hr;

}
void UninitScore(void)
{
	SAFE_RELEASE(g_pScoreTexture);
}
void UpdateScore(void)
{

}
void DrawScore(void)
{
	SetPolygonAlpha(1);
	SetPolygonAngle(0);
	SetPolygonTexture(g_pScoreTexture);
	SetPolygonFrameSize(1.0f / 13, 1.0f);
	SetPolygonSize(20, 40);

	int num = g_ScoreSec;
	float x = 620;
	float y = 320;
	
	do
	{
		SetPolygonUV(//1‚ÌˆÊ
			(num % 10) / 13.0f, 0.0f);

		//SetPolygonUV(//10‚ÌˆÊ
		//	((num / 10) % 10) / 10.0f, 0.0f);

		num /= 10;

		SetPolygonPos(x, y);


		UpdatePolygon();
		DrawPolygon(GetDeviceContext());
		x -= 20;
	} while (num > 0);
}

int GetScore(void)
{
	return g_ScoreSec;
}

void SetScore(int sec)
{
	g_ScoreSec += sec;
	g_scoreFrame = 0;
}