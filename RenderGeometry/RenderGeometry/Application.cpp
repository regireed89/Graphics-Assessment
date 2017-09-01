#include "Application.h"
#include "gl_core_4_4.h"
#include <GLFW/glfw3.h>



Application::Application()
{
}


Application::~Application()
{
}

void Application::run(const char* title, unsigned width, unsigned height, bool fullscreen)
{
	startup();
	glfwInit();
	window = glfwCreateWindow(width, height, title, nullptr, nullptr);
	if(window == nullptr)
	{
		glfwTerminate();
	}
	glfwMakeContextCurrent(window);
	if(ogl_LoadFunctions() == ogl_LOAD_FAILED)
	{
		glfwDestroyWindow(window);
		glfwTerminate();
	}
	
	while(true)
	{
		if(glfwWindowShouldClose(window))	
			break;
		
		if(glfwGetKey(window, GLFW_KEY_ESCAPE))
			glfwWindowShouldClose(window);
		update(1);
		draw();
		glfwSwapBuffers(window);
		glfwPollEvents();
	}
	glfwDestroyWindow(window);
	glfwTerminate();
	
}
