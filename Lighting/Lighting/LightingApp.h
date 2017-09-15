#pragma once
#include "Application.h"
#include <GLM\glm.hpp>
#include "Shader.h"
#include "Mesh.h"
#include "Camera.h"
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
	Camera* _camera;
	unsigned int m_VBO;
	unsigned int m_VAO;
	unsigned int m_IBO;
	unsigned int m_index_count;

	struct DirectionalLight
	{
		glm::vec3 direction;
		glm::vec3 diffuse;
		glm::vec3 specular;
	}m_directionalLight;

	glm::vec3 m_ambientLight;

	struct Material
	{
		glm::vec3 ambient;
		glm::vec3 diffuse;
		glm::vec3 specular;
		float specularPower;
	}m_material;
	glm::mat4 m_modeMatrix;
};

