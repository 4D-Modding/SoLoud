#pragma once

#include "SoLoud.h"

namespace fdm::SoLoud
{
	struct _iobuf
	{
		void* _Placeholder;
	};

	class File
	{
	public:
		virtual ~File() {}
		virtual int eof() { return 0; }
		virtual unsigned int read(uint8_t* aDst, uint32_t aBytes) { return 0; }
		virtual unsigned int length() { return 0; }
		virtual void seek(int aOffset) { }
		virtual unsigned int pos() { return 0; }
		virtual FILE* getFilePtr()
		{
			return reinterpret_cast<FILE * (__thiscall*)(SoLoud::File * self)>(getFuncAddr((int)Func::SoLoud::File::getFilePtr))(this);
		}
		virtual const uint8_t* getMemPtr()
		{
			return reinterpret_cast<const uint8_t * (__thiscall*)(SoLoud::File * self)>(getFuncAddr((int)Func::SoLoud::File::getMemPtr))(this);
		}
		uint32_t read32()
		{
			return reinterpret_cast<uint32_t (__thiscall*)(SoLoud::File* self)>(getFuncAddr((int)Func::SoLoud::File::read32))(this);
		}
	};
}
