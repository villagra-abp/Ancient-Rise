#include "../headerfiles/GestorSonido.h"

static GestorSonido* instance;

GestorSonido::GestorSonido(){
	system = NULL;
	result = FMOD::Studio::System::create(&system);
	GestorErrores::getInstance()->errcheck(result);

	result = system->initialize(CANALES, FMOD_STUDIO_INIT_NORMAL, FMOD_INIT_NORMAL, 0);
	GestorErrores::getInstance()->errcheck(result);

	result = system->getLowLevelSystem(&syslow);
	GestorErrores::getInstance()->errcheck(result);

	channels = new FMOD::Channel*[CANALES];
}

GestorSonido* GestorSonido::getInstance(){
	if(instance == NULL) instance = new GestorSonido();
	return (instance);
}

GestorSonido::~GestorSonido(){
	system->release();
}


//Carga un Sonido 2D como decompressed sample 
Sonido* GestorSonido::create2DSound(const char* name){
	result = syslow->createSound(name, /*FMOD_NONBLOCKING|*/FMOD_DEFAULT,0,&sound);

	GestorErrores::getInstance()->errcheck(result);
	std::cout<<"Cargado sonido "<<name<<std::endl;

	Sonido* sonido = new Sonido(sound);

	return(sonido);	
}

//Carga un Sonido 3D como decompressed sample
Sonido* GestorSonido::create3DSound(const char* name){

	result = syslow->createSound(name, FMOD_3D/*|FMOD_NONBLOCKING*/,0,&sound);
	GestorErrores::getInstance()->errcheck(result);
	std::cout<<"Cargado sonido "<<name<<std::endl;

	Sonido* sonido = new Sonido(sound);

	return(sonido);	
}

//Carga una musica en un stream
Sonido* GestorSonido::createMusic(const char* name){
	result = syslow->createSound(name, FMOD_CREATESTREAM,0,&sound);

	GestorErrores::getInstance()->errcheck(result);
	std::cout<<"Cargado sonido "<<name<<" como stream "<<std::endl;

	Sonido* sonido = new Sonido(sound);

	return(sonido);	
}


//Crea un reverb 3D
Reverb* GestorSonido::create3DReverb(){
	result = syslow->createReverb3D(&reverb);
	GestorErrores::getInstance()->errcheck(result);

	Reverb* reverberacion = new Reverb(reverb);

	return(reverberacion);
}

//Se le pasa un puntero a un Sonido previamente cargado con uno de los metodos create
void GestorSonido::playSound(Sonido* sonido){
	FMOD::Channel* channel;
	bool isplaying;
//	FMOD_OPENSTATE open;
//	sonido->getSound()->getOpenState(&open,0,0,0);	
//	if(open == FMOD_OPENSTATE_READY){


		if(sonido->getCanal() == NULL ){
			//channel = new FMOD::Channel();
			result = syslow->playSound(sonido->getSound(),0,false,&channel);
			GestorErrores::getInstance()->errcheck(result);
			Canal* canal = new Canal(channel);
			channel = NULL;
			sonido->setCanal(canal);

		}
		else{
			result = sonido->getCanal()->getCanal()->isPlaying(&isplaying);
			//printf("FMOD error! (%d) %s\n", result, FMOD_ErrorString(result));
			if(result == FMOD_ERR_CHANNEL_STOLEN){
				result = syslow->playSound(sonido->getSound(),0,false,&channel);
				GestorErrores::getInstance()->errcheck(result);
				Canal* canal = sonido->getCanal();
				canal->setCanal(channel);
				channel = NULL;

			}
			else if(result == FMOD_ERR_INVALID_HANDLE){
				result = syslow->playSound(sonido->getSound(),0,false, &channel);
				GestorErrores::getInstance()->errcheck(result);
//				sonido->getCanal()->setCanal(channel);
			}
		}
//	}
}

void GestorSonido::update(){
	system->update();
}


void GestorSonido::setListener(float x, float y, float z){
	FMOD_VECTOR pos = {x,y,z};
	syslow->set3DListenerAttributes(0,&pos,0,0,0);
}
