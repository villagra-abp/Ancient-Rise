#include "../headerfiles/MyEventReceiver.h"

/**
    Clase para poder recoger los eventos ( entrada por teclado )
**/
void MyEventReceiver::checkInput(Protagonista *prota,const f32 frameDeltaTime){
	
     /* lanza el salto al pulsat w */

	if(IsKeyDown(irr::KEY_SPACE)){
        saltar(prota,frameDeltaTime,true);
	}else
        saltar(prota,frameDeltaTime,false);
        /* control de correr*/

        if(IsKeyDown(irr::KEY_LSHIFT)){
        	sprintar(prota,frameDeltaTime);
        }else
            prota->setCorrer(false);



        /* hacemos un set de ataque a 2 que es arriba */
        if(IsKeyDown(irr::KEY_KEY_W))
        {
           pos_pelea(prota,7);
           pos_defensa(prota,3);
		}
		else if(IsKeyDown(irr::KEY_KEY_S))
		{
			pos_pelea(prota,-9);
            pos_defensa(prota,1);
		}
		else
		{
			pos_pelea(prota,0);
            pos_defensa(prota,2);
		}



        /* control de ataque*/
        if(IsKeyDown(irr::KEY_KEY_P))
        {  
        	atacar(prota,true);
		}
		/* control de ataque*/
        if(IsKeyDown(irr::KEY_KEY_K))
        {
			defender(prota,true);

		}else
        {
            defender(prota,false);
        }

        /* movimiento hacia los lados y control de la velocidad en funcion de
        las variables de correr, sigilo y vitalidad */

		if(IsKeyDown(irr::KEY_KEY_A))
        {
            direccion(prota,0);
			moverse(prota,frameDeltaTime);
		}

		else if(IsKeyDown(irr::KEY_KEY_D)){

            direccion(prota,1);
			moverse(prota,frameDeltaTime);
		}
}
void MyEventReceiver::checkSigilo(Protagonista *prota,const f32 frameDeltaTime){
	 if(IsKeyDown(irr::KEY_KEY_C)) // AGACHARSE
     {
        relentizar(prota,frameDeltaTime);
     }
}
