
#include<GLFW\glfw3.h>
#include<stdio.h>
#include <GLM/vec3.hpp>





int main()
{
	if (!glfwInit())
	{
		printf("no glfw");
	}

	GLFWwindow* window = glfwCreateWindow(800, 800, "its me", nullptr, nullptr);
	while(true)
	{
		glfwPollEvents();
		if (glfwWindowShouldClose(window))
			break;
		if (glfwGetKey(window, GLFW_KEY_ESCAPE))
			glfwSetWindowShouldClose(window, true);
	}
	return 0;
} 