#ifndef MESH_H
#define MESH_H



#include <glm/glm.hpp>
#include <glad/glad.h>
#include <vector>
#include "Block.h"



class Vertex
{
public:
	Vertex(const glm::vec3& pos, const glm::vec2& texCoord)
	{
		this->pos = pos;
		this->texCoord = texCoord;
	}

	inline glm::vec3* getPos() { return &pos; }
	inline glm::vec2* getTexCoord() { return &texCoord; }
	inline void translateVertex(Vertex* vertices, unsigned int numVertices, glm::vec3 trans) {
		for (int i = 0; i < numVertices; i++)
			*vertices[i].getPos() =+ trans;
	}

protected:
private:
	glm::vec3 pos;
	glm::vec2 texCoord;

};




class Mesh
{
public:
	Mesh(std::vector<glm::vec3> vertices, std::vector<glm::vec2> texCoords);
	void Draw();


	virtual ~Mesh();
private:
	Mesh(const Mesh& other);
	void operator=(const Mesh& other);

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

#endif // MESH_H