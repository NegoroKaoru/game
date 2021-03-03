#ifndef	__ENEMY_H__
#define __ENEMY_H__

#include "main.h"

//=== マクロ・定数定義 ===
#define MAX_ENEMY_NUM (100)

//＝＝＝定数＝＝＝
 enum EnemyType
{
	NULL_ENEMY,
	//小惑星
	ET_ASTEROID,
	//通常敵(最終左移動）
	ET_NORMAL_L,
	//通常敵（最終右移動）
	ET_NORMAL_R,
	//左右に動く
	ET_ROTATION,
	//弾幕敵
	ET_HANABI,
	//ボス
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