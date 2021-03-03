#include "DirectX.h"
#include "character.h"
#include "polygon.h"
#include "Texture.h"
#include "input.h"
#include "bullet.h"
#include "enemy.h"
#include "map.h"
#include"coin.h"
#include"sound.h"
#include"eBullet.h"

//=== マクロ・定数定義 ===
#define CHARACTER_TEX_PATH ("data/TEXTURE/player.png")
#define CHARACTER2_TEX_PATH ("data/TEXTURE/pCenter.png")
#define BARRIER_TEX_PATH ("data/TEXTURE/barrier.png")
#define PLAYER_SIZE_X		200								// ポリゴンのサイズ
#define PLAYER_SIZE_Y		200
#define PLAYER_SCROLL_X		(PLAYER_SIZE_X*4)
#define PLAYER_SCROLL_Y		(PLAYER_SIZE_Y*4)

//=== グローバル変数宣言 ===
CharacterInfo g_CharacterInfo;
ID3D11ShaderResourceView* g_pTexCharacter[3];

static XMFLOAT2	g_map;		// マップ サイズ
static XMFLOAT2	g_mappos;	// マップ位置

int sCnt;			//発射間隔
bool sFlg;		//発射フラグ
int fCnt;			//点滅間隔
int rCnt;			//復活間隔

