#include "gl_core_4_4.h"
#include "Gizmos.h"
#include <assert.h>
#include <GLFW\glfw3.h>
#include <glm\vec3.hpp>
#include <glm\vec4.hpp>
#include <glm\vec2.hpp>
#include <glm\mat4x4.hpp>
#include <stdio.h>
#include <iostream>
#include <gtc/matrix_transform.inl>
#include <glm/gtc/matrix_transform.inl>
#include <glm/gtc/constants.inl>


int main()
{
	glm::vec3 v = glm::vec3(1, 1, 1);
	if(!glfwInit())
	{
		printf("no glfw");
	}

	GLFWwindow* window = glfwCreateWindow(800, 800, "my window", nullptr, nullptr);
	if(window == nullptr)
	{
		glfwTerminate();
		return -2;
	}
	assert(window != nullptr);
	glfwMakeContextCurrent(window);

	if(ogl_LoadFunctions() == ogl_LOAD_FAILED)
	{
		glfwDestroyWindow(window);
		glfwTerminate();
		return -3;
	}

	auto major = ogl_GetMajorVersion();
	auto minor = ogl_GetMinorVersion();

	printf("GL: %i.%i\n", major, minor);
	glClearColor(0.5f, 0.5f, 1.0f, 1.0f);
	glm::vec4 clearcolor = glm::vec4(0.5f, 0.5f, 1.0f, 1.0f);
	Gizmos::create();

	glm::mat4 view = lookAt(glm::vec3(10, 10, 10), glm::vec3(0), glm::vec3(0, 1, 0));
	glm::mat4 projection = glm::perspective(glm::pi<float>() * 0.25f, 16 / 9.f, 0.1f, 1000.f);
	while(true)
	{
		Gizmos::destroy();
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		if (glfwWindowShouldClose(window))
			break;
		if (glfwGetKey(window, GLFW_KEY_ESCAPE))
			glfwSetWindowShouldClose(window, true);
		if (glfwGetKey(window, GLFW_KEY_F))
		{
			clearcolor.r -= .001f;
			clearcolor.g -= .001f;
			clearcolor.b -= .001f;
		}

		Gizmos::clear();
		Gizmos::addTransform(glm::mat4(1));
		glClearColor(clearcolor.r, clearcolor.g, clearcolor.b, clearcolor.a);
		glfwSwapBuffers(window);
		glfwPollEvents();


	}


	glfwDestroyWindow(window);
	glfwTerminate();
	return 0;
}
