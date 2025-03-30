#pragma once

#include "SoLoud.h"

namespace fdm::SoLoud
{
	class AudioAttenuator
	{
	public:
		virtual float attenuate(float aDistance, float aMinDistance, float aMaxDistance, float aRolloffFactor) { return 0; }
	};
}
