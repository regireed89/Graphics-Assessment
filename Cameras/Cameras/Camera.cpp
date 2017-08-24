#include "Camera.h"
#include <glm.hpp>
#include <gtc/constants.inl>
#include <gtc/matrix_transform.inl>
using namespace glm;


Camera::Camera()
{
}


Camera::~Camera()
{
}

void Camera::update(float deltaTime)
{
}

void Camera::setOrthographic(float left, float right, float bottom, float top, float near, float far)
{
	vec4 x = vec4(2 / (right - left), 0, 0, 0);
	vec4 y = vec4(0, 2 / (top - bottom), 0, 0);
	vec4 z = vec4(0, 0, -2 / (far - near), 0);
	vec4 w = vec4(-((left + right) / 2), -((top + bottom) / 2), -((far + near) / 2), 1);
}

void Camera::setPerspective(float fieldOfView, float aspectRatio, float near, float far)
{
	m_fov = fieldOfView;
	m_aspectRatio = aspectRatio;
	m_near = near;
	m_far = far;
	auto x = 1.f / (m_aspectRatio * tan(m_fov / 2.f));
	auto y = 1.f / (tan(m_fov / 2.f));
	auto z = -1.f * ((m_far + m_near) / (m_far - m_near));
	auto w = -1.f * ((2.f * m_far * m_near) / (m_far - m_near));
	m_projection = glm::mat4(vec4(x, 0, 0, 0), vec4(0, y, 0, 0), vec4(0, 0, z, -1.f), vec4(0, 0, w, 0));
	auto copy = glm::perspective(m_fov, 16 / 9.f, 0.1f, 1.f);
	assert(copy == m_projection);
}

glm::mat4 Camera::setLookAt(glm::vec3 eye, glm::vec3 center, glm::vec3 up)
{
	vec3 f = eye - center;
	vec3 z = normalize(f);

	vec3 s = cross(up, z);
	vec3 x = normalize(s);

	vec3 u = cross(z, x);
	vec3 y = normalize(u);

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

	assert(View == e);
	mat4 M = inverse(View);

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
