#pragma once

#include <stdint.h>
#include <vector>
#include <renderer/Texture.h>

namespace Minecraft {

	enum Block : uint32_t {
		Air = 0, 
		Grass, 
		Dirt, 
		Stone
	};

	class TextureAtlas {
	public:
		enum Side : uint32_t { LEFT, RIGHT, TOP, BOTTOM, FRONT, BACK };

		void SetTexture(std::shared_ptr<Engine::Texture> texture);

		void SetTexture(const Side side, std::shared_ptr<Engine::Texture> texture);
		std::shared_ptr<Engine::Texture> GetTexture(Side side);
		const std::shared_ptr<Engine::Texture> GetTexture(Side side) const;
	private:
		std::shared_ptr<Engine::Texture> textures[6];
	};

	struct BlockData {
		BlockData(Block type) : 
			type(type), solid(true), meshBlock(true) {}
		Block type;
		bool solid;
		bool meshBlock;
		TextureAtlas textureAtlas;
		// transparent
	};

	

	class BlockRegistry {
	public:
		static void Initialize();
		static const BlockData& GetBlockData(const Block& type);
	};

	
}