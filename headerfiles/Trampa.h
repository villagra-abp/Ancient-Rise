#ifndef TRAMPA_H
#define TRAMPA_H

#include "../headerfiles/Objeto.h"



class Trampa : public Objeto
{

	public:
		Trampa(Posicion* pos);
		void* getNode();

	private:
        void * trampa;
        //core::vector3df trampaPosition;
        //IVideoDriver* 		driver;
};

#endif // TRAMPA_H
