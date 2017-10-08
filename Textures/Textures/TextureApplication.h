#pragma once
#include "Application.h"
#include "Mesh.h"
#include "Shader.h"
#include "Camera.h"
class TextureApplication :
	public Application
{
public:
	TextureApplication();
	virtual ~TextureApplication();

	void generateGrid(unsigned int, unsigned int);
	void perlinNoise();
	float lerp(float a0, float a1, float w);
	float dotGridGradient(int ix, int iy, float x, float y);
	float regiNoise(float x, float y);
	unsigned int getRandom(unsigned int seed0, unsigned int seed1);
	double regiNoise2(int x, int y);
	// Inherited via Application
	virtual void startup() override;
	virtual void update(float) override;
	virtual void shutdown() override;
	virtual void draw() override;
	unsigned int _texture;
	float runtime;
	Shader* _textureshader;
	Mesh* _plane;
	Camera* _camera;
};

