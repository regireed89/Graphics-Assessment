#include "LightingApp.h"
#include "gl_core_4_4.h"
#include <GLM\glm.hpp>
#include <GLM\ext.hpp>
#include "Shader.h"
#include <GLFW\glfw3.h>
using namespace glm;
using namespace std;



LightingApp::LightingApp() : m_VAO(0), m_VBO(0), m_IBO(0), m_index_count(0), m_modeMatrix(1)
{
	_shader = new Shader();
	_phongShader = new Shader();
	_blinnphongShader = new Shader();
	_camera = new Camera();
}


LightingApp::~LightingApp()
{
}

void LightingApp::generateSphere(unsigned int segments, unsigned int rings,
	unsigned int& vao, unsigned int& vbo, unsigned int& ibo,
	unsigned int& indexCount) {

	unsigned int vertCount = (segments + 1) * (rings + 2);
	indexCount = segments * (rings + 1) * 6;

	// using AIEVertex for now, but could be any struct as long as it has the correct elements
	Vertex* vertices = new Vertex[vertCount];
	unsigned int* indices = new unsigned int[indexCount];

	float ringAngle = glm::pi<float>() / (rings + 1);
	float segmentAngle = 2.0f * glm::pi<float>() / segments;

	Vertex* vertex = vertices;

	for (unsigned int ring = 0; ring < (rings + 2); ++ring) {
		float r0 = glm::sin(ring * ringAngle);
		float y0 = glm::cos(ring * ringAngle);

		for (unsigned int segment = 0; segment < (segments + 1); ++segment, ++vertex) {
			float x0 = r0 * glm::sin(segment * segmentAngle);
			float z0 = r0 * glm::cos(segment * segmentAngle);

			vertex->position = glm::vec4(x0 * 0.5f, y0 * 0.5f, z0 * 0.5f, 1);
			vertex->normal = glm::vec4(x0, y0, z0, 0);

			vertex->tangent = glm::vec4(glm::sin(segment * segmentAngle + glm::half_pi<float>()), 0, glm::cos(segment * segmentAngle + glm::half_pi<float>()), 0);

			// not a part of the AIEVertex, but this is how w generate bitangents
			vertex->bitangent = glm::vec4(glm::cross(glm::vec3(vertex->normal), glm::vec3(vertex->tangent)), 0);

			vertex->texcoord = glm::vec2(segment / (float)segments, ring / (float)(rings + 1));
		}
	}

	unsigned int index = 0;
	for (unsigned i = 0; i < (rings + 1); ++i) {
		for (unsigned j = 0; j < segments; ++j) {
			indices[index++] = i * (segments + 1) + j;
			indices[index++] = (i + 1) * (segments + 1) + j;
			indices[index++] = i * (segments + 1) + (j + 1);

			indices[index++] = (i + 1) * (segments + 1) + (j + 1);
			indices[index++] = i * (segments + 1) + (j + 1);
			indices[index++] = (i + 1) * (segments + 1) + j;
		}
	}

	// generate buffers
	glGenBuffers(1, &vbo);
	glGenBuffers(1, &ibo);

	// generate vertex array object (descriptors)
	glGenVertexArrays(1, &vao);

	// all changes will apply to this handle
	glBindVertexArray(vao);

	// set vertex buffer data
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, vertCount * sizeof(Vertex), vertices, GL_STATIC_DRAW);

	// index data
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indexCount * sizeof(unsigned int), indices, GL_STATIC_DRAW);

	// position
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), 0);

	// colors
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(sizeof(glm::vec4)));

	// normals
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 4, GL_FLOAT, GL_TRUE, sizeof(Vertex), (void*)(sizeof(glm::vec4) * 2));

	// texcoords
	glEnableVertexAttribArray(3);
	glVertexAttribPointer(3, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(sizeof(glm::vec4) * 3));

	// tangents
	glEnableVertexAttribArray(4);
	glVertexAttribPointer(4, 4, GL_FLOAT, GL_TRUE, sizeof(Vertex), (void*)(sizeof(glm::vec4) * 3 + sizeof(glm::vec2)));

	// safety
	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	delete[] indices;
	delete[] vertices;
}

void LightingApp::startup()
{
	glClearColor(1.f, 1.f, 1.f, 0.f);
	glEnable(GL_DEPTH_TEST);
	_phongShader->load("phong.vert", GL_VERTEX_SHADER);
	_phongShader->load("phong.frag", GL_FRAGMENT_SHADER);
	_phongShader->attach();
	_blinnphongShader->load("blinnphong.frag", GL_FRAGMENT_SHADER);
	_blinnphongShader->attach();

	_camera->setLookAt(vec3(10, 10, 10), vec3(0, 0, 0), vec3(0, 1, 0));

	m_directionalLight.diffuse = vec3(1);
	m_directionalLight.specular = vec3(1,0,0);
	m_ambientLight = vec3(0,0.25,0);

	m_material.diffuse = vec3(1);
	m_material.ambient = vec3(1);
	m_material.specular = vec3(1);
	m_material.specularPower = 10;

	generateSphere(100, 100, m_VAO, m_VBO, m_IBO, m_index_count);
	m_modeMatrix = glm::scale(vec3(5));

	
}

