#pragma once
#include <GLM\glm.hpp>
class Shader
{
public:
	Shader();
	~Shader();
	void bind();
	void unbind();
	void load(const char * filename, unsigned int type);
	void attach();
	void defaultLoad();
	//void load();
	unsigned int getUniform(const char *);
	void bindUniform(const char * c, float val);
	void bindUniform(const char *, glm::mat4);
	unsigned int m_vertexShader;
	unsigned int m_fragmentShader;
	const char* vsSource;
	const char* fsSource;
	
	unsigned int m_program;
};
