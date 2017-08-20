#include <iostream>
#include "Application.h"
#include "IntroApplication.h"

int main()
{
	Application* app = new IntroApplication();
	app->run("Regi", 1000, 600 , false);

	return 0;
}