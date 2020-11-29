#include "Block.h"



namespace Minecraft {

	static std::vector<BlockData> s_blockData;

	void BlockRegistry::Initialize() {
		BlockData& airBlock = s_blockData.emplace_back(Block::Air);
		airBlock.meshBlock = false;
		
		std::shared_ptr<Engine::Texture> dirt = Engine::Texture::CreateFromFile("res/textures/dirt.png");
		BlockData& grassBlock = s_blockData.emplace_back(Block::Grass);
		grassBlock.solid = true;
		grassBlock.textureAtlas.SetTexture(Engine::Texture::CreateFromFile("res/textures/grass.png"));
		grassBlock.textureAtlas.SetTexture(TextureAtlas::Side::TOP, Engine::Texture::CreateFromFile("res/textures/grass-top.png"));

		BlockData& dirtBlock = s_blockData.emplace_back(Block::Dirt);
		dirtBlock.solid = true;
		dirtBlock.textureAtlas.SetTexture(dirt);


		BlockData& stoneBlock = s_blockData.emplace_back(Block::Stone);
		stoneBlock.solid = true;
		stoneBlock.textureAtlas.SetTexture(Engine::Texture::CreateFromFile("res/textures/stone.png"));

	}

	const BlockData& BlockRegistry::GetBlockData(const Block& type) {
		return s_blockData[(uint32_t) type];
	}

	void TextureAtlas::SetTexture(std::shared_ptr<Engine::Texture> texture) {
		for (uint32_t i = 0; i < sizeof(textures) / sizeof(std::shared_ptr<Engine::Texture>); i++) {
			textures[i] = texture;
		}
	}

	void TextureAtlas::SetTexture(const Side side, std::shared_ptr<Engine::Texture> texture) {
		textures[side] = texture;
	}

	std::shared_ptr<Engine::Texture> TextureAtlas::GetTexture(Side side) {
		return textures[side];
	}

	const std::shared_ptr<Engine::Texture> TextureAtlas::GetTexture(Side side) const {
		return textures[side];
	}

}