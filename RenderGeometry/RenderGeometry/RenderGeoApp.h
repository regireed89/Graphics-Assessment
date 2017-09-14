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
	
	


	Camera* cam;
	Mesh* ball_mesh;
	Mesh* static_ball_mesh;
	Mesh* cube_mesh;
	Mesh* plane_mesh;
	Shader* _shader;
	std::vector<vec4>generateHalfCircleX(float radius, unsigned np);
	std::vector<vec4>generateHalfCircleY(float radius, unsigned int np);
	std::vector<vec4>generateHalfCircleZ(float radius, unsigned int np);
	std::vector<vec4>rotatePointsX(std::vector<vec4> points, unsigned int nm);
	std::vector<vec4>rotatePointsY(std::vector<vec4> points, unsigned int nm);
	std::vector<vec4>rotatePointsZ(std::vector<vec4> points, unsigned int nm);
	std::vector<unsigned int>generateIndices(unsigned int np, unsigned int nm);
	void proceduralSphere();
	void generateCube();
	void generatePlane();
	

protected:
	virtual void startup()override;
	virtual void update(float delta)override;
	virtual void shutdown()override;
	virtual void draw()override;
};

