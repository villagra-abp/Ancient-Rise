#ifndef HUD_H
#define HUD_H

#include "../headerfiles/Objeto.h"



class Hud : public Objeto
{

	public:
		Hud( Posicion* pos);
		void* getNode();

	private:
        void * hud1;
        void * hud2;
        void * hud3;
        void * hud4;
        
};

#endif // HUD_H
