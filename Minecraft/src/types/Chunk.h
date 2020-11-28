#pragma once

#include "Block.h"
#include <core/Logger.h>
#include "vec3i.h"
#include "renderer/VertexArray.h"
#include "renderer/VertexBuffer.h"
#include "renderer/IndexBuffer.h"


#define CHUNK_SIZE (16)

namespace Minecraft {

	class MeshBuilder;

	class Chunk {
	public:
		Chunk(const Vec3i& chunkPosition);

		const void Set(Block type, uint32_t x, uint32_t y, uint32_t z);

		const Block& GetBlock(uint32_t x, uint32_t y, uint32_t z) const;

		const BlockData& GetBlockData(uint32_t x, uint32_t y, uint32_t z) const;

		inline bool IsDirty() const { return m_isDirty; }

		Vec3i TranslateChunkToWorldCoordinates(uint32_t x, uint32_t y, uint32_t z) const;

		inline const std::shared_ptr<Engine::VertexArray> GetVertexArray() const { return vao; }
		inline uint32_t GetNumMeshIndices() const { return ibo->GetIndexCount(); }
	private:
		Block m_blocks[CHUNK_SIZE][CHUNK_SIZE][CHUNK_SIZE];
		bool m_isDirty = true;
		Vec3i m_chunkPosition;

		std::shared_ptr<Engine::VertexArray> vao = NULL;
		std::shared_ptr<Engine::IndexBuffer> ibo = NULL;
		std::shared_ptr<Engine::VertexBuffer> vbo = NULL;
		friend class MeshBuilder;
	};
}
