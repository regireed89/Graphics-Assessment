#include "Application.h"
#include "gl_core_4_4.h"
#include <GLFW/glfw3.h>


Application::Application():m_window(nullptr)
{
}


Application::~Application()
{
}


void Application::run(const char* title, unsigned int width, unsigned int height, bool fullscreen)
{
	startup();
	if (glfwInit() == GL_FALSE)
		return;
	GLFWmonitor* monitor = (fullscreen) ? glfwGetPrimaryMonitor() : nullptr;

	m_window = glfwCreateWindow(width, height, title, monitor, nullptr);
		
	double prevTime = glfwGetTime();
	double currentTime = 0;
	double deltaTime = 0;
	while(!m_gameover)
	{
		currentTime = glfwGetTime();
		deltaTime = currentTime - prevTime;
		prevTime = currentTime;
		glfwPollEvents();
		update(deltaTime);
	}

	if (ogl_LoadFunctions() == ogl_LOAD_FAILED)
	{
		glfwDestroyWindow(m_window);
		glfwTerminate();
	}
		
}