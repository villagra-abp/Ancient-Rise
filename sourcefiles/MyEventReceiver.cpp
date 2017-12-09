#include "../headerfiles/MyEventReceiver.h"

/**
    Clase para poder recoger los eventos ( entrada por teclado )
**/
void MyEventReceiver::checkInput(Protagonista *prota,const f32 frameDeltaTime){
	
     /* lanza el salto al pulsat w */

		if(IsKeyDown(irr::KEY_SPACE) && prota->getPosition().Y<=0){
            saltar(prota,frameDeltaTime);

		}
        /* control de correr*/

        if(IsKeyDown(irr::KEY_LSHIFT)){
        	sprintar(prota,frameDeltaTime);
        }else
            prota->setCorrer(false);



        /* hacemos un set de ataque a 2 que es arriba */
        if(IsKeyDown(irr::KEY_KEY_W))
        {
           pos_pelea(prota,2);

		}
		else if(IsKeyDown(irr::KEY_KEY_S))
		{
			pos_pelea(prota,0);

		}
		else
		{
			pos_pelea(prota,1);
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
