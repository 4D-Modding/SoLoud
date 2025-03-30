#pragma once

#include "SoLoud.h"

namespace fdm::SoLoud
{
	class Soloud;
	class AudioSourceInstance3dData;
	class AudioCollider
	{
	public:
		// Calculate volume multiplier. Assumed to return value between 0 and 1.
		virtual float collide(Soloud* aSoloud, AudioSourceInstance3dData* aAudioInstance3dData, int aUserData) { return 0; }
	};
}
