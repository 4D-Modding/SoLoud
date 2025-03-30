#pragma once

#include <cstdlib>
#include <cstdint>

namespace fdm::SoLoud
{
	// i hate myself -- tr1ngle from june 18th 2024
	// that is true and i also hate miniaudio -- tr1ngle from march 23rd 2025
	namespace miniaudio
	{
		enum ma_device_type : int
		{
			ma_device_type_playback = 1,
			ma_device_type_capture,
			ma_device_type_duplex,
			ma_device_type_loopback,
		};
		enum ma_share_mode : int
		{
			ma_share_mode_shared = 0,
			ma_share_mode_exclusive,
		};
		enum ma_format : int
		{
			ma_format_unknown = 0,
			ma_format_u8,
			ma_format_s16,
			ma_format_s24,
			ma_format_s32,
			ma_format_f32,

			ma_format_count,
		};
		enum ma_backend : int
		{
			ma_backend_wasapi = 0,
			ma_backend_dsound,
			ma_backend_winmm,
			ma_backend_coreaudio,
			ma_backend_sndio,
			ma_backend_audio4,
			ma_backend_oss,
			ma_backend_pulseaudio,
			ma_backend_alsa,
			ma_backend_jack,
			ma_backend_aaudio,
			ma_backend_opensl,
			ma_backend_webaudio,
			ma_backend_null,
		};
		enum ma_thread_priority : int
		{
			ma_thread_priority_idle = -5,
			ma_thread_priority_lowest,
			ma_thread_priority_low,
			ma_thread_priority_normal,
			ma_thread_priority_high,
			ma_thread_priority_highest,
			ma_thread_priority_realtime,

