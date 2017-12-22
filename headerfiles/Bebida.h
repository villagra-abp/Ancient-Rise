#ifndef BEBIDA_H
#define BEBIDA_H

#include "../headerfiles/Objeto.h"



class Bebida : public Objeto
{

	public:

		Bebida(ISceneManager* smgr, Posicion pos);
		scene::ISceneNode* getNode();

	private:
        scene::ISceneNode * bebida;
        core::vector3df bebidaPosition;
};

#endif // BEBDIA_H