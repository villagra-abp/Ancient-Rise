#ifndef MUERTE_H
#define MUERTE_H

#include "../headerfiles/Posicion.h"
#include "../headerfiles/Fachada.h"

class Muerte
{

	public:
		Muerte( Posicion* pos);
        void update(int n);
        int getEstado();

	private:
        void * muerte;
        int estado=2;
        Fachada* fachada;
};

#endif // MUERTE_H
