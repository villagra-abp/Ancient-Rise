#include "../headerfiles/GrupoCanales.h"


GrupoCanales::GrupoCanales(FMOD::ChannelGroup* grupete){
	channelGroup = grupete;
}


GrupoCanales::~GrupoCanales(){

}

void GrupoCanales::addDSP(DSP* dsp){
	channelGroup->addDSP(1,dsp->getDSP());
}

void GrupoCanales::setVolumen(float volumen){
	channelGroup->setVolume(volumen);
}

FMOD::ChannelGroup* GrupoCanales::getChannelGroup(){
	return channelGroup;
}

float GrupoCanales::getVolumen(){
	float volumen;
	channelGroup->getVolume(&volumen);

	return volumen;
}
