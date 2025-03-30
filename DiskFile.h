#pragma once

#include "SoLoud.h"
#include "File.h"

namespace fdm::SoLoud
{
	class DiskFile : public SoLoud::File
	{
	public:
		FILE* mFileHandle; // 0x8
		DiskFile()
		{
			reinterpret_cast<void (__thiscall*)(SoLoud::DiskFile* self)>(getFuncAddr((int)Func::SoLoud::DiskFile::DiskFile))(this);
		}
		~DiskFile() override
		{
			reinterpret_cast<void (__thiscall*)(SoLoud::DiskFile* self)>(getFuncAddr((int)Func::SoLoud::DiskFile::destr_DiskFile))(this);
		}
		int eof() override
		{
			return reinterpret_cast<int (__thiscall*)(SoLoud::DiskFile* self)>(getFuncAddr((int)Func::SoLoud::DiskFile::eof))(this);
		}
		FILE* getFilePtr() override
		{
			return reinterpret_cast<FILE * (__thiscall*)(SoLoud::DiskFile* self)>(getFuncAddr((int)Func::SoLoud::DiskFile::getFilePtr))(this);
		}
		uint32_t length() override
		{
			return reinterpret_cast<uint32_t (__thiscall*)(SoLoud::DiskFile* self)>(getFuncAddr((int)Func::SoLoud::DiskFile::length))(this);
		}
		result open(const char* path)
		{
			return reinterpret_cast<result(__thiscall*)(SoLoud::DiskFile* self, const char*)>(getFuncAddr((int)Func::SoLoud::DiskFile::open))(this, path);
		}
		uint32_t pos() override
		{
			return reinterpret_cast<uint32_t (__thiscall*)(SoLoud::DiskFile* self)>(getFuncAddr((int)Func::SoLoud::DiskFile::pos))(this);
		}
		uint32_t read(uint8_t* aDst, uint32_t aBytes) override
		{
			return reinterpret_cast<uint32_t (__thiscall*)(SoLoud::DiskFile* self, uint8_t*, uint32_t)>(getFuncAddr((int)Func::SoLoud::DiskFile::read))(this, aDst, aBytes);
		}
		void seek(int aOffset) override
		{
			return reinterpret_cast<void (__thiscall*)(SoLoud::DiskFile* self, int)>(getFuncAddr((int)Func::SoLoud::DiskFile::seek))(this, aOffset);
		}
	};
}
