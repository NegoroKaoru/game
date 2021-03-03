#ifndef _EBULLET_H__
#define _EBULLET_H__

#include"main.h"

//ƒ}ƒNƒ’è‹`
#define MAX_eBullet_NUM (999)
//’e‚Ìí—Ş
enum eBulletKind
{
	//’Êí
	eBullet_NORMAL,
	//“G‚ÉŒü‚©‚¤
	eBullet_AIM,
	//™X‚É“G‚ÉŒü‚©‚¤
	eBullet_HANABI,
	//‰ñ“]
	eBullet_ROTATION,
};

//’e‚Ìî•ñ
struct eBulletInfo
{
	bool use;
	eBulletKind kind;
	float posX;
	float posY;
	float moveX;
	float moveY;
	float homingAngle;
	int	  type;
};

struct CreateeBulletArg
{
	eBulletKind kind;
	float x;
	float y;
	int type;
	int shotRotation;
};

HRESULT IniteBullet(void);
void UniniteBullet(void);
void UpdateeBullet(void);
void DraweBullet(void);

void CreateeBullet(CreateeBulletArg arg);
eBulletInfo GetEbulletInfo(int);


#endif //_eBullet_H__