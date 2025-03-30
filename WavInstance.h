#pragma once

#include "SoLoud.h"
#include "AudioSourceInstance.h"

namespace fdm::SoLoud
{
	class Wav;
	class WavInstance : public SoLoud::AudioSourceInstance
	{
	public:
		SoLoud::Wav* mParent; // 0x1F0
		uint32_t mOffset; // 0x1F8
		uint32_t getAudio(float* aBuffer, uint32_t aSamplesToRead, uint32_t aBufferSize) override
		{
			return reinterpret_cast<uint32_t (__thiscall*)(SoLoud::WavInstance* self, float*, uint32_t, uint32_t)>(getFuncAddr((int)Func::SoLoud::WavInstance::getAudio))(this, aBuffer, aSamplesToRead, aBufferSize);
		}
		bool hasEnded() override
		{
			return reinterpret_cast<bool (__thiscall*)(SoLoud::WavInstance* self)>(getFuncAddr((int)Func::SoLoud::WavInstance::hasEnded))(this);
		}
		uint32_t rewind() override
		{
			return reinterpret_cast<uint32_t (__thiscall*)(SoLoud::WavInstance* self)>(getFuncAddr((int)Func::SoLoud::WavInstance::rewind))(this);
		}
	};
}
