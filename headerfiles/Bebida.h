#ifndef BEBIDA_H
#define BEBIDA_H

#include "../headerfiles/Objeto.h"



class Bebida : public Objeto
{

	public:
		Bebida(IrrlichtDevice *dev, ISceneManager* smgr, Posicion* pos);
		void* getNode();

	private:
        void * bebida;
        //core::vector3df bebidaPosition;
        //IVideoDriver* 		driver;
};

#endif // BEBDIA_H
