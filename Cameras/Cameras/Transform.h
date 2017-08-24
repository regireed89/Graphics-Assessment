#pragma once
#include <glm.hpp>
using namespace glm;

enum Axis
{
	ZAXIS,
	YAXIS,
	XAXIS
};


class Transform
{
public:
	Transform();
	 ~Transform();
	 mat4 m_world;
	 mat4 m_local;
	 mat3 m_rotation;
	 vec3 m_position;
	 void rotate(float raadians, Axis rotationAxis);
	 void translate(vec3 trans);

};

