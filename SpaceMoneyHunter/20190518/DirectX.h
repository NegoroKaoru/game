#ifndef __HEADER_DIRECTX_H
#define __HEADER_DIRECTX_H
#include <d3d11.h>
#pragma comment(lib, "d3d11")//no Semicolon

//=== �}�N����` ===
#define SAFE_RELEASE(p) if(p){p->Release(); p = NULL;}
//�}�N������\�����Ή��s�ł���


//=== �v���g�^�C�v�錾 ===
bool DXInit(UINT, UINT, HWND, bool);		//����������
void DXUninit(void);		//�I������

//DX�̕`��J�n�E�I��
void DXBeginRender(void);
void DXEndRender(void);

ID3D11Device* GetDevice(void);
ID3D11DeviceContext* GetDeviceContext(void);

#endif //__HEADER_DIRECTX_H