HRESULT InitCharacter(void)
{
	g_CharacterInfo.nStepCnt = 0;
	g_CharacterInfo.x = 0.0f;
	g_CharacterInfo.y = -100.0f;
	g_CharacterInfo.bDash = false;
	g_CharacterInfo.nDashCnt = 0;
	g_CharacterInfo.nTexAnimeCnt = 0;
	g_CharacterInfo.fTexV = 0.0f;
	g_CharacterInfo.Life = 3;
	g_CharacterInfo.flash = false;
	g_CharacterInfo.bulletNum = 0;
	g_CharacterInfo.barrier = false;

	sCnt = 0;			//発射間隔
	sFlg = false;		//発射フラグ
	fCnt = 0;			//点滅間隔
	rCnt = 0;			//復活間隔

	CreateTextureFromFile(GetDevice(), CHARACTER_TEX_PATH, &g_pTexCharacter[0]);
	CreateTextureFromFile(GetDevice(), CHARACTER2_TEX_PATH, &g_pTexCharacter[1]);
	return CreateTextureFromFile(GetDevice(), BARRIER_TEX_PATH, &g_pTexCharacter[2]);
}
void UninitCharacter(void)
{
	for (int i = 0; i < 2; i++)
	SAFE_RELEASE(g_pTexCharacter[i]);
}
void UpdateCharacter(void)
{
	const float cfSpeed = 5.0f;
	g_CharacterInfo.fTexV = 0;


	if (IsPressInput(VK_LEFT) && g_CharacterInfo.x >= -(SCREEN_X * 0.5f - 20))
	{
		g_CharacterInfo.x -= cfSpeed;
		g_CharacterInfo.fTexV = 1;
	}

	if (IsPressInput(VK_RIGHT) && g_CharacterInfo.x <= (SCREEN_X * 0.5f - 20))
	{
		g_CharacterInfo.x += cfSpeed;
		g_CharacterInfo.fTexV = 2;
	}

	if (IsPressInput(VK_UP) && g_CharacterInfo.y < (SCREEN_Y * 0.5f - 20))
	{
		g_CharacterInfo.y += cfSpeed;

	}

	if (IsPressInput(VK_DOWN)&& g_CharacterInfo.y > -(SCREEN_Y * 0.5f - 20))
	{
		g_CharacterInfo.y -= cfSpeed;

	}

	if (IsPressInput(VK_SHIFT))
	{
		if (sFlg == false && !g_CharacterInfo.flash)
		{
			CreateBulletArg arg;
			switch (g_CharacterInfo.bulletNum)
			{
			case 0:
				arg.kind = BULLET_NORMAL;
				arg.x = g_CharacterInfo.x;
				arg.y = g_CharacterInfo.y;
				arg.dir = 1;
				CreateBullet(arg);
				break;
			case 1:
				arg.kind = BULLET_NORMAL;
				arg.x = g_CharacterInfo.x - 32;
				arg.y = g_CharacterInfo.y;
				arg.dir = 1;
				CreateBullet(arg);

				arg.x = g_CharacterInfo.x + 32;
				arg.y = g_CharacterInfo.y;
				arg.dir = 1;
				CreateBullet(arg);
				break;

				case 2:
					arg.kind = BULLET_NORMAL;
					arg.x = g_CharacterInfo.x;
					arg.y = g_CharacterInfo.y;
					arg.dir = 1;
					CreateBullet(arg);

					arg.kind = BULLET_NORMAL;
					arg.x = g_CharacterInfo.x - 32;
					arg.y = g_CharacterInfo.y;
					arg.dir = 1;
					CreateBullet(arg);

					arg.x = g_CharacterInfo.x + 32;
					arg.y = g_CharacterInfo.y;
					arg.dir = 1;
					CreateBullet(arg);
					break;
			default:
				break;
			}



			sFlg = true;
		}
		else
		{
			if (sCnt == 5)
			{
				sFlg = false;
				sCnt = 0;
			}

			sCnt++;

			
		}
	}

	//点滅中であれば当たり判定なし
	if (!g_CharacterInfo.flash)	
	{
		EnemyHitCheck();	//敵との当たり判定
		eBulletHitCheck();  //敵弾との当たり判定
	}

	CoinHitCheck();		//コイン当たり判定

	//点滅から元に戻す処理
	if (g_CharacterInfo.flash)
	{
		if (rCnt == 100)
		{
			g_CharacterInfo.flash = false;
			rCnt = 0;
		}
		rCnt++;
	}


	g_CharacterInfo.nStepCnt++;
}
void DrawCharacter(void)
{
	//キャラクターの描画
	SetPolygonTexture(g_pTexCharacter[0]);
	SetPolygonSize(100, 100);
	SetPolygonPos(g_CharacterInfo.x, g_CharacterInfo.y);
	SetPolygonFrameSize(1.0f / 3, 1.0f / 2);
	SetPolygonUV(g_CharacterInfo.fTexV / 3.0f, g_CharacterInfo.nTexAnimeCnt / 2.0f);
	if(g_CharacterInfo.nStepCnt % 5 == 0)
		g_CharacterInfo.nTexAnimeCnt++;
	g_CharacterInfo.nTexAnimeCnt %= 3;

	UpdatePolygon();

	//キャラの描画
	if (g_CharacterInfo.flash)	
	{
		if (fCnt == 5)
		{
			DrawPolygon(GetDeviceContext());	//点滅中の描画
			fCnt = 0;
		}
		fCnt++;
	}
	else
	{
		DrawPolygon(GetDeviceContext());	//通常描画
	}

	//当たり判定の中心玉の描画
	SetPolygonTexture(g_pTexCharacter[1]);
	SetPolygonFrameSize(1, 1);
	SetPolygonUV(0, 0);
	SetPolygonAngle(0);
	SetPolygonAlpha(1);
	SetPolygonSize(24, 24);
	SetPolygonPos(g_CharacterInfo.x, g_CharacterInfo.y);
	UpdatePolygon();
	DrawPolygon(GetDeviceContext());


	//バリアの描画
	if (g_CharacterInfo.barrier)
	{
		SetPolygonTexture(g_pTexCharacter[2]);
		SetPolygonSize(150, 150);
		SetPolygonAngle(90.0f);
		SetPolygonAlpha(0.5f);
		SetPolygonPos(g_CharacterInfo.x, g_CharacterInfo.y - 20);
		SetPolygonFrameSize(1.0f, 1.0f);
		SetPolygonUV(0, 1);
		DrawPolygon(GetDeviceContext());	
	}
}
CharacterInfo GetCharacterInfo(void)
{
	return g_CharacterInfo;
}

