#include "Transform.h"



Transform::Transform()
{
}


Transform::~Transform()
{
}

void Transform::rotate(float raadians, Axis rotationAxis)
{
}

void Transform::translate(vec3 trans)
{
	mat4 translation = mat4(1);
	translation[3].x = trans.x;
	translation[3].y = trans.y;
	translation[3].z = trans.z;
	m_world = m_world * translation;
}
