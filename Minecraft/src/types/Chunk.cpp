#include "Chunk.h"

namespace Minecraft {


	const void Chunk::Set(Block type, uint32_t x, uint32_t y, uint32_t z) {
		ASSERT(x < CHUNK_SIZE&& y < CHUNK_SIZE && z < CHUNK_SIZE);
		m_blocks[x][y][z] = type;
		m_isDirty = true;
	}

	const Block& Chunk::GetBlock(uint32_t x, uint32_t y, uint32_t z) const {
		ASSERT(x < CHUNK_SIZE&& y < CHUNK_SIZE && z < CHUNK_SIZE);
		return m_blocks[x][y][z];
	}

	const BlockData& Chunk::GetBlockData(uint32_t x, uint32_t y, uint32_t z) const {
		ASSERT(x < CHUNK_SIZE&& y < CHUNK_SIZE && z < CHUNK_SIZE);
		return BlockRegistry::GetBlockData(m_blocks[x][y][z]);
	}


	Vec3i Chunk::TranslateChunkToWorldCoordinates(uint32_t x, uint32_t y, uint32_t z) const {
		ASSERT(x < CHUNK_SIZE&& y < CHUNK_SIZE && z < CHUNK_SIZE);
		return (m_chunkPosition * CHUNK_SIZE) + Vec3i((int32_t)x, (int32_t)y, (int32_t) z);
	}
}