#ifndef SONIDO_H
#define SONIDO_H

#include <fmod_studio.hpp>
#include <fmod.hpp>
#include <fmod_errors.h>

#include <iostream>


#include "Canal.h"

class Sonido{
public:
	Sonido(FMOD::Sound* sonido);
	Sonido(FMOD::Sound* sonido, int repeticiones); //repeticiones = numero de veces que se puede repetir a la vez el sonido
	~Sonido();

	void setCanal(Canal* channel);
	//void setMinMax(float min, float max);

	Canal* getCanal();
	//Devuelve uno de los canales vacíos del array de canales
	//Canal* getCanal2();
	FMOD::Sound* getSound();

private:
	FMOD::Sound* sound;
	Canal** canales;		//Diversos canales si se repite el sonido
	Canal* canal; 			//Canal si no tiene repeticiones
	bool unique;
};

#endif //SONIDO_H