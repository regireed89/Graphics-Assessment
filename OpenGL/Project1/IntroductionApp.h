#pragma once
#include "Application.h"
class IntroductionApp :
	public Application
{
public:
	IntroductionApp();
	virtual ~IntroductionApp();
	virtual void startup() override;
	virtual void shutdown() override;
	virtual void update(float) override;
	virtual void draw() override;

	void run(const char* title, unsigned int width, unsigned int height, bool fullscreen);
};

