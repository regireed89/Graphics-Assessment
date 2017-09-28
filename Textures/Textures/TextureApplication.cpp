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
	_textureshader = new Shader();
	_plane = new Mesh();
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

	_shader->load("vsSource.vert", GL_VERTEX_SHADER);
	_shader->load("fsSource.frag", GL_FRAGMENT_SHADER);
	_shader->attach();
	_shader->unbind();

	_textureshader->load("texture.frag", GL_FRAGMENT_SHADER);
	_textureshader->load("texture.vert", GL_VERTEX_SHADER);
	_textureshader->attach();
	_textureshader->unbind();
	int texWidth, texHeight, texFormat;
	unsigned char* image = stbi_load("../texture/crate.png", &texWidth, &texHeight, &texFormat, STBI_default);

	glGenTextures(1, &_texture);
	glBindTexture(GL_TEXTURE_2D, _texture);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, texWidth, texHeight, 0, GL_RGB, GL_FLOAT, image);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	generateGrid(10, 10);

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

	glPolygonMode(GL_FRONT, GL_FILL);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glLineWidth(2.0f);

	_shader->bind();
	glm::mat4 view = glm::lookAt(glm::vec3(10, 10, 10), glm::vec3(0), glm::vec3(0, 1, 0));
	mat4 projection = glm::perspective(quarter_pi<float>(), 16 / 9.f, 0.1f, 1000.f);
	mat4 mvp = projection * view * glm::scale(vec3(3, 3, 3)) * glm::translate(vec3(0, 0, -3));

	_shader->bindUniform("projectionViewWorldMatrix", mvp);
	_shader->bindUniform("time", glfwGetTime());

	_plane->Draw(GL_TRIANGLES);

	glUseProgram(0);
}
