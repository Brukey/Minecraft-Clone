#include "MeshBuilder.h"
#include <vector>
#include <glm/glm.hpp>
#include "Engine.h"
#include "types/World.h"
#include <core/Logger.h>
#include "types/Block.h"

namespace Minecraft {

	struct Vertex {
		glm::vec3 position;
		glm::vec2 uv;
		glm::vec3 normal;
		float textureSlot;
	};

	static float GetTextureSlot(std::vector<std::shared_ptr<Engine::Texture>>& textureSlots, const std::shared_ptr<Engine::Texture> texture) {
		uint32_t idx = 0;
		for (auto tex : textureSlots) {
			if (tex.get() == texture.get()) {
				return (float) idx;
			}
			idx++;
		}
		textureSlots.push_back(texture);
		return (float) textureSlots.size() - 1;
	}

	static void CheckBlock(const World& world, Chunk& chunk, uint32_t x, uint32_t y, uint32_t z, std::vector<Vertex>& vertexList, std::vector<uint32_t>& indices, std::vector<std::shared_ptr<Engine::Texture>>& textureSlots) {

		const BlockData& currentBlock = chunk.GetBlockData(x, y, z);
		if (currentBlock.type == Block::Air)
			return;

		const Vec3i worldPosition = chunk.TranslateChunkToWorldCoordinates(x, y, z);
				

		Vec3i leftBlockPos = Vec3i{worldPosition.x - 1, worldPosition.y, worldPosition.z};
		Vec3i rightBlockPos = Vec3i{ worldPosition.x + 1, worldPosition.y, worldPosition.z };
		Vec3i topBlockPos = Vec3i{ worldPosition.x, worldPosition.y + 1, worldPosition.z };
		Vec3i bottomBlockPos = Vec3i{ worldPosition.x, worldPosition.y - 1, worldPosition.z };
		Vec3i frontBlockPos = Vec3i{ worldPosition.x, worldPosition.y, worldPosition.z + 1};
		Vec3i backBlockPos = Vec3i{ worldPosition.x, worldPosition.y, worldPosition.z - 1 };

		Block lBlock = world.GetBlock(leftBlockPos);
		Block rBlock = world.GetBlock(rightBlockPos);
		
		Block tBlock = world.GetBlock(topBlockPos);
		Block bBlock = world.GetBlock(bottomBlockPos);
		
		Block fBlock = world.GetBlock(frontBlockPos);
		Block backBlock = world.GetBlock(backBlockPos);

		uint32_t facesAdded = 0;
		uint32_t prevOffset = (uint32_t) vertexList.size();

		const float left = (float) worldPosition.x;
		const float right = (float)worldPosition.x + 1.0f;
		const float top = (float)worldPosition.y + 1.0f;
		const float bottom = (float)worldPosition.y;
		const float front = (float)worldPosition.z;
		const float back = (float)worldPosition.z - 1;

		if (!BlockRegistry::GetBlockData(lBlock).meshBlock) {
			// add left face to mesh
			Vertex vertices[4];

			vertices[0].position = {left, bottom, back};
			vertices[1].position = { left, bottom, front };
			vertices[2].position = { left, top, front };
			vertices[3].position = { left, top, back };
			
			vertices[0].uv = { 0.0f, 0.0f };
			vertices[1].uv = { 1.0f, 0.0f };
			vertices[2].uv = { 1.0f, 1.0f };
			vertices[3].uv = { 0.0f, 1.0f };
			
			float textureSlot = GetTextureSlot(textureSlots, currentBlock.textureAtlas.GetTexture(TextureAtlas::Side::LEFT));
			for (uint32_t i = 0; i < 4; i++) {
				vertices[i].normal = {-1.0f, 0.0f, 0.0f};
				vertices[i].textureSlot = textureSlot;
				vertexList.push_back(vertices[i]);
			}
			facesAdded++;
		}

		if (!BlockRegistry::GetBlockData(rBlock).meshBlock) {
			// add right face to mesh
			Vertex vertices[4];

			vertices[0].position = { right, bottom, front };
			vertices[1].position = { right, bottom, back };
			vertices[2].position = { right, top, back };
			vertices[3].position = { right, top, front };

			vertices[0].uv = { 0.0f, 0.0f };
			vertices[1].uv = { 1.0f, 0.0f };
			vertices[2].uv = { 1.0f, 1.0f };
			vertices[3].uv = { 0.0f, 1.0f };

			float textureSlot = GetTextureSlot(textureSlots, currentBlock.textureAtlas.GetTexture(TextureAtlas::Side::RIGHT));
			for (uint32_t i = 0; i < 4; i++) {
				vertices[i].normal = { 1.0f, 0.0f, 0.0f };
				vertices[i].textureSlot = textureSlot;
				vertexList.push_back(vertices[i]);
			}
			facesAdded++;
		}

		if (!BlockRegistry::GetBlockData(tBlock).meshBlock) {
			// add top face to mesh
			Vertex vertices[4];

			vertices[0].position = { left, top, front };
			vertices[1].position = { right, top, front };
			vertices[2].position = { right, top, back };
			vertices[3].position = { left, top, back };

			vertices[0].uv = { 0.0f, 0.0f };
			vertices[1].uv = { 1.0f, 0.0f };
			vertices[2].uv = { 1.0f, 1.0f };
			vertices[3].uv = { 0.0f, 1.0f };

			float textureSlot = GetTextureSlot(textureSlots, currentBlock.textureAtlas.GetTexture(TextureAtlas::Side::TOP));
			for (uint32_t i = 0; i < 4; i++) {
				vertices[i].normal = { 0.0f, 1.0f, 0.0f };
				vertices[i].textureSlot = textureSlot;
				vertexList.push_back(vertices[i]);
			}
			facesAdded++;
		}

		if (!BlockRegistry::GetBlockData(bBlock).meshBlock) {
			// add bottom face to mesh
			Vertex vertices[4];

			vertices[0].position = { right, bottom, front };
			vertices[1].position = { left, bottom, front };
			vertices[2].position = { left, bottom, back };
			vertices[3].position = { right, bottom, back };

			vertices[0].uv = { 0.0f, 0.0f };
			vertices[1].uv = { 1.0f, 0.0f };
			vertices[2].uv = { 1.0f, 1.0f };
			vertices[3].uv = { 0.0f, 1.0f };

			float textureSlot = GetTextureSlot(textureSlots, currentBlock.textureAtlas.GetTexture(TextureAtlas::Side::BOTTOM));
			for (uint32_t i = 0; i < 4; i++) {
				vertices[i].normal = { 0.0f, -1.0f, 0.0f };
				vertices[i].textureSlot = textureSlot;
				vertexList.push_back(vertices[i]);
			}
			facesAdded++;
		}

		if (!BlockRegistry::GetBlockData(fBlock).meshBlock) {
			// add front face to mesh
			Vertex vertices[4];

			vertices[0].position = { left, bottom, front };
			vertices[1].position = { right, bottom, front };
			vertices[2].position = { right, top, front };
			vertices[3].position = { left, top, front };

			vertices[0].uv = { 0.0f, 0.0f };
			vertices[1].uv = { 1.0f, 0.0f };
			vertices[2].uv = { 1.0f, 1.0f };
			vertices[3].uv = { 0.0f, 1.0f };

			float textureSlot = GetTextureSlot(textureSlots, currentBlock.textureAtlas.GetTexture(TextureAtlas::Side::FRONT));
			for (uint32_t i = 0; i < 4; i++) {
				vertices[i].normal = { 0.0f, 0.0f, 1.0f };
				vertices[i].textureSlot = textureSlot;
				vertexList.push_back(vertices[i]);
			}
			facesAdded++;
		}

		if (!BlockRegistry::GetBlockData(backBlock).meshBlock) {
			// add back face to mesh
			Vertex vertices[4];

			vertices[0].position = { right, bottom, back };
			vertices[1].position = { left, bottom, back };
			vertices[2].position = { left, top, back };
			vertices[3].position = { right, top, back };

			vertices[0].uv = { 0.0f, 0.0f };
			vertices[1].uv = { 1.0f, 0.0f };
			vertices[2].uv = { 1.0f, 1.0f };
			vertices[3].uv = { 0.0f, 1.0f };

			float textureSlot = GetTextureSlot(textureSlots, currentBlock.textureAtlas.GetTexture(TextureAtlas::Side::BACK));
			for (uint32_t i = 0; i < 4; i++) {
				vertices[i].normal = { 0.0f, 0.0f, -1.0f };
				vertices[i].textureSlot = textureSlot;
				vertexList.push_back(vertices[i]);
			}
			facesAdded++;
		}

		for (uint32_t i = 0; i < facesAdded; i++) {
			indices.push_back(prevOffset + 0);
			indices.push_back(prevOffset + 1);
			indices.push_back(prevOffset + 2);

			indices.push_back(prevOffset + 0);
			indices.push_back(prevOffset + 2);
			indices.push_back(prevOffset + 3);
			prevOffset += 4;
		}


	}

