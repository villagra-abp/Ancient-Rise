#ifndef PANTALLACARGA_H
#define PANTALLACARGA_H

#include "../headerfiles/Posicion.h"
#include "../headerfiles/Fachada.h"

class PantallaCarga
{

	public:
		PantallaCarga( Posicion* pos);
        void update(int n);
        int getEstado();

	private:

		void* cargaLevel1;
		int estado;
      
};

#endif // PANTALLACARGA_H
