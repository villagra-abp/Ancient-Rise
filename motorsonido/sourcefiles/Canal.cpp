#include "../headerfiles/Canal.h"

Canal::Canal(FMOD::Channel* channel){
	canal = channel;
	grupo = NULL;
}

Canal::~Canal(){

}

void Canal::addDSP(DSP* dsp){
	FMOD_RESULT result;
	FMOD::DSP* ndsp = dsp->getDSP();

	canal->addDSP(0,ndsp);
	//GestorErrores::getInstance()->errcheck(result);
}

bool Canal::stop(){
	canal->stop();
}

FMOD::Channel* Canal::getCanal(){
	return canal;
}

void Canal::setCanal(FMOD::Channel* channel){
	canal = channel;
}

void Canal::setGrupoCanales(GrupoCanales* grupete){
	grupo = grupete;
	canal->setChannelGroup(grupo->getChannelGroup());
}