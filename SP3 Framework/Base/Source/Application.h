#ifndef APPLICATION_H
#define APPLICATION_H

#include "timer.h"

#include "Sound.h"

//Include Scenes
#include "Scene3D.h"

class Application {

public:
	//Scene
	static Scene3D* scene;
	
	//Sound Engine
	//Getter(s)
	static Application& GetInstance();
	int GetWindowWidth();
	int GetWindowHeight();

	//Function(s)
	void Init();
	void Run();
	void Exit();

private:
	//Constructor(s) & Destructor
	Application();
	~Application();

	//Declare the window width and height as constant integer
	const static int m_window_width = 1024;
	const static int m_window_height = 800;
	
	//Declare a window object
	StopWatch m_timer;

	//Threads
	enum THREAD {

		UPDATE_USER_INPUT,
		UPDATE_SCENE,

		NUM_THREAD,

	};

	bool quit;

	double elapsedTime;
	double accumulatedTime[NUM_THREAD];

};

#endif