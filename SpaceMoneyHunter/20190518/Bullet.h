#ifndef _BULLET_H__
#define _BULLET_H__

#include"main.h"

//’e‚Ìí—Ş
enum BulletKind
{
	//’Êí
	BULLET_NORMAL,
	//“G‚ÉŒü‚©‚¤
	BULLET_AIM,	
	//™X‚É“G‚ÉŒü‚©‚¤
	BULLET_HOMING,
};

//’e‚Ìî•ñ
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
	float dir;	//Œü‚¢‚Ä‚¢‚é•ûŒü
};

HRESULT InitBullet(void);
void UninitBullet(void);
void UpdateBullet(void);
void DrawBullet(void);

void CreateBullet(CreateBulletArg arg);


#endif //_BULLET_H__