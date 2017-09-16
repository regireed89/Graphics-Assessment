#include <iostream>
#include "RenderGeoApp.h"
#include "gl_core_4_4.h"
#include <glm.hpp>
#include <GLM/ext.hpp>
#include <vector>
#include "Mesh.h"
#include <GLFW\glfw3.h>
#include "Shader.h"
using namespace glm;
using namespace std;
#define PI 3.1415926535897932384626433832795

RenderGeoApp::RenderGeoApp()
{
	cam = new Camera();
	ball_mesh = new Mesh();
	cube_mesh = new Mesh();
	plane_mesh = new Mesh();
	static_ball_mesh = new Mesh();

}

RenderGeoApp::~RenderGeoApp()
{
}

std::vector<vec4> RenderGeoApp::generateHalfCircleX(float radius, unsigned np)
{
	auto pts = std::vector<vec4>();
	for (int i = 0; i < np; i++)
	{
		float slice = PI / np;
		float theta = slice * i;

		float x = cos(theta) * radius;
		float y = sin(theta) * radius;
		float z = 0;
		auto md = Vertex();
		md.position = vec4(x, y, z, 1);
		md.color = vec4(1, 0, 0, 0);
		pts.push_back(md.position);
	}
	return 	pts;
}

std::vector<vec4> RenderGeoApp::generateHalfCircleY(float radius, unsigned int np)
{
	float slice = PI / (np-1);//find angle between points based on # of points
	auto pts = std::vector<vec4>();
	for (int i = 0; i < np; i++)
	{
		float theta = slice * i;//angle of rotation from 0 for each specific point

		float x = sin(theta) * radius;//rotation math for points
		float y = cos(theta) * radius;
		float z = 0;
		auto md = Vertex();
		md.position = vec4(x, y, z, 1);//position of point on circle
		md.color = vec4(1, 0, 0, 0);
		pts.push_back(md.position);
	}
	return pts;
}

std::vector<vec4> RenderGeoApp::generateHalfCircleZ(float radius, unsigned int np)
{
	auto pts = std::vector<vec4>();
	for (int i = 0; i < np; i++)
	{
		float slice = PI / np;
		float theta = slice * i;

		float x = cos(theta) * radius;
		float y = 0;
		float z = sin(theta) * radius;
		auto md = Vertex();
		md.position = vec4(x, y, z, 1);
		md.color = vec4(1, 0, 0, 0);
		pts.push_back(md.position);
	}
	return pts;
	 
}

std::vector<vec4> RenderGeoApp::rotatePointsX(std::vector<vec4> points, unsigned int nm)
{
	auto supercalifragilisticexpialidocious = std::vector<vec4>();

	for (int i = 0; i <= nm; i++)
	{
		float slice = 2 * PI / nm;
		float phi = slice * i;
		for (int j = 0; j < points.size(); j++)
		{

			float x = points[j].x;
			float y = points[j].y * cos(phi) + points[j].z * sin(phi);
			float z = points[j].y * -sin(phi) + points[j].z * cos(phi);


			auto pablo = Vertex();
			pablo.position = vec4(x, y, z, 1);
			pablo.color = vec4(1, 1, 1, 1);
			supercalifragilisticexpialidocious.push_back(pablo.position);
		}
	}
	return supercalifragilisticexpialidocious;
}

std::vector<vec4> RenderGeoApp::rotatePointsY(std::vector<vec4> points, unsigned int nm)
{
	auto supercalifragilisticexpialidocious = std::vector<vec4>();
	for (int i = 0; i <= nm; i++)
	{
		float slice = 2 * PI / nm;// determines angle between each meridian on sphere
		float phi = slice * i;//angle of rotation for meridians
		for (int j = 0; j < points.size(); j++)
		{
			float x = points[j].x * cos(phi) + points[j].z * -sin(phi);
			float y = points[j].y;
			float z = points[j].x * sin(phi) + points[j].z * cos(phi);

			auto pablo = Vertex();
			pablo.position = vec4(x, y, z, 1);
			pablo.color = vec4(1, 1, 1, 1);
			supercalifragilisticexpialidocious.push_back(pablo.position);
		}
	}

	return supercalifragilisticexpialidocious;
}

