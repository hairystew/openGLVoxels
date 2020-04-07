#pragma once
#include "Mesh.h"
#include <glm/glm.hpp>
#include <glad/glad.h>
#include <vector>


class chunk
{
public:
	glm::vec3 location;
	std::vector<Vertex> blockData;
	static const int CHUNK_SIZE = 16;
	void Draw();
	void createMesh();
	void createCube(glm::vec3 pos);
	chunk(glm::vec3 location);
	int blocks();
	int chunkData[CHUNK_SIZE][CHUNK_SIZE][CHUNK_SIZE];
	std::vector<glm::vec3> vertices;
	std::vector<glm::vec2> texCoords;


	~chunk();

private:
	enum
	{
		POSITION_VB,

		NUM_BUFFERS,

		TEXCOORD_VB
	};

	GLuint m_vertexArrayObject;
	GLuint m_vertexArrayBuffers[NUM_BUFFERS];
	unsigned int m_drawCount;


};

