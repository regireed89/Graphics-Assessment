#pragma once
#include "Camera.h"
#include <glm.hpp>

class FlyCamera :
	public Camera
{
public:
	FlyCamera();
	~FlyCamera();

	void update(float deltatime);
	int setSpeed(float speed);
private:
	float speed;
	glm::vec3 up;


};
