#ifndef __HEADER_CHARACTER_H
#define __HEADER_CHARACTER_H

#include "main.h"

//=== ç\ë¢ëÃíËã` ===
typedef struct {
	int nStepCnt;		//counter for step
	float x;			//x Coordinate
	float y;			//y Coordinate
	bool bDash;			//Dash or not
	int nDashCnt;		//Counter for dash
	int nTexAnimeCnt;	//Counter for Texture Animation
	float fTexV;		//pos where Animation starts
	int Life;			//player life
	bool flash;		
	int bulletNum;	
	bool barrier;
}CharacterInfo;

HRESULT InitCharacter(void);
void UninitCharacter(void);
void UpdateCharacter(void);
void DrawCharacter(void);
CharacterInfo GetCharacterInfo(void);
void EnemyHitCheck(void);
void eBulletHitCheck(void);
void CoinHitCheck(void);
void damegeHit(void);
void SetCharacterInfo(int);

#endif	//__HEADER_CHARACTER_H