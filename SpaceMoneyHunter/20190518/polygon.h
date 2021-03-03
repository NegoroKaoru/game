//=============================================================================
//
// ポリゴン処理 [polygon.h]
// Author : HIROHIKO HAMAYA
//
//=============================================================================
#pragma once

#include "main.h"
#include "DirectX.h"

#define NUM_VERTEX	(4)	// 頂点数
#define NUM_POLYGON	(2)	// ポリゴン数

typedef struct {
	DirectX::XMFLOAT3 vtx;		// 頂点座標
	DirectX::XMFLOAT4 diffuse;	// 頂点カラー
	DirectX::XMFLOAT2 tex;		// テクスチャ座標
} VERTEX_2D;

//*****************************************************************************
// プロトタイプ宣言
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
