//=============================================================================
//
// �|���S������ [polygon.h]
// Author : HIROHIKO HAMAYA
//
//=============================================================================
#pragma once

#include "main.h"
#include "DirectX.h"

#define NUM_VERTEX	(4)	// ���_��
#define NUM_POLYGON	(2)	// �|���S����

typedef struct {
	DirectX::XMFLOAT3 vtx;		// ���_���W
	DirectX::XMFLOAT4 diffuse;	// ���_�J���[
	DirectX::XMFLOAT2 tex;		// �e�N�X�`�����W
} VERTEX_2D;

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT InitPolygon(ID3D11Device* pDevice);
void UninitPolygon(void);
void UpdatePolygon(void);
void DrawPolygon(ID3D11DeviceContext* pDeviceContext);
void SetPolygonTexture(ID3D11ShaderResourceView* pTexture);
void SetPolygonPos(float fX, float fY);
void SetPolygonSize(float fScaleX, float fScaleY);
void SetPolygonAngle(float fAngle);
void SetPolygonUV(float fU, float fV);
void SetPolygonFrameSize(float fWidth, float fHeight);
void SetPolygonColor(float fRed, float fGreen, float fBlue);
void SetPolygonAlpha(float fAlpha);
