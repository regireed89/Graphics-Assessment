#pragma once
#include <iostream>
#include "gl_core_4_4.h"
#include "Gizmos.h"
#include <glm.hpp>

class Camera
{
public:
	Camera();
	virtual ~Camera();

	virtual void update(float deltaTime);
	void setPerspective(float fieldOfView, float aspectRatio, float near, float far);
	glm::mat4 setLookAt(glm::vec3 eye, glm::vec3 center, glm::vec3 up);
	
	glm::mat4 setPosition(glm::vec3 position);
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