//敵との当たり判定
void EnemyHitCheck()
{
	for (int i = 0; i < MAX_ENEMY_NUM; i++)
	{
		EnemyInfo eInfo = GetEnemyInfo(i);

		//未使用の場合は処理しない
		if (!eInfo.bUse)
			continue;

		//四角形の当たり判定
		float xDist = fabsf(eInfo.fPosX - g_CharacterInfo.x);
		float yDist = fabsf(eInfo.fPosY - g_CharacterInfo.y);

		float enemyWidth;
		float enemyHeight;
		float characterSize;

		if(eInfo.Type == ET_BOSS)
		{
			enemyWidth = 200;
			enemyHeight = 180;
			characterSize = 24;
		}
		else
		{
			enemyWidth = 80;
			enemyHeight = 60;
			characterSize = 24;
		}

		//円の当たり判定
		float dist = xDist * xDist + yDist * yDist;
		float er = max(enemyWidth, enemyHeight) * 0.5f;
		float eb = characterSize * 0.5f;
		float radius = er * er + eb + eb;

		if (dist < radius)
			//if (xDist < enemyWidth + bulletSize && yDist < enemyHeight + bulletSize)
		{
			if(!eInfo.Type == ET_BOSS)
				DestroyEnemy(i);

			damegeHit();
		}
	}
}

//敵弾との当たり判定
void eBulletHitCheck()
{
	for (int i = 0; i < MAX_eBullet_NUM; i++)
	{
		eBulletInfo eBInfo = GetEbulletInfo(i);

		//未使用の場合は処理しない
		if (!eBInfo.use)
			continue;

		//四角形の当たり判定
		float xDist = fabsf(eBInfo.posX - g_CharacterInfo.x);
		float yDist = fabsf(eBInfo.posY - g_CharacterInfo.y);

		float enemyWidth = 24;
		float enemyHeight = 24;
		float characterSize = 24;

		//円の当たり判定
		float dist = xDist * xDist + yDist * yDist;
		float er = max(enemyWidth, enemyHeight) * 0.5f;
		float eb = characterSize * 0.5f;
		float radius = er * er + eb + eb;

		if (dist < radius)
			//if (xDist < enemyWidth + bulletSize && yDist < enemyHeight + bulletSize)
		{
			damegeHit();
		}
	}
}

//コインとの当たり判定
void CoinHitCheck()
{

	for (int i = 0; i < MAX_ENEMY_NUM; i++)
	{
		CoinInfo cInfo = GetCoinInfo(i);

		//未使用の場合は処理しない
		if (!cInfo.bUse)
			continue;

		//四角形の当たり判定
		float xDist = fabsf(cInfo.fPosX - g_CharacterInfo.x);
		float yDist = fabsf(cInfo.fPosY - g_CharacterInfo.y);

		float coinWidth = 90;
		float coinHeight = 90;
		float characterSize = 200;

		//円の当たり判定
		float dist = xDist * xDist + yDist * yDist;
		float er = max(coinWidth, coinHeight) * 0.5f;
		float eb = characterSize * 0.5f;
		float radius = er * er + eb + eb;


		if (dist < radius)
			//if (xDist < enemyWidth + bulletSize && yDist < enemyHeight + bulletSize)
		{
			DestroyCoin(i);
		}

	}
}

void damegeHit()
{
	//バリア張っている様態の場合
	if (g_CharacterInfo.barrier)
	{
		PlaySound(SOUND_LABEL_SE_BARRIERBREAK);
		g_CharacterInfo.barrier = false;
		g_CharacterInfo.flash = true;
	}
	else
	{
		g_CharacterInfo.Life -= 1;
		g_CharacterInfo.flash = true;
		PlaySound(SOUND_LABEL_DEATH);
		g_CharacterInfo.bulletNum = 0;
	}

	if (g_CharacterInfo.Life == 0)
		g_CharacterInfo.y = 700;
}

void SetCharacterInfo(int num)
{
	switch (num)
	{
	case 0:
		g_CharacterInfo.bulletNum++;
		break;
	case 1:
		g_CharacterInfo.Life++;
		break;
	case 2:
		g_CharacterInfo.barrier = true;
		break;
	default:
		break;
	}
}


