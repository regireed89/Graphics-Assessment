#pragma once
#include <vector>
#include "LightingApp.h"

struct Vertex
{
	glm::vec4 position;
	glm::vec4 color;
	glm::vec4 normal;
	glm::vec4 tangent;
	glm::vec4 bitangent;
	glm::vec2 texcoord;
};
class Mesh
{

public:
	Mesh();
	virtual ~Mesh();
	void Create_Buffers();
	void initialize(std::vector<Vertex>&verts, std::vector<unsigned int>&indices);
	void Bind();
	void Unbind();
	void Draw(unsigned int);
	unsigned int index_count;
	unsigned int vertex_count;

private:
	unsigned int m_VAO;
	unsigned int m_VBO;
	unsigned int m_IBO;
	std::vector<unsigned int> m_indices;
	std::vector<Vertex> m_vertex;
	 
};

