#include <iostream>
#include "LightingApp.h"


int main()
{
	Application* app = new LightingApp();
	app->run("dat light doe", 1000, 800, false);

}