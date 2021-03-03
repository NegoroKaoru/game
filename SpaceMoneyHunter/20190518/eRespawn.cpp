#include"SceneManager.h"
#include"enemy.h"
#include"eRespawn.h"
#include"fade.h"
#include"enemy.h"
#include"eBullet.h"
#include"polygon.h"
#include"Texture.h"
#include"sound.h"

//ゲーム開始時間
int now_time;
//敵出現
int eCnt = 0;
//damger描画時間
bool dmgFlg;
//どのステージか
int respawnNum;
//ボス突入でBGM切り替え
bool bossMusic;

ID3D11ShaderResourceView*
g_image;


HRESULT IniteRespawn(void)
{
	//ゲーム開始時間を代入
	now_time = 0.0f;

	//damger描画時間
	dmgFlg = false;

	//どのステージか
	respawnNum = GetStageNum();

	//ボス突入でBGM切り替え
	bossMusic = false;

	HRESULT hr;

	hr = CreateTextureFromFile(GetDevice(), "data/TEXTURE/warning.png", &g_image);
	return hr;
}
void UniniteRespawn(void)
{
	SAFE_RELEASE(g_image);
}
void UpdateeRespawn(void)
{

	//小惑星乱数生成
	if (eCnt == 100)
	{
		CreateEnemy(ET_ASTEROID, ((rand() % SCREEN_X)) - SCREEN_X * 0.5, SCREEN_Y * 0.5);
		eCnt = 0;
	}

	//各ステージによるリスポン
	switch (respawnNum)
	{
	case 0:
		//ステージ1リスポーン予定表
		switch (now_time)
		{
		case 150:
			CreateEnemy(ET_NORMAL_R, 400, SCREEN_Y * 0.5 - 40);
			CreateEnemy(ET_NORMAL_L, -400, SCREEN_Y * 0.5 - 40);
			break;
		case 600:
			CreateEnemy(ET_NORMAL_L, -400, SCREEN_Y * 0.5 - 40);
			CreateEnemy(ET_NORMAL_L, -300, SCREEN_Y * 0.5 - 40);
			CreateEnemy(ET_NORMAL_L, -200, SCREEN_Y * 0.5 - 40);
			CreateEnemy(ET_NORMAL_L, -100, SCREEN_Y * 0.5 - 40);
			break;
		case 1000:
			CreateEnemy(ET_NORMAL_R, 400, SCREEN_Y * 0.5 - 40);
			CreateEnemy(ET_NORMAL_R, 300, SCREEN_Y * 0.5 - 40);
			CreateEnemy(ET_NORMAL_R, 200, SCREEN_Y * 0.5 - 40);
			CreateEnemy(ET_NORMAL_R, 100, SCREEN_Y * 0.5 - 40);
			break;

		case 1600:
		case 1900:
		case 2100:
			CreateEnemy(ET_NORMAL_R, 500, SCREEN_Y * 0.5 - 40);
			CreateEnemy(ET_NORMAL_L, -500, SCREEN_Y * 0.5 - 40);
			break;

		case 2900:
			CreateEnemy(ET_NORMAL_L, -400, SCREEN_Y * 0.5 - 40);
			CreateEnemy(ET_NORMAL_L, -300, SCREEN_Y * 0.5 - 40);
			CreateEnemy(ET_NORMAL_L, -200, SCREEN_Y * 0.5 - 40);
			CreateEnemy(ET_NORMAL_L, -100, SCREEN_Y * 0.5 - 40);
			CreateEnemy(ET_NORMAL_L, 0, SCREEN_Y * 0.5 - 40);
			CreateEnemy(ET_NORMAL_R, 400, SCREEN_Y * 0.5 - 40);
			CreateEnemy(ET_NORMAL_R, 300, SCREEN_Y * 0.5 - 40);
			CreateEnemy(ET_NORMAL_R, 200, SCREEN_Y * 0.5 - 40);
			CreateEnemy(ET_NORMAL_R, 100, SCREEN_Y * 0.5 - 40);
			break;

		case 3500:
			CreateEnemy(ET_ROTATION, 500, SCREEN_Y * 0.5 - 40);
			CreateEnemy(ET_ROTATION, -500, SCREEN_Y * 0.5 - 40);
			break;

		case 3800:
			CreateEnemy(ET_NORMAL_L, 0, SCREEN_Y * 0.5 - 30);
			break;
		case 3850:
			CreateEnemy(ET_NORMAL_R, 0, SCREEN_Y * 0.5 - 30);
			break;
		case 3900:
			CreateEnemy(ET_NORMAL_L, 0, SCREEN_Y * 0.5 - 30);
			break;
		case 3950:
			CreateEnemy(ET_NORMAL_R, 0, SCREEN_Y * 0.5 - 30);
			break;

		case 4300:
			CreateEnemy(ET_NORMAL_L, 0, SCREEN_Y * 0.5 - 30);
			break;
		case 4350:
			CreateEnemy(ET_NORMAL_R, 0, SCREEN_Y * 0.5 - 30);
			break;
		case 4400:
			CreateEnemy(ET_NORMAL_L, 0, SCREEN_Y * 0.5 - 30);
			break;
		case 4450:
			CreateEnemy(ET_NORMAL_R, 0, SCREEN_Y * 0.5 - 30);
			break;

		case 5800:
			CreateEnemy(ET_HANABI, 0, SCREEN_Y * 0.5 - 30);
			break;

		default:
			break;
		}

		//クリア条件
		if (now_time > 5800)
		{
			//敵が存在しない場合クリア
			if (AllKill())
			{
				ChangeScene(SCENE_RESULT);
				SetGameClear();
				SetFade(FADE_OUT);
			}
		}
		break;

	case 1:
		//ステージ2リスポーン予定表
		switch (now_time)
		{
		case 200:
			CreateEnemy(ET_ROTATION, 0, SCREEN_Y * 0.5 - 40);
			CreateEnemy(ET_NORMAL_R, 400, SCREEN_Y * 0.5 - 40);
			CreateEnemy(ET_NORMAL_L, -400, SCREEN_Y * 0.5 - 40);
			break;

		case 600:
			CreateEnemy(ET_NORMAL_R, 400, SCREEN_Y * 0.5 - 40);
			CreateEnemy(ET_NORMAL_L, -400, SCREEN_Y * 0.5 - 40);
			break;

		case 800:
			CreateEnemy(ET_NORMAL_R, 400, SCREEN_Y * 0.5 - 40);
			CreateEnemy(ET_NORMAL_L, -400, SCREEN_Y * 0.5 - 40);
			break;

		case 1400:
			CreateEnemy(ET_NORMAL_R, 50, SCREEN_Y * 0.5 - 40);
			CreateEnemy(ET_NORMAL_L, -50, SCREEN_Y * 0.5 - 40);
			break;

		case 1500:
			CreateEnemy(ET_NORMAL_R, 50, SCREEN_Y * 0.5 - 40);
			CreateEnemy(ET_NORMAL_L, -50, SCREEN_Y * 0.5 - 40);
			break;

		case 1600:
			CreateEnemy(ET_NORMAL_R, 50, SCREEN_Y * 0.5 - 40);
			CreateEnemy(ET_NORMAL_L, -50, SCREEN_Y * 0.5 - 40);
			break;

		case 2500:
			CreateEnemy(ET_NORMAL_L, 0, SCREEN_Y * 0.5 - 40);
			break;
		case 2550:
			CreateEnemy(ET_NORMAL_L, -100, SCREEN_Y * 0.5 - 40);
			CreateEnemy(ET_NORMAL_R, 100, SCREEN_Y * 0.5 - 40);
			break;
		case 2600:
			CreateEnemy(ET_NORMAL_L, -200, SCREEN_Y * 0.5 - 40);
			CreateEnemy(ET_NORMAL_R, 200, SCREEN_Y * 0.5 - 40);
			break;
		case 2750:
			CreateEnemy(ET_NORMAL_L, -300, SCREEN_Y * 0.5 - 40);
			CreateEnemy(ET_NORMAL_R, 300, SCREEN_Y * 0.5 - 40);
			break;
		case 2800:
			CreateEnemy(ET_NORMAL_L, -400, SCREEN_Y * 0.5 - 40);
			CreateEnemy(ET_NORMAL_R, 400, SCREEN_Y * 0.5 - 40);
			break;


		case 3500:
			CreateEnemy(ET_NORMAL_L, -400, SCREEN_Y * 0.5 - 40);
			CreateEnemy(ET_NORMAL_R, 400, SCREEN_Y * 0.5 - 40);
			break;
		case 3550:
			CreateEnemy(ET_NORMAL_L, -300, SCREEN_Y * 0.5 - 40);
			CreateEnemy(ET_NORMAL_R, 300, SCREEN_Y * 0.5 - 40);
			break;
		case 3600:
			CreateEnemy(ET_NORMAL_L, -200, SCREEN_Y * 0.5 - 40);
			CreateEnemy(ET_NORMAL_R, 200, SCREEN_Y * 0.5 - 40);
			break;
		case 3650:
			CreateEnemy(ET_NORMAL_L, -100, SCREEN_Y * 0.5 - 40);
			CreateEnemy(ET_NORMAL_R, 100, SCREEN_Y * 0.5 - 40);
			break;
		case 3700:
			CreateEnemy(ET_NORMAL_L, 0, SCREEN_Y * 0.5 - 40);
			break;

		case 4700:
			CreateEnemy(ET_NORMAL_L, -400, SCREEN_Y * 0.5 - 40);
			CreateEnemy(ET_NORMAL_L, -300, SCREEN_Y * 0.5 - 40);
			CreateEnemy(ET_NORMAL_L, -200, SCREEN_Y * 0.5 - 40);
			CreateEnemy(ET_NORMAL_L, -100, SCREEN_Y * 0.5 - 40);
			CreateEnemy(ET_NORMAL_L, 0, SCREEN_Y * 0.5 - 40);
			CreateEnemy(ET_NORMAL_R, 400, SCREEN_Y * 0.5 - 40);
			CreateEnemy(ET_NORMAL_R, 300, SCREEN_Y * 0.5 - 40);
			CreateEnemy(ET_NORMAL_R, 200, SCREEN_Y * 0.5 - 40);
			CreateEnemy(ET_NORMAL_R, 100, SCREEN_Y * 0.5 - 40);
			break;

		case 5700:
			CreateEnemy(ET_ROTATION, 500, SCREEN_Y * 0.5 - 40);
			CreateEnemy(ET_ROTATION, -500, SCREEN_Y * 0.5 - 40);
			break;

		case 6000:
			CreateEnemy(ET_NORMAL_L, -100, SCREEN_Y * 0.5 - 40);
			CreateEnemy(ET_NORMAL_R, 100, SCREEN_Y * 0.5 - 40);
			break;

		case 6300:
			CreateEnemy(ET_NORMAL_L, -100, SCREEN_Y * 0.5 - 40);
			CreateEnemy(ET_NORMAL_R, 100, SCREEN_Y * 0.5 - 40);
			break;

		case 6600:
			CreateEnemy(ET_NORMAL_L, -100, SCREEN_Y * 0.5 - 40);
			CreateEnemy(ET_NORMAL_R, 100, SCREEN_Y * 0.5 - 40);
			break;

		case 6900:
			CreateEnemy(ET_NORMAL_L, -100, SCREEN_Y * 0.5 - 40);
			CreateEnemy(ET_NORMAL_R, 100, SCREEN_Y * 0.5 - 40);
			break;

		case 8500:
			SetFade(FADE_OUT);
			InitEnemy();
			IniteBullet();
			dmgFlg = true;
			StopSound();
			PlaySound(SOUND_LABEL_BGM_BOSS);
			break;
		case 8700:
			for (int i = 0; i < MAX_ENEMY_NUM; i++)
			{
				DestroyEnemy(i);
			}
			CreateEnemy(ET_BOSS, 0, SCREEN_Y * 0.5 - 60);
			dmgFlg = false;
			break;

		default:
			break;
		}

		//クリア条件
		if (now_time > 8700)
		{
			//敵が存在しない場合クリア
			if (AllKill())
			{
				ChangeScene(SCENE_RESULT);
				SetGameClear();
				SetFade(FADE_OUT);
			}
		}
		break;

	default:
		break;
	}



	eCnt++;
	now_time++;
}

void damger()
{
	if (dmgFlg)
	{
		//damger描画
		SetPolygonAlpha(1);
		SetPolygonAngle(0);
		SetPolygonTexture(g_image);
		SetPolygonFrameSize(1, 1);
		SetPolygonSize(400, 100);
		SetPolygonUV(0, 1);
		SetPolygonPos(0, 0);
		UpdatePolygon();
		DrawPolygon(GetDeviceContext());
	}
}

void SetRespawnNum(int num)
{
	respawnNum = num;
}