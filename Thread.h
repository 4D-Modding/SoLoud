#pragma once

#include "SoLoud.h"

namespace fdm::SoLoud
{
	namespace Thread
	{
		inline void* createMutex()
		{
			return reinterpret_cast<void* (__fastcall*)()>(getFuncAddr((int)Func::SoLoud::Thread::createMutex))();
		}
		inline void destroyMutex(void* mutex)
		{
			return reinterpret_cast<void (__fastcall*)(void*)>(getFuncAddr((int)Func::SoLoud::Thread::destroyMutex))(mutex);
		}
		inline void lockMutex(void* mutex)
		{
			return reinterpret_cast<void (__fastcall*)(void*)>(getFuncAddr((int)Func::SoLoud::Thread::lockMutex))(mutex);
		}
		inline void unlockMutex(void* mutex)
		{
			return reinterpret_cast<void (__fastcall*)(void*)>(getFuncAddr((int)Func::SoLoud::Thread::unlockMutex))(mutex);
		}
	}
}
