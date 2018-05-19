#ifndef MENU_H
#define MENU_H

#include "../headerfiles/Posicion.h"
#include "../headerfiles/Fachada.h"

class Menu
{

	public:
		Menu( Posicion* pos);
        void update(int n);
        int getEstado();

	private:
        void * menu;
        void * menu2;
        void * menu3;
        int estado=3;
};

#endif // MENU_H
