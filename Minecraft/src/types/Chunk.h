#pragma once

#include "Block.h"
#include <core/Logger.h>
#include "vec3i.h"


#define CHUNK_SIZE (16)

namespace Minecraft {

	class Chunk {
	public:

		const void Set(Block type, uint32_t x, uint32_t y, uint32_t z);

		const Block& GetBlock(uint32_t x, uint32_t y, uint32_t z) const;

		const BlockData& GetBlockData(uint32_t x, uint32_t y, uint32_t z) const;

		inline bool IsDirty() const { return m_isDirty; }

		Vec3i TranslateChunkToWorldCoordinates(uint32_t x, uint32_t y, uint32_t z) const;
	private:
		Block m_blocks[CHUNK_SIZE][CHUNK_SIZE][CHUNK_SIZE];
		bool m_isDirty = false;
		Vec3i m_chunkPosition;
	};
}
