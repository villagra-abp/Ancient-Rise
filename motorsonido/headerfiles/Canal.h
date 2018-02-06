#ifndef CANAL_H
#define CANAL_H

#include <fmod_studio.hpp>
#include <fmod.hpp>
#include <fmod_errors.h>

#include <iostream>

#include "GrupoCanales.h"
#include "DSP.h"
#include "GestorErrores.h"

using namespace std;

class Canal{
public:
	Canal(FMOD::Channel* channel);
	~Canal();

	void addDSP(DSP* dsp);

	FMOD::Channel* getCanal();

	void setCanal(FMOD::Channel* channel);
	void setGrupoCanales(GrupoCanales* grupete);
private:
	FMOD::Channel* canal;
	GrupoCanales* grupo;
};

#endif //CANAL_H