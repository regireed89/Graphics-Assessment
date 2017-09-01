#pragma once
#include <vector>
#include "RenderGeoApp.h"

class Mesh
{
public:
	Mesh();
	virtual ~Mesh();
	void Create_Buffers();
	void initialize(std::vector<RenderGeoApp::Vertex>&verts, std::vector<unsigned int>&indices);
	void Bind();
	void Unbind();
	unsigned int index_count;
	unsigned int vertex_count;
private:
	unsigned int m_VAO;
	unsigned int m_VBO;
	unsigned int m_IBO;
	std::vector<unsigned int> m_indices;
	std::vector<RenderGeoApp::Vertex> m_vertex;

};

