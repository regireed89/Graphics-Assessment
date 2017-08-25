#include "CameraApp.h"
#include "Gizmos.h"
#include "glm.hpp"
#include <GLFW/glfw3.h>
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
