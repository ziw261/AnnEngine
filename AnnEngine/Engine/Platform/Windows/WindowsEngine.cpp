#include "WindowsEngine.h"

#if defined(_WIN32)
#include "WindowsMessageProcessing.h"

int FWindowsEngine::PreInit(FWinMainCommandParameters inParameters)
{

	if (InitWindows(inParameters))
	{

	}

	return 0;
}

int FWindowsEngine::Init()
{
	return 0;
}

int FWindowsEngine::PostInit()
{
	return 0;
}

void FWindowsEngine::Tick()
{
}

int FWindowsEngine::PreExit()
{
	return 0;
}

int FWindowsEngine::Exit()
{
	return 0;
}

int FWindowsEngine::PostExit()
{
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
		MessageBox(nullptr, L"Register Fail,", L"Error", MB_OK);
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
		MessageBox(0, L"CreateWindow Failed.", 0, 0);
		return false;
	}

	ShowWindow(hwnd, SW_SHOW);

	UpdateWindow(hwnd);

	return true;
}

#endif