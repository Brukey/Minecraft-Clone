#pragma once

#include <stdint.h>
#include <vector>

namespace Minecraft {

	enum Block : uint32_t {Air = 0, Grass, Dirt, Stone};

	struct BlockData {
		BlockData(Block type) : type(type), solid(true), meshBlock(true) {}
		Block type;
		bool solid;
		bool meshBlock;
		// texture
		// transparent
	};

	class BlockRegistry {
	public:
		static void Initialize();
		static const BlockData& GetBlockData(const Block& type);
	};
}