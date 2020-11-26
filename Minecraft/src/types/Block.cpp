#include "Block.h"


namespace Minecraft {

	static std::vector<BlockData> s_blockData;

	void BlockRegistry::Initialize() {
		BlockData& airBlock = s_blockData.emplace_back(Block::Air);
		airBlock.meshBlock = false;

		BlockData& grassBlock = s_blockData.emplace_back(Block::Grass);
		grassBlock.solid = true;


		BlockData& dirtBlock = s_blockData.emplace_back(Block::Dirt);
		dirtBlock.solid = true;


		BlockData& stoneBlock = s_blockData.emplace_back(Block::Stone);
		stoneBlock.solid = true;
	}

	const BlockData& BlockRegistry::GetBlockData(const Block& type) {
		return s_blockData[(uint32_t) type];
	}
}