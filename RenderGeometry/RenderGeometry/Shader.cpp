#include <iostream>
#include "Shader.h"
#include "gl_core_4_4.h"


Shader::Shader(): m_vertexShader(0), m_fragmentShader(0), vsSource(nullptr), fsSource(nullptr), m_program(0)
{
}

Shader::~Shader()
{
}

void Shader::bind()
{
		
}

void Shader::unbind()
{
	glClearColor(1.f, 1.f, 1.f, 1.f);
}

void Shader::load(const char* filename, unsigned type)
{
	FILE* file;
	fopen_s(&file, filename, "r");
	if (file == nullptr)
		perror("no file found");
	fseek(file, 0, SEEK_END);
	auto size = ftell(file);
	auto buffer = new char[size + 1];
	fseek(file, 0, SEEK_SET);
	auto num = fread(buffer, sizeof(char), size + 1, file);
	buffer[num] = '\0';
	
	const char * data = buffer;

	switch(type)
	{
	case GL_VERTEX_SHADER:
		m_vertexShader = glCreateShader(type);
		vsSource = buffer;
		glShaderSource(m_vertexShader, 1, (const char**)&vsSource, 0);
		glCompileShader(m_vertexShader);

	case GL_FRAGMENT_SHADER:
		m_fragmentShader = glCreateShader(type);
		fsSource = buffer;
		glShaderSource(m_fragmentShader, 1, (const char**)&fsSource, 0);
		glCompileShader(m_fragmentShader);		
	}
}

void Shader::attach()
{
	int success = GL_FALSE;
	m_program = glCreateProgram();
	glAttachShader(m_program, m_vertexShader);
	glAttachShader(m_program, m_fragmentShader);
	glLinkProgram(m_program);

	glGetProgramiv(m_program, GL_LINK_STATUS, &success);

	if (success == GL_FALSE)
	{
		int infoLogLength = 0;
		glGetProgramiv(m_program, GL_INFO_LOG_LENGTH, &infoLogLength);
		char* infoLog = new char[infoLogLength];

		glGetProgramInfoLog(m_program, infoLogLength, nullptr, infoLog);
		printf("Error: Failed to link shader program!\n");
		printf("%s\n", infoLog);
		delete[] infoLog;
	}
}

void Shader::defaultLoad()
{
}

unsigned Shader::getUniform(const char* c)
{
	unsigned int projectionViewUniform = glGetUniformLocation(m_program, c);
	return projectionViewUniform;
}
