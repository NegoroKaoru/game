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

//グローバル変数
HINSTANCE g_hInstance;
HWND g_hWnd;

//ウィンドウプロシージャ
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
HRESULT InitGame(void);
void UninitGame(void);
void UpdateGame(void);
void DrawGame(void);

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	WNDCLASSEX WindowClass;	//ウィンドウクラス構造体
	HWND hWnd;	//ウィンドウハンドル
	MSG message;//メッセージ

	g_hInstance = hInstance;

	//ウィンドウ作成の流れ
	//①ウィンドウクラス情報の設定
	ZeroMemory(&WindowClass, sizeof(WNDCLASSEX));
	WindowClass.hInstance = hInstance;			//どの領域を使わせるか
	WindowClass.lpszClassName = "Class Name";	//これから作るウィンドウの識別用
	WindowClass.lpfnWndProc = WndProc;			//
	WindowClass.style = CS_CLASSDC;				//ウィンドウをどの形で表示するか(CS_CLASSDCがデフォルト)
	WindowClass.cbSize = sizeof(WNDCLASSEX);	//今回のWNDCLASSEXがどれくらい大きいか
	WindowClass.hIcon = LoadIcon(NULL, IDI_APPLICATION);	//表示するアイコン IDI_APPLICATIONがデフォ
	WindowClass.hIconSm = WindowClass.hIcon;				//
	WindowClass.hCursor = LoadCursor(NULL, IDC_ARROW);		//
	WindowClass.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);	//

																		//②ウィンドウクラス構造体の登録
	if (!RegisterClassEx(&WindowClass))
	{
		MessageBox(NULL, "Failed setting WindowClass Structure", "Error", MB_OK | MB_ICONERROR);
		return 0;
	}


	//③ウィンドウの作成
	hWnd = CreateWindowEx(
		WS_EX_OVERLAPPEDWINDOW,	//WindowStyle
		WindowClass.lpszClassName,
		"AT12D171-18 根来カオル",	//左上に表示される文字/Windowsのタイトル
		WS_CAPTION | WS_SYSMENU,
		0, 0, SCREEN_X, SCREEN_Y,	//左限上限をCW_USEDEFAULTでいい感じに配置される
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

	//ポリゴンの初期化
	if (FAILED(InitPolygon(GetDevice())))
	{
		MessageBox(hWnd, "Failed initializing polygon", "error!", MB_OK);
	}



	//④ウィンドウ表示
	ShowWindow(hWnd, nCmdShow);

	//⑤クライアント領域のリフレッシュ
	UpdateWindow(hWnd);

	if (FAILED(InitGame()))
	{
		MessageBox(hWnd, "Error!", "Failed initializing stats.", MB_OK);
	}


	timeBeginPeriod(1);//1msec間隔で時間を取得して
	DWORD previousTime = timeGetTime();	//前回の実行時間を格納
	DWORD currentTime;

	//FPS計測
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
			//fps計測
			if (currentTime - prevFpsTime >= 1000)
			{
				StartDebugProc();
				PrintDebugProc("%dfps", nFpsCount);
				//sprintf(sFpsMessage, "%dfps", nFpsCount);
				//SetWindowText(hWnd, sFpsMessage);
				prevFpsTime = currentTime;
				nFpsCount = 0;
			}
			if (currentTime - previousTime < 1000 / 60) continue;//ダメだったら経過したかで取る
																 //UpdateInput();//ゲーム処理の最初にやるから
			UpdateGame();
			DrawGame();
			previousTime = currentTime;
			nFpsCount++;
		}
	}

	timeEndPeriod(1);//時間計測をもとに戻す

	UninitGame();

	//ウィンドウクラス情報の破棄
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
InitGame関数
引数：なし
戻り値：HRESULT型
ゲームの初期化処理
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
UninitGame関数
引数・戻り値：なし
ゲームの解放処理
+++++++++++++++++++++++++++++++++++++*/
void UninitGame(void)
{
	UninitInput();
	//音の初期化
	UninitSound();
	//シーン初期化
	UninitScene();
	//デバッグ終了処理
	UninitDebugProc();
	//入力終了処理
	UninitInput();
	//ポリゴンの終了処理
	UninitPolygon();

}


/*++++++++++++++++++++++++++++++++++++++
UpdateGame関数
引数・戻り値：なし
ゲームの更新処理
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
DrawGame関数
引数・戻り値：なし
ゲームの描画処理
+++++++++++++++++++++++++++++++++++++*/
void DrawGame(void)
{
	DXBeginRender();
	{
		DrawScene();

		//デバッグ描画
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