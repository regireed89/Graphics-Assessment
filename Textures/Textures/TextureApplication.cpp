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
				vec4(float(c), 0, float(r), 1),
				vec4(sin(r), cos(c), 0, 1),
				vec4(0, 1, 0, 0),
				vec4(0),
				vec2((float(c) / float(cols),float(r) / float(rows),
				vec4(0)))
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
	_textureshader->unbind();
	int texWidth, texHeight, texFormat;
	unsigned char* image = stbi_load("texture/crate.png", &texWidth, &texHeight, &texFormat, STBI_default);

	glGenTextures(1, &_texture);
	glBindTexture(GL_TEXTURE_2D, _texture);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, texWidth, texHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	generateGrid(10, 10);
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

	glClearColor(1.f, 1.f, 1.f, 0.f);
	glEnable(GL_DEPTH_TEST);
	
	glPolygonMode(GL_FRONT, GL_FILL);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	
	_textureshader->bind();
	glm::mat4 view = glm::lookAt(glm::vec3(15, 15, 20), glm::vec3(0), glm::vec3(0, 1, 0));
	mat4 projection = glm::perspective(quarter_pi<float>(), 16 / 9.f, 0.1f, 1000.f);
	mat4 mvp = projection * view;

	_textureshader->bindUniform("projectionViewWorldMatrix", mvp);
	_textureshader->bindUniform("time", glfwGetTime());
	
	int sample = _textureshader->getUniform("tex");
	glUniform1i(sample, 0);
		
	_plane->Draw(GL_TRIANGLES);


	
}
