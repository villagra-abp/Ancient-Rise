#ifndef COMIDA_H
#define COMIDA_H

#include "../headerfiles/Objeto.h"



class Comida : public Objeto
{

	public:

		Comida(Posicion* pos);
		virtual void update() override;
		void* getNode();

	private:
        //core::vector3df comidaPosition;
        //IVideoDriver* 		driver;
};

#endif // COMIDA_H

