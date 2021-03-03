#include"eBullet.h"
#include"polygon.h"
#include"Texture.h"
#include"character.h"
#include"score.h"
#include"sound.h"
#include"coin.h"
#include <math.h>
#include"enemy.h"

//�������O���[�o���ϐ�������
eBulletInfo g_eBulletInfo[MAX_eBullet_NUM];
ID3D11ShaderResourceView* g_peBulletTexture[2];

//=== �}�N���E�萔��` ===
#define RAD(deg)  (deg*(3.14/180))


HRESULT IniteBullet(void)
{
	for (int i = 0; i < MAX_eBullet_NUM; i++)
	{
		g_eBulletInfo[i].use = false;
		g_eBulletInfo[i].kind = eBullet_NORMAL;
		g_eBulletInfo[i].posX = 0;
		g_eBulletInfo[i].posY = 0;
		g_eBulletInfo[i].moveX = 0;
		g_eBulletInfo[i].moveY = 0;
		g_eBulletInfo[i].homingAngle = 0;
		g_eBulletInfo[i].type = 0;
	}
	HRESULT hr;
	CreateTextureFromFile(GetDevice(), "data/TEXTURE/eBullet.png", &g_peBulletTexture[0]);
	hr = CreateTextureFromFile(GetDevice(), "data/TEXTURE/eBullet2.png", &g_peBulletTexture[1]);
	return hr;

}
void UniniteBullet(void)
{
	for (int i = 0; i < 2; i++)
	SAFE_RELEASE(g_peBulletTexture[i]);
}
void UpdateeBullet(void)
{
	//���g�p�̏ꍇ�̂�
	for (int i = 0; i < MAX_eBullet_NUM; i++)
	{
		//���g�p�͏������Ȃ�
		if (!g_eBulletInfo[i].use)
			continue;

		//�ړ�����
		g_eBulletInfo[i].posX += g_eBulletInfo[i].moveX;
		g_eBulletInfo[i].posY += g_eBulletInfo[i].moveY;

		//��ʊO�ɏo����
		if (fabsf(g_eBulletInfo[i].posX) > SCREEN_X * 0.5f + 16 ||
			fabsf(g_eBulletInfo[i].posX) < -(SCREEN_X * 0.5f + 16) ||
			fabsf(g_eBulletInfo[i].posY) < -(SCREEN_Y * 0.5f + 16) ||
			fabsf(g_eBulletInfo[i].posY) > SCREEN_Y * 0.5 + 16)
		{
			g_eBulletInfo[i].use = false;
		}

	}
}
void DraweBullet(void)
{

	//���g�p�̏ꍇ�̂�
	for (int i = 0; i < MAX_eBullet_NUM; i++)
	{
		//���g�p�͏������Ȃ�
		if (!g_eBulletInfo[i].use)
			continue;

		EnemyInfo eInfo = GetEnemyInfo(i);

			SetPolygonTexture(g_peBulletTexture[0]);
			SetPolygonFrameSize(1, 1);
			SetPolygonUV(0, 0);
			SetPolygonAngle(0);
			SetPolygonAlpha(1);
			SetPolygonSize(34, 34);
			SetPolygonPos(g_eBulletInfo[i].posX, g_eBulletInfo[i].posY);
			UpdatePolygon();
			DrawPolygon(GetDeviceContext());
	}
}


//�������e����������
void CreateeBullet(CreateeBulletArg arg)
{ 
	//�v���C���[���擾
	CharacterInfo cInfo = GetCharacterInfo();
	//�e���쐬���̒e���̐�
	int hanabiNum;	


		switch (arg.kind)
		{
			//�G�Ɍ�����
		case eBullet_AIM:
			break;
		case eBullet_HANABI:
			hanabiNum = 0;
			for (int i = 0; i < MAX_eBullet_NUM; i++)
			{
				//�g�p���͏������Ȃ�
				if (g_eBulletInfo[i].use)
					continue;

				g_eBulletInfo[i].use = true;
				g_eBulletInfo[i].kind = arg.kind;
				g_eBulletInfo[i].posX = arg.x;
				g_eBulletInfo[i].posY = arg.y;
				g_eBulletInfo[i].moveX = cos(RAD(hanabiNum * 18));
				g_eBulletInfo[i].moveY = sin(RAD(hanabiNum * 18));
				g_eBulletInfo[i].type = arg.type;

				if (hanabiNum == 20)
				{
					break;
				}
				hanabiNum++;
			}

			break;
			//����
		case eBullet_NORMAL:
			for (int i = 0; i < MAX_eBullet_NUM; i++)
			{
				//�g�p���͏������Ȃ�
				if (g_eBulletInfo[i].use)
					continue;

				g_eBulletInfo[i].use = true;
				g_eBulletInfo[i].kind = arg.kind;
				g_eBulletInfo[i].posX = arg.x;
				g_eBulletInfo[i].posY = arg.y;
				g_eBulletInfo[i].type = arg.type;

				//�G�ƃv���C���[�̊p�x
				double rad = atan2(cInfo.y - g_eBulletInfo[i].posY, cInfo.x - g_eBulletInfo[i].posX);

				g_eBulletInfo[i].moveX = 2 * cos(rad);
				g_eBulletInfo[i].moveY = 2 * sin(rad);
		

				break;
			}
			break;
		case eBullet_ROTATION:
			for (int i = 0; i < MAX_eBullet_NUM; i++)
			{
				//�g�p���͏������Ȃ�
				if (g_eBulletInfo[i].use)
					continue;

				g_eBulletInfo[i].use = true;
				g_eBulletInfo[i].kind = arg.kind;
				g_eBulletInfo[i].posX = arg.x;
				g_eBulletInfo[i].posY = arg.y;
				g_eBulletInfo[i].type = arg.type;
				
				g_eBulletInfo[i].moveX = 2 * cos(arg.shotRotation);
				g_eBulletInfo[i].moveY = 2 * sin(arg.shotRotation);


				break;
			}
			break;

		default :
			break;
		}
}


eBulletInfo GetEbulletInfo(int index)
{
	return g_eBulletInfo[index];
}