void LightingApp::update(float deltaTime)
{
	
	runTime += deltaTime;
	_camera->update(deltaTime);
	m_directionalLight.direction = normalize(vec3(sinf(runTime / 2.f), 0, cosf(runTime / 2.f)));

	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
	{
		glm::vec3 npos = glm::vec3(_camera->getWorldTransform()[3] -= _camera->getWorldTransform()[2] * mat4(0.25f));
		_camera->setPosition(npos);
	}
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
	{
		glm::vec3 nneg = glm::vec3(_camera->getWorldTransform()[3] += _camera->getWorldTransform()[2] * mat4(0.25f));
		_camera->setPosition(nneg);
	}
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
	{
		glm::vec3 npos = glm::vec3(_camera->getWorldTransform()[3] -= _camera->getWorldTransform()[0] * mat4(0.25f));
		_camera->setPosition(npos);
	}
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
	{
		glm::vec3 nneg = glm::vec3(_camera->getWorldTransform()[3] += _camera->getWorldTransform()[0] * mat4(0.25f));
		_camera->setPosition(nneg);
	}
	{
		////controls rotation of camera using mouse
		//static bool sbMouseButtonDown = false;
		//if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_2) == GLFW_PRESS)
		//{

		//	static double siPrevMouseX = 0;
		//	static double siPrevMouseY = 0;

		//	if (sbMouseButtonDown == false)
		//	{
		//		sbMouseButtonDown = true;
		//		glfwGetCursorPos(window, &siPrevMouseX, &siPrevMouseY);
		//	}
		//	double mouseX = 0, mouseY = 0;
		//	glfwGetCursorPos(window, &mouseX, &mouseY);

		//	double iDeltaX = mouseX - siPrevMouseX;
		//	double iDeltaY = mouseY - siPrevMouseY;

		//	siPrevMouseX = mouseX;
		//	siPrevMouseY = mouseY;

		//	//mat4 z = mat4(cos(iDeltaX*iDeltaY), -sin(iDeltaX*iDeltaY), 0, 0, sin(iDeltaX*iDeltaY), cos(iDeltaX*iDeltaY), 0, 0, 0, 0, 1, 0, 0, 0, 0, 1);
		//	mat4 x = mat4(1, 0, 0, 0, 0, cos(iDeltaY / 200), -sin(iDeltaY / 200), 0, 0, sin(iDeltaY / 200), cos(iDeltaY / 200), 0, 0, 0, 0, 1);
		//	mat4 y = mat4(cos(iDeltaX / 50), 0, sin(iDeltaX / 200), 0, 0, 1, 0, 0, -sin(iDeltaX / 200), 0, cos(iDeltaX / 200), 0, 0, 0, 0, 1);



		//	//auto Elevation = rotate(static_cast<float>(iDeltaX) * 1 / 800, vec3(0, 1, 0));
		//	//auto Azimuth = rotate(static_cast<float>(iDeltaY) * 1 / 800, vec3(1, 0, 0));
		//	_camera->getView() = x * y * _camera->getView();
		//	_camera->getWorldTransform() = glm::inverse(_camera->getView());
		//}
	}
	if (glfwGetKey(window, GLFW_KEY_R) == GLFW_PRESS)
	{
		_camera->setLookAt(vec3(10, 10, 10), vec3(0, 0, 0), vec3(0, 1, 0));
	}
}

void LightingApp::shutdown()
{
}

void LightingApp::draw()
{

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

	mat4 view = glm::lookAt(glm::vec3(10, 10, 10), glm::vec3(0), glm::vec3(0, 1, 0));
	mat4 projection = glm::perspective(quarter_pi<float>(), 16 / 9.f, 0.1f, 1000.f);
	mat4 model = glm::scale(vec3(8));
	mat4 mvp = projection * view * model;

	_phongShader->bind();	
	//_blinnphongShader->bind();

	int lightUniform;

	int matUniform = _phongShader->getUniform("ProjectionViewModel");
	glUniformMatrix4fv(matUniform, 1, GL_FALSE, &mvp[0][0]);

	lightUniform = _phongShader->getUniform("direction");
	glUniform3fv(lightUniform, 1, &m_directionalLight.direction[0]);

	lightUniform = _phongShader->getUniform("Id");
	glUniform3fv(lightUniform, 1, &m_directionalLight.diffuse[0]);

	lightUniform = _phongShader->getUniform("Is");
	glUniform3fv(lightUniform, 1, &m_directionalLight.specular[0]);

	lightUniform = _phongShader->getUniform("Ia");
	glUniform3fv(lightUniform, 1, &m_ambientLight[0]);

	lightUniform = _phongShader->getUniform("Ka");
	glUniform3fv(lightUniform, 1, &m_material.ambient[0]);

	lightUniform = _phongShader->getUniform("Kd");
	glUniform3fv(lightUniform, 1, &m_material.diffuse[0]);

	lightUniform = _phongShader->getUniform("Ks");
	glUniform3fv(lightUniform, 1, &m_material.specular[0]);

	lightUniform = _phongShader->getUniform("camPos");
	glUniform3fv(lightUniform, 1, &view[0][0]);

	lightUniform = _phongShader->getUniform("a");
	glUniform1f(lightUniform, m_material.specularPower);

	lightUniform = _phongShader->getUniform("V");
	glUniform3fv(lightUniform, 1, &view[0][0]);


	glBindVertexArray(m_VAO);
	glDrawElements(GL_TRIANGLES, m_index_count, GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);
	_phongShader->unbind();
	//_blinnphongShader->unbind();

	

}

