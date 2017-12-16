#ifndef OBJETO_H
#define OBJETO_H

#include <irrlicht.h>
#include <iostream>
#include <vector>

#include "../headerfiles/Posicion.h"

using namespace irr;
using namespace std;

using namespace core;
using namespace scene;
using namespace video;
using namespace io;
using namespace gui;


// Clase Objeto base para todos los objetos consumibles del juego

class Objeto 
{

	public:

		Objeto();
		virtual ~Objeto();

		//getters y setters

		void setRecogido(bool r);


		scene::ISceneNode* getObjeto();








	protected:

		bool recogido;  				// Para saber si hemos cogido el objeto o no
		scene::ISceneNode * objeto;
		int tipo;  						// Para saber que tipo de objeto es 
 

};

#endif // OBJETO_H