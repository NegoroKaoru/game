#ifndef	__COIN_H__
#define __COIN_H__

#include "main.h"

//=== マクロ・定数定義 ===
#define MAX_COIN_NUM (100)


struct CoinInfo
{
	bool bUse;
	float fPosX, fPosY;
	float fMoveX, fMoveY;
	int nTexAnimeCnt;
};

HRESULT InitCoin(void);
void UninitCoin(void);
void UpdateCoin(void);
void DrawCoin(void);
void CreateCoin(float, float);
void DestroyCoin(int index);

CoinInfo GetCoinInfo(int index);


#endif// _Coin_H__