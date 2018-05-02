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
        int estado=1;
};

#endif // MENU_H
