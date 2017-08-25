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
	Gizmos::create();
}

void CameraApp::update(float)
{
}

void CameraApp::shutdown()
{
}


glm::mat4 s1 = glm::mat4(1);
glm::vec4 center = glm::vec4(0, 0, 0, 1);
glm::vec4 color = glm::vec4(0, 0, 0, 0);
void CameraApp::draw()
{
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
