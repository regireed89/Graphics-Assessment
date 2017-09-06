#include <iostream>
#include "RenderGeoApp.h"
#include "gl_core_4_4.h"
#include <glm.hpp>
#include <GLM/fwd.hpp>
#include <GLM/ext.hpp>
#include <vector>
#include "Mesh.h"
#include <GLFW\glfw3.h>

RenderGeoApp::RenderGeoApp()
{
	cam = new Camera();
	mesh = new Mesh();
}

RenderGeoApp::~RenderGeoApp()
{
}

void RenderGeoApp::startup()
{
	const char* vsSource = "#version 410\n \
						layout(location = 0) in vec4 position; \
						layout(location=1) in vec4 color; \
						out vec4 vColor; \
						uniform mat4 projectionViewWorldMatrix; \
						void main() { vColor = color; gl_Position = projectionViewWorldMatrix * position; }";

	const char* fsSource = "#version 410\n \
						in vec4 vColor; \
						out vec4 fragColor; \
						void main() { fragColor = vColor; }";

	int success = GL_FALSE;
	unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
	unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

	glShaderSource(vertexShader, 1, (const char**)&vsSource, 0);
	glCompileShader(vertexShader);
	glShaderSource(fragmentShader, 1, (const char**)&fsSource, 0);
	glCompileShader(fragmentShader);


	m_programID = glCreateProgram();
	glAttachShader(m_programID, vertexShader);
	glAttachShader(m_programID, fragmentShader);
	glLinkProgram(m_programID);

	glGetProgramiv(m_programID, GL_LINK_STATUS, &success);
	if (success == GL_FALSE)
	{
		int infoLogLength = 0;
		glGetProgramiv(m_programID, GL_INFO_LOG_LENGTH, &infoLogLength);
		char* infoLog = new char[infoLogLength];

		glGetProgramInfoLog(m_programID, infoLogLength, nullptr, infoLog);
		printf("Error: Failed to link shader program!\n");
		printf("%s\n", infoLog);
		delete[] infoLog;
	}
	glShaderSource(vertexShader, 1, static_cast<const char**>(&vsSource), nullptr);
	glCompileShader(vertexShader);

	glDeleteShader(fragmentShader);
	glDeleteShader(vertexShader);

	glClearColor(1.f, 1.f, 1.f, 1.f);

	Vertex x0 = { glm::vec4(0, 4, 0, 1), glm::vec4(.1, .1, .1, 1) };

	Vertex x1 = { glm::vec4(2,  3, -2, 1), glm::vec4(.1, .1, .1, 1) };
	Vertex x2 = { glm::vec4(2,  3, 2, 1), glm::vec4(.1, .1, .1, 1) };
	Vertex x3 = { glm::vec4(-2, 3, 2, 1), glm::vec4(.1, .1, .1, 1) };
	Vertex x4 = { glm::vec4(-2, 3, -2, 1), glm::vec4(.1, .1, .1, 1) };

	Vertex x5 = { glm::vec4(0,  2, -4, 1), glm::vec4(.1, .1, .1, 1) };
	Vertex x6 = { glm::vec4(3,  2, -3, 1), glm::vec4(.1, .1, .1, 1) };
	Vertex x7 = { glm::vec4(4,  2, 0, 1), glm::vec4(.1, .1, .1, 1) };
	Vertex x8 = { glm::vec4(3,  2, 3, 1), glm::vec4(.1, .1, .1, 1) };
	Vertex x9 = { glm::vec4(0,  2, 4, 1), glm::vec4(.1, .1, .1, 1) };
	Vertex x10 = { glm::vec4(-3, 2, 3, 1), glm::vec4(.1, .1, .1, 1) };
	Vertex x11 = { glm::vec4(-4, 2, 0, 1), glm::vec4(.1, .1, .1, 1) };
	Vertex x12 = { glm::vec4(-3, 2, -3, 1), glm::vec4(.1, .1, .1, 1) };

	Vertex x13 = { glm::vec4(2,  0, -6, 1), glm::vec4(.1, .1, .1, 1) };
	Vertex x14 = { glm::vec4(4,  0, -4, 1), glm::vec4(.1, .1, .1, 1) };
	Vertex x15 = { glm::vec4(6,  0, -2, 1), glm::vec4(.1, .1, .1, 1) };
	Vertex x16 = { glm::vec4(6,  0, 2, 1), glm::vec4(.1, .1, .1, 1) };
	Vertex x17 = { glm::vec4(4,  0, 4, 1), glm::vec4(.1, .1, .1, 1) };
	Vertex x18 = { glm::vec4(2,  0, 6, 1), glm::vec4(.1, .1, .1, 1) };
	Vertex x19 = { glm::vec4(-2,  0, 6, 1), glm::vec4(.1, .1, .1, 1) };
	Vertex x20 = { glm::vec4(-4,  0, 4, 1), glm::vec4(.1, .1, .1, 1) };
	Vertex x21 = { glm::vec4(-6,  0, 2, 1), glm::vec4(.1, .1, .1, 1) };
	Vertex x22 = { glm::vec4(-6,  0, -2, 1), glm::vec4(.1, .1, .1, 1) };
	Vertex x23 = { glm::vec4(-4,  0, -4, 1), glm::vec4(.1, .1, .1, 1) };
	Vertex x24 = { glm::vec4(-2,  0, -6, 1), glm::vec4(.1, .1, .1, 1) };

	Vertex x25 = { glm::vec4(0,  -2, -4, 1), glm::vec4(.1, .1, .1, 1) };
	Vertex x26 = { glm::vec4(3,  -2, -3, 1), glm::vec4(.1, .1, .1, 1) };
	Vertex x27 = { glm::vec4(4,  -2, 0, 1), glm::vec4(.1, .1, .1, 1) };
	Vertex x28 = { glm::vec4(3,  -2, 3, 1), glm::vec4(.1, .1, .1, 1) };
	Vertex x29 = { glm::vec4(0,  -2, 4, 1), glm::vec4(.1, .1, .1, 1) };
	Vertex x30 = { glm::vec4(-3, -2, 3, 1), glm::vec4(.1, .1, .1, 1) };
	Vertex x31 = { glm::vec4(-4, -2, 0, 1), glm::vec4(.1, .1, .1, 1) };
	Vertex x32 = { glm::vec4(-3, -2, -3, 1), glm::vec4(.1, .1, .1, 1) };

	Vertex x33 = { glm::vec4(2,  -3, -2, 1), glm::vec4(.1, .1, .1, 1) };
	Vertex x34 = { glm::vec4(2,  -3, 2, 1), glm::vec4(.1, .1, .1, 1) };
	Vertex x35 = { glm::vec4(-2, -3, 2, 1), glm::vec4(.1, .1, .1, 1) };
	Vertex x36 = { glm::vec4(-2, -3, -2, 1), glm::vec4(.1, .1, .1, 1) };

	Vertex x37 = { glm::vec4(0, -4, 0, 1), glm::vec4(.1, .1, .1, 1) };


	std::vector<Vertex>verts = { x0,x1,x2,x3,x4,x5,x6,x7,x8,x9,x10,x11,x12,x13,x14,x15,x16,x17,x18,x19,x20,x21,x22,x23,x24,x25,x26,x27,x28,x29,x30,x31,x32,x33,x34,x35,x36,x37 };
	std::vector<unsigned int>indices = { 0,1,2, 
		0,2,3,
		0,3,4,
		0,4,1,

		1,7,6,
		1,6,5,
		1,5,4,
		4,5,12,
		4,12,11,
		4,11,3,
		3,11,10,
		3,10,9,
		3,9,2,
		2,9,8,
		2,8,7,


		5,13,24, 
		12,24,23, 
		12,23,22, 
		11,22,21, 
		10,21,20, 
		10,20,19, 
		9,19,18, 
		8,18,17, 
		8,17,16, 
		7,16,15, 
		6,15,14, 
		6,14,13,
	
		25,13,24,
		32,24,23,
		32,23,22,
		31,22,21,
		30,21,20,
		30,20,19,
		29,19,18,
		28,18,17,
		28,17,16,
		27,16,15,
		26,15,14,
		26,14,13,


		33,27,26,
		33,26,25,
		33,25,36,
		36,25,32,
		36,32,31,
		36,31,35,
		35,31,30,
		35,10,29,
		35,29,34,
		34,29,28,
		34,28,27,
	
		37,34,35,
		37,35,36,
		37,36,33, };

	mesh->initialize(verts, indices);
	mesh->Create_Buffers();

	verts.clear();
	indices.clear();
}

