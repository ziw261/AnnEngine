#include "WindowsEngine.h"
#include "../../Debug/EngineDebug.h"

#if defined(_WIN32)
#include "WindowsMessageProcessing.h"

int FWindowsEngine::PreInit(FWinMainCommandParameters inParameters)
{

	const char logPath[] = "../log";
	init_log_system(logPath);
	Engine_Log("Log Init.");

	if (InitWindows(inParameters))
	{

	}

	if (InitDirect3D())
	{

	}

	Engine_Log("Engine pre-initialization complete.");
	return 0;
}

int FWindowsEngine::Init()
{
	Engine_Log("Engine initialization complete.");
	return 0;
}

int FWindowsEngine::PostInit()
{
	Engine_Log("Engine post-initialization complete.");
	return 0;
}

void FWindowsEngine::Tick()
{
}

int FWindowsEngine::PreExit()
{
	Engine_Log("Engine pre-exit complete.");
	return 0;
}

int FWindowsEngine::Exit()
{
	Engine_Log("Engine exit complete.");
	return 0;
}

int FWindowsEngine::PostExit()
{
	Engine_Log("Engine post-exit complete.");
	return 0;
}

bool FWindowsEngine::InitWindows(FWinMainCommandParameters inParameters)
{
	WNDCLASSEX windowsClass;
	windowsClass.cbSize = sizeof(WNDCLASSEX);
	windowsClass.cbClsExtra = 0;
	windowsClass.cbWndExtra = 0;
	windowsClass.hbrBackground = nullptr;
	windowsClass.hCursor = LoadCursor(NULL, IDC_ARROW);
	windowsClass.hIcon = nullptr;
	windowsClass.hIconSm = nullptr;
	windowsClass.hInstance = inParameters.hInstance;
	windowsClass.lpszClassName = L"AnnEngine";
	windowsClass.lpszMenuName = nullptr;
	windowsClass.style = CS_VREDRAW | CS_HREDRAW;
	windowsClass.lpfnWndProc = EngineWindowProc;

	ATOM registerAtom = RegisterClassEx(&windowsClass);

	if (!registerAtom)
	{
		Engine_Log_Error("Register windows class failed");
		MessageBox(nullptr, L"Register windows class failed,", L"Error", MB_OK);
	}

	RECT rect = { 0, 0, 1280, 720 };

	AdjustWindowRect(&rect, WS_OVERLAPPEDWINDOW, NULL);

	int windowWidth = rect.right - rect.left;
	int windowHeight = rect.bottom - rect.top;

	HWND hwnd = CreateWindowEx(
		NULL,
		L"AnnEngine",
		L"Ann Engine",
		WS_OVERLAPPEDWINDOW,
		100, 100,
		windowWidth, windowHeight,
		NULL,
		nullptr,
		inParameters.hInstance,
		NULL
	);

	if (!hwnd)
	{
		Engine_Log_Error("Application window creation failed");
		MessageBox(0, L"CreateWindow Failed.", 0, 0);
		return false;
	}

	ShowWindow(hwnd, SW_SHOW);

	UpdateWindow(hwnd);

	Engine_Log("Application window initialization complete.");

	return true;
}

bool FWindowsEngine::InitDirect3D()
{
	//HRESULT
	//S_OK				0x00000000
	//E_UNEXPECTED		0x8000FFFF
	//E_NOTIMPL			0x8007000E
	//E_INVALIDARG		0x80070057
	//E_NOINTERFACE		0x80004002
	//E_POINTER			0x80004003
	//E_HANDLE			0x80070006
	//E_ABORT			0x80004004
	//E_FAIL			0x80004005
	//E_ACCESSDENIED	0x80070005
	ANALYSIS_HRESULT(CreateDXGIFactory1(IID_PPV_ARGS(&DXGIFactory)));

	HRESULT D3dDeviceResult = D3D12CreateDevice(NULL, D3D_FEATURE_LEVEL_11_0, IID_PPV_ARGS(&D3dDevice));
	if (FAILED(D3dDeviceResult))
	{
		//warp
		ComPtr<IDXGIAdapter> WARPAdapter;
		ANALYSIS_HRESULT(DXGIFactory->EnumWarpAdapter(IID_PPV_ARGS(&WARPAdapter)));

		ANALYSIS_HRESULT(D3D12CreateDevice(WARPAdapter.Get(), D3D_FEATURE_LEVEL_11_0, IID_PPV_ARGS(&D3dDevice)));
	}

	//D3D12_FENCE_FLAG_NONE
	//D3D11_FENCE_FLAG_SHARED
	//D3D11_FENCE_FALG_SHARED_CROSS_ADAPTER
	/*
	Fence->SetEventOnCompletion
	Queue->Signal
	wait
	*/

	ANALYSIS_HRESULT(D3dDevice->CreateFence(0, D3D12_FENCE_FLAG_NONE, IID_PPV_ARGS(&Fence)));

	return false;
}

#endif
