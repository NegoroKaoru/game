#ifndef __Score_H__
#define __Score_H__

#include "main.h"

HRESULT InitScore(void);
void UninitScore(void);
void UpdateScore(void);
void DrawScore(void);

int GetScore(void);
void SetScore(int sec);
#endif