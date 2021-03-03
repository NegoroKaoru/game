#include"SceneManager.h"
#include"Character.h"
#include"enemy.h"
#include"score.h"
#include"Explosion.h"
#include"input.h"
#include"Bullet.h"
#include"title.h"
#include"result.h"
#include"sound.h"
#include"background.h"
#include"life.h"
#include"coin.h"
#include"eBullet.h"
#include"eRespawn.h"
#include"fade.h"
#include"shop.h"
#include"stageSelect.h"

//���̃V�[��
SceneKind g_scene = SCENE_TITTLE;
//���̃V�[��
SceneKind g_nextScene = SCENE_TITTLE;
//�V�[�����Z�b�g
bool g_screenReset = false;

//�ǂ̃X�e�[�W��I��������
int stageNum;

HRESULT InitScene(void)
{
	HRESULT hr = E_FAIL;
	switch (g_nextScene)
	{
		case SCENE_TITTLE:
			PlaySound(SOUND_LABEL_BGM_OP);

			hr = S_OK;
			//�^�C�g������������
			if (FAILED(InitTitle()))
				return E_FAIL;

			if (FAILED(InitCharacter()))
				return E_FAIL;

			if (FAILED(InitBG()))
				return E_FAIL;

			break;
		case SCENE_STAGESELECT:
			//�^�C�g������������
			if (FAILED(InitStageSelect()))
				return E_FAIL;

			break;
		case SCENE_GAME:
			StopSound(SOUND_LABEL_BGM_OP);
			switch (stageNum)
			{
			case 0:
			//�X�e�[�W�P��BGM
			PlaySound(SOUND_LABEL_BGM_STAGE1);
				break;
			case 1:
				//�X�e�[�W2��BGM
				PlaySound(SOUND_LABEL_BGM_STAGE2);
				break;
			default:
				break;
			}

			//�e��X�e�[�^�X������
			if (FAILED(InitpLife()))
				return E_FAIL;
			if (FAILED(InitBG()))
				return E_FAIL;
			if (FAILED(InitCharacter()))
				return E_FAIL;
			if (FAILED(InitEnemy()))
				return E_FAIL;
			if (FAILED(InitExplosion()))
				return E_FAIL;
			if (FAILED(InitScore()))
				return E_FAIL;
			if (FAILED(InitBullet()))
				return E_FAIL;
			if (FAILED(InitCoin()))
				return E_FAIL;
			if (FAILED(IniteBullet()))
				return E_FAIL;
			if (FAILED(InitFade()))
				return E_FAIL;
			if (FAILED(IniteRespawn()))
				return E_FAIL;
			if (FAILED(Initshop()))
				return E_FAIL;

			
			hr = S_OK;


			break;
		case SCENE_RESULT:
			StopSound();
			if (FAILED(InitResult()))
				return E_FAIL;
			break;

	}
	
	return hr;

}
void UninitScene(void)
{
	switch (g_scene)
	{
	case SCENE_TITTLE:
		UninitTitle();
		UninitCharacter();
		break;
	case SCENE_STAGESELECT:
		UninitBG();
		UninitStageSelect();
		break;
	case SCENE_GAME:
		//�e�N�X�`���̉��
		UninitBG();
		UninitExplosion();
		UninitCharacter();
		UninitEnemy();
		UninitScore();
		UninitBullet();
		UninitpLife();
		UninitCoin();
		UniniteBullet();
		UniniteRespawn();
		Uninitshop();
		break;
	case SCENE_RESULT:
		UninitResult();
		break;
	}

	UninitFade();
}
void UpdateScene(void)
{
	//�t�F�[�h��ʂ̃A�b�v�f�[�g
	UpdateFade();

	//�V�[���؂�ւ�����
	if (g_scene != g_nextScene || g_screenReset)
	{
		if (GetFade() == FADE_IN)
		{
			UninitScene();
			InitScene();
			g_scene = g_nextScene;
			g_screenReset = false;
		}

	}

	//�V�[���ʂ̏���
	switch (g_scene)
	{
	case SCENE_TITTLE:
		if (IsTriggerInput(VK_RETURN))
		{
			ChangeScene(SCENE_STAGESELECT);
			SetFade(FADE_OUT);
		}
			UpdateTitle();
			UpdateBG();
		break;
	case SCENE_STAGESELECT:
		UpdateStageSelect();
		UpdateBG();
		break;
	case SCENE_GAME:
		//���U���g��ʂɍs������
		if (GetCharacterInfo().Life == 0)
		{
			ChangeScene(SCENE_RESULT);
			SetFade(FADE_OUT);
		}
	
		//���j���[���J��
		if (IsTriggerInput(VK_CONTROL) && !GetShopInfo().EnterShop)
		{
			SetShopInfo();
			switch (stageNum)
			{
			case 0:
				PauseSound(SOUND_LABEL_BGM_STAGE1);
				break;
			case 1:
				PauseSound(SOUND_LABEL_BGM_STAGE2);
				break;
			}
			PlaySound(SOUND_LABEL_BGM_SHOP);
		}
	
		if (GetShopInfo().EnterShop)
		{
			Updateshop();		//���j���[���J���Ă���
		}
		else
		{						//���j���[���J���ĂȂ����
			UpdateBG();
			UpdateCharacter();
			UpdateEnemy();
			UpdateBullet();
			UpdateExplosion();
			UpdateCoin();
			UpdateeBullet();
			UpdateeRespawn();
		}

		//��ɓ�����������
		UpdatepLife();
		UpdateScore();

	/*	UpdateDebugProc();*/
		break;
	case SCENE_RESULT:
		if (IsTriggerInput(VK_RETURN))
		{
			ChangeScene(SCENE_TITTLE);
			ResetScene();
			SetFade(FADE_OUT);
		}
		UpdateResult();
		break;
	}
}
void DrawScene(void)
{
	switch (g_scene)
	{
	case SCENE_TITTLE:
		DrawBG();
		DrawTitle();
		DrawCharacter();
		break;
	case SCENE_STAGESELECT:
		DrawBG();
		DrawStageSelect();
		break;
	case SCENE_GAME:
		if (GetShopInfo().EnterShop)
		{
			Drawshop();
		}
		else {
			//�w�i�`��
			DrawBG();
			DrawEnemy();
			DrawCharacter();
			DrawBullet();
			DrawExplosion();
			DrawCoin();
			DraweBullet();
			damger();
		}

		//��ɕ`�悷�����
		DrawpLife();
		DrawScore();
		break;
	case SCENE_RESULT:
			DrawResult();
		break;
	}

	//�t�F�[�h�͏�ɕ`��
	DrawFade();

}

void ChangeScene(SceneKind scene)
{
	g_nextScene = scene;
}

void ResetScene(void)
{
	g_screenReset = true;
}

void SetStageNum(int num)
{
	stageNum = num;
}

int GetStageNum()
{
	return stageNum;
}
