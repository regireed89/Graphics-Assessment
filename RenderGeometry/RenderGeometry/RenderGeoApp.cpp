#include <iostream>
#include "RenderGeoApp.h"
#include "gl_core_4_4.h"
#include <glm.hpp>
#include <GLM/ext.hpp>


RenderGeoApp::RenderGeoApp()
{
	cam = new Camera();
}


RenderGeoApp::~RenderGeoApp()
{
}

void RenderGeoApp::generateGrid()
{
	Vertex* aoVertices = new Vertex[rows * cols];
	for (unsigned int r = 0; r < rows; ++r)
	{
		for (unsigned int c = 0; c < cols; ++c)
		{
			aoVertices[r * cols + c].position = vec4((float)c, 0, (float)r, 1);
			vec3 color = vec3(sinf((c / (float)(cols - 1))*(r / (float)(rows - 1))));
		}
	}
	unsigned int* auiIndices = new unsigned int[(rows - 1) * (cols - 1) * 6];

	unsigned int index = 0;
	for (unsigned int r = 0; r < (rows - 1); ++r)
	{
		for (unsigned int c = 0; c < cols; ++r)
		{
			auiIndices[index++] = r * cols + c;
			auiIndices[index++] = (r + 1)* cols + c;
			auiIndices[index++] = (r + 1) * cols + (c + 1);

			auiIndices[index++] = r * cols + c;
			auiIndices[index++] = (r + 1)*cols + c;
			auiIndices[index++] = r * cols + (c + 1);
		}
	}

	glGenBuffers(1, &m_VBO);
	glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
	glBufferData(GL_ARRAY_BUFFER, (rows*cols) * sizeof(Vertex), aoVertices, GL_STATIC_DRAW);

	glGenBuffers(1, &m_IBO);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_IBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, (rows - 1) * (cols - 1) * 6 * sizeof(unsigned int), auiIndices, GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), 0);
	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(sizeof(vec4)));

	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glGenBuffers(1, &m_VBO);
	glGenBuffers(1, &m_IBO);

	glGenVertexArrays(1, &m_VAO);

	glBindVertexArray(m_VAO);

	glBindVertexArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);



	delete[]aoVertices;
	delete[]auiIndices;
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

		glGetProgramInfoLog(m_programID, infoLogLength, 0, infoLog);
		printf("Error: Failed to link shader program!\n");
		printf("%s\n", infoLog);
		delete[] infoLog;
	}
	glShaderSource(vertexShader, 1, (const char**)&vsSource, 0);
	glCompileShader(vertexShader);


	glUseProgram(m_programID);
	unsigned int projectionViewUniform = glGetUniformLocation(m_programID, "projectionViewWorldMatrix");
	glUniformMatrix4fv(projectionViewUniform, 1, false, glm::value_ptr(cam->getProjectionView()));
	glBindVertexArray(m_VAO);
	unsigned int indexCount = (rows - 1) * (cols - 1) * 6;
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	glDrawElements(GL_TRIANGLES, indexCount, GL_UNSIGNED_INT, 0);


	glDeleteShader(fragmentShader);
	glDeleteShader(vertexShader);

}

void RenderGeoApp::update(float)
{
}

void RenderGeoApp::shutdown()
{
}

void RenderGeoApp::draw()
{
}
