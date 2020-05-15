#pragma once
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <fstream>
#include "chunk.h"




//inline int CHUNK_SIZE = 16;
void generateChunk(glm::vec3 position);
void loadChunk(glm::vec3 position);
void updateChunks();
