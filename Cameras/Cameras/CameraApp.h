#pragma once
#include "Application.h"
#include "Camera.h"
class CameraApp :
	public Application
{
public:
	CameraApp();
	~CameraApp();
	Camera* m_camera;
	float runtime;
protected:
	virtual void startup() override;
	virtual void update(float deltaTime) override;
	virtual void shutdown() override;
	virtual void draw() override;
};

