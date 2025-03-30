#pragma once

#include "SoLoud.h"
#include "AudioSource.h"

namespace fdm::SoLoud
{
	class MemoryFile;
	class Wav : public SoLoud::AudioSource
	{
	public:
		float* mData = nullptr; // 0x98
		uint32_t mSampleCount = 0; // 0xA0
		Wav()
		{
			reinterpret_cast<void (__thiscall*)(SoLoud::Wav* self)>(getFuncAddr((int)Func::SoLoud::Wav::Wav))(this);
		}
		~Wav() override
		{
			reinterpret_cast<void (__thiscall*)(SoLoud::Wav* self)>(getFuncAddr((int)Func::SoLoud::Wav::destr_Wav))(this);
		}
		SoLoud::AudioSourceInstance* createInstance() override
		{
			return reinterpret_cast<SoLoud::AudioSourceInstance* (__thiscall*)(SoLoud::Wav* self)>(getFuncAddr((int)Func::SoLoud::Wav::createInstance))(this);
		}
		uint32_t load(const char* aFilename)
		{
			return reinterpret_cast<uint32_t (__thiscall*)(SoLoud::Wav* self, const char*)>(getFuncAddr((int)Func::SoLoud::Wav::load))(this, aFilename);
		}
		uint32_t loadflac(SoLoud::MemoryFile* aReader)
		{
			return reinterpret_cast<uint32_t (__thiscall*)(SoLoud::Wav* self, SoLoud::MemoryFile*)>(getFuncAddr((int)Func::SoLoud::Wav::loadflac))(this, aReader);
		}
		uint32_t loadmp3(SoLoud::MemoryFile* aReader)
		{
			return reinterpret_cast<uint32_t (__thiscall*)(SoLoud::Wav* self, SoLoud::MemoryFile*)>(getFuncAddr((int)Func::SoLoud::Wav::loadmp3))(this, aReader);
		}
		uint32_t loadwav(SoLoud::MemoryFile* aReader)
		{
			return reinterpret_cast<uint32_t (__thiscall*)(SoLoud::Wav* self, SoLoud::MemoryFile*)>(getFuncAddr((int)Func::SoLoud::Wav::loadwav))(this, aReader);
		}
		uint32_t testAndLoadFile(SoLoud::MemoryFile* aReader)
		{
			return reinterpret_cast<uint32_t (__thiscall*)(SoLoud::Wav* self, SoLoud::MemoryFile*)>(getFuncAddr((int)Func::SoLoud::Wav::testAndLoadFile))(this, aReader);
		}
	};
}
