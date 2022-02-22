#include "WinMainCommandParameters.h"

FWinMainCommandParameters::FWinMainCommandParameters(HINSTANCE inhInstance, HINSTANCE inprevInstance, PSTR incmdLine, int inshowCmd)
	:hInstance(inhInstance), prevInstance(inprevInstance), cmdLine(incmdLine), showCmd(inshowCmd)
{

}

