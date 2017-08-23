#include "Camera.h"
#include <glm.hpp>
#include <gtc/constants.inl>
#include <gtc/matrix_transform.inl>


Camera::Camera()
{
}


Camera::~Camera()
{
}

void Camera::update(float deltaTime)
{
}

void Camera::setPerspective(float fieldOfView, float aspectRatio, float, float)
{
	return;
}

glm::mat4 Camera::setLookAt(glm::vec3 eye, glm::vec3 center, glm::vec3 up)
{
	glm::vec3 f = eye - center;
	glm::vec3 z = glm::normalize(f);

	glm::vec3 s = glm::cross(up, z);
	glm::vec3 x = glm::normalize(s);

	glm::vec3 u = glm::cross(z, x);
	glm::vec3 y = glm::normalize(u);

	glm::mat4 V = glm::mat4(glm::vec4(x[0], y[0], z[0], 0),
							glm::vec4(x[1], y[1], z[1], 0),
							glm::vec4(x[2], y[2], z[2], 0),
							glm::vec4(0, 0, 0, 1));
	

	glm::mat4 T = glm::mat4(glm::vec4(1, 0, 0, 0),
							glm::vec4(0, 1, 0, 0),
							glm::vec4(0, 0, 1, 0),
							glm::vec4(-eye.x, -eye.y, -eye.z, 1));

	glm::mat4 View = V * T;
	glm::mat4 e = glm::lookAt(eye, center, up);

	assert(View == e);
	glm::mat4 M = glm::inverse(View);
	
	return M;
}

glm::mat4 Camera::setPosition(glm::vec3 position)
{
	return{};
}

glm::mat4 Camera::getView()
{
	return{};
}

glm::mat4 Camera::getProjection()
{
	return{};
}

glm::mat4 Camera::getProjectionView()
{
	return{};
}

glm::mat4 Camera::getWorldTransform()
{
	return{};
}

glm::mat4 Camera::updateProjectionViewTransform()
{
	return{};
}
