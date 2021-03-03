#include"enemy.h"
#include"polygon.h"
#include"Texture.h"
#include"Explosion.h"
#include"character.h"
#include"coin.h"
#include"eBullet.h"
#include"sound.h"


//=== グローバル変数宣言 ===
ID3D11ShaderResourceView* g_pEnemyTexture[5];
EnemyInfo g_EnemyInfo[MAX_ENEMY_NUM];

int damegeCnt;	//色変更間隔（ダメージ時）
int direction;	//途中から左右飛ぶ方向
int bossGauge;	//ボスのゲージ
int bossCnt;	//ボス用カウント

//敵初期化処理
HRESULT InitEnemy(void)
{
	//グローバル変数の初期化
	damegeCnt = 0;
	direction = 1;
	bossGauge = 0;
	bossCnt	  = 0;

	//敵のステータスの初期化
	for (int i = 0; i < MAX_ENEMY_NUM; i++)
	{
		g_EnemyInfo[i].bUse = false;
		g_EnemyInfo[i].Type = NULL_ENEMY;
		g_EnemyInfo[i].fPosX = 0.0f;
		g_EnemyInfo[i].fPosY = 0.0f;
		g_EnemyInfo[i].fMoveX = 0.0f;
		g_EnemyInfo[i].fMoveY = 0.0f;
		g_EnemyInfo[i].nFrameCnt = 0;
		g_EnemyInfo[i].rColer = false;
		g_EnemyInfo[i].eLife = 0;
		g_EnemyInfo[i].nTexAnimeCnt = 0;
		g_EnemyInfo[i].animeFrame = 0;
		g_EnemyInfo[i].shotFrame = 0;
		g_EnemyInfo[i].shotRotation = 0;
		g_EnemyInfo[i].fTexV = 0.0f;
	}

	CreateTextureFromFile(GetDevice(), "data/TEXTURE/asteroid.png", &g_pEnemyTexture[0]);
	CreateTextureFromFile(GetDevice(), "data/TEXTURE/enemy1.png", &g_pEnemyTexture[1]);
	CreateTextureFromFile(GetDevice(), "data/TEXTURE/enemy3.png", &g_pEnemyTexture[2]);
	CreateTextureFromFile(GetDevice(), "data/TEXTURE/enemy2.png", &g_pEnemyTexture[3]);
	return (CreateTextureFromFile(GetDevice(), "data/TEXTURE/dragon.png", &g_pEnemyTexture[4]));
}

//敵後処理
void UninitEnemy(void)
{
	for(int i = 0 ;i< 5;i++)
	SAFE_RELEASE(g_pEnemyTexture[i]);
}

