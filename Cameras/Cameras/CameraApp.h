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
protected:
	virtual void startup() override;
	virtual void update(float) override;
	virtual void shutdown() override;
	virtual void draw() override;
};

