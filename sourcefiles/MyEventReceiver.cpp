#include "../headerfiles/MyEventReceiver.h"




MyEventReceiver::MyEventReceiver()
{
    for (u32 i=0; i<KEY_KEY_CODES_COUNT; ++i)
            KeyIsDown[i] = false;
}


bool MyEventReceiver::OnEvent(const SEvent& event)
{
    // Remember whether each key is down or up
     if (event.EventType == irr::EET_KEY_INPUT_EVENT)
    {
        KeyIsDown[event.KeyInput.Key] = event.KeyInput.PressedDown;
    }

    // The state of each connected joystick is sent to us
    // once every run() of the Irrlicht device.  Store the
    // state of the first joystick, ignoring other joysticks.
    // This is currently only supported on Windows and Linux.
    if (event.EventType == irr::EET_JOYSTICK_INPUT_EVENT
            && event.JoystickEvent.Joystick == 0)
    {
        JoystickState = event.JoystickEvent;
    }
    return false;
}

 /*
Para saber que tecla esta pulsada
*/
bool MyEventReceiver::IsKeyDown(EKEY_CODE keyCode) const
{
    return KeyIsDown[keyCode];
}

/**
    Clase para poder recoger los eventos ( entrada por teclado y por mando)
**/
void MyEventReceiver::checkInput(Protagonista *prota,const f32 frameDeltaTime)
{
    
    /*Recogida de eventos del mando*/
        bool movedWithJoystick = false;

        
            f32 moveHorizontal = 0.f; // Range is -1.f for full left to +1.f for full right
            f32 moveVertical = 0.f; // -1.f for full down to +1.f for full up.

            const SEvent::SJoystickEvent & joystickData = this->GetJoystickState();
        if(mando){
            // We receive the full analog range of the axes, and so have to implement our
            // own dead zone.  This is an empirical value, since some joysticks have more
            // jitter or creep around the center point than others.  We'll use 5% of the
            // range as the dead zone, but generally you would want to give the user the
            // option to change this.
            const f32 DEAD_ZONE = 0.25f;

            moveHorizontal =
                (f32)joystickData.Axis[SEvent::SJoystickEvent::AXIS_X] / 32767.f;
            if(fabs(moveHorizontal) < DEAD_ZONE)
                moveHorizontal = 0.f;

            moveVertical =
                (f32)joystickData.Axis[SEvent::SJoystickEvent::AXIS_Y] / -32767.f;
            if(fabs(moveVertical) < DEAD_ZONE)
                moveVertical = 0.f;

            // POV hat info is only currently supported on Windows, but the value is
            // guaranteed to be 65535 if it's not supported, so we can check its range.
            /*const u16 povDegrees = joystickData.POV / 100;
            if(povDegrees < 360)
            {
                if(povDegrees > 0 && povDegrees < 180)
                    moveHorizontal = 1.f;
                else if(povDegrees > 180)
                    moveHorizontal = -1.f;

                if(povDegrees > 90 && povDegrees < 270)
                    moveVertical = -1.f;
                else if(povDegrees > 270 || povDegrees < 90)
                    moveVertical = +1.f;
            }
            */
            if(!core::equals(moveHorizontal, 0.f) || !core::equals(moveVertical, 0.f))
            {
               // nodePosition.X += 5 * frameDeltaTime * moveHorizontal;
               // nodePosition.Y += 5 * frameDeltaTime * moveVertical;
                if(moveHorizontal<0)
                {
                    direccion(prota,0);
                    moverse(prota,frameDeltaTime);
                }
                else if(moveHorizontal>0)
                {
                    direccion(prota,1);
                    moverse(prota,frameDeltaTime);    
                }   
                
                movedWithJoystick = true;
            }
        
        }

    if(prota->getCombate()==false)         // COMBATE DESACTIVADO --> Saltar, Correr y sigilo
    {
        /* lanza el salto al pulsat w */
        if(IsKeyDown(irr::KEY_SPACE))
        {
            saltar(prota,true);
        }
        else
        {
            saltar(prota,false);
        }

        /* control de correr*/
        if(IsKeyDown(irr::KEY_LSHIFT))
        {
            sprintar(prota);
        }
        else
        {
            prota->setCorrer(false);
        }
     }
     else   // COMBATE ACTIVADO --> Esquivar, Cambiar pos de combate, atacar
     {

        /* hacemos un set de ataque a 2 que es arriba */
        if(IsKeyDown(irr::KEY_KEY_W))
        {
            prota->setPosCombate(1);    // pos_combate = arriba
        }
        else if(IsKeyDown(irr::KEY_KEY_S))
        {
            prota->setPosCombate(3);    // pos_combate = abajo
        }
        else
        {   
            prota->setPosCombate(2);  // pos_combate = centro
        }

        /* control de ataque*/
        if(IsKeyDown(irr::KEY_KEY_P))
        {  
            atacar(prota,true);
        }
        else
        {
            atacar(prota,false);
        }
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
void MyEventReceiver::checkSigilo(Protagonista *prota){
     const SEvent::SJoystickEvent & joystickData = this->GetJoystickState();
     if(IsKeyDown(irr::KEY_KEY_C)||((u32)joystickData.IsButtonPressed(3)&&mando)) // AGACHARSE
     {
        ralentizar(prota);
     }
}

void MyEventReceiver::checkCombate(Protagonista *prota)
{
     const SEvent::SJoystickEvent & joystickData = this->GetJoystickState();
     if(IsKeyDown(irr::KEY_KEY_K)||((u32)joystickData.IsButtonPressed(4)&&mando)) // MODO COMBATE
     {
        prota->setCombate();    // ACTIVAMOS O DESACTIVAMOS
     }

}

/**
    Funciines para poder las acciones de las teclas
**/
void MyEventReceiver::saltar(Protagonista *p, bool salta){
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
}
void MyEventReceiver::ralentizar(Protagonista *p){
    p->setSigilo();
    p->setCorrer(false);

}
void MyEventReceiver::sprintar(Protagonista *p){
    p->setCorrer(true);          
}
void MyEventReceiver::direccion(Protagonista *p,int n){
    p->setDireccion(n);

}
void MyEventReceiver::setMando(bool b){
    mando=b;
}
