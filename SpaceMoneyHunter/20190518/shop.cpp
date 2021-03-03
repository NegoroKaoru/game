#include "shop.h"
#include"polygon.h"
#include"Texture.h"
#include "score.h"
#include"input.h"
#include"sound.h"
#include"character.h"
#include"SceneManager.h"

//==========================================
// �}�N����`
//==========================================
#define TRANSPARENT (0.3f)
#define MAX_BOTTOM  (3)
#define MAX_LIFE (8)

//�������O���[�o���ϐ�������
ID3D11ShaderResourceView*
g_pshopTexture[5];

shopStates shopInfo;

HRESULT Initshop(void)
{
	shopInfo.EnterShop = false;
	shopInfo.selecting = 0;

	//�e�A�C�e���l�i�̐ݒ�
	shopInfo.price[0] = 50;
	shopInfo.price[1] = 150;
	shopInfo.price[2] = 200;


	HRESULT hr;

	CreateTextureFromFile(GetDevice(), "data/TEXTURE/BGshop.jpg", &g_pshopTexture[0]);
	CreateTextureFromFile(GetDevice(), "data/TEXTURE/shopUIbullet.png", &g_pshopTexture[1]);
	CreateTextureFromFile(GetDevice(), "data/TEXTURE/shopUIlife.png", &g_pshopTexture[2]);
	CreateTextureFromFile(GetDevice(), "data/TEXTURE/shopUIbarrier.png", &g_pshopTexture[3]);
	hr = CreateTextureFromFile(GetDevice(), "data/TEXTURE/soldOut.png", &g_pshopTexture[4]);
	return hr;

}
void Uninitshop(void)
{
	for(int i = 0;i<4;i++)
	SAFE_RELEASE(g_pshopTexture[i]);
}
void Updateshop(void)
{
	CharacterInfo characterInfo = GetCharacterInfo();
	int ScoreInfo = GetScore();

	//�Q�[���ɖ߂�
	if (IsTriggerInput(VK_ESCAPE))
	{
		shopInfo.EnterShop = false;
		StopSound(SOUND_LABEL_BGM_SHOP);
		switch (GetStageNum())
		{
		case 0:
			PauseSound(SOUND_LABEL_BGM_STAGE1);
			break;
		case 1:
			PauseSound(SOUND_LABEL_BGM_STAGE2);
			break;
		}
	}

	//�A�C�e���{���ړ�
	if (IsTriggerInput(VK_LEFT))
	{
		shopInfo.selecting--;
		PlaySound(SOUND_LABEL_SE_CURSOL);
	}

	if (IsTriggerInput(VK_RIGHT))
	{
		shopInfo.selecting++;
		PlaySound(SOUND_LABEL_SE_CURSOL);
	}

	shopInfo.selecting = (shopInfo.selecting + MAX_BOTTOM) % MAX_BOTTOM;

	//�A�C�e���w���ɏꍇ
	if (IsTriggerInput(VK_RETURN))
	{
		//����������Ă��邩�ǂ���

		//�w��������
		if (shopInfo.price[shopInfo.selecting] <= ScoreInfo)
		{
			switch (shopInfo.selecting)
			{
				//�e���ː�����
			case 0:
				if (characterInfo.bulletNum < 2)
				{
					PlaySound(SOUND_LABEL_SE_BUY);
					SetScore(-shopInfo.price[shopInfo.selecting]);
					SetCharacterInfo(shopInfo.selecting);
				}
				else
				{
					PlaySound(SOUND_LABEL_SE_NOMONEY);	//����؂�̏ꍇ
				}
				break;
				//���C�t�ǉ�
			case 1:
				if (characterInfo.Life < MAX_LIFE)
				{
					PlaySound(SOUND_LABEL_SE_BUY);
					SetScore(-shopInfo.price[shopInfo.selecting]);
					SetCharacterInfo(shopInfo.selecting);
				}
				else
				{
					PlaySound(SOUND_LABEL_SE_NOMONEY);	//����؂�̏ꍇ
				}
				break;
				//�o���A�t�^
			case 2:
				if (!characterInfo.barrier)
				{
					PlaySound(SOUND_LABEL_SE_BUY);
					SetScore(-shopInfo.price[shopInfo.selecting]);
					SetCharacterInfo(shopInfo.selecting);					
				}
				else
				{
					PlaySound(SOUND_LABEL_SE_NOMONEY);	//����؂�̏ꍇ
				}
				break;
			default:
				break;
			}
		}
		else
		{
			PlaySound(SOUND_LABEL_SE_NOMONEY);
		}
		

	}
}
void Drawshop(void)
{
	//�L����������
	CharacterInfo characterInfo = GetCharacterInfo();
	//�X�R�A�擾
	int ScoreInfo = GetScore();

	//�w�i�`��
	SetPolygonSize(SCREEN_X, SCREEN_Y);
	SetPolygonTexture(g_pshopTexture[0]);
	SetPolygonPos(0, 0);
	SetPolygonUV(0, 1);
	SetPolygonFrameSize(1.0f, 1.0f);
	UpdatePolygon();
	DrawPolygon(GetDeviceContext());

	for (int i = 1; i < 4; i++)
	{
		//UI�`��
		SetPolygonPos(-630 + (i * 300) , 0);
		SetPolygonTexture(g_pshopTexture[i]);
		SetPolygonUV(0, 1);
		SetPolygonFrameSize(1.0f, 1.0f);
		SetPolygonSize(200, 300);

		//�{�����̃A�C�e���ȊO�͔������ɂ���
		if (shopInfo.selecting == i - 1)
		{
			SetPolygonAlpha(1.0f);
		}
		else
		{
			SetPolygonAlpha(TRANSPARENT);
		}

		UpdatePolygon();
		DrawPolygon(GetDeviceContext());
		SetPolygonAlpha(1.0f);
	}

	//����؂�`��
	if (characterInfo.bulletNum == 2)			//�e����؂�
	{
		SetPolygonPos(-630 + (1 * 300), 0);
		SetPolygonTexture(g_pshopTexture[4]);
		SetPolygonUV(0, 1);
		SetPolygonFrameSize(1.0f, 1.0f);
		SetPolygonSize(100, 50);
		DrawPolygon(GetDeviceContext());
	}


	if (characterInfo.Life == MAX_LIFE)				//���C�t�A�C�e������؂�
	{
		SetPolygonPos(-630 + (2 * 300), 0);
		SetPolygonTexture(g_pshopTexture[4]);
		SetPolygonUV(0, 1);
		SetPolygonFrameSize(1.0f, 1.0f);
		SetPolygonSize(100, 50);
		DrawPolygon(GetDeviceContext());
	}

	if (characterInfo.barrier)					//�o���A����؂�
	{
		SetPolygonPos(-630 + (3 * 300), 0);
		SetPolygonTexture(g_pshopTexture[4]);
		SetPolygonUV(0, 1);
		SetPolygonFrameSize(1.0f, 1.0f);
		SetPolygonSize(100, 50);
		DrawPolygon(GetDeviceContext());
	}
	

}

shopStates GetShopInfo(void)
{
	return	shopInfo;
}

void SetShopInfo()
{
	shopInfo.EnterShop = true;
}