//敵更新処理
void UpdateEnemy(void) 
{
	for (int i = 0; i < MAX_ENEMY_NUM; i++)
	{
		if (!g_EnemyInfo[i].bUse) continue;

		//敵HP0以下の場合撃破
		if (g_EnemyInfo[i].eLife <= 0)
		{
			DestroyEnemy(i);
			CreateCoin(g_EnemyInfo[i].fPosX, g_EnemyInfo[i].fPosY);	//コイン作成
		}

		//depends on character
		switch (g_EnemyInfo[i].Type)
		{
		case ET_ASTEROID:
			break;
		case ET_NORMAL_L:
			//行動パターン
			if (g_EnemyInfo[i].nFrameCnt < 150)
				g_EnemyInfo[i].fMoveY = -2;
			else if (g_EnemyInfo[i].nFrameCnt < 150 * 3)
				g_EnemyInfo[i].fMoveX = -2;

			//弾生成
			if (g_EnemyInfo[i].shotFrame == 30)
			{
				PlaySound(SOUND_LABEL_SE_SHOT);
				CreateeBulletArg arg;
				arg.kind = eBullet_NORMAL;
				arg.x = g_EnemyInfo[i].fPosX;
				arg.y = g_EnemyInfo[i].fPosY;
				arg.type = g_EnemyInfo[i].Type;
				CreateeBullet(arg);
				g_EnemyInfo[i].shotFrame = 0;
			}

			//アニメフレーム
			if (g_EnemyInfo[i].animeFrame == 7)
			{
				g_EnemyInfo[i].animeFrame = 0;
				g_EnemyInfo[i].nTexAnimeCnt++;
			}
			if (g_EnemyInfo[i].nTexAnimeCnt == 7)
			{
				g_EnemyInfo[i].nTexAnimeCnt = 0;
			}
			break;
		case ET_NORMAL_R:
			//行動パターン
			if (g_EnemyInfo[i].nFrameCnt < 150)
				g_EnemyInfo[i].fMoveY = -2;
			else if (g_EnemyInfo[i].nFrameCnt < 150 * 3)
				g_EnemyInfo[i].fMoveX = 2;

			//弾生成
			if (g_EnemyInfo[i].shotFrame == 30)
			{
				PlaySound(SOUND_LABEL_SE_SHOT);
				CreateeBulletArg arg;
				arg.kind = eBullet_NORMAL;
				arg.x = g_EnemyInfo[i].fPosX;
				arg.y = g_EnemyInfo[i].fPosY;
				arg.type = g_EnemyInfo[i].Type;
				CreateeBullet(arg);
				g_EnemyInfo[i].shotFrame = 0;
			}

			//アニメフレーム
			if (g_EnemyInfo[i].animeFrame == 7)
			{
				g_EnemyInfo[i].animeFrame = 0;
				g_EnemyInfo[i].nTexAnimeCnt++;
			}

			if (g_EnemyInfo[i].nTexAnimeCnt == 7)
			{
				g_EnemyInfo[i].nTexAnimeCnt = 0;
			}
			break;
		case ET_ROTATION:
			//弾生成
			if (g_EnemyInfo[i].shotFrame == 20)
			{
				PlaySound(SOUND_LABEL_SE_SHOT);
				CreateeBulletArg arg;
				arg.kind = eBullet_ROTATION;
				arg.x = g_EnemyInfo[i].fPosX;
				arg.y = g_EnemyInfo[i].fPosY;
				arg.type = g_EnemyInfo[i].Type;
				arg.shotRotation = g_EnemyInfo[i].shotRotation;
				CreateeBullet(arg);
				g_EnemyInfo[i].shotFrame = 0;

				//弾の飛ぶ角度を変更
				if (g_EnemyInfo[i].shotRotation == 360)
				{
					g_EnemyInfo[i].shotRotation = 0;
				}
				g_EnemyInfo[i].shotRotation += 6;
			}

			//アニメフレーム
			if (g_EnemyInfo[i].animeFrame == 7)
			{
				g_EnemyInfo[i].animeFrame = 0;
				g_EnemyInfo[i].nTexAnimeCnt++;
			}

			if (g_EnemyInfo[i].nTexAnimeCnt == 7)
			{
				g_EnemyInfo[i].nTexAnimeCnt = 0;
			}

			break;

		case ET_HANABI:
			//行動パターン
			if (g_EnemyInfo[i].nFrameCnt < 320)
				g_EnemyInfo[i].fMoveX = -1;
			else if (g_EnemyInfo[i].nFrameCnt < 320 * 2)
				g_EnemyInfo[i].fMoveX = 1;
			else g_EnemyInfo[i].nFrameCnt = 0;

			//弾生成
			if (g_EnemyInfo[i].shotFrame == 50)
			{
				PlaySound(SOUND_LABEL_SE_SHOT);
				CreateeBulletArg arg;
				arg.kind = eBullet_HANABI;
				arg.x = g_EnemyInfo[i].fPosX;
				arg.y = g_EnemyInfo[i].fPosY;
				arg.type = g_EnemyInfo[i].Type;
				CreateeBullet(arg);
				g_EnemyInfo[i].shotFrame = 0;
			}

			//アニメフレーム
			if (g_EnemyInfo[i].animeFrame == 7)
			{
				g_EnemyInfo[i].animeFrame = 0;
				g_EnemyInfo[i].nTexAnimeCnt++;
			}

			if (g_EnemyInfo[i].nTexAnimeCnt == 7)
			{
				g_EnemyInfo[i].nTexAnimeCnt = 0;
			}
			break;

		case ET_BOSS:
			//ゲージ管理
			switch (g_EnemyInfo[i].eLife)
			{
			case 150 * 3:
				bossGauge = 0;
				break;
			case 150 * 2:
				bossGauge = 1;
				//ボス位置変更
				g_EnemyInfo[i].fPosX = 0.0f;
				g_EnemyInfo[i].fPosY = SCREEN_Y * 0.5 - 60;
				g_EnemyInfo[i].nFrameCnt = 0;
				g_EnemyInfo[i].fMoveX = 0.0f;
				g_EnemyInfo[i].fMoveY = 0.0f;
				break;
			case 150 * 1:
				bossGauge = 2;
				//ボス位置変更
				g_EnemyInfo[i].fPosX = 0.0f;
				g_EnemyInfo[i].fPosY = SCREEN_Y * 0.5 - 60;
				g_EnemyInfo[i].nFrameCnt = 0;
				g_EnemyInfo[i].fMoveX = 0.0f;
				g_EnemyInfo[i].fMoveY = 0.0f;
				break;
			default:
				break;
			}

			//行動パターン
			switch (bossGauge)
			{
			case 0:
				//行動パターン
				if (g_EnemyInfo[i].nFrameCnt < 400)
				{
					g_EnemyInfo[i].fMoveY = -1;
					g_EnemyInfo[i].fMoveX = 1;
				}
				else if (g_EnemyInfo[i].nFrameCnt < 400 * 2)
				{
					g_EnemyInfo[i].fMoveY = 1;
					g_EnemyInfo[i].fMoveX = -1;
				}
				else if (g_EnemyInfo[i].nFrameCnt < 400 * 3)
				{
					g_EnemyInfo[i].fMoveY = -1;
					g_EnemyInfo[i].fMoveX = -1;
				}
				else if (g_EnemyInfo[i].nFrameCnt < 400 * 4)
				{
					g_EnemyInfo[i].fMoveY = 1;
					g_EnemyInfo[i].fMoveX = 1;
				}
				else g_EnemyInfo[i].nFrameCnt = 0;

				//弾生成
				if (g_EnemyInfo[i].shotFrame == 5)
				{
					PlaySound(SOUND_LABEL_SE_SHOT);
					CreateeBulletArg arg;
					arg.kind = eBullet_ROTATION;
					arg.x = g_EnemyInfo[i].fPosX;
					arg.y = g_EnemyInfo[i].fPosY;
					arg.type = g_EnemyInfo[i].Type;
					arg.shotRotation = g_EnemyInfo[i].shotRotation;
					CreateeBullet(arg);
					g_EnemyInfo[i].shotFrame = 0;

					//弾の飛ぶ角度を変更
					if (g_EnemyInfo[i].shotRotation == 360)
					{
						g_EnemyInfo[i].shotRotation = 0;
					}
					g_EnemyInfo[i].shotRotation += 6;
				}

				if (bossCnt == 500)
				{
					CreateEnemy(ET_NORMAL_L, -400, SCREEN_Y * 0.5 - 40);
					CreateEnemy(ET_NORMAL_L, -200, SCREEN_Y * 0.5 - 40);
					CreateEnemy(ET_NORMAL_R, 400, SCREEN_Y * 0.5 - 40);
					CreateEnemy(ET_NORMAL_R, 200, SCREEN_Y * 0.5 - 40);
					bossCnt = 0;
				}
				bossCnt++;

				break;
			case 1:
				//行動パターン
				if (g_EnemyInfo[i].nFrameCnt < 300)
					g_EnemyInfo[i].fMoveX = -2;
				else if (g_EnemyInfo[i].nFrameCnt < 300 * 3)
					g_EnemyInfo[i].fMoveX = 2;
				else if (g_EnemyInfo[i].nFrameCnt < 300 * 4)
					g_EnemyInfo[i].fMoveX = -2;
				else g_EnemyInfo[i].nFrameCnt = 0;

				//弾生成
				if (g_EnemyInfo[i].shotFrame == 50)
				{
					PlaySound(SOUND_LABEL_SE_SHOT);
					CreateeBulletArg arg;
					arg.kind = eBullet_HANABI;
					arg.x = ((rand() % SCREEN_X)) - SCREEN_X * 0.5;
					arg.y = SCREEN_Y * 0.5;
					arg.type = g_EnemyInfo[i].Type;
					CreateeBullet(arg);
					g_EnemyInfo[i].shotFrame = 0;
				}
				break;

			case 2:
				//弾生成
				if (g_EnemyInfo[i].shotFrame == 50)
				{
					PlaySound(SOUND_LABEL_SE_SHOT);
					CreateeBulletArg arg;
					arg.kind = eBullet_HANABI;
					arg.x = g_EnemyInfo[i].fPosX;
					arg.y = g_EnemyInfo[i].fPosY;
					arg.type = g_EnemyInfo[i].Type;
					CreateeBullet(arg);
					g_EnemyInfo[i].shotFrame = 0;
				}

				//行動パターン
				if (g_EnemyInfo[i].nFrameCnt < 300)
				{
					g_EnemyInfo[i].fMoveY = -1;
					g_EnemyInfo[i].fMoveX = 1;
				}
				else if (g_EnemyInfo[i].nFrameCnt < 300 * 2)
				{
					g_EnemyInfo[i].fMoveY = -1;
					g_EnemyInfo[i].fMoveX = -1;
				}
				else if (g_EnemyInfo[i].nFrameCnt < 300 * 3)
				{
					g_EnemyInfo[i].fMoveY = 1;
					g_EnemyInfo[i].fMoveX = -1;
				}
				else if (g_EnemyInfo[i].nFrameCnt < 300 * 4)
				{
					g_EnemyInfo[i].fMoveY = 1;
					g_EnemyInfo[i].fMoveX = 1;
				}
				else g_EnemyInfo[i].nFrameCnt = 0;


				//アニメフレーム
				if (g_EnemyInfo[i].animeFrame == 7)
				{
					g_EnemyInfo[i].animeFrame = 0;
					g_EnemyInfo[i].nTexAnimeCnt++;
				}

				if (g_EnemyInfo[i].nTexAnimeCnt == 7)
				{
					g_EnemyInfo[i].nTexAnimeCnt = 0;
				}
				break;
			default:
				break;
			}

			//アニメフレーム
			if (g_EnemyInfo[i].animeFrame == 9)
			{
				g_EnemyInfo[i].animeFrame = 0;
				g_EnemyInfo[i].nTexAnimeCnt++;
			}

			if (g_EnemyInfo[i].nTexAnimeCnt == 3)
			{
				g_EnemyInfo[i].nTexAnimeCnt = 0;
			}

			break; 

		default :
			break;

		}
		//doesn't matter who it is
		g_EnemyInfo[i].fPosX += g_EnemyInfo[i].fMoveX;
		g_EnemyInfo[i].fPosY += g_EnemyInfo[i].fMoveY;
		g_EnemyInfo[i].nFrameCnt++;
		g_EnemyInfo[i].animeFrame++;


		g_EnemyInfo[i].shotFrame++;

		//画面外に
		if (g_EnemyInfo[i].Type == ET_BOSS) continue;
		if (fabsf(g_EnemyInfo[i].fPosX) > SCREEN_X * 0.5f + 16 ||
			fabsf(g_EnemyInfo[i].fPosX) < -(SCREEN_X * 0.5f + 16) ||
			fabsf(g_EnemyInfo[i].fPosY) < -(SCREEN_Y * 0.5f + 16) ||
			fabsf(g_EnemyInfo[i].fPosY) > SCREEN_Y * 0.5 + 16)
		{
			g_EnemyInfo[i].bUse = false;
		}
		

	}
}

