#include "Mesh.h"
#include "gl_core_4_4.h"
#include <GLM/glm.hpp>
#include <GLM/fwd.hpp>
#include <GLM/ext.hpp>
#include <vector>
using namespace glm;


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

	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 4, GL_FLOAT, GL_TRUE, sizeof(Vertex), (void*)(sizeof(glm::vec4) * 2));

	glEnableVertexAttribArray(3);
	glVertexAttribPointer(3, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(sizeof(glm::vec4) * 3));

	glEnableVertexAttribArray(4);
	glVertexAttribPointer(4, 4, GL_FLOAT, GL_TRUE, sizeof(Vertex), (void*)(sizeof(glm::vec4) * 3 + sizeof(glm::vec2)));

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

void Mesh::Draw(unsigned int num)
{
	this->Bind();
	switch (num)
	{
	case GL_TRIANGLES:
		glDrawElements(num, this->index_count, GL_UNSIGNED_INT, 0);
		break;

	case GL_TRIANGLE_STRIP:
		glDrawElements(num, this->index_count, GL_UNSIGNED_INT, 0);
		break;

	case GL_POINT: 
		glDrawArrays(num, 0, this->vertex_count);
		break;
	}
	this->Unbind();

}
