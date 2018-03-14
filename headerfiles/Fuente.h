#ifndef FUENTE_H
#define FUENTE_H


#include "../headerfiles/Objeto.h"


class Fuente : public Objeto
{
	public:
		Fuente(IrrlichtDevice *dev, ISceneManager* smgr, Posicion* pos);

	private:
        //core::vector3df fuentePosition;
        //IVideoDriver* 		driver;
};

#endif 
