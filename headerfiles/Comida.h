#ifndef COMIDA_H
#define COMIDA_H

#include "../headerfiles/Objeto.h"



class Comida : public Objeto
{

	public:

		Comida(ISceneManager* smgr, Posicion pos);
		scene::ISceneNode* getNode();

	private:
        core::vector3df comidaPosition;
};

#endif // COMIDA_H