//敵描画
void DrawEnemy(void)
{
	SetPolygonAlpha(1);
	SetPolygonAngle(0);
	for (int i = 0; i < MAX_ENEMY_NUM; i++)
	{
		if (!g_EnemyInfo[i].bUse) continue;

		switch (g_EnemyInfo[i].Type)
		{
		case ET_ASTEROID:
			SetPolygonTexture(g_pEnemyTexture[0]);
			SetPolygonFrameSize(1, 1);
			SetPolygonUV(0, 1);
			SetPolygonSize(80, 60);
			break;
		case ET_NORMAL_L:
		case ET_NORMAL_R:
			SetPolygonTexture(g_pEnemyTexture[1]);
			SetPolygonFrameSize(1.0f / 7.0f, 1.0f);
			SetPolygonUV(g_EnemyInfo[i].nTexAnimeCnt / 7.09f, 1.0f);
			SetPolygonSize(80, 60);
			break;
		case ET_ROTATION:
			SetPolygonTexture(g_pEnemyTexture[2]);
			SetPolygonFrameSize(1.0f / 7.0f, 1.0f);
			SetPolygonUV(g_EnemyInfo[i].nTexAnimeCnt / 7.05f, 1.0f);
			SetPolygonSize(80, 60);
			break;
		case ET_HANABI:
			SetPolygonTexture(g_pEnemyTexture[3]);
			SetPolygonFrameSize(1.0f / 7.0f, 1.0f);
			SetPolygonUV(g_EnemyInfo[i].nTexAnimeCnt / 7.05f, 1.0f);
			SetPolygonSize(80, 60);
			break;
		case ET_BOSS:
			SetPolygonTexture(g_pEnemyTexture[4]);
			SetPolygonFrameSize(1.0f / 3, 1.0f / 4);
			SetPolygonUV(g_EnemyInfo[i].nTexAnimeCnt / 3.0f, g_EnemyInfo[i].fTexV / 4.0f);
			SetPolygonSize(200, 180);
			break;

		default:
			break;

		}

		SetPolygonPos(g_EnemyInfo[i].fPosX, g_EnemyInfo[i].fPosY);

		//ダメージをくらって赤くなる処理
		if (g_EnemyInfo[i].rColer)
		{
			if (damegeCnt == 10)	//赤くなる間隔
			{
				g_EnemyInfo[i].rColer = false;
				damegeCnt = 0;
				SetPolygonColor(1.0f, 1.0f, 1.0f);
			}

			SetPolygonColor(0.929412f, 0.152941f, 0.564706f);
			damegeCnt++;
		}

			UpdatePolygon();
			DrawPolygon(GetDeviceContext());
			SetPolygonColor(1.0f, 1.0f, 1.0f);
	}
}

