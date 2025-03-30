#pragma once

#include "SoLoud.h"

namespace fdm::SoLoud
{
	class Filter;
	class Soloud;
	class AudioCollider;
	class AudioAttenuator;
	class AudioSourceInstance;
	class AudioSource
	{
	public:
		enum FLAGS : int
		{
			// The instances from this audio source should loop
			SHOULD_LOOP = 1,
			// Only one instance of this audio source should play at the same time
			SINGLE_INSTANCE = 2,
			// Visualization data gathering enabled. Only for busses.
			VISUALIZATION_DATA = 4,
			// Audio instances created from this source are affected by 3d processing
			PROCESS_3D = 8,
			// Audio instances created from this source have listener-relative 3d coordinates
			LISTENER_RELATIVE = 16,
			// Delay start of sound by the distance from listener
			DISTANCE_DELAY = 32,
			// If inaudible, should be killed (default)
			INAUDIBLE_KILL = 64,
			// If inaudible, should still be ticked (default = pause)
			INAUDIBLE_TICK = 128
		};
		enum ATTENUATION_MODELS : int
		{
			// No attenuation
			NO_ATTENUATION = 0,
			// Inverse distance attenuation model
			INVERSE_DISTANCE = 1,
			// Linear distance attenuation model
			LINEAR_DISTANCE = 2,
			// Exponential distance attenuation model
			EXPONENTIAL_DISTANCE = 3
		};
		// Flags. See AudioSource::FLAGS
		uint32_t mFlags;
		// Base sample rate, used to initialize instances
		float mBaseSamplerate;
		// Default volume for created instances
		float mVolume;
		// Number of channels this audio source produces
		uint32_t mChannels;
		// Sound source ID. Assigned by SoLoud the first time it's played.
		uint32_t mAudioSourceID;
		// 3d min distance
		float m3dMinDistance;
		// 3d max distance
		float m3dMaxDistance;
		// 3d attenuation rolloff factor
		float m3dAttenuationRolloff;
		// 3d attenuation model
		uint32_t m3dAttenuationModel;
		// 3d doppler factor
		float m3dDopplerFactor;
		// Filter pointer
		SoLoud::Filter* mFilter[FILTERS_PER_STREAM];
		// Pointer to the Soloud object. Needed to stop all instances in dtor.
		SoLoud::Soloud* mSoloud;
		// Pointer to a custom audio collider object
		AudioCollider* mCollider;
		// Pointer to custom attenuator object
		AudioAttenuator* mAttenuator;
		// User data related to audio collider
		int mColliderData;
		PAD(0x4);
		// When looping, start playing from this time
		time mLoopPoint;
		AudioSource()
		{
			reinterpret_cast<void (__thiscall*)(SoLoud::AudioSource* self)>(getFuncAddr((int)Func::SoLoud::AudioSource::AudioSource))(this);
		}
		// Set filter. Set to NULL to clear the filter.
		virtual void setFilter(uint32_t aFilterId, SoLoud::Filter* aFilter)
		{
			return reinterpret_cast<void (__thiscall*)(SoLoud::AudioSource* self, uint32_t, SoLoud::Filter*)>(getFuncAddr((int)Func::SoLoud::AudioSource::setFilter))(this, aFilterId, aFilter);
		}
		virtual ~AudioSource()
		{
			reinterpret_cast<void(__thiscall*)(SoLoud::AudioSource * self)>(getFuncAddr((int)Func::SoLoud::AudioSource::destr_AudioSource))(this);
		}
		// Create instance from the audio source. Called from within Soloud class.
		virtual AudioSourceInstance* createInstance() { return nullptr; };
		// Stop all instances of this audio source
		void stop()
		{
			return reinterpret_cast<void (__thiscall*)(SoLoud::AudioSource* self)>(getFuncAddr((int)Func::SoLoud::AudioSource::stop))(this);
		}

		// Set default volume for instances
		void setVolume(float aVolume)
		{
			mVolume = aVolume;
		}
		// Set the looping of the instances created from this audio source
		void setLooping(bool aLoop)
		{
			if (aLoop)
			{
				mFlags |= SHOULD_LOOP;
			}
			else
			{
				mFlags &= ~SHOULD_LOOP;
			}
		}
		// Set whether only one instance of this sound should ever be playing at the same time
		void setSingleInstance(bool aSingleInstance)
		{
			if (aSingleInstance)
			{
				mFlags |= SINGLE_INSTANCE;
			}
			else
			{
				mFlags &= ~SINGLE_INSTANCE;
			}
		}

		// Set the minimum and maximum distances for 3d audio source (closer to min distance = max vol)
		void set3dMinMaxDistance(float aMinDistance, float aMaxDistance)
		{
			m3dMinDistance = aMinDistance;
			m3dMaxDistance = aMaxDistance;
		}
		// Set attenuation model and rolloff factor for 3d audio source
		void set3dAttenuation(unsigned int aAttenuationModel, float aAttenuationRolloffFactor)
		{
			m3dAttenuationModel = aAttenuationModel;
			m3dAttenuationRolloff = aAttenuationRolloffFactor;
		}
		// Set doppler factor to reduce or enhance doppler effect, default = 1.0
		void set3dDopplerFactor(float aDopplerFactor)
		{
			m3dDopplerFactor = aDopplerFactor;
		}
		// Set the coordinates for this audio source to be relative to listener's coordinates.
		void set3dListenerRelative(bool aListenerRelative)
		{
			if (aListenerRelative)
			{
				mFlags |= LISTENER_RELATIVE;
			}
			else
			{
				mFlags &= ~LISTENER_RELATIVE;
			}
		}
		// Enable delaying the start of the sound based on the distance.
		void set3dDistanceDelay(bool aDistanceDelay)
		{
			if (aDistanceDelay)
			{
				mFlags |= DISTANCE_DELAY;
			}
			else
			{
				mFlags &= ~DISTANCE_DELAY;
			}
		}

		// Set a custom 3d audio collider. Set to NULL to disable.
		void set3dCollider(AudioCollider* aCollider, int aUserData = 0)
		{
			mCollider = aCollider;
			mColliderData = aUserData;
		}
		// Set a custom attenuator. Set to NULL to disable.
		void set3dAttenuator(AudioAttenuator* aAttenuator)
		{
			mAttenuator = aAttenuator;
		}

		// Set behavior for inaudible sounds
		void setInaudibleBehavior(bool aMustTick, bool aKill)
		{
			mFlags &= ~(AudioSource::INAUDIBLE_KILL | AudioSource::INAUDIBLE_TICK);
			if (aMustTick)
			{
				mFlags |= AudioSource::INAUDIBLE_TICK;
			}
			if (aKill)
			{
				mFlags |= AudioSource::INAUDIBLE_KILL;
			}
		}

		// Set time to jump to when looping
		void setLoopPoint(time aLoopPoint)
		{
			mLoopPoint = aLoopPoint;
		}
		// Get current loop point value
		time getLoopPoint()
		{
			return mLoopPoint;
		}
	};
}
