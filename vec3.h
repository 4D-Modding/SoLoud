#pragma once

#include "SoLoud.h"

namespace fdm::SoLoud
{
	struct vec3
	{
		float mX; // 0x0
		float mY; // 0x4
		float mZ; // 0x8
		void normalize()
		{
			return reinterpret_cast<void (__thiscall*)(SoLoud::vec3* self)>(getFuncAddr((int)Func::SoLoud::vec3::normalize))(this);
		}
	};
}
