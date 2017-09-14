#pragma once
#include "Application.h"
#include <GLM\glm.hpp>
#include "Shader.h"
#include "Mesh.h"
class LightingApp :
	public Application
{
public:
	LightingApp();
	virtual ~LightingApp();
	void generateSphere(unsigned int segments, unsigned int rings, unsigned int & vao, unsigned int & vbo, unsigned int & ibo, unsigned int & indexCount);
	void startup() override;
	void update(float deltaTime) override;
	void draw() override;
	void shutdown() override;
	Shader* _shader;
	Shader* _phongShader;
};

