#ifndef HUD_H
#define HUD_H

#include "../headerfiles/Posicion.h"
#include "../headerfiles/Fachada.h"

class Hud
{

	public:
		Hud( Posicion* pos);
        void update(float vida,float energia);

	private:
        void * hud1;
        void * hud2;
        void * hud3;
        void * hud4;
        void * hud5;//marco vida
        void * hud6;//marco energia
        
};

#endif // HUD_H
