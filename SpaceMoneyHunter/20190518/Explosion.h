#ifndef __HEADER_EXPLOSION_H
#define __HEADER_EXPLOSION_H

#include "main.h"

HRESULT InitExplosion(void);
void UninitExplosion(void);
void UpdateExplosion(void);
void DrawExplosion(void);
bool SetExplosion(float x, float y);


#endif