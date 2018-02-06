#ifndef COMIDA_H
#define COMIDA_H

#include "../headerfiles/Objeto.h"



class Comida : public Objeto
{

	public:

		Comida(IrrlichtDevice *dev, ISceneManager* smgr, Posicion pos);
		scene::ISceneNode* getNode();

	private:
        core::vector3df comidaPosition;
        IVideoDriver* 		driver;
};

#endif // COMIDA_H