std::vector<vec4> RenderGeoApp::rotatePointsZ(std::vector<vec4> points, unsigned int nm)
{
	auto supercalifragilisticexpialidocious = std::vector<vec4>();
	for (int i = 0; i <= nm; i++)
	{
		float slice = 2 * PI / nm;
		float phi = slice * i;
		for (int j = 0; j < points.size(); j++)
		{
			float x = points[j].x * cos(phi) + points[j].y * sin(phi);
			float y = points[j].x * -sin(phi) + points[j].y * cos(phi);
			float z = points[j].z;

			auto pablo = Vertex();
			pablo.position = vec4(x, y, z, 1);
			pablo.color = vec4(1, 1, 1, 1);
			supercalifragilisticexpialidocious.push_back(pablo.position);
		}
	}

	return supercalifragilisticexpialidocious;
	return std::vector<vec4>();
}

std::vector<unsigned int> RenderGeoApp::generateIndices(unsigned int np, unsigned int nm)
{
	unsigned int start;
	unsigned int botleft;
	unsigned int botright;
	auto indices = std::vector<unsigned int>();
	for (int i = 0; i < nm; i++)
	{
		start = i * nm;//tells the triangle strips what point to start at

		for (int j = 0; j < np; j++)
		{
			botleft = start + j;//sets bottom left of the triangle strip
			botright = botleft + np;//sets the bottom right of the triangle strip
			indices.push_back(botleft);
			indices.push_back(botright);
		}
		indices.push_back(0xFFFF);//ends the current triangle strip and moves over to the next
	}
	
	return indices;
}

