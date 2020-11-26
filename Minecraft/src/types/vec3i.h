#pragma once

#include <stdint.h>

namespace Minecraft {

	struct Vec3i {
		Vec3i() : x(0), y(0), z(0) {}
		Vec3i(int32_t x, int32_t y, int32_t z) : x(x), y(y), z(z) {}
		int32_t x;
		int32_t y;
		int32_t z;

		Vec3i operator*(const int32_t value) const {
			return Vec3i{x * value, y * value, z * value};
		}

		Vec3i operator+(const Vec3i& value) const {
			return Vec3i{ x + value.x, y + value.y, z + value.z};
		}


	};
}