			ma_thread_priority_default = ma_thread_priority_highest,
		};
		enum ma_performance_profile : int
		{
			ma_performance_profile_low_latency = 0,
			ma_performance_profile_conservative,
		};
		union ma_device_id
		{
			wchar_t wasapi[64];
			uint8_t dsound[16];
			uint32_t winmm;
			int jack;
			int nullbackend;
		};
		struct ma_device_info
		{
			ma_device_id id;
			char name[256];
			uint32_t formatCount;
			ma_format formats[6];
			uint32_t minChannels;
			uint32_t maxChannels;
			uint32_t minSampleRate;
			uint32_t maxSampleRate;
		};
		struct ma_context;
		struct ma_mutex
		{
			ma_context* pContext;
			union
			{
				struct
				{
					void* hMutex;
				} win32;
				int _unused;
			};
		};
		struct ma_device;
		struct ma_device_config
		{
			ma_device_type deviceType;
			uint32_t sampleRate;
			uint32_t bufferSizeInFrames;
			uint32_t bufferSizeInMilliseconds;
			uint32_t periods;
			ma_performance_profile performanceProfile;
			uint32_t noPreZeroedOutputBuffer;
			uint32_t noClip;
			void(__fastcall* dataCallback)(ma_device*, void*, const void*, uint32_t);
			void(__fastcall* stopCallback)(ma_device*);
			void* pUserData;
			struct
			{
				ma_device_id* pDeviceID;
				ma_format format;
				uint32_t channels;
				uint8_t channelMap[32];
				ma_share_mode shareMode;
			} playback;
			struct
			{
				ma_device_id* pDeviceID;
				ma_format format;
				uint32_t channels;
				uint8_t channelMap[32];
				ma_share_mode shareMode;
			} capture;
			struct
			{
				uint32_t noAutoConvertSRC;
				uint32_t noDefaultQualitySRC;
				uint32_t noAutoStreamRouting;
				uint32_t noHardwareOffloading;
			} wasapi;
			struct
			{
				uint32_t noMMap;
			} alsa;
			struct
			{
				const char* pStreamNamePlayback;
				const char* pStreamNameCapture;
			} pulse;
		};
		struct ma_device;
		struct ma_context
		{
			ma_backend backend;
			void(__fastcall* logCallback)(ma_context*, ma_device*, uint32_t, const char*);
			ma_thread_priority threadPriority;
			void* pUserData;
			ma_mutex deviceEnumLock;
			ma_mutex deviceInfoLock;
			uint32_t deviceInfoCapacity;
			uint32_t playbackDeviceInfoCount;
			uint32_t captureDeviceInfoCount;
			ma_device_info* pDeviceInfos;
			uint32_t isBackendAsynchronous : 1;
			int(__fastcall* onUninit)(ma_context*);
			uint32_t(__fastcall* onDeviceIDEqual)(ma_context*, const ma_device_id*, const ma_device_id*);
			int(__fastcall* onEnumDevices)(ma_context*, uint32_t(__fastcall*)(ma_context*, ma_device_type, const ma_device_info*, void*), void*);
			int(__fastcall* onGetDeviceInfo)(ma_context*, ma_device_type, const ma_device_id*, ma_share_mode, ma_device_info*);
			int(__fastcall* onDeviceInit)(ma_context*, const ma_device_config*, ma_device*);
			void(__fastcall* onDeviceUninit)(ma_device*);
			int(__fastcall* onDeviceStart)(ma_device*);
			int(__fastcall* onDeviceStop)(ma_device*);
			int(__fastcall* onDeviceMainLoop)(ma_device*);
			union
			{
				struct
				{
					int _unused;
				} wasapi;
				struct
				{
					void* hDSoundDLL;
					void(__fastcall* DirectSoundCreate)();
					void(__fastcall* DirectSoundEnumerateA)();
					void(__fastcall* DirectSoundCaptureCreate)();
					void(__fastcall* DirectSoundCaptureEnumerateA)();
				} dsound;
				struct
				{
					void* hWinMM;
					void(__fastcall* waveOutGetNumDevs)();
					void(__fastcall* waveOutGetDevCapsA)();
					void(__fastcall* waveOutOpen)();
					void(__fastcall* waveOutClose)();
					void(__fastcall* waveOutPrepareHeader)();
					void(__fastcall* waveOutUnprepareHeader)();
					void(__fastcall* waveOutWrite)();
					void(__fastcall* waveOutReset)();
					void(__fastcall* waveInGetNumDevs)();
					void(__fastcall* waveInGetDevCapsA)();
					void(__fastcall* waveInOpen)();
					void(__fastcall* waveInClose)();
					void(__fastcall* waveInPrepareHeader)();
					void(__fastcall* waveInUnprepareHeader)();
					void(__fastcall* waveInAddBuffer)();
					void(__fastcall* waveInStart)();
					void(__fastcall* waveInReset)();
				} winmm;
				struct
				{
					void* jackSO;
					void(__fastcall* jack_client_open)();
					void(__fastcall* jack_client_close)();
					void(__fastcall* jack_client_name_size)();
					void(__fastcall* jack_set_process_callback)();
					void(__fastcall* jack_set_buffer_size_callback)();
					void(__fastcall* jack_on_shutdown)();
					void(__fastcall* jack_get_sample_rate)();
					void(__fastcall* jack_get_buffer_size)();
					void(__fastcall* jack_get_ports)();
					void(__fastcall* jack_activate)();
					void(__fastcall* jack_deactivate)();
					void(__fastcall* jack_connect)();
					void(__fastcall* jack_port_register)();
					void(__fastcall* jack_port_name)();
					void(__fastcall* jack_port_get_buffer)();
					void(__fastcall* jack_free)();
					char* pClientName;
					uint32_t tryStartServer;
				} jack;
				struct
				{
					int _unused;
				} null_backend;
			};
			union
			{
				struct
				{
					void* hOle32DLL;
					void(__fastcall* CoInitializeEx)();
					void(__fastcall* CoUninitialize)();
					void(__fastcall* CoCreateInstance)();
					void(__fastcall* CoTaskMemFree)();
					void(__fastcall* PropVariantClear)();
					void(__fastcall* StringFromGUID2)();
					void* hUser32DLL;
					void(__fastcall* GetForegroundWindow)();
					void(__fastcall* GetDesktopWindow)();
					void* hAdvapi32DLL;
					void(__fastcall* RegOpenKeyExA)();
					void(__fastcall* RegCloseKey)();
					void(__fastcall* RegQueryValueExA)();
				} win32;
				int _unused;
			};
		};
		struct ma_event
		{
			ma_context* pContext;

