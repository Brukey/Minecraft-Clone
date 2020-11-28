#include "MeshBuilder.h"
#include <vector>
#include <glm/glm.hpp>
#include "Engine.h"

namespace Minecraft {

	struct Vertex {
		glm::vec3 position;
		glm::vec2 uv;
		glm::vec3 normal;
		float textureSlot;
	};

	static void CheckBlock(Chunk& chunk, uint32_t x, uint32_t y, uint32_t z, std::vector<Vertex>& vertexList, std::vector<uint32_t>& indices) {
		const BlockData& currentBlock = chunk.GetBlockData(x, y, z);
		const Vec3i worldPosition = chunk.TranslateChunkToWorldCoordinates(x, y, z);
		std::shared_ptr<Engine::Texture> texture;
		float textureSlot = 0.0f;

		if (y - 1 < CHUNK_SIZE) {
			const BlockData& bottom = chunk.GetBlockData(x, y - 1, z);
			if (!bottom.meshBlock) {
				// add bottom face
				
			}
		}
		
		if (y + 1 < CHUNK_SIZE) {
			const BlockData& top = chunk.GetBlockData(x, y + 1, z);
			if (!top.meshBlock) {
				// add top face
			}
		}
		
		if (x - 1 < CHUNK_SIZE) {
			const BlockData& left = chunk.GetBlockData(x - 1, y, z);
			if (!left.meshBlock) {
				// add left face
			}
		}
		
		if (x + 1 < CHUNK_SIZE) {
			const BlockData& right = chunk.GetBlockData(x + 1, y, z);
			if (!right.meshBlock) {
				// add right face
			}
		}

		if (z + 1 < CHUNK_SIZE) {
			const BlockData& front = chunk.GetBlockData(x, y, z + 1);
			if (!front.meshBlock) {
				// add front face
				Vertex vertices[4];
				vertices[0].position = { (float)worldPosition.x, (float)worldPosition.y, (float)worldPosition.z };
				vertices[1].position = { (float)worldPosition.x, (float)worldPosition.y + 1.0f, (float)worldPosition.z };
				vertices[2].position = { (float)worldPosition.x + 1.0f, (float)worldPosition.y, (float)worldPosition.z };
				vertices[3].position = { (float)worldPosition.x + 1.0f, (float)worldPosition.y + 1.0f, (float)worldPosition.z };

				vertices[0].uv = { 0.0f, 0.0f };
				vertices[1].uv = { 0.0f, 1.0f };
				vertices[2].uv = { 1.0f, 0.0f };
				vertices[3].uv = { 1.0f, 1.0f };

				uint32_t indexOffset = (uint32_t) vertexList.size();

				for (uint32_t i = 0; i < 4; i++) {
					vertices[i].normal = { 0.0f, 0.0f, -1.0f };
					vertices[i].textureSlot = textureSlot;
					vertexList.push_back(vertices[i]);
				}

				indices.push_back(indexOffset + 0);
				indices.push_back(indexOffset + 2);
				indices.push_back(indexOffset + 1);

				indices.push_back(indexOffset + 2);
				indices.push_back(indexOffset + 3);
				indices.push_back(indexOffset + 1);

			}
		}
		
		if (z - 1 < CHUNK_SIZE) {
			const BlockData& back = chunk.GetBlockData(x, y, z - 1);
			if (!back.meshBlock) {
				// add back face

				Vertex vertices[4];
				vertices[0].position = { (float)worldPosition.x, (float)worldPosition.y, (float)worldPosition.z - 1 };
				vertices[1].position = { (float)worldPosition.x, (float)worldPosition.y + 1.0f, (float)worldPosition.z - 1 };
				vertices[2].position = { (float)worldPosition.x + 1.0f, (float)worldPosition.y, (float)worldPosition.z - 1 };
				vertices[3].position = { (float)worldPosition.x + 1.0f, (float)worldPosition.y + 1.0f, (float)worldPosition.z - 1 };

				vertices[0].uv = { 0.0f, 0.0f };
				vertices[1].uv = { 0.0f, 1.0f };
				vertices[2].uv = { 1.0f, 0.0f };
				vertices[3].uv = { 1.0f, 1.0f };

				uint32_t indexOffset = vertexList.size();
				
				for (uint32_t i = 0; i < 4; i++) {
					vertices[i].normal = { 0.0f, 0.0f, -1.0f };
					vertices[i].textureSlot = textureSlot;
					vertexList.push_back(vertices[i]);
				}
				
				indices.push_back(indexOffset + 0);
				indices.push_back(indexOffset + 1);
				indices.push_back(indexOffset + 2);

				indices.push_back(indexOffset + 2);
				indices.push_back(indexOffset + 1);
				indices.push_back(indexOffset + 3);
			}
		}

	}

	void MeshBuilder::Generate(Chunk& chunk) {
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

		for (uint32_t x = 0; x < CHUNK_SIZE; x++) {
			for (uint32_t y = 0; y < CHUNK_SIZE; y++) {
				for (uint32_t z = 0; z < CHUNK_SIZE; z++) {
					// check if neighbours are transparent or air blocks
					// if so add face to vertex buffer

					CheckBlock(chunk, x, y, z, vertices, indices);
				}
			}
		}

		chunk.vao->Bind();
		chunk.vbo->SetBufferData(vertices.data(), sizeof(Vertex) * (uint32_t) vertices.size());
		chunk.ibo->SetBufferData(indices.data(), (uint32_t) indices.size());
		chunk.m_isDirty = false;
	}
}