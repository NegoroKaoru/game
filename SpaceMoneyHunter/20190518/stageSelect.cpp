#include "DirectX.h"
#include "main.h"
#include "polygon.h"
#include "Texture.h"
#include "StageSelect.h"
#include"input.h"
#include"sound.h"
#include"main.h"
#include"SceneManager.h"
#include"fade.h"


//==========================================
// マクロ定義
//==========================================
#define STAGESELECT_TEX_PATH ("data/TEXTURE/stage.png")
#define STAGESELECT_TEX_PATH1 ("data/TEXTURE/player.png")
#define MAX_STAGE (2)


//==========================================
// グローバル宣言
//==========================================
//現在のステージ
int NowStage;
//キャラのYpos
float cPosY;
//ステージ選択時
bool selectStage;


//背景読込先
ID3D11ShaderResourceView* g_pStageSelect[2];

HRESULT InitStageSelect(void)
{
	NowStage = 0;
	cPosY = 0;
	selectStage = false;

	CreateTextureFromFile(GetDevice(), STAGESELECT_TEX_PATH, &g_pStageSelect[0]);
	return (CreateTextureFromFile(GetDevice(), STAGESELECT_TEX_PATH1, &g_pStageSelect[1]));
}
void UninitStageSelect(void)
{
	for (int i = 0; i < 2; i++)
		SAFE_RELEASE(g_pStageSelect[i]);
}
void UpdateStageSelect(void)
{
	//左右ボタンを押した時の処理
	if (IsTriggerInput(VK_LEFT))
	{
		NowStage--;
		PlaySound(SOUND_LABEL_SE_CURSOL);
	}

	if (IsTriggerInput(VK_RIGHT))
	{
		NowStage++;
		PlaySound(SOUND_LABEL_SE_CURSOL);
	}

	//ステージ選択時
	if (IsTriggerInput(VK_RETURN) || selectStage)
	{
		selectStage = true;

		//キャラが画面外まで動いたらシーン切り替え
		if (cPosY > SCREEN_Y * 0.5)
		{
			ChangeScene(SCENE_GAME);
			SetFade(FADE_OUT);
			SetStageNum(NowStage);
		}

		cPosY += 5;
	}



	NowStage = (NowStage + MAX_STAGE) % MAX_STAGE;
}
void DrawStageSelect(void)
{
	//各ステージ
	SetPolygonSize(800, 200);
	SetPolygonTexture(g_pStageSelect[0]);
	SetPolygonPos(0, 0);
	SetPolygonUV(0, 1);
	SetPolygonFrameSize(1.0f, 1.0f);
	UpdatePolygon();
	DrawPolygon(GetDeviceContext());

	//キャラ
	SetPolygonSize(100, 100);
	SetPolygonTexture(g_pStageSelect[1]);
	SetPolygonPos(-250 + (NowStage * 450) , cPosY);
	SetPolygonFrameSize(1.0f / 3, 1.0f / 2);
	SetPolygonUV(0.0f / 3.0f, 0.0f / 2.0f);
	UpdatePolygon();
	DrawPolygon(GetDeviceContext());
}

int GetNowStage()
{
	return NowStage;
}