			union
			{
				struct
				{
					void* hEvent;
				} win32;
				int _unused;
			};
		};
		struct ma_thread
		{
			ma_context* pContext;

			union
			{
				struct
				{
					void* hThread;
				} win32;
				int _unused;
			};
		};
		struct ma_rb
		{
			void* pBuffer;
			uint32_t subbufferSizeInBytes;
			uint32_t subbufferCount;
			uint32_t subbufferStrideInBytes;
			volatile uint32_t encodedReadOffset;
			volatile uint32_t encodedWriteOffset;
			uint32_t ownsBuffer : 1;
			uint32_t clearOnWriteAcquire : 1;
		};
		struct ma_pcm_rb
		{
			ma_rb rb;
			ma_format format;
			uint32_t channels;
		};
		enum ma_stream_format : int
		{
			ma_stream_format_pcm = 0,
		};
		enum ma_dither_mode : int
		{
			ma_dither_mode_none = 0,
			ma_dither_mode_rectangle,
			ma_dither_mode_triangle,
		};
		struct ma_format_converter;
		struct ma_format_converter_config
		{
			ma_format formatIn;
			ma_format formatOut;
			uint32_t channels;
			ma_stream_format streamFormatIn;
			ma_stream_format streamFormatOut;
			ma_dither_mode ditherMode;
			uint32_t noSSE2 : 1;
			uint32_t noAVX2 : 1;
			uint32_t noAVX512 : 1;
			uint32_t noNEON : 1;
			uint32_t(__fastcall* onRead)(ma_format_converter*, uint32_t, void*, void*);
			uint32_t(__fastcall* onReadDeinterleaved)(ma_format_converter*, uint32_t, void**, void*);
			void* pUserData;
		};
		struct ma_format_converter
		{
			ma_format_converter_config config;
			uint32_t useSSE2 : 1;
			uint32_t useAVX2 : 1;
			uint32_t useAVX512 : 1;
			uint32_t useNEON : 1;
			void(__fastcall* onConvertPCM)(void*, const void*, uint64_t, ma_dither_mode);
			void(__fastcall* onInterleavePCM)(void*, const void**, uint64_t, uint32_t);
			void(__fastcall* onDeinterleavePCM)(void**, const void*, uint64_t, uint32_t);
		};
		enum ma_src_sinc_window_function : int
		{
			ma_src_sinc_window_function_hann = 0,
			ma_src_sinc_window_function_rectangular,
			ma_src_sinc_window_function_default = ma_src_sinc_window_function_hann,
		};
		enum ma_src_algorithm : int
		{
			ma_src_algorithm_linear = 0,
			ma_src_algorithm_sinc,
			ma_src_algorithm_none,
			ma_src_algorithm_default = ma_src_algorithm_linear,
		};
		struct ma_src_config_sinc
		{
			ma_src_sinc_window_function windowFunction;
			uint32_t windowWidth;
		};
		struct ma_src;
		struct ma_src_config
		{
			uint32_t sampleRateIn;
			uint32_t sampleRateOut;
			uint32_t channels;
			ma_src_algorithm algorithm;
			uint32_t neverConsumeEndOfInput : 1;
			uint32_t noSSE2 : 1;
			uint32_t noAVX2 : 1;
			uint32_t noAVX512 : 1;
			uint32_t noNEON : 1;
			uint32_t(__fastcall* onReadDeinterleaved)(ma_src*, uint32_t, void**, void*);
			void* pUserData;
			ma_src_config_sinc sinc;
		};
		enum ma_channel_mix_mode : int
		{
			ma_channel_mix_mode_rectangular = 0,
			ma_channel_mix_mode_tetle,
			ma_channel_mix_mode_custom_weights,
			ma_channel_mix_mode_planar_blend = ma_channel_mix_mode_rectangular,
			ma_channel_mix_mode_default = ma_channel_mix_mode_rectangular,
		};
		struct ma_channel_router;
		struct ma_channel_router_config
		{
			uint32_t channelsIn;
			uint32_t channelsOut;
			uint8_t channelMapIn[32];
			uint8_t channelMapOut[32];
			ma_channel_mix_mode mixingMode;
			float weights[32][32];
			uint32_t noSSE2 : 1;
			uint32_t noAVX2 : 1;
			uint32_t noAVX512 : 1;
			uint32_t noNEON : 1;
			uint32_t(__fastcall* onReadDeinterleaved)(ma_channel_router*, uint32_t, void**, void*);
			void* pUserData;
		};
		struct ma_channel_router
		{
			ma_channel_router_config config;
			uint32_t isPassthrough : 1;
			uint32_t isSimpleShuffle : 1;
			uint32_t isSimpleMonoExpansion : 1;
			uint32_t isStereoToMono : 1;
			uint32_t useSSE2 : 1;
			uint32_t useAVX2 : 1;
			uint32_t useAVX512 : 1;
			uint32_t useNEON : 1;
			uint8_t shuffleTable[32];
		};
		struct ma_src
		{
			union
			{
				struct
				{
					float input[32][256];
					float timeIn;
					uint32_t leftoverFrames;
				} linear;
				struct
				{
					float input[32][320];
					float timeIn;
					uint32_t inputFrameCount;
					uint32_t windowPosInSamples;
					float table[256];
				} sinc;
			};
			ma_src_config config;
			uint32_t isEndOfInputLoaded : 1;
			uint32_t useSSE2 : 1;
			uint32_t useAVX2 : 1;
			uint32_t useAVX512 : 1;
			uint32_t useNEON : 1;
		};
		struct ma_pcm_converter
		{
			uint32_t(__fastcall* onRead)(ma_pcm_converter*, void*, uint32_t, void*);
			void* pUserData;
			ma_format_converter formatConverterIn;
			ma_format_converter formatConverterOut;
			ma_channel_router channelRouter;
			ma_src src;
			uint32_t isDynamicSampleRateAllowed : 1;
			uint32_t isPreFormatConversionRequired : 1;
			uint32_t isPostFormatConversionRequired : 1;
			uint32_t isChannelRoutingRequired : 1;
			uint32_t isSRCRequired : 1;
			uint32_t isChannelRoutingAtStart : 1;
			uint32_t isPassthrough : 1;
		};
		union ma_timer
		{
			__int64 counter;
			long double counterD;
		};
		struct ma_IMMNotificationClient
		{
			void* lpVtbl;
			uint32_t counter;
			ma_device* pDevice;
		};
		struct ma_device
		{
			ma_context* pContext;
			ma_device_type type;
			uint32_t sampleRate;
			uint32_t state;
			void(__fastcall* onData)(ma_device*, void*, const void*, uint32_t);
			void(__fastcall* onStop)(ma_device*);
			void* pUserData;
			ma_mutex lock;
			ma_event wakeupEvent;
			ma_event startEvent;
			ma_event stopEvent;
			ma_thread thread;
			int workResult;
			uint32_t usingDefaultSampleRate : 1;
			uint32_t usingDefaultBufferSize : 1;
			uint32_t usingDefaultPeriods : 1;
			uint32_t isOwnerOfContext : 1;
			uint32_t noPreZeroedOutputBuffer : 1;
			uint32_t noClip : 1;
			float masterVolumeFactor;
			struct
			{
				char name[256];
				ma_share_mode shareMode;
				uint32_t usingDefaultFormat : 1;
				uint32_t usingDefaultChannels : 1;
				uint32_t usingDefaultChannelMap : 1;
				ma_format format;
				uint32_t channels;
				uint8_t channelMap[32];
				ma_format internalFormat;
				uint32_t internalChannels;
				uint32_t internalSampleRate;
				uint8_t internalChannelMap[32];
				uint32_t internalBufferSizeInFrames;
				uint32_t internalPeriods;
				ma_pcm_converter converter;
				uint32_t _dspFrameCount;
				const uint8_t* _dspFrames;
			} playback;
			struct
			{
				char name[256];
				ma_share_mode shareMode;
				uint32_t usingDefaultFormat : 1;
				uint32_t usingDefaultChannels : 1;
				uint32_t usingDefaultChannelMap : 1;
				ma_format format;
				uint32_t channels;
				uint8_t channelMap[32];
				ma_format internalFormat;
				uint32_t internalChannels;
				uint32_t internalSampleRate;
				uint8_t internalChannelMap[32];
				uint32_t internalBufferSizeInFrames;
				uint32_t internalPeriods;
				ma_pcm_converter converter;
				uint32_t _dspFrameCount;
				const uint8_t* _dspFrames;
			} capture;

