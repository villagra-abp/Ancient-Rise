#ifndef PAUSA_H
#define PAUSA_H

#include "../headerfiles/Objeto.h"



class Pausa
{

	public:
		Pausa( Posicion* pos);
        void update(int n);
        int getEstado();

	private:
        void * pausa;
        void * pausa2;
        void * pausa3;
        int estado=3;
        
};

#endif // PAUSA_H
