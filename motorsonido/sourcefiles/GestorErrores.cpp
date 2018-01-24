#include "../headerfiles/GestorErrores.h"

static GestorErrores* instance;

GestorErrores* GestorErrores::getInstance(){
	if(instance==NULL) instance = new GestorErrores();
	return instance;
}

void GestorErrores::errcheck(FMOD_RESULT result){
	if (result != FMOD_OK){
		printf("FMOD error! (%d) %s\n", result, FMOD_ErrorString(result));
	    exit(-1);
	} 

}

GestorErrores::GestorErrores(){

}

GestorErrores::~GestorErrores(){

}