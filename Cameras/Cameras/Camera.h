#pragma once
#include <iostream>
#include "Gizmos.h"
#include <glm.hpp>
using namespace glm;

class Camera
{
public:
	Camera();
	virtual ~Camera();
	
	virtual void update(float deltaTime);
	void setOrthographic(float left, float right, float bottom, float top, float near, float far);
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
	glm::mat4 m_projection;
	float m_fov;
	float m_aspectRatio;
	float m_near;
	float m_far;
	
};


