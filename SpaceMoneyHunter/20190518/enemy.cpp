#include"enemy.h"
#include"polygon.h"
#include"Texture.h"
#include"Explosion.h"
#include"character.h"
#include"coin.h"
#include"eBullet.h"
#include"sound.h"


//=== �O���[�o���ϐ��錾 ===
ID3D11ShaderResourceView* g_pEnemyTexture[5];
EnemyInfo g_EnemyInfo[MAX_ENEMY_NUM];

int damegeCnt;	//�F�ύX�Ԋu�i�_���[�W���j
int direction;	//�r�����獶�E��ԕ���
int bossGauge;	//�{�X�̃Q�[�W
int bossCnt;	//�{�X�p�J�E���g

//�G����������
HRESULT InitEnemy(void)
{
	//�O���[�o���ϐ��̏�����
	damegeCnt = 0;
	direction = 1;
	bossGauge = 0;
	bossCnt	  = 0;

	//�G�̃X�e�[�^�X�̏�����
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

//�G�㏈��
void UninitEnemy(void)
{
	for(int i = 0 ;i< 5;i++)
	SAFE_RELEASE(g_pEnemyTexture[i]);
}

//�G�X�V����
void UpdateEnemy(void) 
{
	for (int i = 0; i < MAX_ENEMY_NUM; i++)
	{
		if (!g_EnemyInfo[i].bUse) continue;

		//�GHP0�ȉ��̏ꍇ���j
		if (g_EnemyInfo[i].eLife <= 0)
		{
			DestroyEnemy(i);
			CreateCoin(g_EnemyInfo[i].fPosX, g_EnemyInfo[i].fPosY);	//�R�C���쐬
		}

		//depends on character
		switch (g_EnemyInfo[i].Type)
		{
		case ET_ASTEROID:
			break;
		case ET_NORMAL_L:
			//�s���p�^�[��
			if (g_EnemyInfo[i].nFrameCnt < 150)
				g_EnemyInfo[i].fMoveY = -2;
			else if (g_EnemyInfo[i].nFrameCnt < 150 * 3)
				g_EnemyInfo[i].fMoveX = -2;

			//�e����
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

			//�A�j���t���[��
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
			//�s���p�^�[��
			if (g_EnemyInfo[i].nFrameCnt < 150)
				g_EnemyInfo[i].fMoveY = -2;
			else if (g_EnemyInfo[i].nFrameCnt < 150 * 3)
				g_EnemyInfo[i].fMoveX = 2;

			//�e����
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

			//�A�j���t���[��
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
			//�e����
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

				//�e�̔�Ԋp�x��ύX
				if (g_EnemyInfo[i].shotRotation == 360)
				{
					g_EnemyInfo[i].shotRotation = 0;
				}
				g_EnemyInfo[i].shotRotation += 6;
			}

			//�A�j���t���[��
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
			//�s���p�^�[��
			if (g_EnemyInfo[i].nFrameCnt < 320)
				g_EnemyInfo[i].fMoveX = -1;
			else if (g_EnemyInfo[i].nFrameCnt < 320 * 2)
				g_EnemyInfo[i].fMoveX = 1;
			else g_EnemyInfo[i].nFrameCnt = 0;

			//�e����
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

			//�A�j���t���[��
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
			//�Q�[�W�Ǘ�
			switch (g_EnemyInfo[i].eLife)
			{
			case 150 * 3:
				bossGauge = 0;
				break;
			case 150 * 2:
				bossGauge = 1;
				//�{�X�ʒu�ύX
				g_EnemyInfo[i].fPosX = 0.0f;
				g_EnemyInfo[i].fPosY = SCREEN_Y * 0.5 - 60;
				g_EnemyInfo[i].nFrameCnt = 0;
				g_EnemyInfo[i].fMoveX = 0.0f;
				g_EnemyInfo[i].fMoveY = 0.0f;
				break;
			case 150 * 1:
				bossGauge = 2;
				//�{�X�ʒu�ύX
				g_EnemyInfo[i].fPosX = 0.0f;
				g_EnemyInfo[i].fPosY = SCREEN_Y * 0.5 - 60;
				g_EnemyInfo[i].nFrameCnt = 0;
				g_EnemyInfo[i].fMoveX = 0.0f;
				g_EnemyInfo[i].fMoveY = 0.0f;
				break;
			default:
				break;
			}

			//�s���p�^�[��
			switch (bossGauge)
			{
			case 0:
				//�s���p�^�[��
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

				//�e����
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

					//�e�̔�Ԋp�x��ύX
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
				//�s���p�^�[��
				if (g_EnemyInfo[i].nFrameCnt < 300)
					g_EnemyInfo[i].fMoveX = -2;
				else if (g_EnemyInfo[i].nFrameCnt < 300 * 3)
					g_EnemyInfo[i].fMoveX = 2;
				else if (g_EnemyInfo[i].nFrameCnt < 300 * 4)
					g_EnemyInfo[i].fMoveX = -2;
				else g_EnemyInfo[i].nFrameCnt = 0;

				//�e����
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
				//�e����
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

				//�s���p�^�[��
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


				//�A�j���t���[��
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

			//�A�j���t���[��
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

		//��ʊO��
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

//�G�`��
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

		//�_���[�W��������ĐԂ��Ȃ鏈��
		if (g_EnemyInfo[i].rColer)
		{
			if (damegeCnt == 10)	//�Ԃ��Ȃ�Ԋu
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

//�G����
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

//�G����
void DestroyEnemy(int index)
{
	g_EnemyInfo[index].bUse = false;

	SetExplosion(g_EnemyInfo[index].fPosX, g_EnemyInfo[index].fPosY);
}

//�G���擾
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