#include <iostream>
#include "CameraApp.h"
#include "Application.h"

int main()
{
	Application* app = new CameraApp();
	app->run("Hello", 800, 800, false);


		return 0;
}