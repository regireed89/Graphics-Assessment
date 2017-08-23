#include <iostream>
#include "Camera.h"

int main()
{
	Camera cam = Camera();
	cam.setLookAt(glm::vec3(1, 0, 0), glm::vec3(0, 1, 0), glm::vec3(0, 0, 1));
	return 0;
}