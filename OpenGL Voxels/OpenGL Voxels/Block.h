#pragma once
#include <iostream>





class Block
{


private:
	int BlockID;

public:
	Block();
	~Block();
	static const int BLOCK_RENDER_SIZE = 1;
	bool isActive();
	void setActive(bool active);
private:
	bool m_active;

	enum BlockType
	{
		BlockType_Default = 0,

		BlockType_Grass,
		BlockType_Dirt,
		BlockType_Water,
		BlockType_Stone,
		BlockType_Wood,
		BlockType_Sand,

		BlockType_NumTypes,
	};

	BlockType m_blockType;



};