	void MeshBuilder::Generate(const World& world, Chunk& chunk) {
		if (!chunk.vao) {
			chunk.vao = Engine::VertexArray::Create();
			chunk.vbo = Engine::VertexBuffer::Create();
			chunk.ibo = Engine::IndexBuffer::Create();

			chunk.vao->Bind();
			chunk.ibo->Bind();
			chunk.vbo->Bind();

			Engine::VertexBufferLayout layout;
			layout.PushFloat(0, 3); // position
			layout.PushFloat(1, 2); // uvs
			layout.PushFloat(2, 3); // normal
			layout.PushFloat(3, 1); // texture slot
			chunk.vbo->SetLayout(layout);
		}
		else {
			chunk.vbo->Bind();
			chunk.ibo->Bind();
		}

		std::vector<Vertex> vertices;
		std::vector<uint32_t> indices;
		chunk.textureSlots.clear();

		for (uint32_t x = 0; x < CHUNK_SIZE; x++) {
			for (uint32_t y = 0; y < CHUNK_SIZE; y++) {
				for (uint32_t z = 0; z < CHUNK_SIZE; z++) {
					// check if neighbours are transparent or air blocks
					// if so add face to vertex buffer

					CheckBlock(world, chunk, x, y, z, vertices, indices, chunk.textureSlots);
				}
			}
		}


		chunk.vao->Bind();
		chunk.vbo->SetBufferData(vertices.data(), sizeof(Vertex) * (uint32_t) vertices.size());
		chunk.ibo->SetBufferData(indices.data(), (uint32_t) indices.size());
		chunk.m_isDirty = false;
	}
}