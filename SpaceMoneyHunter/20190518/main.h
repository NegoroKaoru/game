#ifndef __HEADER_MAIN_H
#define __HEADER_MAIN_H


#define SCREEN_X (1280)
#define SCREEN_Y  (720)

#include <Windows.h>
#include <DirectXMath.h>

using namespace DirectX;
//�擾�֐�
HINSTANCE GetInstance(void);
HWND GetMainWnd(void);

#endif