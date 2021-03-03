//=============================================================================
//
// �}�b�v���� [map.h]
// Author : HIROHIKO HAMAYA
//
//=============================================================================
#pragma once

#include "main.h"

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT InitMap(void);
void UninitMap(void);
void UpdateMap(void);
void DrawMap(void);

int GetMapWidth(void);
int GetMapHeight(void);
void SetMapPosition(int nX, int nY);
POINT* GetMapPosition(void);
int GetMapScrollWidth(void);
int GetMapScrollHeight(void);
