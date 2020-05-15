
#include "ChunkHandler.h"














std::vector<chunk *> chunkList;
std::vector<Mesh *> meshList;






void generateChunk(glm::vec3 position)
{
	std::stringstream name;
	name << "./chunks/" << std::to_string(int(position.x)) << "-" << std::to_string(int(position.y)) << "-" << std::to_string(int(position.z)) << ".txt";
	//chunk* Chunk = new chunk(position);
	std::ofstream chunkData(name.str());


	for (int i = 0; i < CHUNK_SIZE; i++)
	{
		for (int j = 0; j < CHUNK_SIZE; j++)
		{
			for (int k = 0; k < CHUNK_SIZE; k++)
			{
				chunkData << "0" << std::to_string(1);
				
			}
		}
	}
	chunkData.close();


}

void loadChunk(glm::vec3 position)
{

	chunk* Chunk = new chunk(position);
	std::stringstream name;
	name << "./chunks/" << std::to_string(int(position.x)) << "-" << std::to_string(int(position.y)) << "-" << std::to_string(int(position.z)) << ".txt";
	std::ifstream chunkData(name.str());
	std::string data;
	std::getline(chunkData, data);
	int len = data.length();
	int counter = 0;
	std::cout << data[0] << data[1] << std::endl;
	std::stringstream temp;
	for (int i = 0; i < CHUNK_SIZE; i++)
	{
		for (int j = 0; j < CHUNK_SIZE; j++)
		{
			for (int k = 0; k < CHUNK_SIZE; k++)
			{
				
				temp << data[counter] << data[counter + 1];
				int value;
				temp >> value;
				Chunk->chunkData[i][j][k] = value;
				counter=+2;

			}
		}
	}
	chunkData.close();
	//Chunk->createMesh
	//chunkList.push_back(Chunk);
	//return Chunk;

}


void updateChunks()
{
	for (auto & i : chunkList)
	{
		i->createMesh();
		//Mesh mesh(Chunk->vertices, Chunk->texCoords);
	}



}


void unloadChunk(chunk toUnload)
{
	return;
}