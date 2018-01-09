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
           pos_pelea(prota,2);
           pos_defensa(prota,2);
        }
        else if(IsKeyDown(irr::KEY_KEY_S))
        {
            pos_pelea(prota,0);
            pos_defensa(prota,0);
        }
        else
        {
            pos_pelea(prota,1);
            pos_defensa(prota,1);
        }



        /* control de ataque*/
        if(IsKeyDown(irr::KEY_KEY_P))
        {  
            atacar(prota,true);
        }
        
        /* control de defensa*/
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

/**
    Funciines para poder las acciones de las teclas
**/
void MyEventReceiver::saltar(Protagonista *p,const f32 Time, bool salta){
    p->setSalto(salta);
  //prota->setEnergia(-250.f, frameDeltaTime);
}
void MyEventReceiver::moverse(Protagonista *p,const f32 Time){
    p->movimiento(Time);
    if(p->getCorrer()==true)
    {
        p->setEnergia(-20.0f,Time);
    }
}
void MyEventReceiver::atacar(Protagonista *p,bool b){
    p->setAtaque(b);
    //p->setEnergia(-5.0f,.5f);
}
void MyEventReceiver::defender(Protagonista *p,bool b){
    p->setDefensa(b);
}
void MyEventReceiver::relentizar(Protagonista *p,const f32 Time){
    p->setSigilo();
    p->setCorrer(false);

}
void MyEventReceiver::sprintar(Protagonista *p,const f32 Time){
    p->setCorrer(true);          
}
void MyEventReceiver::pos_pelea(Protagonista *p,int n){
    p->setAtaquePosition(n);
    
}
void MyEventReceiver::pos_defensa(Protagonista *p,int n){
    
    p->setDefensaPosition(n);

}
void MyEventReceiver::direccion(Protagonista *p,int n){
    p->setDireccion(n);

}
