#pragma once
#include <iostream>
#include "gl_core_4_4.h"
#include "Gizmos.h"
#include <glm.hpp>

class Camera
{
public:
	Camera();
	~Camera();

	virtual void update(float deltaTime) = 0; 
	setPerspective(float fieldOfView, float aspectRatio, float near, float far);
	update(float deltaTime);
	setLookAt(vec3 from, vec3 to, vec3 up);
	
	glm::mat4 (vec3 position);
	glm::mat4 getView();
	glm::mat4 getProjection();
	glm::mat4 getProjectionView();
	glm::mat4 getWorldTransform();

private:
	glm::mat4 worldTransform;
	glm::mat4 viewTransform;
	glm::mat4 projectionTransform;
	glm::mat4 projectionViewTransform;
	glm::mat4 updateProjectionViewTransform();
};


