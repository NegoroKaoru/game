#include"coin.h"
#include"polygon.h"
#include"Texture.h"
#include"Explosion.h"
#include"sound.h"
#include"score.h"
#include"character.h"

//=== �O���[�o���ϐ��錾 ===
ID3D11ShaderResourceView* g_pCoinTexture;
CoinInfo g_CoinInfo[MAX_COIN_NUM];

//=== �}�N���E�萔��` ===
#define SPLIT_IMAGE_HORIZONTAL (5)
#define SPLIT_IMAGE_VERTICAL (7)
#define SPLIT_IMAGE_NUM (SPLIT_IMAGE_HORIZONTAL * SPLIT_IMAGE_VERTICAL)

//�G����������
HRESULT InitCoin(void)
{
	for (int i = 0; i < MAX_COIN_NUM; i++)
	{
		g_CoinInfo[i].bUse = false;
		g_CoinInfo[i].fPosX = 0.0f;
		g_CoinInfo[i].fPosY = 0.0f;
		g_CoinInfo[i].fMoveX = 0.0f;
		g_CoinInfo[i].fMoveY = 0.0f;
		g_CoinInfo[i].nTexAnimeCnt = 0;
	}

	return (CreateTextureFromFile(GetDevice(), "data/TEXTURE/coin.png", &g_pCoinTexture));
}

//�G�㏈��
void UninitCoin(void)
{
	SAFE_RELEASE(g_pCoinTexture);

}

//�G�X�V����
void UpdateCoin(void)
{
	//�v���C���[�̏��擾
	CharacterInfo cInfo = GetCharacterInfo();

	for (int i = 0; i < MAX_COIN_NUM; i++)
	{
		if (!g_CoinInfo[i].bUse) continue;
			g_CoinInfo[i].fMoveY = -1.0f;

		g_CoinInfo[i].fPosX += g_CoinInfo[i].fMoveX;
		g_CoinInfo[i].fPosY += g_CoinInfo[i].fMoveY;
		g_CoinInfo[i].nTexAnimeCnt++;

		if (g_CoinInfo[i].nTexAnimeCnt == SPLIT_IMAGE_NUM)
		{
			g_CoinInfo[i].nTexAnimeCnt = 0;
		}

	}
}

//�G�`��
void DrawCoin(void)
{
	for (int i = 0; i < MAX_COIN_NUM; i++)
	{
		if (!g_CoinInfo[i].bUse) continue;
			SetPolygonSize(90, 90);


		SetPolygonTexture(g_pCoinTexture);
		SetPolygonFrameSize(1.0f / SPLIT_IMAGE_HORIZONTAL, 1.0f / SPLIT_IMAGE_VERTICAL);
		SetPolygonUV(
			g_CoinInfo[i].nTexAnimeCnt % SPLIT_IMAGE_HORIZONTAL / (float)SPLIT_IMAGE_HORIZONTAL,
			g_CoinInfo[i].nTexAnimeCnt / SPLIT_IMAGE_HORIZONTAL / (float)SPLIT_IMAGE_VERTICAL);

		SetPolygonPos(g_CoinInfo[i].fPosX, g_CoinInfo[i].fPosY);

		UpdatePolygon();
		DrawPolygon(GetDeviceContext());
	}
}

//�R�C������
void CreateCoin(float x, float y)
{
	for (int i = 0; i < MAX_COIN_NUM; i++)
	{
		if (g_CoinInfo[i].bUse) continue;
		g_CoinInfo[i].bUse = true;
		g_CoinInfo[i].fPosX = x;
		g_CoinInfo[i].fPosY = y;
		g_CoinInfo[i].fMoveX = 0.0f;
		g_CoinInfo[i].fMoveY = 0.0f;
		break;
	}
}

//�R�C���l��
void DestroyCoin(int index)
{
	PlaySound(SOUND_LABEL_SE_COIN);

	g_CoinInfo[index].bUse = false;

	SetScore(15);
}

//�R�C�����擾
CoinInfo GetCoinInfo(int index)
{
	if (0 <= index && index < MAX_COIN_NUM)
	{
		return g_CoinInfo[index];
	}
	else
	{
		CoinInfo dummy;
		dummy.bUse = false;
		dummy.fPosX = 0;
		dummy.fPosY = 0;
		return dummy;
	}
}