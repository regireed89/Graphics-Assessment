#pragma once
#include <glm.hpp>
using namespace glm;

class Camera
{
public:
	Camera();
	virtual ~Camera();
	
	virtual void update(float deltaTime);
	void setOrthographic(float left, float right, float bottom, float top, float Near, float Far);
	void setPerspective(float fieldOfView, float aspectRatio, float Near, float Far);
	glm::mat4 setLookAt(glm::vec3 eye, glm::vec3 center, glm::vec3 up);
	void setPosition(glm::vec3 position);
	glm::mat4 getView();
	glm::mat4 getProjection();
	glm::mat4 getProjectionView();
	glm::mat4 getWorldTransform();
	mat4 m_view;

private:
	glm::mat4 worldTransform;//represents object position in world space
	glm::mat4 viewTransform;//inverse of world transform
	glm::mat4 projectionTransform;//transform 3d into 2d
	glm::mat4 projectionViewTransform;
	glm::mat4 updateProjectionViewTransform();
	glm::mat4 m_projection;
	float m_fov;//how much of the world a camera can view
	float m_aspectRatio;//dimensions of the screen
	float m_near;
	float m_far;
	
	
};


