#pragma once

#include "SoLoud.h"

namespace fdm::SoLoud
{
	class AlignedFloatBuffer
	{
	public:
		float* mData; // aligned pointer
		uint8_t* mBasePtr; // raw allocated pointer (for delete)
		int mFloats; // size of buffer (w/out padding)

		AlignedFloatBuffer()
		{
			reinterpret_cast<void (__thiscall*)(SoLoud::AlignedFloatBuffer* self)>(getFuncAddr((int)Func::SoLoud::AlignedFloatBuffer::AlignedFloatBuffer))(this);
		}
		~AlignedFloatBuffer()
		{
			reinterpret_cast<void (__thiscall*)(SoLoud::AlignedFloatBuffer* self)>(getFuncAddr((int)Func::SoLoud::AlignedFloatBuffer::destr_AlignedFloatBuffer))(this);
		}
	};
}
