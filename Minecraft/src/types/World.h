#pragma once

#include <vector>
#include "Chunk.h"

namespace Minecraft {

	class World {
	public:

		void Load();

		void LoadChunk(Chunk& chunk);
		
		Block GetBlock(Vec3i blockposition) const;
		void Render();
	private:
		std::vector<Chunk> loadedChunks;
	};
}