void RenderGeoApp::TriangleSphere()
{
	Vertex x0 = { glm::vec4(0, 4, 0, 1), glm::vec4(1, .1, .1, 0) };

	Vertex x1 = { glm::vec4(2,  3, -2, 1), glm::vec4(1, .1, .1, 0) };
	Vertex x2 = { glm::vec4(2,  3, 2, 1), glm::vec4(1, .1, .1, 0) };
	Vertex x3 = { glm::vec4(-2, 3, 2, 1), glm::vec4(1, .1, .1, 0) };
	Vertex x4 = { glm::vec4(-2, 3, -2, 1), glm::vec4(1, .1, .1, 0) };

	Vertex x5 = { glm::vec4(0,  2, -4, 1), glm::vec4(1, .1, .1, 0) };
	Vertex x6 = { glm::vec4(3,  2, -3, 1), glm::vec4(1, .1, .1, 0) };
	Vertex x7 = { glm::vec4(4,  2, 0, 1), glm::vec4(1, .1, .1, 0) };
	Vertex x8 = { glm::vec4(3,  2, 3, 1), glm::vec4(1, .1, .1, 0) };
	Vertex x9 = { glm::vec4(0,  2, 4, 1), glm::vec4(1, .1, .1, 0) };
	Vertex x10 = { glm::vec4(-3, 2, 3, 1), glm::vec4(1, .1, .1, 0) };
	Vertex x11 = { glm::vec4(-4, 2, 0, 1), glm::vec4(1, .1, .1, 0) };
	Vertex x12 = { glm::vec4(-3, 2, -3, 1), glm::vec4(1, .1, .1, 0) };

	Vertex x13 = { glm::vec4(2,  0, -4.5, 1), glm::vec4(1, .1, .1, 0) };
	Vertex x14 = { glm::vec4(3,  0, -3, 1), glm::vec4(1, .1, .1, 0) };
	Vertex x15 = { glm::vec4(4.5,  0, -2, 1), glm::vec4(1, .1, .1, 0) };
	Vertex x16 = { glm::vec4(4.5,  0, 2, 1), glm::vec4(1, .1, .1, 0) };
	Vertex x17 = { glm::vec4(3,  0, 3, 1), glm::vec4(1, .1, .1, 0) };
	Vertex x18 = { glm::vec4(2,  0, 4.5, 1), glm::vec4(1, .1, .1, 0) };
	Vertex x19 = { glm::vec4(-2,  0, 4.5, 1), glm::vec4(1, .1, .1, 0) };
	Vertex x20 = { glm::vec4(-3,  0, 3, 1), glm::vec4(1, .1, .1, 0) };
	Vertex x21 = { glm::vec4(-4.5,  0, 2, 1), glm::vec4(1, .1, .1, 0) };
	Vertex x22 = { glm::vec4(-4.5,  0, -2, 1), glm::vec4(1, .1, .1, 0) };
	Vertex x23 = { glm::vec4(-3,  0, -3, 1), glm::vec4(1, .1, .1, 0) };
	Vertex x24 = { glm::vec4(-2,  0, -4.5, 1), glm::vec4(1, .1, .1, 0) };

	Vertex x25 = { glm::vec4(0,  -2, -4, 1), glm::vec4(1, .1, .1, 0) };
	Vertex x26 = { glm::vec4(3,  -2, -3, 1), glm::vec4(1, .1, .1, 0) };
	Vertex x27 = { glm::vec4(4,  -2, 0, 1), glm::vec4(1, .1, .1, 0) };
	Vertex x28 = { glm::vec4(3,  -2, 3, 1), glm::vec4(1, .1, .1, 0) };
	Vertex x29 = { glm::vec4(0,  -2, 4, 1), glm::vec4(1, .1, .1, 0) };
	Vertex x30 = { glm::vec4(-3, -2, 3, 1), glm::vec4(1, .1, .1, 0) };
	Vertex x31 = { glm::vec4(-4, -2, 0, 1), glm::vec4(1, .1, .1, 0) };
	Vertex x32 = { glm::vec4(-3, -2, -3, 1), glm::vec4(1, .1, .1, 0) };

	Vertex x33 = { glm::vec4(2,  -3, -2, 1), glm::vec4(1, .1, .1, 0) };
	Vertex x34 = { glm::vec4(2,  -3, 2, 1), glm::vec4(1, .1, .1, 0) };
	Vertex x35 = { glm::vec4(-2, -3, 2, 1), glm::vec4(1, .1, .1, 0) };
	Vertex x36 = { glm::vec4(-2, -3, -2, 1), glm::vec4(1, .1, .1, 0) };

	Vertex x37 = { glm::vec4(0, -4, 0, 1), glm::vec4(1, .1, .1, 0) };


	std::vector<Vertex>verts = {
							x0,
						x1,x2,x3,x4,
				x5,x6,x7,x8,x9,x10,x11,x12,
		x13,x14,x15,x16,x17,x18,x19,x20,x21,x22,x23,x24,
				x25,x26,x27,x28,x29,x30,x31,x32,
					x33,x34,x35,x36,
							x37
	};
	std::vector<unsigned int>indices =
	{
		0,1,2,
		0,2,3,
		0,3,4,
		0,4,1,

		1,7,6,
		1,6,5,
		1,5,4,
		4,5,12,
		4,12,11,
		4,11,3,
		3,11,10,
		3,10,9,
		3,9,2,
		2,9,8,
		2,8,7,


		5,13,24,
		12,24,23,
		12,23,22,
		11,22,21,
		10,21,20,
		10,20,19,
		9,19,18,
		8,18,17,
		8,17,16,
		7,16,15,
		6,15,14,
		6,14,13,

		25,13,24,
		32,24,23,
		32,23,22,
		31,22,21,
		30,21,20,
		30,20,19,
		29,19,18,
		28,18,17,
		28,17,16,
		27,16,15,
		26,15,14,
		26,14,13,


		33,27,26,
		33,26,25,
		33,25,36,
		36,25,32,
		36,32,31,
		36,31,35,
		35,31,30,
		35,10,29,
		35,29,34,
		34,29,28,
		34,28,27,

		37,33,34,
		37,34,35,
		37,35,36,
		37,36,33,
	};

	static_ball_mesh->initialize(verts, indices);
	static_ball_mesh->Create_Buffers();
}

