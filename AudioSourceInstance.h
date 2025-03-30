#pragma once

#include "SoLoud.h"

namespace fdm::SoLoud
{
	class AlignedFloatBuffer;
	class FilterInstance;
	class Fader;
	class AudioCollider;
	class AudioAttenuator;
	class AudioSourceInstance
	{
	public:
		enum FLAGS : int
		{
			// This audio instance loops (if supported)
			LOOPING = 1,
			// This audio instance is protected - won't get stopped if we run out of voices
			PROTECTED = 2,
			// This audio instance is paused
			PAUSED = 4,
			// This audio instance is affected by 3d processing
			PROCESS_3D = 8,
			// This audio instance has listener-relative 3d coordinates
			LISTENER_RELATIVE = 16,
			// Currently inaudible
			INAUDIBLE = 32,
			// If inaudible, should be killed (default = don't kill kill)
			INAUDIBLE_KILL = 64,
			// If inaudible, should still be ticked (default = pause)
			INAUDIBLE_TICK = 128
		};
		// Play index; used to identify instances from handles
		uint32_t mPlayIndex;
		// Loop count
		uint32_t mLoopCount;
		// Flags; see AudioSourceInstance::FLAGS
		uint32_t mFlags;
		// Pan value, for getPan()
		float mPan;
		// Volume for each channel (panning)
		float mChannelVolume[MAX_CHANNELS];
		// Set volume
		float mSetVolume;
		// Overall volume overall = set * 3d
		float mOverallVolume;
		// Base samplerate; samplerate = base samplerate * relative play speed
		float mBaseSamplerate;
		// Samplerate; samplerate = base samplerate * relative play speed
		float mSamplerate;
		// Number of channels this audio source produces
		uint32_t mChannels;
		// Relative play speed; samplerate = base samplerate * relative play speed
		float mSetRelativePlaySpeed;
		// Overall relative plays peed; overall = set * 3d
		float mOverallRelativePlaySpeed;
		PAD(0x4);
		// How long this stream has played, in seconds.
		time mStreamTime;
		// Position of this stream, in seconds.
		time mStreamPosition;
		// Fader for the audio panning
		SoLoud::Fader mPanFader;
		// Fader for the audio volume
		SoLoud::Fader mVolumeFader;
		// Fader for the relative play speed
		SoLoud::Fader mRelativePlaySpeedFader;
		// Fader used to schedule pausing of the stream
		SoLoud::Fader mPauseScheduler;
		// Fader used to schedule stopping of the stream
		SoLoud::Fader mStopScheduler;
		// Affected by some fader
		int mActiveFader;
		// Current channel volumes, used to ramp the volume changes to avoid clicks
		float mCurrentChannelVolume[MAX_CHANNELS];
		// ID of the sound source that generated this instance
		uint32_t mAudioSourceID;
		// Handle of the bus this audio instance is playing on. 0 for root.
		uint32_t mBusHandle;
		PAD(0x4);
		// Filter pointer
		SoLoud::FilterInstance* mFilter[FILTERS_PER_STREAM];
		PAD(0x38);
		// Buffers for the resampler
		SoLoud::AlignedFloatBuffer* mResampleData[2];
		PAD(0x8);
		// Sub-sample playhead; 16.16 fixed point
		uint32_t mSrcOffset;
		// Samples left over from earlier pass
		uint32_t mLeftoverSamples;
		// Number of samples to delay streaming
		uint32_t mDelaySamples;
		PAD(0x4);
		// When looping, start playing from this time
		time mLoopPoint;
		AudioSourceInstance()
		{
			reinterpret_cast<void (__thiscall*)(SoLoud::AudioSourceInstance* self)>(getFuncAddr((int)Func::SoLoud::AudioSourceInstance::AudioSourceInstance))(this);
		}
		// Initialize instance. Mostly internal use.
		void init(SoLoud::AudioSource& aSource, int aPlayIndex)
		{
			return reinterpret_cast<void(__thiscall*)(SoLoud::AudioSourceInstance * self, SoLoud::AudioSource&, int)>(getFuncAddr((int)Func::SoLoud::AudioSourceInstance::init))(this, aSource, aPlayIndex);
		}
		virtual ~AudioSourceInstance()
		{
			reinterpret_cast<void (__thiscall*)(SoLoud::AudioSourceInstance* self)>(getFuncAddr((int)Func::SoLoud::AudioSourceInstance::destr_AudioSourceInstance))(this);
		}
		// Get N samples from the stream to the buffer. Report samples written.
		virtual uint32_t getAudio(float* aBuffer, uint32_t aSamplesToRead, uint32_t aBufferSize) { return 0; }
		// Has the stream ended?
		virtual bool hasEnded() { return false; }
		// Seek to certain place in the stream. Base implementation is generic "tape" seek (and slow).
		virtual uint32_t seek(double aSeconds, float* mScratch, uint32_t mScratchSize)
		{
			return reinterpret_cast<uint32_t (__thiscall*)(SoLoud::AudioSourceInstance* self, double, float*, uint32_t)>(getFuncAddr((int)Func::SoLoud::AudioSourceInstance::seek))(this, aSeconds, mScratch, mScratchSize);
		}
		// Rewind stream. Base implementation returns NOT_IMPLEMENTED, meaning it can't rewind.
		virtual uint32_t rewind()
		{
			return reinterpret_cast<uint32_t(__thiscall*)(SoLoud::AudioSourceInstance * self)>(getFuncAddr((int)Func::SoLoud::AudioSourceInstance::rewind))(this);
		}
		// Get information. Returns 0 by default.
		virtual float getInfo(uint32_t aInfoKey)
		{
			return reinterpret_cast<float(__thiscall*)(SoLoud::AudioSourceInstance * self, uint32_t)>(getFuncAddr((int)Func::SoLoud::AudioSourceInstance::getInfo))(this, aInfoKey);
		}
	};
}
