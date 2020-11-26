#pragma once

#include <stdint.h>
#include <vector>

namespace Minecraft {

	enum BlockType : uint32_t {Grass, Dirt, Stone};

	struct BlockData {
		BlockData() : solid(true) {}
		bool solid;
		// texture
		// transparent
	};

	class BlockRegistry {
	public:
		static void Initialize();
		static const BlockData& GetBlockData(const BlockType& type);
		
	};
}