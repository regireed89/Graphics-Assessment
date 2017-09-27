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
	_shader = new Shader();
	_plane = new Mesh();
}


TextureApplication::~TextureApplication()
{
}

void TextureApplication::generateGrid(unsigned int rows, unsigned int cols)
{
	std::vector<Vertex> vert;
	std::vector<unsigned int> indices;
	for (int i = 0; i < cols; i++)
	{
		for (int j = 0; j < rows; j++)
		{
			Vertex v = { vec4(j,i,0,0), vec4(0,0,0,1),vec4(0),vec4(0),vec2(0),vec4(0) };
			vert.push_back(v);
		}
	}
	_plane->initialize(vert, indices);
	_plane->Create_Buffers();
}

void TextureApplication::startup()
{
	_shader->load("texture.frag", GL_FRAGMENT_SHADER);
	_shader->load("texture.vert", GL_VERTEX_SHADER);
	int texWidth, texHeight, texFormat;
	unsigned char* image = stbi_load("../texture/crate.png", &texWidth, &texHeight, &texFormat, STBI_default);

	glGenTextures(1, &_texture);
	glBindTexture(GL_TEXTURE_2D, _texture);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, texWidth, texHeight, 0, GL_RGB, GL_FLOAT, image);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	
}

void TextureApplication::update(float)
{
}

void TextureApplication::shutdown()
{
}

void TextureApplication::draw()
{
	glClearColor(1.f, 1.f, 1.f, 0.f);
	glEnable(GL_DEPTH_TEST);

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	glLineWidth(1.0f);

	_shader->bind();
	glm::mat4 view = glm::lookAt(glm::vec3(10, 10, 10), glm::vec3(0), glm::vec3(0, 1, 0));
	mat4 projection = glm::perspective(quarter_pi<float>(), 16 / 9.f, 0.1f, 1000.f);
	mat4 mvp = projection * view * glm::scale(vec3(3, 3, 3)) * glm::translate(vec3(0, 0, -3));
	_shader->bindUniform("projectionViewWorldMatrix", mvp);
	_shader->bindUniform("time", glfwGetTime());

	_plane->Draw(GL_TRIANGLES);

	
}
