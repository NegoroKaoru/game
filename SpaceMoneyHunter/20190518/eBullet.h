#ifndef _EBULLET_H__
#define _EBULLET_H__

#include"main.h"

//�������}�N����`������
#define MAX_eBullet_NUM (999)
//�e�̎��
enum eBulletKind
{
	//�ʏ�
	eBullet_NORMAL,
	//�G�Ɍ�����
	eBullet_AIM,
	//���X�ɓG�Ɍ�����
	eBullet_HANABI,
	//��]
	eBullet_ROTATION,
};

//�e�̏��
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