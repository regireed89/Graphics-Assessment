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

void RenderGeoApp::generateGrid()
{
	Vertex a = { glm::vec4(-5, 0, 0, 1)		, glm::vec4(.1, .1, .1, 1) };//bl	
	Vertex b = { glm::vec4(5, 0, 0, 1)			, glm::vec4(.1, .1, .1, 1) };//br
	Vertex c = { glm::vec4(5, -5, 0, 1)			, glm::vec4(.1, .1, .1, 1) };//tl
	Vertex d = { glm::vec4(-5, -5, 0, 1)		, glm::vec4(1, 0, 0, 1) };//tr
	Vertex e = { glm::vec4(-5, 5, 0, 1)		, glm::vec4(0, 0, 1, 1) };//tr	

	std::vector<Vertex> vertices{ a,b,c,d,e };
	std::vector<unsigned int> indices{ 0, 1, 2, 0, 2, 3 , 0, 4, 1};
	indexCount = indices.size();
	//create vertex descriptors
	glGenVertexArrays(1, &m_VAO);
	//bind vertex array object
	glBindVertexArray(m_VAO);
	//bind vertex buffer and ibo 
	glGenBuffers(1, &m_VBO);
	glGenBuffers(1, &m_IBO);

	//buffer vertex info
	glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), vertices.data(), GL_STATIC_DRAW);

	//buffer index info
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_IBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), indices.data(), GL_STATIC_DRAW);

	///vertex descriptors
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), 0);

	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(sizeof(vec4)));

	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

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

	Vertex a = { glm::vec4(-5,  0, 0, 1), glm::vec4(.1, .1, .1, 1) };//bl	
	Vertex b = { glm::vec4(5,  0, 0, 1), glm::vec4(.1, .1, .1, 1) };//br
	Vertex c = { glm::vec4(5, -5, 0, 1), glm::vec4(.1, .1, .1, 1) };//tl
	Vertex d = { glm::vec4(-5, -5, 0, 1), glm::vec4(1, 0, 0, 1) };//tr
	Vertex e = { glm::vec4(-5,  5, 0, 1), glm::vec4(0, 0, 1, 1) };//tr	

	std::vector<Vertex>verts = { a,b,c,d,e };
	std::vector<unsigned int>indices = { 0, 1, 2, 0, 2, 3, 0, 4, 1 };

	mesh->initialize(verts, indices);
	mesh->Create_Buffers();
	


}

void RenderGeoApp::update(float)
{
}

void RenderGeoApp::shutdown()
{
}

void RenderGeoApp::draw()
{
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
