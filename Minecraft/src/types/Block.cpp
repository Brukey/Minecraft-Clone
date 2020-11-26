#include "Block.h"


namespace Minecraft {

	static std::vector<BlockData> s_blockData;

	void BlockRegistry::Initialize() {
		BlockData& grassBlock = s_blockData.emplace_back();
		grassBlock.solid = true;


		BlockData& dirtBlock = s_blockData.emplace_back();
		dirtBlock.solid = true;


		BlockData& stoneBlock = s_blockData.emplace_back();
		stoneBlock.solid = true;
	}

	const BlockData& BlockRegistry::GetBlockData(const BlockType& type) {
		return s_blockData[(uint32_t) type];
	}
}