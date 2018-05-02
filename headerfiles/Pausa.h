#ifndef PAUSA_H
#define PAUSA_H

#include "../headerfiles/Objeto.h"



class Pausa : public Objeto
{

	public:
		Pausa( Posicion* pos);
		void* getNode();
        void update(int n);
        int getEstado();

	private:
        void * pausa;
        int estado=1;
        
};

#endif // PAUSA_H
