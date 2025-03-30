#pragma once

#include "SoLoud.h"

namespace fdm::SoLoud
{
	class AudioCollider;
	class AudioAttenuator;
	class AudioSource;
	class AudioSourceInstance3dData
	{
	public:
		AudioSourceInstance3dData()
		{
			reinterpret_cast<void(__thiscall*)(SoLoud::AudioSourceInstance3dData * self)>(getFuncAddr((int)Func::SoLoud::AudioSourceInstance3dData::AudioSourceInstance3dData))(this);
		}
		void init(SoLoud::AudioSource& aSource)
		{
			return reinterpret_cast<void(__thiscall*)(SoLoud::AudioSourceInstance3dData * self, SoLoud::AudioSource&)>(getFuncAddr((int)Func::SoLoud::AudioSourceInstance3dData::init))(this, aSource);
		}

		// 3d position
		float m3dPosition[3];
		// 3d velocity
		float m3dVelocity[3];
		// 3d cone direction
		/*
		float m3dConeDirection[3];
		// 3d cone inner angle
		float m3dConeInnerAngle;
		// 3d cone outer angle
		float m3dConeOuterAngle;
		// 3d cone outer volume multiplier
		float m3dConeOuterVolume;
		*/
		// 3d min distance
		float m3dMinDistance;
		// 3d max distance
		float m3dMaxDistance;
		// 3d attenuation rolloff factor
		float m3dAttenuationRolloff;
		// 3d attenuation model
		unsigned int m3dAttenuationModel;
		// 3d doppler factor
		float m3dDopplerFactor;
		// Pointer to a custom audio collider object
		AudioCollider* mCollider;
		// Pointer to a custom audio attenuator object
		AudioAttenuator* mAttenuator;
		// User data related to audio collider
		int mColliderData;

		// Doppler sample rate multiplier
		float mDopplerValue;
		// Overall 3d volume
		float m3dVolume;
		// Channel volume
		float mChannelVolume[MAX_CHANNELS];
		// Copy of flags
		unsigned int mFlags;
		// Latest handle for this voice
		handle mHandle;
	};
}
