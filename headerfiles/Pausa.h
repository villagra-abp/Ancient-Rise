#ifndef PAUSA_H
#define PAUSA_H

#include "../headerfiles/Objeto.h"



class Pausa : public Objeto
{

	public:
		Pausa( Posicion* pos);
		void* getNode();

	private:
        void * pausa;
        
};

#endif // PAUSA_H
