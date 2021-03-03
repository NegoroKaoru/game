#include "DirectX.h"
#include "main.h"
#include "polygon.h"
#include "Texture.h"
#include "result.h"

#define Result_RESULT_PATH1 ("data/TEXTURE/gameclear.png")
#define Result_RESULT_PATH2 ("data/TEXTURE/gameover.png")

//�Q�[���N���A�t���O
bool gameclear;

//�w�i�Ǎ���
ID3D11ShaderResourceView* g_presult[2];

HRESULT InitResult(void)
{
	gameclear = false;

	CreateTextureFromFile(GetDevice(), Result_RESULT_PATH1, &g_presult[0]);
	return (CreateTextureFromFile(GetDevice(), Result_RESULT_PATH2, &g_presult[1]));
}
void UninitResult(void)
{
	for (int i = 0; i < 2; i++)
	SAFE_RELEASE(g_presult[i]);
}
void UpdateResult(void)
{

}
void DrawResult(void)
{
	//�w�i�`��
	if (!gameclear) //���U���g����
	{
		SetPolygonTexture(g_presult[0]);	//����
	}
	else
	{
		SetPolygonTexture(g_presult[1]);	//�s�k
	}
		SetPolygonSize(SCREEN_X, SCREEN_Y);
		SetPolygonPos(0, 0);
		SetPolygonUV(0, 1);
		SetPolygonFrameSize(1.0f, 1.0f);
		UpdatePolygon();
		DrawPolygon(GetDeviceContext());
}

void SetGameClear()
{
	gameclear = true;
}