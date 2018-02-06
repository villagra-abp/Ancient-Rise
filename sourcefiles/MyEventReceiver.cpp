#include "../headerfiles/MyEventReceiver.h"

/**
    Clase para poder recoger los eventos ( entrada por teclado )
**/
void MyEventReceiver::checkInput(){
    
     /* lanza el salto al pulsat w */
/*
    if(IsKeyDown(irr::KEY_SPACE)){
        //saltar(true);
    }else
        saltar(false);
       
        if(IsKeyDown(irr::KEY_LSHIFT)){
            sprintar(prota,frameDeltaTime);
        }else
            prota->setCorrer(false);



        /* hacemos un set de ataque a 2 que es arriba 
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



        /* control de ataque
        if(IsKeyDown(irr::KEY_KEY_P))
        {  
            atacar(prota,true);
        }
        
        /* control de defensa
        if(IsKeyDown(irr::KEY_KEY_K))
        {
            defender(prota,true);

        }else
        {
            defender(prota,false);
        }

        /* movimiento hacia los lados y control de la velocidad en funcion de
        las variables de correr, sigilo y vitalidad 

        if(IsKeyDown(irr::KEY_KEY_A))
        {
            direccion(prota,0);
            moverse(prota,frameDeltaTime);
        }

        else if(IsKeyDown(irr::KEY_KEY_D)){

            direccion(prota,1);
            moverse(prota,frameDeltaTime);
        }
        */
}
void MyEventReceiver::checkSigilo(){
     if(IsKeyDown(irr::KEY_KEY_C)) // AGACHARSE
     {
        //relentizar(prota,frameDeltaTime);
     }
}

/**
    Funciines para poder las acciones de las teclas
**/
void MyEventReceiver::saltar(bool salta){
    p->setSalto(salta);
  //prota->setEnergia(-250.f, frameDeltaTime);
}
void MyEventReceiver::moverse(){
    p->movimiento(0.1f);
    if(p->getCorrer()==true)
    {
        p->setEnergia(-20.0f,0.1f);
    }
}
void MyEventReceiver::atacar(bool b){
    p->setAtaque(b);
    //p->setEnergia(-5.0f,.5f);
}
void MyEventReceiver::defender(bool b){
    p->setDefensa(b);
}
void MyEventReceiver::relentizar(){
    p->setSigilo();
    p->setCorrer(false);

}
void MyEventReceiver::sprintar(){
    p->setCorrer(true);          
}
void MyEventReceiver::pos_pelea(int n){
    p->setAtaquePosition(n);
    
}
void MyEventReceiver::pos_defensa(int n){
    
    p->setDefensaPosition(n);

}
void MyEventReceiver::direccion(int n){
    p->setDireccion(n);

}
void MyEventReceiver::setProta(Protagonista *prota){
    p=prota;

}
