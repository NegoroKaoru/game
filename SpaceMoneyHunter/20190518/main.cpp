#include <Windows.h>
#include "DirectX.h"
#include "main.h"
#include "polygon.h"
#include "Texture.h"
#include "Explosion.h"
#include "debugproc.h"
#include "input.h"
#include "character.h"
#include "enemy.h"
#include "score.h"
#include "SceneManager.h"
#include "sound.h"

#pragma comment(lib, "winmm.lib")

//�O���[�o���ϐ�
HINSTANCE g_hInstance;
HWND g_hWnd;

//�E�B���h�E�v���V�[�W��
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
HRESULT InitGame(void);
void UninitGame(void);
void UpdateGame(void);
void DrawGame(void);

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	WNDCLASSEX WindowClass;	//�E�B���h�E�N���X�\����
	HWND hWnd;	//�E�B���h�E�n���h��
	MSG message;//���b�Z�[�W

	g_hInstance = hInstance;

	//�E�B���h�E�쐬�̗���
	//�@�E�B���h�E�N���X���̐ݒ�
	ZeroMemory(&WindowClass, sizeof(WNDCLASSEX));
	WindowClass.hInstance = hInstance;			//�ǂ̗̈���g�킹�邩
	WindowClass.lpszClassName = "Class Name";	//���ꂩ����E�B���h�E�̎��ʗp
	WindowClass.lpfnWndProc = WndProc;			//
	WindowClass.style = CS_CLASSDC;				//�E�B���h�E���ǂ̌`�ŕ\�����邩(CS_CLASSDC���f�t�H���g)
	WindowClass.cbSize = sizeof(WNDCLASSEX);	//�����WNDCLASSEX���ǂꂭ�炢�傫����
	WindowClass.hIcon = LoadIcon(NULL, IDI_APPLICATION);	//�\������A�C�R�� IDI_APPLICATION���f�t�H
	WindowClass.hIconSm = WindowClass.hIcon;				//
	WindowClass.hCursor = LoadCursor(NULL, IDC_ARROW);		//
	WindowClass.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);	//

																		//�A�E�B���h�E�N���X�\���̂̓o�^
	if (!RegisterClassEx(&WindowClass))
	{
		MessageBox(NULL, "Failed setting WindowClass Structure", "Error", MB_OK | MB_ICONERROR);
		return 0;
	}


	//�B�E�B���h�E�̍쐬
	hWnd = CreateWindowEx(
		WS_EX_OVERLAPPEDWINDOW,	//WindowStyle
		WindowClass.lpszClassName,
		"AT12D171-18 �����J�I��",	//����ɕ\������镶��/Windows�̃^�C�g��
		WS_CAPTION | WS_SYSMENU,
		0, 0, SCREEN_X, SCREEN_Y,	//���������CW_USEDEFAULT�ł��������ɔz�u�����
		HWND_DESKTOP, NULL,
		hInstance,
		NULL);
	if (hWnd == NULL)
	{
		MessageBox(NULL, "Failed setting Window Handle", "Error", MB_OK | MB_ICONERROR);
		return 0;
	}

	if (!DXInit(SCREEN_X, SCREEN_Y, hWnd, true))
	{
		MessageBox(hWnd, "Failed Initializing DirectX", "Error!", MB_OK | MB_ICONERROR);
		return 0;
	}

	//�|���S���̏�����
	if (FAILED(InitPolygon(GetDevice())))
	{
		MessageBox(hWnd, "Failed initializing polygon", "error!", MB_OK);
	}



	//�C�E�B���h�E�\��
	ShowWindow(hWnd, nCmdShow);

	//�D�N���C�A���g�̈�̃��t���b�V��
	UpdateWindow(hWnd);

	if (FAILED(InitGame()))
	{
		MessageBox(hWnd, "Error!", "Failed initializing stats.", MB_OK);
	}


	timeBeginPeriod(1);//1msec�Ԋu�Ŏ��Ԃ��擾����
	DWORD previousTime = timeGetTime();	//�O��̎��s���Ԃ��i�[
	DWORD currentTime;

	//FPS�v��
	DWORD prevFpsTime = previousTime;
	int nFpsCount = 0;

	while (true) {
		if (PeekMessage(&message, NULL, 0, 0, PM_NOREMOVE)) {
			if (!GetMessage(&message, NULL, 0, 0)) {
				break;
			}
			else {
				TranslateMessage(&message);
				DispatchMessage(&message);
			}
		}
		else
		{
			currentTime = timeGetTime();
			//fps�v��
			if (currentTime - prevFpsTime >= 1000)
			{
				StartDebugProc();
				PrintDebugProc("%dfps", nFpsCount);
				//sprintf(sFpsMessage, "%dfps", nFpsCount);
				//SetWindowText(hWnd, sFpsMessage);
				prevFpsTime = currentTime;
				nFpsCount = 0;
			}
			if (currentTime - previousTime < 1000 / 60) continue;//�_����������o�߂������Ŏ��
																 //UpdateInput();//�Q�[�������̍ŏ��ɂ�邩��
			UpdateGame();
			DrawGame();
			previousTime = currentTime;
			nFpsCount++;
		}
	}

	timeEndPeriod(1);//���Ԍv�������Ƃɖ߂�

	UninitGame();

	//�E�B���h�E�N���X���̔j��
	UnregisterClass(WindowClass.lpszClassName, hInstance);


	return (int)message.wParam;

	
}

