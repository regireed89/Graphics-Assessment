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
	

	glShaderSource(m_vertexShader, 1, (const char**)&vsSource, 0);
	glCompileShader(m_vertexShader);
	glShaderSource(m_fragmentShader, 1, (const char**)&vsSource, 0);
	glCompileShader(m_fragmentShader);

	
}

void Shader::unbind()
{
	glShaderSource(m_vertexShader, 1, static_cast<const char**>(&vsSource), nullptr);
	glCompileShader(m_vertexShader);

	glDeleteShader(m_fragmentShader);
	glDeleteShader(m_vertexShader);

	glClearColor(1.f, 1.f, 1.f, 1.f);
}

void Shader::load(const char* filename, unsigned type)
{
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
