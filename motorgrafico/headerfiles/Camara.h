#ifndef CAMARA_H
#define CAMARA_H

#include <irrlicht.h>
#include <iostream>
#include "../headerfiles/Motorgrafico.h"
#include "../headerfiles/Vector3D.h"

class Camara{
public:
	virtual ~Camara();
	Camara(int type);


	Vector3D getPosicion();
	Vector3D getRotation();
	float getFOV();

	void setFOV(float fov);
	void setPosicion(Vector3D pos);
	void setRotation(Vector3D rotation);

private:	

	Motorgrafico* grafico;
	scene::ISceneManager* escena;

	scene::ICameraSceneNode* node;
} ;


#endif //CAMARA_H
