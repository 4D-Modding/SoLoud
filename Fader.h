#pragma once

#include "SoLoud.h"

namespace fdm::SoLoud
{
	class Fader
	{
	public:
		float mFrom; // 0x0
		float mTo; // 0x4
		float mDelta; // 0x8
		PAD(0x4);
		double mTime; // 0x10
		double mStartTime; // 0x18
		double mEndTime; // 0x20
		float mCurrent; // 0x28
		int mActive; // 0x2C
		Fader()
		{
			reinterpret_cast<void (__thiscall*)(SoLoud::Fader* self)>(getFuncAddr((int)Func::SoLoud::Fader::Fader))(this);
		}
		float get(double aCurrentTime)
		{
			return reinterpret_cast<float (__thiscall*)(SoLoud::Fader* self, double)>(getFuncAddr((int)Func::SoLoud::Fader::get))(this, aCurrentTime);
		}
	};
}
