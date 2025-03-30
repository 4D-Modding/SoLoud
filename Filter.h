#pragma once

#include "SoLoud.h"

namespace fdm::SoLoud
{
	class Fader;
	class FilterInstance;
	class Filter
	{
	public:
		enum PARAMTYPE : int
		{
			FLOAT_PARAM = 0x0,
			INT_PARAM = 0x1,
			BOOL_PARAM = 0x2,
		};

		virtual int getParamCount() { return 0; }
		virtual const char*  getParamName(unsigned int) { return NULL; }
		virtual unsigned int getParamType(unsigned int) { return 0; }
		virtual float getParamMax(unsigned int) { return 0; }
		virtual float getParamMin(unsigned int) { return 0; }
		virtual SoLoud::FilterInstance* createInstance() { return NULL; }
		virtual ~Filter() {}
	};
	class FilterInstance
	{
	public:
		unsigned int mNumParams;
		unsigned int mParamChanged;
		float* mParam;
		SoLoud::Fader* mParamFader;

		virtual unsigned int initParams(int) { return 0; }
		virtual void updateParams(long double) {}
		virtual void filter(float*, unsigned int, unsigned int, float, long double) {}
		virtual void filterChannel(float*, unsigned int, float, long double, unsigned int, unsigned int) {}
		virtual float getFilterParameter(unsigned int) { return 0; }
		virtual void setFilterParameter(unsigned int, float) {}
		virtual void fadeFilterParameter(unsigned int, float, long double, long double) {}
		virtual void oscillateFilterParameter(unsigned int, float, float, long double, long double) {}
		virtual ~FilterInstance() {}
	};
}
