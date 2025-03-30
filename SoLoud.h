#pragma once

#include <stdint.h>

// Maximum number of filters per stream
#define FILTERS_PER_STREAM 8
// Number of samples to process on one go
#define SAMPLE_GRANULARITY 512
// Maximum number of concurrent voices (hard limit is 4095)
#define VOICE_COUNT 1024
// Use linear resampler
#define RESAMPLER_LINEAR
// 1)mono, 2)stereo 4)quad 6)5.1 8)7.1
#define MAX_CHANNELS 8

namespace fdm::SoLoud
{
	typedef uint32_t result;
	typedef uint32_t handle;
	typedef double time;
}

#include "../4dm.h"
#include "miniaudioTypes.h"
#include "AudioCollider.h"
#include "AudioAttenuator.h"
#include "File.h"
#include "MemoryFile.h"
#include "DiskFile.h"
#include "Thread.h"
#include "vec3.h"
#include "Fader.h"
#include "Filter.h"
#include "AlignedFloatBuffer.h"
#include "AudioSource.h"
#include "AudioSourceInstance.h"
#include "AudioSourceInstance3dData.h"
#include "Wav.h"
#include "WavInstance.h"

namespace fdm
{
	namespace SoLoud
	{
		class Soloud
		{
		public:
			using BackendCleanupFunc = std::add_pointer<void(SoLoud::Soloud* soloud)>::type;
			enum BACKENDS : int
			{
				AUTO = 0,
				SDL1 = 1,
				SDL2 = 2,
				PORTAUDIO = 3,
				WINMM = 4,
				XAUDIO2 = 5,
				WASAPI = 6,
				ALSA = 7,
				JACK = 8,
				OSS = 9,
				OPENAL = 10,
				COREAUDIO = 11,
				OPENSLES = 12,
				VITA_HOMEBREW = 13,
				MINIAUDIO = 14,
				NOSOUND = 15,
				NULLDRIVER = 16,
				BACKEND_MAX = 17,
			};
			enum FLAGS : int
			{
				CLIP_ROUNDOFF = 1,
				ENABLE_VISUALIZATION = 2,
				LEFT_HANDED_3D = 4,
				NO_FPU_REGISTER_CHANGE = 8,
			};
			void* mBackendData; // 0x0
			void* mAudioThreadMutex; // 0x8
			bool mInsideAudioThreadMutex; // 0x10
			PAD(0x7);
			BackendCleanupFunc mBackendCleanupFunc; // 0x18
			uint32_t mMaxActiveVoices; // 0x20
			uint32_t mHighestVoice; // 0x24
			SoLoud::AlignedFloatBuffer mScratch; // 0x28
			uint32_t mScratchSize; // 0x40
			uint32_t mScratchNeeded; // 0x44
			SoLoud::AlignedFloatBuffer mOutputScratch; // 0x48
			SoLoud::AlignedFloatBuffer* mResampleData; // 0x60
			SoLoud::AudioSourceInstance** mResampleDataOwner; // 0x68
			SoLoud::AudioSourceInstance* mVoice[1024]; // 0x70
			uint32_t mSamplerate; // 0x2070
			uint32_t mChannels; // 0x2074
			uint32_t mBackendID; // 0x2078
			PAD(0x4);
			const char* mBackendString; // 0x2080
			uint32_t mBufferSize; // 0x2088
			uint32_t mFlags; // 0x208C
			float mGlobalVolume; // 0x2090
			float mPostClipScaler; // 0x2094
			uint32_t mPlayIndex; // 0x2098
			uint32_t mAudioSourceID; // 0x209C
			SoLoud::Fader mGlobalVolumeFader; // 0x20A0
			double mStreamTime; // 0x20D0
			double mLastClockedTime; // 0x20D8
			SoLoud::Filter* mFilter[8]; // 0x20E0
			SoLoud::FilterInstance* mFilterInstance[8]; // 0x2120
			float mVisualizationChannelVolume[8]; // 0x2160
			float mVisualizationWaveData[256]; // 0x2180
			float mFFTData[256]; // 0x2580
			float mWaveData[256]; // 0x2980
			float m3dPosition[3]; // 0x2D80
			float m3dAt[3]; // 0x2D8C
			float m3dUp[3]; // 0x2D98
			float m3dVelocity[3]; // 0x2DA4
			float m3dSoundSpeed; // 0x2DB0
			float m3dSpeakerPosition[24]; // 0x2DB4
			PAD(0x4);
			SoLoud::AudioSourceInstance3dData m3dData[1024]; // 0x2E18
			uint32_t** mVoiceGroup; // 0x20E18
			uint32_t mVoiceGroupCount; // 0x20E20
			uint32_t mActiveVoice[1024]; // 0x20E24
			uint32_t mActiveVoiceCount; // 0x21E24
			bool mActiveVoiceDirty; // 0x21E28
			uint32_t play(SoLoud::AudioSource& aSound, float aVolume, float aPan, bool aPaused, uint32_t aBus)
			{
				return reinterpret_cast<uint32_t(__thiscall*)(SoLoud::Soloud * self, SoLoud::AudioSource&, float, float, bool, uint32_t)>(getFuncAddr((int)Func::SoLoud::Soloud::play))(this, aSound, aVolume, aPan, aPaused, aBus);
			}
			void stop(uint32_t aVoiceHandle)
			{
				return reinterpret_cast<void(__thiscall*)(SoLoud::Soloud * self, uint32_t)>(getFuncAddr((int)Func::SoLoud::Soloud::stop))(this, aVoiceHandle);
			}
			void stopAll()
			{
				return reinterpret_cast<void(__thiscall*)(SoLoud::Soloud * self)>(getFuncAddr((int)Func::SoLoud::Soloud::stopAll))(this);
			}
			void stopAudioSource(SoLoud::AudioSource& aSound)
			{
				return reinterpret_cast<void(__thiscall*)(SoLoud::Soloud * self, SoLoud::AudioSource&)>(getFuncAddr((int)Func::SoLoud::Soloud::stopAudioSource))(this, aSound);
			}
			uint32_t addVoiceToGroup(uint32_t aVoiceGroupHandle, uint32_t aVoiceHandle)
			{
				return reinterpret_cast<uint32_t(__thiscall*)(SoLoud::Soloud * self, uint32_t, uint32_t)>(getFuncAddr((int)Func::SoLoud::Soloud::addVoiceToGroup))(this, aVoiceGroupHandle, aVoiceHandle);
			}
			uint32_t createVoiceGroup()
			{
				return reinterpret_cast<uint32_t(__thiscall*)(SoLoud::Soloud * self)>(getFuncAddr((int)Func::SoLoud::Soloud::createVoiceGroup))(this);
			}
			uint32_t play3d(SoLoud::AudioSource& aSound, float aPosX, float aPosY, float aPosZ, float aVelX, float aVelY, float aVelZ, float aVolume, bool aPaused, uint32_t aBus)
			{
				return reinterpret_cast<uint32_t(__thiscall*)(SoLoud::Soloud * self, SoLoud::AudioSource&, float, float, float, float, float, float, float, bool, uint32_t)>(getFuncAddr((int)Func::SoLoud::Soloud::play3d))(this, aSound, aPosX, aPosY, aPosZ, aVelX, aVelY, aVelZ, aVolume, aPaused, aBus);
			}
			void set3dListenerAt(float aAtX, float aAtY, float aAtZ)
			{
				return reinterpret_cast<void(__thiscall*)(SoLoud::Soloud * self, float, float, float)>(getFuncAddr((int)Func::SoLoud::Soloud::set3dListenerAt))(this, aAtX, aAtY, aAtZ);
			}
			void set3dListenerUp(float aUpX, float aUpY, float aUpZ)
			{
				return reinterpret_cast<void(__thiscall*)(SoLoud::Soloud * self, float, float, float)>(getFuncAddr((int)Func::SoLoud::Soloud::set3dListenerUp))(this, aUpX, aUpY, aUpZ);
			}
			void set3dListenerVelocity(float aVelocityX, float aVelocityY, float aVelocityZ)
			{
				return reinterpret_cast<void(__thiscall*)(SoLoud::Soloud * self, float, float, float)>(getFuncAddr((int)Func::SoLoud::Soloud::set3dListenerVelocity))(this, aVelocityX, aVelocityY, aVelocityZ);
			}
			void set3dSourceAttenuation(uint32_t aVoiceHandle, uint32_t aAttenuationModel, float aAttenuationRolloffFactor)
			{
				return reinterpret_cast<void(__thiscall*)(SoLoud::Soloud * self, uint32_t, uint32_t, float)>(getFuncAddr((int)Func::SoLoud::Soloud::set3dSourceAttenuation))(this, aVoiceHandle, aAttenuationModel, aAttenuationRolloffFactor);
			}
			void set3dSourceParameters(uint32_t aVoiceHandle, float aPosX, float aPosY, float aPosZ, float aVelocityX, float aVelocityY, float aVelocityZ)
			{
				return reinterpret_cast<void(__thiscall*)(SoLoud::Soloud * self, uint32_t, float, float, float, float, float, float)>(getFuncAddr((int)Func::SoLoud::Soloud::set3dSourceParameters))(this, aVoiceHandle, aPosX, aPosY, aPosZ, aVelocityX, aVelocityY, aVelocityZ);
			}
			void update3dAudio()
			{
				return reinterpret_cast<void(__thiscall*)(SoLoud::Soloud * self)>(getFuncAddr((int)Func::SoLoud::Soloud::update3dAudio))(this);
			}
			bool isValidVoiceHandle(uint32_t aVoiceHandle)
			{
				return reinterpret_cast<bool(__thiscall*)(SoLoud::Soloud * self, uint32_t)>(getFuncAddr((int)Func::SoLoud::Soloud::isValidVoiceHandle))(this, aVoiceHandle);
			}
			Soloud()
			{
				reinterpret_cast<void(__thiscall*)(SoLoud::Soloud * self)>(getFuncAddr((int)Func::SoLoud::Soloud::Soloud))(this);
			}
			~Soloud()
			{
				reinterpret_cast<void(__thiscall*)(SoLoud::Soloud * self)>(getFuncAddr((int)Func::SoLoud::Soloud::destr_Soloud))(this);
			}
			void deinit()
			{
				return reinterpret_cast<void(__thiscall*)(SoLoud::Soloud * self)>(getFuncAddr((int)Func::SoLoud::Soloud::deinit))(this);
			}
			uint32_t init(uint32_t aFlags, uint32_t aBackend, uint32_t aSamplerate, uint32_t aBufferSize, uint32_t aChannels)
			{
				return reinterpret_cast<uint32_t(__thiscall*)(SoLoud::Soloud * self, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t)>(getFuncAddr((int)Func::SoLoud::Soloud::init))(this, aFlags, aBackend, aSamplerate, aBufferSize, aChannels);
			}
			void mix(float* aBuffer, uint32_t aSamples)
			{
				return reinterpret_cast<void(__thiscall*)(SoLoud::Soloud * self, float*, uint32_t)>(getFuncAddr((int)Func::SoLoud::Soloud::mix))(this, aBuffer, aSamples);
			}
			void setDelaySamples(uint32_t aVoiceHandle, uint32_t aSamples)
			{
				return reinterpret_cast<void(__thiscall*)(SoLoud::Soloud * self, uint32_t, uint32_t)>(getFuncAddr((int)Func::SoLoud::Soloud::setDelaySamples))(this, aVoiceHandle, aSamples);
			}
			void setGlobalVolume(float aVolume)
			{
				return reinterpret_cast<void(__thiscall*)(SoLoud::Soloud * self, float)>(getFuncAddr((int)Func::SoLoud::Soloud::setGlobalVolume))(this, aVolume);
			}
			void setPause(uint32_t aVoiceHandle, bool aPause)
			{
				return reinterpret_cast<void(__thiscall*)(SoLoud::Soloud * self, uint32_t, bool)>(getFuncAddr((int)Func::SoLoud::Soloud::setPause))(this, aVoiceHandle, aPause);
			}
			void setProtectVoice(uint32_t aVoiceHandle, bool aProtect)
			{
				return reinterpret_cast<void(__thiscall*)(SoLoud::Soloud * self, uint32_t, bool)>(getFuncAddr((int)Func::SoLoud::Soloud::setProtectVoice))(this, aVoiceHandle, aProtect);
			}
			void setVolume(uint32_t aVoiceHandle, float aVolume)
			{
				return reinterpret_cast<void(__thiscall*)(SoLoud::Soloud * self, uint32_t, float)>(getFuncAddr((int)Func::SoLoud::Soloud::setVolume))(this, aVoiceHandle, aVolume);
			}
		};

