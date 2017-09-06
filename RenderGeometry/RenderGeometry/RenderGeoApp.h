#pragma once
#include "Application.h"
#include <glm.hpp>
#include "Camera.h"
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

protected:
	virtual void startup()override;
	virtual void update(float delta)override;
	virtual void shutdown()override;
	virtual void draw()override;
};