/*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+


*+*+*+*+**+*+*+*+*+*+*+*+*+*+*+*+**/
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message) {
		//	case WM_LBUTTONUP:
		//	break;
	case WM_CLOSE:
		DestroyWindow(hWnd);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		break;
	}
	return DefWindowProc(hWnd, message, wParam, lParam);
}
/*++++++++++++++++++++++++++++++++++++++
InitGame�֐�
�����F�Ȃ�
�߂�l�FHRESULT�^
�Q�[���̏���������
+++++++++++++++++++++++++++++++++++++*/
HRESULT InitGame(void)
{
	InitInput();
	if (FAILED(InitSound(g_hWnd)))
		return E_FAIL;


	if (FAILED(InitDebugProc()))
		return E_FAIL;
	if (FAILED(InitScene()))
	{
		return E_FAIL;
	}
	if (FAILED(InitInput()))
		return E_FAIL;


	return S_OK;

}

/*++++++++++++++++++++++++++++++++++++++
UninitGame�֐�
�����E�߂�l�F�Ȃ�
�Q�[���̉������
+++++++++++++++++++++++++++++++++++++*/
void UninitGame(void)
{
	UninitInput();
	//���̏�����
	UninitSound();
	//�V�[��������
	UninitScene();
	//�f�o�b�O�I������
	UninitDebugProc();
	//���͏I������
	UninitInput();
	//�|���S���̏I������
	UninitPolygon();

}


/*++++++++++++++++++++++++++++++++++++++
UpdateGame�֐�
�����E�߂�l�F�Ȃ�
�Q�[���̍X�V����
+++++++++++++++++++++++++++++++++++++*/
void UpdateGame(void)
{
	UpdateInput();

	UpdateScene();
	//if (IsRepeatInput('Z')) 
	//{
	//	SetExplosion((rand() % 300) - 150, (rand() % 300) - 150);
	//}

	UpdateDebugProc();
}
/*++++++++++++++++++++++++++++++++++++++
DrawGame�֐�
�����E�߂�l�F�Ȃ�
�Q�[���̕`�揈��
+++++++++++++++++++++++++++++++++++++*/
void DrawGame(void)
{
	DXBeginRender();
	{
		DrawScene();

		//�f�o�b�O�`��
		DrawDebugProc();
	}
	DXEndRender();
}
HINSTANCE GetInstance(void)
{
	return g_hInstance;
}
HWND GetMainWnd(void)
{
	return g_hWnd;
}