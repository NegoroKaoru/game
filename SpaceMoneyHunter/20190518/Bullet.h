#ifndef _BULLET_H__
#define _BULLET_H__

#include"main.h"

//弾の種類
enum BulletKind
{
	//通常
	BULLET_NORMAL,
	//敵に向かう
	BULLET_AIM,	
	//徐々に敵に向かう
	BULLET_HOMING,
};

//弾の情報
struct BulletInfo
{
	bool use;
	BulletKind kind;
	float posX;
	float posY;
	float moveX;
	float moveY;
	int targetIndex;
	float homingAngle;
};

struct CreateBulletArg
{
	BulletKind kind;
	float x;
	float y;
	float dir;	//向いている方向
};

HRESULT InitBullet(void);
void UninitBullet(void);
void UpdateBullet(void);
void DrawBullet(void);

void CreateBullet(CreateBulletArg arg);


#endif //_BULLET_H__