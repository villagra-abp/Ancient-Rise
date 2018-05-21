#ifndef PANTALLACARGA_H
#define PANTALLACARGA_H

#include "../headerfiles/Posicion.h"
#include "../headerfiles/Fachada.h"

class PantallaCarga
{

	public:
		PantallaCarga( Posicion* pos);
        void update();
        int getEstado();
        void setPantallaCarga(int p);
        int getPantallaCarga();

	private:

		void* cargaLevel1, *cargaLevel2, *cargaLevel3;
		int estado, pantallaCarga;
		Fachada* fachada;
      
};

#endif // PANTALLACARGA_H
