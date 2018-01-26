#ifndef DSP_H
#define DSP_H

#include <fmod_studio.hpp>
#include <fmod.hpp>
#include <fmod_errors.h>

class DSP{
public:
	DSP(FMOD::DSP* ndsp);
	~DSP();

	FMOD::DSP* getDSP();

private:
	FMOD::DSP* dsp;
};

#endif //DSP_H