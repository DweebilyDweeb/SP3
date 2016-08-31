#include "Application.h"
#include<iostream>
#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>

int main(void) {

	Application &app = Application::GetInstance();
	app.Init();
	app.Run();
	app.Exit();
	_CrtDumpMemoryLeaks();

	return 0;

}