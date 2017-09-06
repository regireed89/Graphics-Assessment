#include <iostream>
#include "RenderGeoApp.h"
#include "gl_core_4_4.h"
#include <glm.hpp>
#include <GLM/fwd.hpp>
#include <GLM/ext.hpp>
#include <vector>
#include "Mesh.h"


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

	Vertex a0 = { glm::vec4(0,  -6, 0, 1), glm::vec4(.1, .1, .1, 1) };

	Vertex b1 = { glm::vec4(2,  4, -2, 1), glm::vec4(.1, .1, .1, 1) };
	Vertex c2 = { glm::vec4(2,  4, 2, 1), glm::vec4(.1, .1, .1, 1) };
	Vertex d3 = { glm::vec4(-2, 4, 2, 1), glm::vec4(.1, .1, .1, 1) };
	Vertex e4 = { glm::vec4(-2, 4, -2, 1), glm::vec4(.1, .1, .1, 1) };

	Vertex f5 = { glm::vec4(2,  2, -2, 1), glm::vec4(.1, .1, .1, 1) };
	Vertex g6 = { glm::vec4(2,  2, -2, 1), glm::vec4(.1, .1, .1, 1) };
	Vertex h7 = { glm::vec4(2,  2, -2, 1), glm::vec4(.1, .1, .1, 1) };
	Vertex i8 = { glm::vec4(2,  2, -2, 1), glm::vec4(.1, .1, .1, 1) };
	Vertex j9 = { glm::vec4(2,  2, -2, 1), glm::vec4(.1, .1, .1, 1) };
	Vertex k10 = { glm::vec4(2, 2, -2, 1), glm::vec4(.1, .1, .1, 1) };
	Vertex l11 = { glm::vec4(2, 2, -2, 1), glm::vec4(.1, .1, .1, 1) };
	Vertex m12 = { glm::vec4(2, 2, -2, 1), glm::vec4(.1, .1, .1, 1) };


	std::vector<Vertex>verts = { a0,b1,c2,d3,e4 };
	std::vector<unsigned int>indices = { 0,1,2, 0,2,3, 0,3,4, 0,4,1 };

	mesh->initialize(verts, indices);
	mesh->Create_Buffers();

	verts.clear();
	indices.clear();
}

void RenderGeoApp::update(float delta)
{
	cam->update(delta);
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
	glm::mat4 view = glm::lookAt(glm::vec3(10, 10, 10), glm::vec3(0), glm::vec3(0, 1, 0));
	mat4 projection = glm::perspective(quarter_pi<float>(), 16 / 9.f, 0.1f, 1000.f);
	mat4 mvp = projection * view * glm::mat4(1);
	unsigned int projectionViewUniform = glGetUniformLocation(m_programID, "projectionViewWorldMatrix");
	glUniformMatrix4fv(projectionViewUniform, 1, false, glm::value_ptr(mvp));
	mesh->Bind();
	glDrawElements(GL_TRIANGLES, mesh->index_count, GL_UNSIGNED_INT, nullptr);
	mesh->Unbind();
	glUseProgram(0);
}