void RenderGeoApp::generateCube()
{

	Vertex x0 = { glm::vec4(0,0,0,1),glm::vec4(1,0,0,1) };
	Vertex x1 = { glm::vec4(1,0,0,1),glm::vec4(1,0,0,1) };
	Vertex x2 = { glm::vec4(1,-1,0,1),glm::vec4(1,0,0,1) };
	Vertex x3 = { glm::vec4(0,-1,0,1),glm::vec4(1,0,0,1) };
	//defines positions and color of points
	Vertex x4 = { glm::vec4(0,0,-1,1),glm::vec4(1,0,0,1) };
	Vertex x5 = { glm::vec4(1,0,-1,1),glm::vec4(1,0,0,1) };
	Vertex x6 = { glm::vec4(1,-1,-1,1),glm::vec4(1,0,0,1) };
	Vertex x7 = { glm::vec4(0,-1,-1,1),glm::vec4(1,0,0,1) };

	std::vector<Vertex> verts{ x0,x1,x2,x3,x4,x5,x6,x7 };
	std::vector<unsigned int>indices = { //how the points are connected to make triangles
		0,1,2, 0,3,2, 0,1,5, 0,4,5, 0,4,7, 0,3,7, 
		6,2,3, 6,7,3, 6,5,1, 6,2,1, 6,5,4, 6,7,4 };

	cube_mesh->initialize(verts, indices);
	cube_mesh->Create_Buffers();
}

void RenderGeoApp::generatePlane()
{
	Vertex x0 = { vec4(0,0,0,1), vec4(1,0,0,1) };
	Vertex x1 = { vec4(1,0,0,1), vec4(1,0,0,1) };
	Vertex x2 = { vec4(1,0,-1,1), vec4(1,0,0,1) };
	Vertex x3 = { vec4(0,0,-1,1), vec4(1,0,0,1) };

	std::vector<Vertex> vert = { x0,x1,x2,x3 };
	std::vector<unsigned int> indices = { 0,1,2, 0,2,3 };

	plane_mesh->initialize(vert, indices);
	plane_mesh->Create_Buffers();
}

void RenderGeoApp::startup()
{
	_shader = new Shader();
	_shader->load("vsSource.vert", GL_VERTEX_SHADER);
	_shader->load("fsSource.frag", GL_FRAGMENT_SHADER);

	_shader->attach();
	_shader->unbind();

	TriangleSphere();
	generateCube();
	generatePlane();

	std::vector<vec4> halfcircley = generateHalfCircleY(3, 20);//makes half circle
	std::vector<vec4> rotatey = rotatePointsY(halfcircley, 20);//rotates points in half circle
	std::vector<Vertex> vertsy;
	for (auto p : rotatey)
		vertsy.push_back(Vertex{ p, glm::normalize(p) });

	ball_mesh->initialize(vertsy, generateIndices(20,20));//makes indices for sphere
	ball_mesh->Create_Buffers();
}

void RenderGeoApp::update(float delta)
{
	cam->update(delta);
}

void RenderGeoApp::shutdown()
{
}

void RenderGeoApp::draw()
{
	glClearColor(1.f, 1.f, 1.f, 0.f);
	glEnable(GL_DEPTH_TEST);
	
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	glLineWidth(1.0f);
	glPointSize(4.0f);

	_shader->bind();
	glm::mat4 view = glm::lookAt(glm::vec3(10, 10, 10), glm::vec3(0), glm::vec3(0, 1, 0));
	mat4 projection = glm::perspective(quarter_pi<float>(), 16 / 9.f, 0.1f, 1000.f);
	mat4 mvp = projection * view * glm::scale(vec3(3, 3, 3)) * glm::translate(vec3(0, 0, -3));
	_shader->bindUniform("projectionViewWorldMatrix", mvp);
	_shader->bindUniform("time", glfwGetTime());
	cube_mesh->Draw(GL_TRIANGLES);

	mvp = projection * view;
	_shader->bindUniform("projectionViewWorldMatrix", mvp);
	_shader->bindUniform("time", glfwGetTime());
	ball_mesh->Draw(GL_TRIANGLE_STRIP);

	mvp = projection * view * glm::scale(vec3(5,5,5)) * glm::translate(vec3(-3,0,0));
	_shader->bindUniform("projectionViewWorldMatrix", mvp);
	_shader->bindUniform("time", glfwGetTime());
	plane_mesh->Draw(GL_TRIANGLES);

	mvp = projection * view * glm::scale(vec3(.5, .5, .5)) * glm::translate(vec3(0, 0, 14));
	_shader->bindUniform("projectionViewWorldMatrix", mvp);
	_shader->bindUniform("time", glfwGetTime());
	static_ball_mesh->Draw(GL_TRIANGLES);

	glUseProgram(0);
	
}
 