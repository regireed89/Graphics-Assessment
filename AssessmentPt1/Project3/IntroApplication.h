#pragma once
#include "Application.h"

class IntroApplication :
	public Application
{
public:
	IntroApplication();
	virtual ~IntroApplication();
	virtual void startup() override;
	virtual void shutdown() override;
	virtual void update(float) override;
	virtual void draw() override;
};

