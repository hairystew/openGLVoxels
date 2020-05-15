#include "chunk.h"



std::vector<Vertex> cube=
{







};

glm::vec3 indi[8] = {
	glm::vec3(0,0,0), //0
	glm::vec3(1,0,0), //1
	glm::vec3(0,1,0), //2
	glm::vec3(1,1,0), //3
	glm::vec3(0,0,1), //4
	glm::vec3(1,0,1), //5
	glm::vec3(0,1,1), //6
	glm::vec3(1,1,1), //7
};

glm::vec2 texIndi[8] = {
	glm::vec2(0,0), //top left				(0)
	glm::vec2(0,1), //bottom left			(1)
	glm::vec2(1.f / 3,0), // top third		(2)
	glm::vec2(1.f / 3,1), // bottom third	(3)
	glm::vec2(2.f / 3,0), // top 2 third	(4)
	glm::vec2(2.f / 3,1), // bottom 2 third (5)
	glm::vec2(1,0), // top right			(6)
	glm::vec2(1,1), // bottom right			(7)
};




void chunk::Draw()
{

}

void chunk::createMesh()
{

	
	//take 3D array of block IDs

	//loop through array and add face vertices and tex coords to buffer if next to air
	for (int i = 0; i < CHUNK_SIZE; i++)
	{
		for (int j = 0; j < CHUNK_SIZE; j++)
		{
			for (int k = 0; k < CHUNK_SIZE; k++)
			{
				
				//check for air on -x face
				if ((i == 0 && chunkData[i][j][k] != 0) || (i != 0 && chunkData[i - 1][j][k] == 0 && chunkData[i][j][k] != 0)) {
					vertices.push_back(indi[0] + glm::vec3(i + location.x, j + location.y, k + location.z));
					vertices.push_back(indi[6] + glm::vec3(i + location.x, j + location.y, k + location.z));
					vertices.push_back(indi[2] + glm::vec3(i + location.x, j + location.y, k + location.z));
					vertices.push_back(indi[0] + glm::vec3(i + location.x, j + location.y, k + location.z));
					vertices.push_back(indi[4] + glm::vec3(i + location.x, j + location.y, k + location.z));
					vertices.push_back(indi[6] + glm::vec3(i + location.x, j + location.y, k + location.z));
					//push tex coords
					texCoords.push_back(texIndi[3]);
					texCoords.push_back(texIndi[4]);
					texCoords.push_back(texIndi[2]);
					texCoords.push_back(texIndi[3]);
					texCoords.push_back(texIndi[5]);
					texCoords.push_back(texIndi[4]);

				}
				//check for air on +x face
				if ((i == CHUNK_SIZE - 1 && chunkData[i][j][k] != 0) || (i != CHUNK_SIZE - 1 && chunkData[i + 1][j][k] == 0 && chunkData[i][j][k] != 0)) {
					vertices.push_back(indi[1] + glm::vec3(i + location.x, j + location.y, k + location.z));
					vertices.push_back(indi[3] + glm::vec3(i + location.x, j + location.y, k + location.z));
					vertices.push_back(indi[7] + glm::vec3(i + location.x, j + location.y, k + location.z));
					vertices.push_back(indi[1] + glm::vec3(i + location.x, j + location.y, k + location.z));
					vertices.push_back(indi[7] + glm::vec3(i + location.x, j + location.y, k + location.z));
					vertices.push_back(indi[5] + glm::vec3(i + location.x, j + location.y, k + location.z));
					//push tex coords
					texCoords.push_back(texIndi[5]);
					texCoords.push_back(texIndi[4]);
					texCoords.push_back(texIndi[2]);
					texCoords.push_back(texIndi[5]);
					texCoords.push_back(texIndi[2]);
					texCoords.push_back(texIndi[3]);
				}

				
				//check for air on -y face
				if ((j == 0 && chunkData[i][j][k] != 0) || (j != 0 && chunkData[i][j - 1][k] == 0 && chunkData[i][j][k] != 0)) {
					vertices.push_back(indi[0] + glm::vec3(i + location.x, j + location.y, k + location.z));
					vertices.push_back(indi[5] + glm::vec3(i + location.x, j + location.y, k + location.z));
					vertices.push_back(indi[4] + glm::vec3(i + location.x, j + location.y, k + location.z));
					vertices.push_back(indi[0] + glm::vec3(i + location.x, j + location.y, k + location.z));
					vertices.push_back(indi[1] + glm::vec3(i + location.x, j + location.y, k + location.z));
					vertices.push_back(indi[5] + glm::vec3(i + location.x, j + location.y, k + location.z));
					//push tex coords
					texCoords.push_back(texIndi[6]);
					texCoords.push_back(texIndi[5]);
					texCoords.push_back(texIndi[7]);
					texCoords.push_back(texIndi[6]);
					texCoords.push_back(texIndi[4]);
					texCoords.push_back(texIndi[5]);
				}
				//check for air on +y face
				if ((j == CHUNK_SIZE - 1 && chunkData[i][j][k] != 0) || (j != CHUNK_SIZE - 1 && chunkData[i][j + 1][k] == 0 && chunkData[i][j][k] != 0)) {
					vertices.push_back(indi[2] + glm::vec3(i + location.x, j + location.y, k + location.z));
					vertices.push_back(indi[6] + glm::vec3(i + location.x, j + location.y, k + location.z));
					vertices.push_back(indi[7] + glm::vec3(i + location.x, j + location.y, k + location.z));
					vertices.push_back(indi[2] + glm::vec3(i + location.x, j + location.y, k + location.z));
					vertices.push_back(indi[7] + glm::vec3(i + location.x, j + location.y, k + location.z));
					vertices.push_back(indi[3] + glm::vec3(i + location.x, j + location.y, k + location.z));
					//push tex coords
					texCoords.push_back(texIndi[3]);
					texCoords.push_back(texIndi[2]);
					texCoords.push_back(texIndi[0]);
					texCoords.push_back(texIndi[3]);
					texCoords.push_back(texIndi[0]);
					texCoords.push_back(texIndi[1]);
				}
			
				//check for air on -z face
				if ((k == 0 && chunkData[i][j][k] != 0) || (k != 0 && chunkData[i][j][k - 1] == 0 && chunkData[i][j][k] != 0)) {
					vertices.push_back(indi[0] + glm::vec3(i + location.x, j + location.y, k + location.z));
					vertices.push_back(indi[2] + glm::vec3(i + location.x, j + location.y, k + location.z));
					vertices.push_back(indi[3] + glm::vec3(i + location.x, j + location.y, k + location.z));
					vertices.push_back(indi[0] + glm::vec3(i + location.x, j + location.y, k + location.z));
					vertices.push_back(indi[3] + glm::vec3(i + location.x, j + location.y, k + location.z));
					vertices.push_back(indi[1] + glm::vec3(i + location.x, j + location.y, k + location.z));
					//push tex coords
					texCoords.push_back(texIndi[5]);
					texCoords.push_back(texIndi[4]);
					texCoords.push_back(texIndi[2]);
					texCoords.push_back(texIndi[5]);
					texCoords.push_back(texIndi[2]);
					texCoords.push_back(texIndi[3]);
				}
				//check for air on +z face
				if ((k == CHUNK_SIZE - 1 && chunkData[i][j][k] != 0) || (k != CHUNK_SIZE - 1 && chunkData[i][j][k + 1] == 0 && chunkData[i][j][k] != 0)) {
					vertices.push_back(indi[4] + glm::vec3(i + location.x, j + location.y, k + location.z));
					vertices.push_back(indi[7] + glm::vec3(i + location.x, j + location.y, k + location.z));
					vertices.push_back(indi[6] + glm::vec3(i + location.x, j + location.y, k + location.z));
					vertices.push_back(indi[4] + glm::vec3(i + location.x, j + location.y, k + location.z));
					vertices.push_back(indi[5] + glm::vec3(i + location.x, j + location.y, k + location.z));
					vertices.push_back(indi[7] + glm::vec3(i + location.x, j + location.y, k + location.z));
					//push tex coords
					texCoords.push_back(texIndi[3]);
					texCoords.push_back(texIndi[4]);
					texCoords.push_back(texIndi[2]);
					texCoords.push_back(texIndi[3]);
					texCoords.push_back(texIndi[5]);
					texCoords.push_back(texIndi[4]);
				}







			}
		}
	}

	


}




void chunk::createCube(glm::vec3 pos)
{

}

chunk::chunk(glm::vec3 location)
{

	this->location = location;
	// Create the blocks
	
	for (int i = 0; i < CHUNK_SIZE; i++)
	{
		for (int j = 0; j < CHUNK_SIZE; j++)
		{
			for (int k = 0; k < CHUNK_SIZE; k++)
			{
				chunkData[i][j][k] = 1;
			}
		}
	}

	//chunkData[5][1][7] = 1;
	//chunkData[6][1][7] = 1;
	//chunkData[7][1][7] = 1;
	//chunkData[8][1][7] = 1;
	//chunkData[9][1][8] = 1;
	//chunkData[9][1][6] = 1;





}

int chunk::blocks()
{


	return int();
}


chunk::~chunk()
{
	// Delete the blocks





}
