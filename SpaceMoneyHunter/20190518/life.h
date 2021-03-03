#ifndef __PLIFE_H__
#define __PLIFE_H__

#include "main.h"

HRESULT InitpLife(void);
void UninitpLife(void);
void UpdatepLife(void);
void DrawpLife(void);

int GetpLife(void);
void SetpLife(int sec);
#endif