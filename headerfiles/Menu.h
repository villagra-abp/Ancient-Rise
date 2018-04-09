#ifndef MENU_H
#define MENU_H

#include "../headerfiles/Objeto.h"



class Menu : public Objeto
{

	public:
		Menu( Posicion* pos);
		void* getNode();

	private:
        void * menu;
        
};

#endif // MENU_H
