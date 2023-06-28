#include "systemclass.h"

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PSTR pScmdline, int iCmdshow)
{
	SystemClass* System;
	bool result;

	//new system object
	System = new SystemClass;
	if (!System)
		return 0;

	//Initialize System
	result = System->Initialize();

	if (result)
		System->Run();

	//Shutdown and release system object
	System->Shutdown();
	delete System;
	System = NULL;
	return 0;
}
