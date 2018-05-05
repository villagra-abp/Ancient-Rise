#ifndef BEBIDA_H
#define BEBIDA_H

#include "../headerfiles/Objeto.h"



class Bebida : public Objeto
{

	public:
		Bebida( Posicion* pos);
		virtual void update() override;
		void* getNode();

	private:
        void * bebida;
};

#endif // BEBDIA_H
