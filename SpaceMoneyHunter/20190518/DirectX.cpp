//=== �C���N���[�h�� ===
#include "DirectX.h"

//=== �O���[�o���ϐ� ===
//�o�b�N�o�b�t�@(���z�I�ȃo�b�t�@)���Ǘ�
IDXGISwapChain*		g_pSwapChain;
//DirectX�������郊�\�[�X���Ǘ�
//(�e�N�X�`���A�V�F�[�_�A���_���)
ID3D11Device*		g_pDevice;
//�`����s��
ID3D11DeviceContext* g_pDeviceContext;
//�����_�[�^�[�Q�b�g�r���[
ID3D11RenderTargetView *g_pRenderTarget;
//�u�����h�X�e�[�g
ID3D11BlendState* g_pBlendState;
//�T���v���[
ID3D11SamplerState *g_pSamplerState;
//���X�^�[
ID3D11RasterizerState* g_pRasterizerState;

/*+++++++++++++++++++++
Init�֐�
�����F�Ȃ��@�߂�l�Fbool
++++++++++++++++++++++*/
bool DXInit(UINT width, UINT height, HWND hWnd, bool bWindow)
{
	HRESULT hr = E_FAIL;

	//�f�o�C�X�A�X���b�v�`�F�[���̍쐬
	DXGI_SWAP_CHAIN_DESC scd;
	ZeroMemory(&scd, sizeof(scd));
	scd.BufferCount = 1;				//�o�b�t�@�̐�
	scd.BufferDesc.Width = width;		//�o�b�t�@�̉���
	scd.BufferDesc.Height = height;		//���Ă͂�
	scd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;//�o�b�t�@�̐F���
	//���t���b�V�����[�g
	scd.BufferDesc.RefreshRate.Numerator = 60;
	scd.BufferDesc.RefreshRate.Denominator = 1;
	//�o�b�t�@�̎g����
	scd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	//DirectX�ƕR�Â���E�B���h�E�̎w��
	scd.OutputWindow = hWnd;
	scd.Windowed = bWindow;	//true:�E�B���h�E���[�h false:�t���X�N���[�����[�h
	//�}���`�T���v�����O���g�p���Ȃ��ݒ�
	scd.SampleDesc.Count = 1;
	scd.SampleDesc.Quality = 0;

	D3D_FEATURE_LEVEL featureLevel[] = {
	D3D_FEATURE_LEVEL_11_0,
	D3D_FEATURE_LEVEL_11_1,
	};

	hr = D3D11CreateDeviceAndSwapChain(
		NULL,
		D3D_DRIVER_TYPE_HARDWARE, //�n�[�h�E�F�A�ŕ`��
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

	//�o�b�N�o�b�t�@���쐬
	ID3D11Texture2D *pBackBuffer = NULL;
	g_pSwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)&pBackBuffer);

	hr = g_pDevice->CreateRenderTargetView(pBackBuffer, NULL, &g_pRenderTarget);
	pBackBuffer->Release();

	if (FAILED(hr)) {
		return false;
	}

	//�����_�[�^�[�Q�b�g�ݒ�
	g_pDeviceContext->OMSetRenderTargets(1, &g_pRenderTarget, NULL);

	//�Q�[�����̋�Ԃ̑傫�����w��
	//�r���[�|�[�g�̐ݒ�
	D3D11_VIEWPORT vp;
	vp.Width = (float)width;
	vp.Height = (float)height;
	vp.MinDepth = 0;//z�� ��O
	vp.MaxDepth = 1;//z��   ��
	vp.TopLeftX = 0;
	vp.TopLeftY = 0;
	g_pDeviceContext->RSSetViewports(1, &vp);

	//���ߏ����̐ݒ�
	//���u�����h�X�e�[�g�̐ݒ�
	D3D11_BLEND_DESC bd;
	ZeroMemory(&bd, sizeof(bd));

	bd.RenderTarget[0].BlendEnable = TRUE;
	//�F�̃u�����h���@
	//���ꂩ��`�����މ摜
	//(�`�����މ摜�̐F* �`�����މ摜�̓��ߐF
	bd.RenderTarget[0].SrcBlend = D3D11_BLEND_SRC_ALPHA;
	//�`�����ݐ�̐F
	//(�`�����ݐ�̉摜�̐F * 1 - �`�����މ摜�̓��ߐF)
	bd.RenderTarget[0].DestBlend = D3D11_BLEND_INV_SRC_ALPHA;
	//SrcBlend�̐F + DestBlend�̐F
	//�v�Z�����F�̏o�͕��@
	bd.RenderTarget[0].BlendOp = D3D11_BLEND_OP_ADD;

	//�����x�̃u�����h���@
	//�`�����މ摜�̓����x*1
	bd.RenderTarget[0].SrcBlendAlpha = D3D11_BLEND_ONE;
	//�`�����މ摜�̓����x*0
	bd.RenderTarget[0].DestBlendAlpha = D3D11_BLEND_ZERO;
	//SrcBlendAlpha + DestBlendAlpha
	bd.RenderTarget[0].BlendOpAlpha = D3D11_BLEND_OP_ADD;

	//�o�͂���F
	bd.RenderTarget[0].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;

	//�u�����h�X�e�[�g�쐬
	float blendFactor[4] = {1,1,1,1};
	g_pDevice->CreateBlendState(&bd, &g_pBlendState);
	g_pDeviceContext->OMSetBlendState(g_pBlendState, blendFactor, 0xffffffff);

	//�T���v���[�X�e�[�g�쐬
	D3D11_SAMPLER_DESC sd;
	ZeroMemory(&sd, sizeof(sd));

	//�������̃e�N�X�`���J��Ԃ��ݒ�
	sd.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
	/*D3D11_TEXTURE_ADDRESS_WRAP�Ƃ�
	WRAP �J��Ԃ��ăe�N�X�`����\��
	CLAMP�@�J��Ԃ��Ȃ�
	MIRROR ���ʂ��ŌJ��Ԃ�
	MIRROW_ONCE�@��x��������

	*/
	//�c�����̃e�N�X�`���J��Ԃ��ݒ�
	sd.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;

	//���s�����̃e�N�X�`���J��Ԃ�
	sd.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;

	//�摜�g�k���̕�Ԋ���
	sd.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
	/*
	D3D11_FILTER_MIN_MAG_MIP_LINEAR
	LINEAR ���`���
	POINT ��ԂȂ�

	*/

	g_pDevice->CreateSamplerState(&sd, &g_pSamplerState);
	
	g_pDeviceContext->PSSetSamplers(0, 1, &g_pSamplerState);

	//���X�^���C�U�X�e�[�g�쐬
	D3D11_RASTERIZER_DESC rd;
	ZeroMemory(&rd, sizeof(rd));
	rd.CullMode = D3D11_CULL_NONE;
	/*
	D3D11_CULL_NONE
	FRONT �O�����Ă���|���S���͕\�����Ȃ�
	BACK �������Ă�|���S���͕\�����Ȃ�
	NONE �S���\��
	
	*/
	
	rd.FillMode = D3D11_FILL_SOLID;
	/*
	D3D11_FILL_WIREFRAME
	WIREFRAME ���C���[�t���[���\��
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
	//�t�����g�o�b�t�@�ƃo�b�N�o�b�t�@�̓���ւ�
	g_pSwapChain->Present(
		1,//��������
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