#include "Debug/Log/SimpleLog.h"
#include "EngineMinimal.h"
#include "EngineFactory.h"

int Init(FEngine* engine, HINSTANCE hInstance, HINSTANCE prevInstance, PSTR cmdLine, int showCmd)
{
	int returnValue = engine->PreInit(
#if defined(_WIN32)
		FWinMainCommandParameters(hInstance, prevInstance, cmdLine, showCmd)
#endif
	);

	if (returnValue != 0)
	{
		Engine_Log_Error("[%i]Engine pre-initialization error.", returnValue);
		return returnValue;
	}

	returnValue = engine->Init();
	if (returnValue != 0)
	{
		Engine_Log_Error("[%i]Engine initialization error.", returnValue);
		return returnValue;
	}

	returnValue = engine->PostInit();
	if (returnValue != 0)
	{
		Engine_Log_Error("[%i]Engine post-initialization error.", returnValue);
		return returnValue;
	}

	return returnValue;
}

void Tick(FEngine* engine)
{
	engine->Tick();
}


int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE prevInstance, PSTR cmdLine, int showCmd)
{
	int returnValue = 0;

	if (FEngine* engine = FEngineFactory::CreateEngine())
	{
		returnValue = Init(engine, hInstance, prevInstance, cmdLine, showCmd);

		while (true)
		{
			Tick(engine);
		}

		returnValue = engine->PreExit();
		if (returnValue != 0)
		{
			Engine_Log_Error("[%i]Engine pre-exit failed.", returnValue);
			return returnValue;
		}

		returnValue = engine->Exit();
		if (returnValue != 0)
		{
			Engine_Log_Error("[%i]Engine exit failed.", returnValue);
			return returnValue;
		}

		returnValue = engine->PostExit();
		if (returnValue != 0)
		{
			Engine_Log_Error("[%i]Engine post-exit failed.", returnValue);
			return returnValue;
		}

		returnValue = 0;
	}
	else
	{
		returnValue = 1;
	}

	Engine_Log("[%i]Engine has existed.", returnValue);
	return returnValue;
}