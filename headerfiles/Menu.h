#ifndef MENU_H
#define MENU_H

#include "../headerfiles/Objeto.h"



class Menu : public Objeto
{

	public:
		Menu( Posicion* pos);
		void* getNode();
        void update(int n);
        int getEstado();

	private:
        void * menu;
        void * menu2;
        void * menu3;
        int estado=3;
};

#endif // MENU_H
