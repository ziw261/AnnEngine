#pragma once


#if defined(_WIN32)
#include "../EngineMinimal.h"
class FWinMainCommandParameters
{
public:
	FWinMainCommandParameters(HINSTANCE inhInstance, HINSTANCE inprevInstance, PSTR incmdLine, int inshowCmd);

	HINSTANCE hInstance;
	HINSTANCE prevInstance;
	PSTR cmdLine;
	int showCmd;
};

#elif 1

#endif // 0