//敵生成
void CreateEnemy(EnemyType type, float x, float y)
{
	for (int i = 0; i < MAX_ENEMY_NUM; i++)
	{
		if (g_EnemyInfo[i].bUse) continue;
		g_EnemyInfo[i].bUse = true;
		g_EnemyInfo[i].Type = type;
		g_EnemyInfo[i].fPosX = x;
		g_EnemyInfo[i].fPosY = y;
		g_EnemyInfo[i].fMoveX = 0.0f;
		g_EnemyInfo[i].fMoveY = 0.0f;
		g_EnemyInfo[i].nFrameCnt = 0;
		g_EnemyInfo[i].rColer = false;
		g_EnemyInfo[i].animeFrame = 0;
		g_EnemyInfo[i].shotFrame = 0;
		g_EnemyInfo[i].shotRotation = 0;
		g_EnemyInfo[i].fTexV = 0.0f;

		switch (g_EnemyInfo[i].Type)
		{
		case ET_ASTEROID:
			g_EnemyInfo[i].eLife = 8;
			g_EnemyInfo[i].fMoveY = -1.0f;
			break;
		case ET_NORMAL_R:
		case ET_NORMAL_L:
			g_EnemyInfo[i].eLife = 5;
			break;
		case ET_ROTATION:
			g_EnemyInfo[i].eLife = 80;
			break;
		case ET_HANABI:
			g_EnemyInfo[i].eLife = 150;
			break;
		case ET_BOSS:
			g_EnemyInfo[i].eLife = 200 * 3;
			break;
		}
		break;
	}
}

