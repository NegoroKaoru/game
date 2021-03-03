#ifndef _BULLET_H__
#define _BULLET_H__

#include"main.h"

//�e�̎��
enum BulletKind
{
	//�ʏ�
	BULLET_NORMAL,
	//�G�Ɍ�����
	BULLET_AIM,	
	//���X�ɓG�Ɍ�����
	BULLET_HOMING,
};

//�e�̏��
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
	float dir;	//�����Ă������
};

HRESULT InitBullet(void);
void UninitBullet(void);
void UpdateBullet(void);
void DrawBullet(void);

void CreateBullet(CreateBulletArg arg);


#endif //_BULLET_H__