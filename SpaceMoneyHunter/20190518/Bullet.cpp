#include"Bullet.h"
#include"polygon.h"
#include"Texture.h"
#include"enemy.h"
#include"score.h"
#include"sound.h"
#include"coin.h"
#include"SceneManager.h"

//＝＝＝マクロ定義＝＝＝
#define MAX_BULLET_NUM (100)


//＝＝＝グローバル変数＝＝＝
BulletInfo g_bulletInfo[MAX_BULLET_NUM];
ID3D11ShaderResourceView* g_pBulletTexture;

//＝＝＝プロトタイプ宣言＝＝＝
void BulletHitCheck(int index);


HRESULT InitBullet(void)
{
	for (int i = 0; i < MAX_BULLET_NUM; i++)
	{
		g_bulletInfo[i].use = false;
		g_bulletInfo[i].kind = BULLET_NORMAL;
		g_bulletInfo[i].posX = 0;
		g_bulletInfo[i].posY = 0;
		g_bulletInfo[i].moveX = 0;
		g_bulletInfo[i].moveY = 0;
		g_bulletInfo[i].targetIndex = -1;
		g_bulletInfo[i].homingAngle = 0;
	}

	HRESULT hr;
	hr = CreateTextureFromFile(GetDevice(), "data/TEXTURE/Fire_Frame.png", &g_pBulletTexture);
	return hr;

}
void UninitBullet(void)
{
	SAFE_RELEASE(g_pBulletTexture);
}
void UpdateBullet(void)
{
	//未使用の場合のみ
	for (int i = 0; i < MAX_BULLET_NUM; i++)
	{
		//未使用は処理しない
		if (!g_bulletInfo[i].use)
			continue;

		//ホーミング処理
		if (g_bulletInfo[i].kind == BULLET_HOMING)
		{
			EnemyInfo eInfo = GetEnemyInfo(g_bulletInfo[i].targetIndex);

			if (eInfo.bUse)
			{
				float homingAngle = 
					atan2f(eInfo.fPosY - g_bulletInfo[i].posY, eInfo.fPosX - g_bulletInfo[i].posX);

				float subAngle = homingAngle - g_bulletInfo[i].homingAngle;
				float pi = 3.1415926535f;

				if (fabsf(subAngle) > pi)
				{
					if (subAngle > 0)
					{
						subAngle = subAngle - pi * 2;
					}
					else
					{
						subAngle = pi * 2 + subAngle;
					}
				}

				subAngle *= 0.01f;
				g_bulletInfo[i].homingAngle += subAngle;
				homingAngle = g_bulletInfo[i].homingAngle;


				g_bulletInfo[i].moveX = cosf(homingAngle) * 3.0f;
				g_bulletInfo[i].moveY = sinf(homingAngle) * 3.0f;
			}

		}

		//移動処理
		g_bulletInfo[i].posX += g_bulletInfo[i].moveX;
		g_bulletInfo[i].posY += g_bulletInfo[i].moveY;

		//敵との当たり判定
		BulletHitCheck(i);

		//画面外に出たか
		if (fabsf(g_bulletInfo[i].posX) > SCREEN_X * 0.5f + 16 ||
			(fabsf(g_bulletInfo[i].posY) > SCREEN_Y * 0.5 + 16))
		{
			g_bulletInfo[i].use = false;
		}

	}
}
void DrawBullet(void)
{
	SetPolygonTexture(g_pBulletTexture);
	SetPolygonFrameSize(1, 1);
	SetPolygonUV(0, 0);
	SetPolygonAngle(0);
	SetPolygonAlpha(1);
	SetPolygonSize(16, 16);

	for (int i = 0; i < MAX_BULLET_NUM; i++)
	{
		if (!g_bulletInfo[i].use)
		{
			continue;
		}

		SetPolygonPos(g_bulletInfo[i].posX, g_bulletInfo[i].posY);
		UpdatePolygon();
		DrawPolygon(GetDeviceContext());
	}
}

//＝＝＝弾生成＝＝＝
void CreateBullet(CreateBulletArg arg)
{
	bool search = false;	//敵が見つかったか

	PlaySound(SOUND_LABEL_SE_SHOT);

	for (int i = 0; i < MAX_BULLET_NUM; i++)
	{
		//使用中は処理しない
		if (g_bulletInfo[i].use)
		{
			continue;
		}

		g_bulletInfo[i].use = true;
		g_bulletInfo[i].kind = arg.kind;
		g_bulletInfo[i].posX = arg.x;
		g_bulletInfo[i].posY = arg.y;
		g_bulletInfo[i].moveX = 0;
		g_bulletInfo[i].moveY = 0;
		g_bulletInfo[i].targetIndex = -1;
		

		switch (arg.kind)
		{
			//敵に向かう
		case BULLET_AIM:
		case BULLET_HOMING:

			for (int j = 0; MAX_ENEMY_NUM; j++)
			{
				EnemyInfo eInfo = GetEnemyInfo(j);

				//未使用は処理しない
				if (!g_bulletInfo[j].use)
					continue;

				if (arg.kind == BULLET_AIM)
				{
					//アークタンジェント…ラジアンを出せす
					float aimAngle = atan2(eInfo.fPosY - arg.y, eInfo.fPosX - arg.x);
					g_bulletInfo[i].moveX = cosf(aimAngle) * 6;
					g_bulletInfo[i].moveY = sinf(aimAngle) * 6;
				}
				else
				{
					g_bulletInfo[i].targetIndex = j;
					g_bulletInfo[i].homingAngle = 0;
				}

				search = true;
				break;

			}	//←breakが無いのは意図的　
			if (search)	//敵が見つかった場合は抜ける
			{
				break;
			}
			//fallthrough　意図的にbreakが書いてないかどうか


			//普通
		case BULLET_NORMAL:
			g_bulletInfo[i].moveY = 10 * arg.dir;

			break;


		}
		break;
	}

	
}

//敵との当たり判定
void BulletHitCheck(int index)
{
	for (int i = 0; i < MAX_ENEMY_NUM; i++)
	{
		EnemyInfo eInfo = GetEnemyInfo(i);

		//未使用の場合は処理しない
		if (!eInfo.bUse)
			continue;

		//四角形の当たり判定
		float xDist = fabsf(eInfo.fPosX - g_bulletInfo[index].posX);
		float yDist = fabsf(eInfo.fPosY - g_bulletInfo[index].posY);

		float enemyWidth =  50;
		float enemyHeight = 70;
		float bulletSize = 16;

		//円の当たり判定
		float dist = xDist * xDist + yDist * yDist;
		float er = max(enemyWidth, enemyHeight) * 0.5f;
		float eb = bulletSize * 0.5f;
		float radius = er * er + eb + eb;


		if(dist < radius)
		//if (xDist < enemyWidth + bulletSize && yDist < enemyHeight + bulletSize)
		{
			PlaySound(SOUND_LABEL_SE_EXPLOSION);
			g_bulletInfo[index].use = false;
			SetEnemyDamage(i);
		}
	
	}

}