//敵消滅
void DestroyEnemy(int index)
{
	g_EnemyInfo[index].bUse = false;

	SetExplosion(g_EnemyInfo[index].fPosX, g_EnemyInfo[index].fPosY);
}

//敵情報取得
EnemyInfo GetEnemyInfo(int index)
{
	if (0 <= index && index < MAX_ENEMY_NUM)
	{
		return g_EnemyInfo[index];
	}
	else
	{
		EnemyInfo dummy;
		dummy.bUse = false;
		dummy.Type = ET_ASTEROID;
		dummy.fPosX = 0;
		dummy.fPosY = 0;
		return dummy;
	}
}

void SetEnemyDamage(int index)
{
	g_EnemyInfo[index].rColer = true;
	g_EnemyInfo[index].eLife--;
}

bool AllKill()
{
	for (int i = 0; i < MAX_ENEMY_NUM; i++)
	{
		if (g_EnemyInfo[i].bUse == true)
			if(
				g_EnemyInfo[i].Type == ET_NORMAL_R||
				g_EnemyInfo[i].Type == ET_NORMAL_L||
				g_EnemyInfo[i].Type == ET_HANABI||
				g_EnemyInfo[i].Type == ET_ROTATION||
				g_EnemyInfo[i].Type == ET_BOSS
				
				) return false;
	}
	return true;
}