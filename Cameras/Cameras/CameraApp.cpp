#include "CameraApp.h"
#include "Gizmos.h"
#include "glm.hpp"
#include <GLFW/glfw3.h>
#include <iostream>
using namespace glm;

CameraApp::CameraApp()
{
}


CameraApp::~CameraApp()
{
}

void CameraApp::startup()
{
	m_camera = new Camera();
	m_camera->setLookAt(vec3(10, 10, 10), vec3(0, 0, 0), vec3(0, 1, 0));
	glEnable(GL_DEPTH_TEST);
	glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
	Gizmos::create();
}

void CameraApp::update(float deltaTime)
{
	runtime += deltaTime;
	//controls keybord movement of camera
	if(glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
	{
		glm::vec3 npos = glm::vec3(m_camera->getWorldTransform()[3] -= m_camera->getWorldTransform()[2]);		
		m_camera->setPosition(npos);
	}
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
	{
		glm::vec3 nneg = glm::vec3(m_camera->getWorldTransform()[3] += m_camera->getWorldTransform()[2]);
		m_camera->setPosition(nneg);
	}
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
	{
		glm::vec3 npos = glm::vec3(m_camera->getWorldTransform()[3] -= m_camera->getWorldTransform()[0]);
		m_camera->setPosition(npos);
	}
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
	{
		glm::vec3 nneg = glm::vec3(m_camera->getWorldTransform()[3] += m_camera->getWorldTransform()[0]);
		m_camera->setPosition(nneg);
	}

	//controls rotation of camera using mouse
	static bool sbMouseButtonDown = false;
	if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_2) == GLFW_PRESS) 
	{

		static double siPrevMouseX = 0;
		static double siPrevMouseY = 0;

		if (sbMouseButtonDown == false)
		{
			sbMouseButtonDown = true;
			glfwGetCursorPos(window, &siPrevMouseX, &siPrevMouseY);
		}

		double mouseX = 0, mouseY = 0;
		glfwGetCursorPos(window, &mouseX, &mouseY);

		double iDeltaX = mouseX - siPrevMouseX;
		double iDeltaY = mouseY - siPrevMouseY;
		
		siPrevMouseX = mouseX;
		siPrevMouseY = mouseY;

		//mat4 z = mat4(cos(iDeltaX*iDeltaY), -sin(iDeltaX*iDeltaY), 0, 0, sin(iDeltaX*iDeltaY), cos(iDeltaX*iDeltaY), 0, 0, 0, 0, 1, 0, 0, 0, 0, 1);
		mat4 x = mat4(1, 0, 0, 0, 0, cos(iDeltaY/200), -sin(iDeltaY/200), 0, 0, sin(iDeltaY/200), cos(iDeltaY/200), 0, 0, 0, 0, 1);
		mat4 y = mat4(cos(iDeltaX/50), 0, sin(iDeltaX/200), 0, 0, 1, 0, 0, -sin(iDeltaX/200), 0, cos(iDeltaX/200), 0, 0, 0, 0, 1);

		
		
		//auto Elevation = rotate(static_cast<float>(iDeltaX) * 1 / 800, vec3(0, 1, 0));
		//auto Azimuth = rotate(static_cast<float>(iDeltaY) * 1 / 800, vec3(1, 0, 0));
		m_camera->m_view = x * y * m_camera->m_view;
	}

	if (glfwGetKey(window, GLFW_KEY_R))
	{
		m_camera->setLookAt(vec3(10, 10, 10), vec3(0, 0, 0), vec3(0, 1, 0));
	}
}

void CameraApp::shutdown()
{
}

glm::mat4 s1 = glm::mat4(1);
glm::vec4 center = glm::vec4(0, 0, 0, 1);
glm::vec4 color = glm::vec4(0, 0, 0, 0);
void CameraApp::draw()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

	Gizmos::clear();
	Gizmos::addSphere(s1[3], 1, 20, 20, color);
	Gizmos::addTransform(s1, 4);
	glm::vec4 white(1);
	glm::vec4 black(0, 0, 0, 1);
	for(int i = 0; i < 21; ++i)
	{
		Gizmos::addLine(glm::vec3(-10 + i, 0, 10), glm::vec3(-10 + i, 0, -10), i == 10 ? white : black);
		Gizmos::addLine(glm::vec3(10 , 0, -10 + i), glm::vec3(-10 , 0, -10 + i), i == 10 ? white : black);
	}
	Gizmos::draw(m_camera->getProjectionView());
}


