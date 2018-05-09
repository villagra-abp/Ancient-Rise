#ifndef FUENTE_H
#define FUENTE_H


#include "../headerfiles/Objeto.h"


class Fuente : public Objeto
{
	public:
		Fuente( Posicion* pos);
		virtual void update() override;
		virtual ~Fuente();

	private:
        //core::vector3df fuentePosition;
        //IVideoDriver* 		driver;
};

#endif 
