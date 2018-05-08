#ifndef OPCIONES_H
#define OPCIONES_H

#include "../headerfiles/Objeto.h"



class Opciones
{

	public:
		Opciones( Posicion* pos);
        void update(int n,bool sonido,bool sombra);
        int getEstado();
        bool getShadow();
        bool getSound();
        bool getJuego();
        void setJuego(bool jugando);

	private:
        void * opcion1;
        void * opcion2;
        int estado=5;
        bool sound=true;
        bool shadow=true;
        bool juego=false;
        
};

#endif // OPCIONES_H
