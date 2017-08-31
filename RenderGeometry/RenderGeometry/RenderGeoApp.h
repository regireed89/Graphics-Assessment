#pragma once
#include "Application.h"
#include <glm.hpp>
#include "Camera.h"
using namespace glm;

class RenderGeoApp :
	public Application
{
public:
	RenderGeoApp();
	~RenderGeoApp();
	void generateGrid();
	struct Vertex
	{
		vec4 position;
		vec4 color;
	};
	unsigned int m_VAO;
	unsigned int m_VBO;
	unsigned int m_IBO;
	unsigned int m_programID;
	unsigned int rows;
	unsigned int cols;
	Camera* cam;
protected:
	virtual void startup()override;
	virtual void update(float)override;
	virtual void shutdown()override;
	virtual void draw()override;
};

