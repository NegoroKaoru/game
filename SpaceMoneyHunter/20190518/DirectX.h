#ifndef __HEADER_DIRECTX_H
#define __HEADER_DIRECTX_H
#include <d3d11.h>
#pragma comment(lib, "d3d11")//no Semicolon

//=== マクロ定義 ===
#define SAFE_RELEASE(p) if(p){p->Release(); p = NULL;}
//マクロ作る際\おけば改行できる


//=== プロトタイプ宣言 ===
bool DXInit(UINT, UINT, HWND, bool);		//初期化処理
void DXUninit(void);		//終了処理

//DXの描画開始・終了
void DXBeginRender(void);
void DXEndRender(void);

ID3D11Device* GetDevice(void);
ID3D11DeviceContext* GetDeviceContext(void);

#endif //__HEADER_DIRECTX_H