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
// �}�N����`
//==========================================
#define STAGESELECT_TEX_PATH ("data/TEXTURE/stage.png")
#define STAGESELECT_TEX_PATH1 ("data/TEXTURE/player.png")
#define MAX_STAGE (2)


//==========================================
// �O���[�o���錾
//==========================================
//���݂̃X�e�[�W
int NowStage;
//�L������Ypos
float cPosY;
//�X�e�[�W�I����
bool selectStage;


//�w�i�Ǎ���
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
	//���E�{�^�������������̏���
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

	//�X�e�[�W�I����
	if (IsTriggerInput(VK_RETURN) || selectStage)
	{
		selectStage = true;

		//�L��������ʊO�܂œ�������V�[���؂�ւ�
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
	//�e�X�e�[�W
	SetPolygonSize(800, 200);
	SetPolygonTexture(g_pStageSelect[0]);
	SetPolygonPos(0, 0);
	SetPolygonUV(0, 1);
	SetPolygonFrameSize(1.0f, 1.0f);
	UpdatePolygon();
	DrawPolygon(GetDeviceContext());

	//�L����
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