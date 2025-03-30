#pragma once

#include "SoLoud.h"
#include "File.h"

namespace fdm::SoLoud
{
	class MemoryFile : public SoLoud::File
	{
	public:
		const uint8_t* mDataPtr; // 0x8
		uint32_t mDataLength; // 0x10
		uint32_t mOffset; // 0x14
		bool mDataOwned; // 0x18
		MemoryFile()
		{
			reinterpret_cast<void (__thiscall*)(SoLoud::MemoryFile* self)>(getFuncAddr((int)Func::SoLoud::MemoryFile::MemoryFile))(this);
		}
		~MemoryFile() override
		{
			reinterpret_cast<void (__thiscall*)(SoLoud::MemoryFile* self)>(getFuncAddr((int)Func::SoLoud::MemoryFile::destr_MemoryFile))(this);
		}
		int eof() override
		{
			return reinterpret_cast<int (__thiscall*)(SoLoud::MemoryFile* self)>(getFuncAddr((int)Func::SoLoud::MemoryFile::eof))(this);
		}
		const uint8_t* getMemPtr() override
		{
			return reinterpret_cast<const uint8_t* (__thiscall*)(SoLoud::MemoryFile* self)>(getFuncAddr((int)Func::SoLoud::MemoryFile::getMemPtr))(this);
		}
		uint32_t length() override
		{
			return reinterpret_cast<uint32_t (__thiscall*)(SoLoud::MemoryFile* self)>(getFuncAddr((int)Func::SoLoud::MemoryFile::length))(this);
		}
		result openFileToMem(SoLoud::File* aFile)
		{
			return reinterpret_cast<result(__thiscall*)(SoLoud::MemoryFile* self, SoLoud::File*)>(getFuncAddr((int)Func::SoLoud::MemoryFile::openFileToMem))(this, aFile);
		}
		uint32_t pos() override
		{
			return reinterpret_cast<uint32_t (__thiscall*)(SoLoud::MemoryFile* self)>(getFuncAddr((int)Func::SoLoud::MemoryFile::pos))(this);
		}
		uint32_t read(uint8_t* aDst, uint32_t aBytes) override
		{
			return reinterpret_cast<uint32_t (__thiscall*)(SoLoud::MemoryFile* self, uint8_t*, uint32_t)>(getFuncAddr((int)Func::SoLoud::MemoryFile::read))(this, aDst, aBytes);
		}
		void seek(int aOffset) override
		{
			return reinterpret_cast<void (__thiscall*)(SoLoud::MemoryFile* self, int)>(getFuncAddr((int)Func::SoLoud::MemoryFile::seek))(this, aOffset);
		}
	};
}
