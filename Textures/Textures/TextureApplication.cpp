#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>
#include "TextureApplication.h"
#include "gl_core_4_4.h"
#include <GLFW\glfw3.h>
#include <GLM\glm.hpp>
#include <GLM\ext.hpp>
using namespace glm;


TextureApplication::TextureApplication()
{
	_textureshader = new Shader();
	_plane = new Mesh();
	_camera = new Camera();
}


TextureApplication::~TextureApplication()
{
}


void TextureApplication::generateGrid(unsigned int rows, unsigned int cols)
{
	auto aoVertices = new Vertex[rows * cols];
	for (unsigned int r = 0; r < rows; ++r)
	{
		for (unsigned int c = 0; c < cols; ++c)
		{
			Vertex verts = {
				vec4(float(c), 0, float(r), 1),//vertex position
				vec4(0, 0, 0, 1),
				vec4(0, 1, 0, 0),
				vec2(float(c) / float(cols-1),float(r) / float(rows-1))//UV mapping to grid for each vertex
			};
			aoVertices[r * cols + c] = verts;
		}
	}

	std::vector<Vertex> verts = std::vector<Vertex>();
	std::vector<unsigned int> indices = std::vector<unsigned int>();

	//Defining index count based off quad count (2 triangles per quad)
	unsigned int* auiIndices = new unsigned int[(rows - 1) * (cols - 1) * 6];
	unsigned int index = 0;
	for (unsigned int r = 0; r < (rows - 1); ++r)
	{
		for (unsigned int c = 0; c < (cols - 1); ++c)
		{
			//Triangle 1
			auiIndices[index++] = r * cols + c;
			auiIndices[index++] = (r + 1) * cols + c;
			auiIndices[index++] = (r + 1) * cols + (c + 1);
			//Triangle 2
			auiIndices[index++] = r * cols + c;
			auiIndices[index++] = (r + 1) * cols + (c + 1);
			auiIndices[index++] = r * cols + (c + 1);
		}
	}
	//Create and bind buffers to a vertex array object
	for (unsigned int i = 0; i < (rows * cols); i++)
		verts.push_back(aoVertices[i]);
	for (unsigned int i = 0; i < index; i++)
		indices.push_back(auiIndices[i]);

	_plane->initialize(verts, indices);
	_plane->Create_Buffers();
}




void TextureApplication::startup()
{
	_textureshader->load("texturev.vert", GL_VERTEX_SHADER);
	_textureshader->load("texturef.frag", GL_FRAGMENT_SHADER);
	_textureshader->attach();
	
	int texWidth, texHeight, texFormat;
	//loads image in formation
	unsigned char* image = stbi_load("texture/crate.png", &texWidth, &texHeight, &texFormat, STBI_default);

	int dims = 64;
	float* perlinData = new float[dims * dims];
	float scale = (1.0f / dims) * 3;
	int octaves = 6;
	for (int x = 0; x < dims; ++x)
	{
		for (int y = 0; y < dims; ++y)
		{
			float amplitude = 1.f;
			float persistence = 0.3f;
			perlinData[y * dims + x] = 0;
			for (int o = 0; o < octaves; ++o)
			{
				float freq = powf(2, (float)o);
				float perlinSample = glm::perlin(vec2((float)x, (float)y) * scale * freq) * 0.5f + 0.5f;
				perlinData[y * dims + x] += perlinSample * amplitude;
				amplitude *= persistence;
			}
			
		}
	}

	glGenTextures(1, &_texture);//generates texture
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, _texture);//binds texture as a 2d texture
	glTexImage2D(GL_TEXTURE_2D, 0, GL_R32F, 64, 64, 0, GL_RED, GL_FLOAT, perlinData);


	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);


	generateGrid(64, 64);
}

void TextureApplication::update(float deltaTime)
{
	runtime += deltaTime;
	//controls keybord movement of camera
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
	{
		glm::vec3 npos = glm::vec3(_camera->getWorldTransform()[3] -= _camera->getWorldTransform()[2]);
		_camera->setPosition(npos);
	}
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
	{
		glm::vec3 nneg = glm::vec3(_camera->getWorldTransform()[3] += _camera->getWorldTransform()[2]);
		_camera->setPosition(nneg);
	}
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
	{
		glm::vec3 npos = glm::vec3(_camera->getWorldTransform()[3] -= _camera->getWorldTransform()[0]);
		_camera->setPosition(npos);
	}
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
	{
		glm::vec3 nneg = glm::vec3(_camera->getWorldTransform()[3] += _camera->getWorldTransform()[0]);
		_camera->setPosition(nneg);
	}
}

void TextureApplication::shutdown()
{
}

void TextureApplication::draw()
{

	glClearColor(0.f, 1.f, 0.f, 0.f);
	glEnable(GL_DEPTH_TEST);
	
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	
	_textureshader->bind();
	glm::mat4 view = glm::lookAt(glm::vec3(70, 70, 70), glm::vec3(32, 0, 32), glm::vec3(0, 1, 0));
	mat4 projection = glm::perspective(quarter_pi<float>(), 16 / 9.f, 0.1f, 1000.f);
	mat4 mvp = projection * view;
	
	_textureshader->bindUniform("projectionViewWorldMatrix", mvp);
	_textureshader->bindUniform("time", glfwGetTime());
	

	int sample = _textureshader->getUniform("tex");
	glUniform1i(sample, 0);

	sample = _textureshader->getUniform("perlinTexture");
	glUniform1i(sample, 0);
		
	_plane->Draw(GL_TRIANGLES);
	_textureshader->unbind();

	
}
