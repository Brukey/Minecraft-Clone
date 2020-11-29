#include "World.h"
#include "meshgenerator/MeshBuilder.h"
#include <renderer/RenderCommand.h>


namespace Minecraft {

	void World::Render() {
		for (Chunk& chunk : loadedChunks) {
			if (chunk.IsDirty()) {
				// generate mesh
				MeshBuilder::Generate(*this, chunk);
			}
			
			// bind textures
			const auto& textureSlots = chunk.GetTextureSlots();
			for (uint32_t i = 0; i < textureSlots.size(); i++) {
				textureSlots[i]->Bind(i);
			}

			chunk.GetVertexArray()->Bind();
			uint32_t numIndices = chunk.GetNumMeshIndices();
			Engine::RenderCommand::DrawIndexed(numIndices);
		}
	}

	void World::LoadChunk(Chunk& chunk) {
		for (uint32_t i = 0; i < CHUNK_SIZE; i++) {
			for (uint32_t j = 0; j < CHUNK_SIZE; j++) {
				const uint32_t maxHeight = (i + j) / 3 + 2;
				for (uint32_t k = 0; k < maxHeight; k++) {
					if(k == maxHeight - 1)
						chunk.Set(Block::Grass, i, k, j);
					else if(k > maxHeight - 4)
						chunk.Set(Block::Dirt, i, k, j);
					else
						chunk.Set(Block::Stone, i, k, j);
				}
			}
		}
		loadedChunks.push_back(chunk);
	}

	void World::Load() {
		// setup render data
		for (int32_t x = 0; x < 3; x++) {
			for (int32_t z = 0; z < 3; z++) {
				Chunk chunk{ Vec3i(x, 0, -z) };
				LoadChunk(chunk);
			}
		}
	}

	Block World::GetBlock(Vec3i blockposition) const {
		Vec3i chunkPos = blockposition / CHUNK_SIZE;
	
		Vec3i inChunkPos = (blockposition + CHUNK_SIZE * 1000) % CHUNK_SIZE;
		
		if (blockposition.x < 0) {
			chunkPos.x -= 1;
		}

		if (blockposition.z < 0) {
			chunkPos.z -= 1;
		}
		if (chunkPos.y < 0) return Block::Air;
		
		for (Chunk chunk : loadedChunks) {
			if (chunk.GetChunkPosition() == chunkPos) {
				return chunk.GetBlock((uint32_t) inChunkPos.x, (uint32_t)inChunkPos.y, (uint32_t)inChunkPos.z);
			}
		}
		
		return Block::Air;
	}
}