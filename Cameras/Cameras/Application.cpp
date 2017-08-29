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
	glfwInit();
	window = glfwCreateWindow(width, height, title, nullptr, nullptr);
	if(window == nullptr)//checks if ther is a window or not
	{
		glfwTerminate();//if there is no window the GLFW libray is stopped
	}
	glfwMakeContextCurrent(window);//makes context in window current
	if(ogl_LoadFunctions() == ogl_LOAD_FAILED)//checks if opengl functions loaded
	{
		glfwDestroyWindow(window);//if not the window is closed
		glfwTerminate(); //GLFW library is terminated
	}
	startup();
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
