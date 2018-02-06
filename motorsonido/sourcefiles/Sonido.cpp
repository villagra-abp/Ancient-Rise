#include "../headerfiles/Sonido.h"

Sonido::Sonido(FMOD::Sound* sonido){
	sound = sonido;
	unique = true;
	canales = NULL;
	canal = NULL;
}

Sonido::Sonido(FMOD::Sound* sonido, int repeticiones){
	sound = sonido;
	unique = false;
	canales = new Canal*[repeticiones];
	canal = NULL;
}

Sonido::~Sonido(){

}

FMOD::Sound* Sonido::getSound(){
	return sound;
}

void Sonido::setCanal(Canal* channel){
	canal = channel;
}

/*void Sonido::setMinMax(float min, float max){
	result = sound->set3DMinMaxDistance(30.0f * DISTANCEFACTOR, 5000.0f * DISTANCEFACTOR);
   	GestorErrores::getInstance()->errcheck(result);
}*/

Canal* Sonido::getCanal(){
	return canal;
}
/*
Canal* Sonido::getCanal2(){
	canal = NULL
}*/