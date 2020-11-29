#pragma once

#include "types/Chunk.h"
#include "types/World.h"

namespace Minecraft {

	class MeshBuilder {
	public:
		static void Generate(const World& world, Chunk& chunk);
	private:
		
	};
}