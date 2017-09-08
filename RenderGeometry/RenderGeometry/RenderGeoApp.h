#pragma once
#include "Application.h"
#include <glm.hpp>
#include "Camera.h"
#include <vector>
class Shader;
class Mesh;
using namespace glm;

class RenderGeoApp :
	public Application
{
public:
	RenderGeoApp();
	~RenderGeoApp();
	
	unsigned int indexCount;
	unsigned int m_VAO;
	unsigned int m_VBO;
	unsigned int m_IBO; 
	unsigned int m_programID;


	Camera* cam;
	Mesh* mesh;
	Shader* _shader;
	vec4 RenderSphere();
	std::vector<vec4>generateHalfCircle(float radius, unsigned int np);
	vec4 rotatePoints(std::vector<vec4> points, unsigned int nm);
	void proceduralSphere();

protected:
	virtual void startup()override;
	virtual void update(float delta)override;
	virtual void shutdown()override;
	virtual void draw()override;
};

