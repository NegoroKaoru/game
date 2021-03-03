//=== インクルード部 ===
#include "DirectX.h"

//=== グローバル変数 ===
//バックバッファ(仮想的なバッファ)を管理
IDXGISwapChain*		g_pSwapChain;
//DirectXが扱えるリソースを管理
//(テクスチャ、シェーダ、頂点情報)
ID3D11Device*		g_pDevice;
//描画を行う
ID3D11DeviceContext* g_pDeviceContext;
//レンダーターゲットビュー
ID3D11RenderTargetView *g_pRenderTarget;
//ブレンドステート
ID3D11BlendState* g_pBlendState;
//サンプラー
ID3D11SamplerState *g_pSamplerState;
//ラスター
ID3D11RasterizerState* g_pRasterizerState;

/*+++++++++++++++++++++
Init関数
引数：なし　戻り値：bool
++++++++++++++++++++++*/
bool DXInit(UINT width, UINT height, HWND hWnd, bool bWindow)
{
	HRESULT hr = E_FAIL;

	//デバイス、スワップチェーンの作成
	DXGI_SWAP_CHAIN_DESC scd;
	ZeroMemory(&scd, sizeof(scd));
	scd.BufferCount = 1;				//バッファの数
	scd.BufferDesc.Width = width;		//バッファの横幅
	scd.BufferDesc.Height = height;		//たてはば
	scd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;//バッファの色情報
	//リフレッシュレート
	scd.BufferDesc.RefreshRate.Numerator = 60;
	scd.BufferDesc.RefreshRate.Denominator = 1;
	//バッファの使い方
	scd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	//DirectXと紐づけるウィンドウの指定
	scd.OutputWindow = hWnd;
	scd.Windowed = bWindow;	//true:ウィンドウモード false:フルスクリーンモード
	//マルチサンプリングを使用しない設定
	scd.SampleDesc.Count = 1;
	scd.SampleDesc.Quality = 0;

	D3D_FEATURE_LEVEL featureLevel[] = {
	D3D_FEATURE_LEVEL_11_0,
	D3D_FEATURE_LEVEL_11_1,
	};

	hr = D3D11CreateDeviceAndSwapChain(
		NULL,
		D3D_DRIVER_TYPE_HARDWARE, //ハードウェアで描画
		NULL, 0,
		featureLevel, _countof(featureLevel),
		D3D11_SDK_VERSION,
		&scd,
		&g_pSwapChain,
		&g_pDevice,
		NULL,
		&g_pDeviceContext
	);

	if (FAILED(hr)) {
		return false;
	}

	//バックバッファを作成
	ID3D11Texture2D *pBackBuffer = NULL;
	g_pSwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)&pBackBuffer);

	hr = g_pDevice->CreateRenderTargetView(pBackBuffer, NULL, &g_pRenderTarget);
	pBackBuffer->Release();

	if (FAILED(hr)) {
		return false;
	}

	//レンダーターゲット設定
	g_pDeviceContext->OMSetRenderTargets(1, &g_pRenderTarget, NULL);

	//ゲーム内の空間の大きさを指定
	//ビューポートの設定
	D3D11_VIEWPORT vp;
	vp.Width = (float)width;
	vp.Height = (float)height;
	vp.MinDepth = 0;//z軸 手前
	vp.MaxDepth = 1;//z軸   奥
	vp.TopLeftX = 0;
	vp.TopLeftY = 0;
	g_pDeviceContext->RSSetViewports(1, &vp);

	//透過処理の設定
	//※ブレンドステートの設定
	D3D11_BLEND_DESC bd;
	ZeroMemory(&bd, sizeof(bd));

	bd.RenderTarget[0].BlendEnable = TRUE;
	//色のブレンド方法
	//これから描き込む画像
	//(描きこむ画像の色* 描きこむ画像の透過色
	bd.RenderTarget[0].SrcBlend = D3D11_BLEND_SRC_ALPHA;
	//描き込み先の色
	//(描き込み先の画像の色 * 1 - 描きこむ画像の透過色)
	bd.RenderTarget[0].DestBlend = D3D11_BLEND_INV_SRC_ALPHA;
	//SrcBlendの色 + DestBlendの色
	//計算した色の出力方法
	bd.RenderTarget[0].BlendOp = D3D11_BLEND_OP_ADD;

	//透明度のブレンド方法
	//描きこむ画像の透明度*1
	bd.RenderTarget[0].SrcBlendAlpha = D3D11_BLEND_ONE;
	//描きこむ画像の透明度*0
	bd.RenderTarget[0].DestBlendAlpha = D3D11_BLEND_ZERO;
	//SrcBlendAlpha + DestBlendAlpha
	bd.RenderTarget[0].BlendOpAlpha = D3D11_BLEND_OP_ADD;

	//出力する色
	bd.RenderTarget[0].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;

	//ブレンドステート作成
	float blendFactor[4] = {1,1,1,1};
	g_pDevice->CreateBlendState(&bd, &g_pBlendState);
	g_pDeviceContext->OMSetBlendState(g_pBlendState, blendFactor, 0xffffffff);

	//サンプラーステート作成
	D3D11_SAMPLER_DESC sd;
	ZeroMemory(&sd, sizeof(sd));

	//横方向のテクスチャ繰り返し設定
	sd.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
	/*D3D11_TEXTURE_ADDRESS_WRAPとは
	WRAP 繰り返してテクスチャを表示
	CLAMP　繰り返さない
	MIRROR 鏡写しで繰り返し
	MIRROW_ONCE　一度だけ鏡写

	*/
	//縦方向のテクスチャ繰り返し設定
	sd.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;

	//奥行方向のテクスチャ繰り返し
	sd.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;

	//画像拡縮時の補間完了
	sd.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
	/*
	D3D11_FILTER_MIN_MAG_MIP_LINEAR
	LINEAR 線形補間
	POINT 補間なし

	*/

	g_pDevice->CreateSamplerState(&sd, &g_pSamplerState);
	
	g_pDeviceContext->PSSetSamplers(0, 1, &g_pSamplerState);

	//ラスタライザステート作成
	D3D11_RASTERIZER_DESC rd;
	ZeroMemory(&rd, sizeof(rd));
	rd.CullMode = D3D11_CULL_NONE;
	/*
	D3D11_CULL_NONE
	FRONT 前向いているポリゴンは表示しない
	BACK 後ろ向いてるポリゴンは表示しない
	NONE 全部表示
	
	*/
	
	rd.FillMode = D3D11_FILL_SOLID;
	/*
	D3D11_FILL_WIREFRAME
	WIREFRAME ワイヤーフレーム表示
	SOLID 

	*/

	g_pDevice->CreateRasterizerState(&rd, &g_pRasterizerState);
	g_pDeviceContext->RSSetState(g_pRasterizerState);

	return true;
}

void DXBeginRender(void) {
	float clearColor[4] = {0.0f, 0.0f, 0.0f, 0.0f};
	g_pDeviceContext->ClearRenderTargetView(g_pRenderTarget, clearColor);
}
void DXEndRender(void) {
	//フロントバッファとバックバッファの入れ替え
	g_pSwapChain->Present(
		1,//垂直同期
		0);
}

void DXUninit(void)
{
	SAFE_RELEASE(g_pRenderTarget);
	SAFE_RELEASE(g_pSwapChain);
	SAFE_RELEASE(g_pDeviceContext);
	SAFE_RELEASE(g_pDevice);
	SAFE_RELEASE(g_pBlendState);
	SAFE_RELEASE(g_pSamplerState);
	SAFE_RELEASE(g_pRasterizerState);
}
/*+++++++++++++++++++++++++++++++++++++


++++++++++++++++++++++++++++++++++++++*/
ID3D11Device* GetDevice(void)
{
	return g_pDevice;
}
ID3D11DeviceContext* GetDeviceContext(void)
{
	return g_pDeviceContext;
}