		inline ma_device& gDevice = *reinterpret_cast<ma_device*>(getDataAddr((int)Data::SoLoud::gDevice));
		inline void panAndExpand(SoLoud::AudioSourceInstance* aVoice, float* aBuffer, uint32_t aSamplesToRead, uint32_t aBufferSize, float* aScratch, uint32_t aChannels)
		{
			return reinterpret_cast<void(__fastcall*)(SoLoud::AudioSourceInstance*, float*, uint32_t, uint32_t, float*, uint32_t)>(getFuncAddr((int)Func::SoLoud::panAndExpand))(aVoice, aBuffer, aSamplesToRead, aBufferSize, aScratch, aChannels);
		}
		inline void resample(float* aSrc, float* aSrc1, float* aDst, int aSrcOffset, int aDstSampleCount, float __formal, float __formala, int aStepFixed)
		{
			return reinterpret_cast<void(__fastcall*)(float*, float*, float*, int, int, float, float, int)>(getFuncAddr((int)Func::SoLoud::resample))(aSrc, aSrc1, aDst, aSrcOffset, aDstSampleCount, __formal, __formala, aStepFixed);
		}
		inline uint32_t miniaudio_init(SoLoud::Soloud* aSoloud, uint32_t aFlags, uint32_t aSamplerate, uint32_t aBuffer, uint32_t aChannels)
		{
			return reinterpret_cast<uint32_t(__fastcall*)(SoLoud::Soloud*, uint32_t, uint32_t, uint32_t, uint32_t)>(getFuncAddr((int)Func::SoLoud::miniaudio_init))(aSoloud, aFlags, aSamplerate, aBuffer, aChannels);
		}
		inline void soloud_miniaudio_audiomixer(ma_device* pDevice, void* pOutput, const void* pInput, uint32_t frameCount)
		{
			return reinterpret_cast<void(__fastcall*)(ma_device*, void*, const void*, uint32_t)>(getFuncAddr((int)Func::SoLoud::soloud_miniaudio_audiomixer))(pDevice, pOutput, pInput, frameCount);
		}
		inline void soloud_miniaudio_deinit(SoLoud::Soloud* aSoloud)
		{
			return reinterpret_cast<void(__fastcall*)(SoLoud::Soloud*)>(getFuncAddr((int)Func::SoLoud::soloud_miniaudio_deinit))(aSoloud);
		}
	}
}
