#pragma once
#include "Application.h"
#include "Mesh.h"
#include "Shader.h"
class TextureApplication :
	public Application
{
public:
	TextureApplication();
	virtual ~TextureApplication();

	void generateGrid(unsigned int, unsigned int);

	// Inherited via Application
	virtual void startup() override;
	virtual void update(float) override;
	virtual void shutdown() override;
	virtual void draw() override;
	unsigned int _texture;
	Shader* _shader;
	Shader* _textureshader;
	Mesh* _plane;
};

