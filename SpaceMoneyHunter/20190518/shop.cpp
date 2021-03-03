#include "shop.h"
#include"polygon.h"
#include"Texture.h"
#include "score.h"
#include"input.h"
#include"sound.h"
#include"character.h"
#include"SceneManager.h"

//==========================================
// マクロ定義
//==========================================
#define TRANSPARENT (0.3f)
#define MAX_BOTTOM  (3)
#define MAX_LIFE (8)

//＝＝＝グローバル変数＝＝＝
ID3D11ShaderResourceView*
g_pshopTexture[5];

shopStates shopInfo;

HRESULT Initshop(void)
{
	shopInfo.EnterShop = false;
	shopInfo.selecting = 0;

	//各アイテム値段の設定
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

	//ゲームに戻る
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

	//アイテム閲覧移動
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

	//アイテム購入に場合
	if (IsTriggerInput(VK_RETURN))
	{
		//お金が足りているかどうか

		//購入成功時
		if (shopInfo.price[shopInfo.selecting] <= ScoreInfo)
		{
			switch (shopInfo.selecting)
			{
				//弾発射数増加
			case 0:
				if (characterInfo.bulletNum < 2)
				{
					PlaySound(SOUND_LABEL_SE_BUY);
					SetScore(-shopInfo.price[shopInfo.selecting]);
					SetCharacterInfo(shopInfo.selecting);
				}
				else
				{
					PlaySound(SOUND_LABEL_SE_NOMONEY);	//売り切れの場合
				}
				break;
				//ライフ追加
			case 1:
				if (characterInfo.Life < MAX_LIFE)
				{
					PlaySound(SOUND_LABEL_SE_BUY);
					SetScore(-shopInfo.price[shopInfo.selecting]);
					SetCharacterInfo(shopInfo.selecting);
				}
				else
				{
					PlaySound(SOUND_LABEL_SE_NOMONEY);	//売り切れの場合
				}
				break;
				//バリア付与
			case 2:
				if (!characterInfo.barrier)
				{
					PlaySound(SOUND_LABEL_SE_BUY);
					SetScore(-shopInfo.price[shopInfo.selecting]);
					SetCharacterInfo(shopInfo.selecting);					
				}
				else
				{
					PlaySound(SOUND_LABEL_SE_NOMONEY);	//売り切れの場合
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
	//キャラ情報樹徳
	CharacterInfo characterInfo = GetCharacterInfo();
	//スコア取得
	int ScoreInfo = GetScore();

	//背景描画
	SetPolygonSize(SCREEN_X, SCREEN_Y);
	SetPolygonTexture(g_pshopTexture[0]);
	SetPolygonPos(0, 0);
	SetPolygonUV(0, 1);
	SetPolygonFrameSize(1.0f, 1.0f);
	UpdatePolygon();
	DrawPolygon(GetDeviceContext());

	for (int i = 1; i < 4; i++)
	{
		//UI描画
		SetPolygonPos(-630 + (i * 300) , 0);
		SetPolygonTexture(g_pshopTexture[i]);
		SetPolygonUV(0, 1);
		SetPolygonFrameSize(1.0f, 1.0f);
		SetPolygonSize(200, 300);

		//閲覧中のアイテム以外は半透明にする
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

	//売り切れ描画
	if (characterInfo.bulletNum == 2)			//弾売り切れ
	{
		SetPolygonPos(-630 + (1 * 300), 0);
		SetPolygonTexture(g_pshopTexture[4]);
		SetPolygonUV(0, 1);
		SetPolygonFrameSize(1.0f, 1.0f);
		SetPolygonSize(100, 50);
		DrawPolygon(GetDeviceContext());
	}


	if (characterInfo.Life == MAX_LIFE)				//ライフアイテム売り切れ
	{
		SetPolygonPos(-630 + (2 * 300), 0);
		SetPolygonTexture(g_pshopTexture[4]);
		SetPolygonUV(0, 1);
		SetPolygonFrameSize(1.0f, 1.0f);
		SetPolygonSize(100, 50);
		DrawPolygon(GetDeviceContext());
	}

	if (characterInfo.barrier)					//バリア売り切れ
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
