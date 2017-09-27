#include "Application.h"
#include "TextureApplication.h"

int main()
{
	Application* app = new TextureApplication();
	app->run("dem textures", 800, 600, false);
}