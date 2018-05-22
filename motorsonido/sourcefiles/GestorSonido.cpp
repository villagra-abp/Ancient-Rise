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

	//Guardamos el channel group master
	FMOD::ChannelGroup* grupo;
	result = syslow->getMasterChannelGroup(&grupo);
	GestorErrores::getInstance()->errcheck(result);
	master = new GrupoCanales(grupo);

	//Creamos los channel group de los diferentes tipos de sonido del juego
	//Grupo de voces
	result = syslow->createChannelGroup("voces",&grupo);
	GestorErrores::getInstance()->errcheck(result);
	voces = new GrupoCanales(grupo);
	result = master->getChannelGroup()->addGroup(grupo);
	GestorErrores::getInstance()->errcheck(result);

	//Grupo de musica
	result = syslow->createChannelGroup("musica",&grupo);
	GestorErrores::getInstance()->errcheck(result);
	musica = new GrupoCanales(grupo);
	result = master->getChannelGroup()->addGroup(grupo);	
	GestorErrores::getInstance()->errcheck(result);

	//Grupo de ambiente
	result = syslow->createChannelGroup("ambiente",&grupo);
	GestorErrores::getInstance()->errcheck(result);
	ambiente = new GrupoCanales(grupo);
	result = master->getChannelGroup()->addGroup(grupo);
	GestorErrores::getInstance()->errcheck(result);

	master->setVolumen(0.2f);

}

GestorSonido* GestorSonido::getInstance(){
	if(instance == NULL) instance = new GestorSonido();
	return (instance);
}

GestorSonido::~GestorSonido(){
	system->release();
	syslow->release();
}

GrupoCanales* GestorSonido::createGrupoCanales(){
	FMOD::ChannelGroup* grupete;
	result = syslow->createChannelGroup(NULL,&grupete);
	GestorErrores::getInstance()->errcheck(result);

	std::cout<<"Creado grupo de canales."<<endl;

	GrupoCanales* grupo = new GrupoCanales(grupete);

	return(grupo);
}
GrupoCanales* GestorSonido::createGrupoCanales(const char* name){
	FMOD::ChannelGroup* grupete;
	result = syslow->createChannelGroup(name,&grupete);
	GestorErrores::getInstance()->errcheck(result);

	std::cout<<"Creado grupo de canales "<<name<<"."<<endl;

	GrupoCanales* grupo = new GrupoCanales(grupete);

	return(grupo);
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
//Crea un DSP del tipo que se le pasa por parametro
DSP* GestorSonido::createDSP(const char* tipo){
	FMOD::DSP* dsp;

	FMOD_DSP_TYPE type;

	if(tipo == "echo"){
		type = FMOD_DSP_TYPE_ECHO;
	}
	else if(tipo == "distortion"){
		type = FMOD_DSP_TYPE_DISTORTION;
	}
	else if(tipo == "fader"){
		type = FMOD_DSP_TYPE_FADER;
	}
	else if(tipo == "chorus"){
		type = FMOD_DSP_TYPE_CHORUS;
	}
	else if(tipo == "tremolo"){
		type = FMOD_DSP_TYPE_TREMOLO;
	} else type = FMOD_DSP_TYPE_ECHO;


	result = syslow->createDSPByType(type,&dsp);
	GestorErrores::getInstance()->errcheck(result);

	DSP* ndsp = new DSP(dsp);
	return ndsp;
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
//Output: true si ha creado canal nuevo, false si lo ha reutilizado
bool GestorSonido::playSound(Sonido* sonido){
	FMOD::Channel* channel;
	bool isplaying;
//	FMOD_OPENSTATE open;
//	sonido->getSound()->getOpenState(&open,0,0,0);	
//	if(open == FMOD_OPENSTATE_READY){
	bool flag = false;

		if(sonido->getCanal() == NULL ){
			//channel = new FMOD::Channel();
			result = syslow->playSound(sonido->getSound(),0,false,&channel);
			GestorErrores::getInstance()->errcheck(result);
			Canal* canal = new Canal(channel);
			channel = NULL;
			sonido->setCanal(canal);
			flag = true;
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
				flag = true;
			}
			else if(result == FMOD_ERR_INVALID_HANDLE){
				result = syslow->playSound(sonido->getSound(),0,false,&channel);
				GestorErrores::getInstance()->errcheck(result);
				Canal* canal = sonido->getCanal();
				canal->setCanal(channel);
				channel = NULL;
				flag = true;
			}
			/*else if(result == FMOD_ERR_INVALID_HANDLE){
				result = syslow->playSound(sonido->getSound(),0,false, &channel);
				GestorErrores::getInstance()->errcheck(result);
				flag = false;
//				sonido->getCanal()->setCanal(channel);
			}*/
		}
	return flag;
//	}
}

int GestorSonido::playRandomSound(vector<Sonido*> lista){
	int resultado = -1;
	bool sonando = false;

	for(int i = 0; i < lista.size() && sonando == false; i++){
		if(lista[i]->getCanal() != NULL)
			result = lista[i]->getCanal()->getCanal()->isPlaying(&sonando);
	}

	if(!sonando){
		int v1 = rand() % lista.size();
		sonando = playSound(lista[v1]);
		if(sonando) resultado = v1;
	}

	return resultado;
}

void GestorSonido::update(){
	system->update();
}


void GestorSonido::setListener(float x, float y, float z){
	FMOD_VECTOR pos = {x,y,z};
	syslow->set3DListenerAttributes(0,&pos,0,0,0);
}


GrupoCanales* GestorSonido::getMasterGroup(){
	return master;
}
GrupoCanales* GestorSonido::getGrupoMusica(){
	return musica;
}
GrupoCanales* GestorSonido::getGrupoAmbiente(){
	return ambiente;
}
GrupoCanales* GestorSonido::getGrupoVoces(){
	return voces;
}