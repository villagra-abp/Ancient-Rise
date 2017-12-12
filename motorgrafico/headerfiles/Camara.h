#ifndef CAMARA_H
#define CAMARA_H

#include <irrlicht/irrlicht.h>
#include <iostream>
#include "../headerfiles/Motorgrafico.h"

class Camara{
public:
	virtual ~Camara();
	Camara(int type);

	float* getPosicion();

	void setPosicion(float x, float y, float z);

private:	

	Motorgrafico* grafico;
	scene::ISceneManager* escena;

	scene::ICameraSceneNode* node;
} ;


#endif //CAMARA_H