void RenderGeoApp::update(float delta)
{
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

		mat4 x = mat4(1, 0, 0, 0, 0, cos(iDeltaY / 200), -sin(iDeltaY / 200), 0, 0, sin(iDeltaY / 200), cos(iDeltaY / 200), 0, 0, 0, 0, 1);
		mat4 y = mat4(cos(iDeltaX / 50), 0, sin(iDeltaX / 200), 0, 0, 1, 0, 0, -sin(iDeltaX / 200), 0, cos(iDeltaX / 200), 0, 0, 0, 0, 1);


		cam->m_view = x * y * cam->m_view;

	}
}

void RenderGeoApp::shutdown()
{
}

void RenderGeoApp::draw()
{

	glClearColor(1.f, 1.f, 1.f, 0.f);
	glEnable(GL_DEPTH_TEST);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	glLineWidth(2.0f);
	glUseProgram(m_programID);
	glm::mat4 view = glm::lookAt(glm::vec3(0, 0, 10), glm::vec3(0), glm::vec3(0, 1, 0));
	mat4 projection = glm::perspective(quarter_pi<float>(), 16 / 9.f, 0.1f, 1000.f);
	mat4 mvp = projection * view * glm::mat4(1);
	unsigned int projectionViewUniform = glGetUniformLocation(m_programID, "projectionViewWorldMatrix");
	glUniformMatrix4fv(projectionViewUniform, 1, false, glm::value_ptr(mvp));
	mesh->Bind();
	glDrawElements(GL_TRIANGLES, mesh->index_count, GL_UNSIGNED_INT, nullptr);
	mesh->Unbind();
	glUseProgram(0);
}
