#ifndef GRUPOCANALES_H
#define GRUPOCANALES_H

#include <fmod_studio.hpp>
#include <fmod.hpp>
#include <fmod_errors.h>

#include "DSP.h"

class GrupoCanales{
public:
	GrupoCanales(FMOD::ChannelGroup* grupete);
	~GrupoCanales();

	void addDSP(DSP* dsp);

	void setVolumen(float volumen);

	FMOD::ChannelGroup* getChannelGroup();
	float getVolumen();
private:
	FMOD::ChannelGroup* channelGroup;
};

#endif //GRUPOCANALES_H