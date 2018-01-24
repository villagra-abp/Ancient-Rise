#ifndef OBJETO_H
#define OBJETO_H


#include "../headerfiles/GameObject.h"


// Clase Objeto base para todos los objetos consumibles del juego

class Objeto : public GameObject
{

	public:

		Objeto();
		virtual ~Objeto();

		//getters y setters

		core::vector3df getVector3df();
		bool  getActivado();
		
		void setRecogido(bool r);
		void setActivado(bool a);


		scene::ISceneNode* getObjeto();


		virtual core::vector3df getPosition() const override { return objeto->getPosition(); }	//Devuelve la posicion.

	protected:

		bool recogido;  				// Para saber si hemos cogido el objeto o no
		bool activado;					// Para saber si el objeto ha sido activado o no
		scene::ISceneNode * objeto;
		int tipo;  						// Para saber que tipo de objeto es 
 

};

#endif // OBJETO_H