			union
			{
				struct
				{
					void* pAudioClientPlayback;
					void* pAudioClientCapture;
					void* pRenderClient;
					void* pCaptureClient;
					void* pDeviceEnumerator;
					ma_IMMNotificationClient notificationClient;
					void* hEventPlayback;
					void* hEventCapture;
					uint32_t actualBufferSizeInFramesPlayback;
					uint32_t actualBufferSizeInFramesCapture;
					uint32_t originalBufferSizeInFrames;
					uint32_t originalBufferSizeInMilliseconds;
					uint32_t originalPeriods;
					uint32_t hasDefaultPlaybackDeviceChanged;
					uint32_t hasDefaultCaptureDeviceChanged;
					uint32_t periodSizeInFramesPlayback;
					uint32_t periodSizeInFramesCapture;
					uint32_t isStartedCapture;
					uint32_t isStartedPlayback;
					uint32_t noAutoConvertSRC : 1;
					uint32_t noDefaultQualitySRC : 1;
					uint32_t noHardwareOffloading : 1;
					uint32_t allowCaptureAutoStreamRouting : 1;
					uint32_t allowPlaybackAutoStreamRouting : 1;
				} wasapi;
				struct
				{
					void* pPlayback;
					void* pPlaybackPrimaryBuffer;
					void* pPlaybackBuffer;
					void* pCapture;
					void* pCaptureBuffer;
				} dsound;
				struct
				{
					void* hDevicePlayback;
					void* hDeviceCapture;
					void* hEventPlayback;
					void* hEventCapture;
					uint32_t fragmentSizeInFrames;
					uint32_t fragmentSizeInBytes;
					uint32_t iNextHeaderPlayback;
					uint32_t iNextHeaderCapture;
					uint32_t headerFramesConsumedPlayback;
					uint32_t headerFramesConsumedCapture;
					uint8_t* pWAVEHDRPlayback;
					uint8_t* pWAVEHDRCapture;
					uint8_t* pIntermediaryBufferPlayback;
					uint8_t* pIntermediaryBufferCapture;
					uint8_t* _pHeapData;
				} winmm;
				struct
				{
					void* pClient;
					void* pPortsPlayback[32];
					void* pPortsCapture[32];
					float* pIntermediaryBufferPlayback;
					float* pIntermediaryBufferCapture;
					ma_pcm_rb duplexRB;
				} jack;
				struct
				{
					ma_thread deviceThread;
					ma_event operationEvent;
					ma_event operationCompletionEvent;
					uint32_t operation;
					int operationResult;
					ma_timer timer;
					long double priorRunTime;
					uint32_t currentPeriodFramesRemainingPlayback;
					uint32_t currentPeriodFramesRemainingCapture;
					uint64_t lastProcessedFramePlayback;
					uint32_t lastProcessedFrameCapture;
					uint32_t isStarted;
				} null_device;
			};
		};
	}
}
using namespace fdm::SoLoud::miniaudio;
