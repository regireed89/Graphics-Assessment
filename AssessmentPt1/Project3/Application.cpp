#include "Application.h"
#include "IntroApplication.h"
#include "gl_core_4_4.h"
#include "../dep/GLFW/include/GLFW/glfw3.h"
#include "GLM/vec2.hpp"


Application::Application()
{
}


Application::~Application()
{
}

void Application::run(const char* title, unsigned int width, unsigned int height, bool fullscreen)
{
	startup();
	GLFWmonitor* monitor = glfwGetPrimaryMonitor();
	GLFWwindow* window = glfwCreateWindow(width, height, title, monitor, nullptr);//creates window for opengl

	if(window == nullptr)//checks if ther is a window or not
	{
		glfwTerminate();//if there is no window the GLFW libray is stopped
	}
	assert(window != nullptr);//says that window should not be null 
	glfwMakeContextCurrent(window);//makes context in window current
	if(ogl_LoadFunctions() == ogl_LOAD_FAILED)//checks if opengl functions loaded
	{
		glfwDestroyWindow(window);//if not the window is closed
		glfwTerminate();//GLFW library is terminated
	}

}
