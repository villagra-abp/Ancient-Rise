#include "../headerfiles/Sonido.h"

static Sonido* instance;

Sonido::Sonido(){
	fmod = NULL;
	result = FMOD::Studio::System::create(&fmod);
	if(result != FMOD_OK){
		printf("FMOD error! (%d) %s\n", result, FMOD_ErrorString(result));
	    exit(-1);
	} 

	result = fmod->initialize(CANALES, FMOD_STUDIO_INIT_NORMAL, FMOD_INIT_NORMAL, 0);
	if(result != FMOD_OK){
		printf("FMOD error! (%d) %s\n", result, FMOD_ErrorString(result));
	    exit(-1);
	} 

	result = fmod->getLowLevelSystem(&fmodlow);
	if(result != FMOD_OK){
		printf("FMOD error! (%d) %s\n", result, FMOD_ErrorString(result));
	    exit(-1);
	} 

	channels = new FMOD::Channel*[CANALES];
}

Sonido* Sonido::getInstance(){
	if(instance == NULL) instance = new Sonido();
	return (instance);
}

Sonido::~Sonido(){
	fmod->release();
}

void Sonido::update(){
	fmod->update();
}

void Sonido::playSound(const char* name){

	result = fmodlow->createSound(name,FMOD_DEFAULT,0,&sound);

	if(result != FMOD_OK){
		printf("FMOD error! (%d) %s\n", result, FMOD_ErrorString(result));
	    exit(-1);
	}

	bool isplaying;
		if(channels[0] == NULL){
			fmodlow->playSound(sound,0,false, &channels[0]);
		}
		else{
			result = channels[0]->isPlaying(&isplaying);
			if(result == FMOD_ERR_INVALID_HANDLE){
				fmodlow->playSound(sound,0,false, &channels[0]);
			}
		}

}