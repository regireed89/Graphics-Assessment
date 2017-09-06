#include "Mesh.h"
#include "gl_core_4_4.h"
#include <glm.hpp>
#include <GLM/fwd.hpp>
#include <GLM/ext.hpp>
#include <vector>
#include "RenderGeoApp.h"

Mesh::Mesh()
{

}

Mesh::~Mesh()
{
}

void Mesh::Create_Buffers()
{
	//create vertex descriptors
	glGenVertexArrays(1, &m_VAO);


	//bind vertex buffer and ibo 
	glGenBuffers(1, &m_VBO);
	glGenBuffers(1, &m_IBO);

	glBindVertexArray(m_VAO);
	glBindBuffer(GL_ARRAY_BUFFER, m_VBO);

	glBufferData(GL_ARRAY_BUFFER, m_vertex.size() * sizeof(Vertex), m_vertex.data(), GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_IBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_indices.size() * sizeof(unsigned int), m_indices.data(), GL_STATIC_DRAW);

	//position
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), 0);

	//color
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(sizeof(vec4)));

	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void Mesh::initialize(std::vector<Vertex>& verts, std::vector<unsigned>& indices)
{

	for (auto v : verts)
	{
		m_vertex.push_back(v);
	}
	for (auto i : indices)
	{
		m_indices.push_back(i);
	}
	vertex_count = m_vertex.size();
	index_count = m_indices.size();
}

void Mesh::Bind()
{
	//bind vertex array object
	glBindVertexArray(m_VAO);
}

void Mesh::Unbind()
{
	glBindVertexArray(0);
}
