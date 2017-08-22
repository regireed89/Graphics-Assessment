#pragma once
#include "Camera.h"
#include <glm.hpp>
class FlyCamera :
	public Camera
{
public:
	FlyCamera();
	~FlyCamera();

	float speed;
	glm::vec3 up;
	update(float deltatime);
	setSpeed(float speed);
};

