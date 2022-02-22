#include "Debug/Log/SimpleLog.h"
#include "EngineMinimal.h"
#include "EngineFactory.h"

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE prevInstance, PSTR cmdLine, int showCmd)
{
	int ReturnValue = 0;

	if (FEngine* Engine = FEngineFactory::CreateEngine())
	{
		ReturnValue = Engine->PreInit(
#if defined(_WIN32)
			FWinMainCommandParameters(hInstance, prevInstance, cmdLine, showCmd)
#endif
		);
		
		
		if (ReturnValue != 0)
		{
			Engine_Log_Error("[%i]Engine pre-initialization error.", ReturnValue);
			return ReturnValue;
		}

		
		ReturnValue = Engine->Init();
		if (ReturnValue != 0)
		{
			Engine_Log_Error("[%i]Engine initialization error.", ReturnValue);
			return ReturnValue;
		}

		ReturnValue = Engine->PostInit();
		if (ReturnValue != 0)
		{
			Engine_Log_Error("[%i]Engine post-initialization error.", ReturnValue);
			return ReturnValue;
		}

		while (true)
		{
			Engine->Tick();
		}

		ReturnValue = Engine->PreExit();
		if (ReturnValue != 0)
		{
			Engine_Log_Error("[%i]Engine pre-exit failed.", ReturnValue);
			return ReturnValue;
		}

		ReturnValue = Engine->Exit();
		if (ReturnValue != 0)
		{
			Engine_Log_Error("[%i]Engine exit failed.", ReturnValue);
			return ReturnValue;
		}

		ReturnValue = Engine->PostExit();
		if (ReturnValue != 0)
		{
			Engine_Log_Error("[%i]Engine post-exit failed.", ReturnValue);
			return ReturnValue;
		}

		ReturnValue = 0;
	}
	else
	{
		ReturnValue = 1;
	}

	Engine_Log("[%i]Engine has existed.", ReturnValue);
	return ReturnValue;
}