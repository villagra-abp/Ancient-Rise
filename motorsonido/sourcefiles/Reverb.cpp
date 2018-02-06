#include "../headerfiles/Reverb.h"

Reverb::Reverb(FMOD::Reverb3D* cosa){
	reverb = cosa;
	
}

Reverb::~Reverb(){

}


float Reverb::getX(){
	FMOD_VECTOR* pos;
	float min;
	float max;

	reverb->get3DAttributes(pos,&min,&max);


	return pos->x;
}
float Reverb::getY(){
	FMOD_VECTOR* pos;
	float min;
	float max;
	reverb->get3DAttributes(pos,&min,&max);

	return pos->y;
}
float Reverb::getZ(){
	FMOD_VECTOR* pos;
	float min;
	float max;
	reverb->get3DAttributes(pos,&min,&max);

	return pos->z;
}
float Reverb::getMin(){
	FMOD_VECTOR* pos;
	float min;
	float max;
	reverb->get3DAttributes(pos,&min,&max);

	return min;
}
float Reverb::getMax(){
	FMOD_VECTOR* pos;
	float min;
	float max;
	reverb->get3DAttributes(pos,&min,&max);

	return  max;
}

//Las constantes de tipo estan definidas en GestorSonido.h
void Reverb::setTipo(const char* tipo){
	FMOD_REVERB_PROPERTIES prop;

	
	if(tipo == "cueva")
		prop = FMOD_PRESET_CAVE;
	else if(tipo =="bosque")
		prop = FMOD_PRESET_FOREST;
	else if(tipo == "ciudad")
		prop = FMOD_PRESET_CITY;
	else if(tipo == "habitacion")
		prop = FMOD_PRESET_ROOM;

	reverb->setProperties(&prop);


}
void Reverb::setAtributos3D(float x, float y, float z, float min, float max){
	FMOD_VECTOR pos = {x,y,z};
	reverb->set3DAttributes(&pos,min,max);
}