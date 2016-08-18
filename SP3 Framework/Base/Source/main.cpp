#include "Application.h"
#include<iostream>
#define _CRTDBG_MAP_ALLOC
#include<stdlib.h>
#include <crtdbg.h>
#ifdef _DEBUG
#define DEBUG_NEW new(_NORMAL_BLOCK, __FILE__, __LINE__)
#define new DEBUG_NEW
#endif

int main(void) {

	Application &app = Application::GetInstance();
	app.Init();
	app.Run();
	app.Exit();
	_CrtDumpMemoryLeaks();

	return 0;

}