#include "WindowsEngine.h"

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

#endif