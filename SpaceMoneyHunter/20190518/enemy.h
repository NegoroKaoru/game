#ifndef	__ENEMY_H__
#define __ENEMY_H__

#include "main.h"

//=== �}�N���E�萔��` ===
#define MAX_ENEMY_NUM (100)

//�������萔������
 enum EnemyType
{
	NULL_ENEMY,
	//���f��
	ET_ASTEROID,
	//�ʏ�G(�ŏI���ړ��j
	ET_NORMAL_L,
	//�ʏ�G�i�ŏI�E�ړ��j
	ET_NORMAL_R,
	//���E�ɓ���
	ET_ROTATION,
	//�e���G
	ET_HANABI,
	//�{�X
	ET_BOSS,
};

struct EnemyInfo
{
	bool bUse;
	EnemyType Type;
	float fPosX, fPosY;
	float fMoveX, fMoveY;
	int nFrameCnt;
	bool rColer;
	int eLife;
	float nTexAnimeCnt;
	int animeFrame;
	int shotFrame;
	int shotRotation;
	float fTexV;
};

HRESULT InitEnemy(void);
void UninitEnemy(void);
void UpdateEnemy(void);
void DrawEnemy(void);
void CreateEnemy(EnemyType, float, float);
void DestroyEnemy(int index);
void SetEnemyDamage(int index);
bool AllKill(void);

EnemyInfo GetEnemyInfo(int index);


#endif// _ENEMY_H__