#ifndef BEBIDA_H
#define BEBIDA_H

#include "../headerfiles/Objeto.h"



class Bebida : public Objeto
{

	public:

		Bebida(IrrlichtDevice *dev, ISceneManager* smgr, Posicion pos);
		scene::ISceneNode* getNode();

	private:
        scene::ISceneNode * bebida;
        core::vector3df bebidaPosition;
        IVideoDriver* 		driver;
};

#endif // BEBDIA_H