#pragma once

#if defined(_WIN32)
#include "../../Core/Engine.h"

class FWindowsEngine : public FEngine
{
public:
	virtual int PreInit(FWinMainCommandParameters inParameters);

	virtual int Init();
	virtual int PostInit();

	virtual void Tick();

	virtual int PreExit();
	virtual int Exit();
	virtual int PostExit();

private:
	bool InitWindows(FWinMainCommandParameters inParameters);

	bool InitDirect3D();

protected:
	ComPtr<IDXGIFactory4> DXGIFactory; // Create DirectX DXGI Object
	ComPtr<ID3D12Device> D3dDevice; // Create CommandAllocator, CommandList, CommandQueue, Fence, Resource and other
	ComPtr<ID3D12Fence> Fence; // Synchronize CPU and GPU objects
};
#endif
