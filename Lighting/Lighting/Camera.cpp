#define GLM_FORCE_SWIZZLE
#include "Camera.h"
#include "GLM/glm.hpp"
#include <GLFW/glfw3.h>
#include <ext.hpp>
#include <glm.hpp>
#include "Application.h"

using namespace glm;


Camera::Camera(): m_fov(0), m_aspectRatio(0), m_near(0), m_far(0)
{
	setPerspective(pi<float>() / 4.f, 16 / 9.f, 0.1f, 1000.f);
}


Camera::~Camera()
{
}

void Camera::update(float deltaTime)
{
}

void Camera::setOrthographic(float left, float right, float bottom, float top, float Near, float Far)
{
	vec4 x = vec4(2 / (right - left), 0, 0, 0);
	vec4 y = vec4(0, 2 / (top - bottom), 0, 0);
	vec4 z = vec4(0, 0, -2 / (Far - Near), 0);
	vec4 w = vec4(-((left + right) / 2), -((top + bottom) / 2), -((Far + Near) / 2), 1);
	mat4 o = mat4(x, y, z, w);
	
}

glm::mat4 Camera::setPerspective(float fieldOfView, float aspectRatio, float Near, float Far)
{
	m_fov = fieldOfView;
	m_aspectRatio = aspectRatio;
	m_near = Near;
	m_far = Far;
	auto x = 1.f / (m_aspectRatio * tan(m_fov / 2.f));
	auto y = 1.f / (tan(m_fov / 2.f));
	auto z = -1.f * ((m_far + m_near) / (m_far - m_near));
	auto w = -1.f * ((2.f * m_far * m_near) / (m_far - m_near));
	m_projection = glm::mat4(vec4(x, 0, 0, 0), vec4(0, y, 0, 0), vec4(0, 0, z, -1.f), vec4(0, 0, w, 0));
	auto copy = glm::perspective(m_fov, aspectRatio, Near, Far);
	return copy;
}

glm::mat4 Camera::setLookAt(glm::vec3 eye, glm::vec3 center, glm::vec3 up)
{
	vec3 f = eye - center;
	vec3 z = normalize(f);

	vec3 s = cross(up, z);
	vec3 x = normalize(s);

	vec3 y = cross(z, x);

	mat4 V = mat4(vec4(x[0], y[0], z[0], 0),
		vec4(x[1], y[1], z[1], 0),
		vec4(x[2], y[2], z[2], 0),
		vec4(0, 0, 0, 1));


	mat4 T = mat4(vec4(1, 0, 0, 0),
		vec4(0, 1, 0, 0),
		vec4(0, 0, 1, 0),
		vec4(-eye.x, -eye.y, -eye.z, 1));

	mat4 View = V * T;
	mat4 e = lookAt(eye, center, up);
	m_view = View;
	assert(View == e);
	mat4 M = inverse(View);

	return M;
}

void Camera::setPosition(glm::vec3 position)
{
	worldTransform[3].x = position.x;
	worldTransform[3].y = position.y;
	worldTransform[3].z = position.z;
	worldTransform[3].w = 1;
	m_view = inverse(worldTransform);

}

glm::mat4 Camera::getView()
{
	return viewTransform;
}

glm::mat4 Camera::getProjection()
{
	return projectionTransform;
}

glm::mat4 Camera::getProjectionView()
{
	return m_projection * m_view;
}

glm::mat4 Camera::getWorldTransform()
{
	return worldTransform;
}

glm::mat4 Camera::updateProjectionViewTransform()
{
	return{};
}
