#include "../headerfiles/Protagonista.h"

/**
 Constructor: CREA UN NODO PASANDOLE POR PARAMETRO EL DEVICE Y EL PUNTERO PARA GESTIONAR LA ESCENA
**/
Protagonista::Protagonista(IrrlichtDevice *dev, ISceneManager* smgr)
{

    /**
	Creamos un nodo que va ser movido con las teclas WSAD. Es una esfera que posicionamos
	en (0,0,30) y le asignamos una texura. Como no tenemos luces dinamicas en esta escena
	desabilitamos la luz en cada modelo (sino los modelos serian negros )

	**/
    
    rec=smgr->addSphereSceneNode();
    energy=smgr->addCubeSceneNode();
    life=smgr->addCubeSceneNode();

    if (rec) /** SI HEMOS CREADO EL CUBO **/
	{
		rec->setPosition(core::vector3df(0,0,30));
		//rec->setMaterialTexture(0, driver->getTexture(mediaPath + "wall.bmp"));
		rec->setMaterialFlag(video::EMF_LIGHTING, true);
	}
    
    life->setMaterialFlag(video::EMF_LIGHTING,false);

    ataca=false;
    defensa=false;
    saltando=false;
    correr=false;
    sigilo=false;
    direccion=1;
    cont_ataque=0;
    cont_defensa=0;
    cont_recarga_enemigo=0;
    ataque_position=0;
    defensa_position=0;
    energia = 100.f;
    vida = 100.f;
    protaPosition=rec->getPosition();
    energyScale=energy->getScale();
    energyScale.Z=0.1f;
    lifeScale=life->getScale();
    lifeScale.Z=0.1f;
    energy->setScale(energyScale);
    life->setScale(lifeScale);

}
/**
FUNCION PARA DIBUJAR LA INTERFAZ
**/
void Protagonista::pintarInterfaz()
{
    //barra para mostrar la enegia
    energyPosition=protaPosition;
    energyPosition.X-=80;
    energyPosition.Y=120;
    energyPosition.Z-=30;
    energy->setPosition(energyPosition);
    lifePosition=protaPosition;
    lifePosition.X-=80;
    lifePosition.Y=140;
    lifePosition.Z-=30;
    life->setPosition(lifePosition);
    energyScale.X=energia/10;
    energy->setScale(energyScale);
    lifeScale.X=vida/10;
    life->setScale(lifeScale);
    //std::cout<<ataca<<"\n";
}
/**
FUNCION PARA CONTROLAR EL SALTO DEL PROTA
**/
void Protagonista::salto(const f32 Time)
{

    if(protaPosition.Y<30 && saltando==true){
        if(correr==true)
        {
            protaPosition.Y += VELOCIDAD_MOVIMIENTO * Time*2.;
        }else
        {
            protaPosition.Y += VELOCIDAD_MOVIMIENTO * Time*1.5;
        }
        
	    if(energia>0)
	       setEnergia(-50.f,Time);
        /*
        if(direccion==1){
           protaPosition.X += VELOCIDAD_MOVIMIENTO * Time*0;
        }
        else
            protaPosition.X -= VELOCIDAD_MOVIMIENTO * Time*0;
        */
    }
    else
    {
        saltando=false;
    }

    // SIMULA LA GRAVEDAD
    if(protaPosition.Y>0 && saltando==false)
    {
        protaPosition.Y -= VELOCIDAD_MOVIMIENTO * Time*1.5;
    }
    if(protaPosition.Y<0)
    {
        protaPosition.Y=0;
    }

    
}
/**
FUNCION PARA CONTROLAR EL ATAQUE DEL PROTA
**/
void Protagonista::ataque(const f32 Time)
{
    //std::cout<<cont_ataque<<"\n";
    
    
    if(cont_ataque>0 && cont_ataque<20){
        
        if(ataca==true && direccion==1){
            if(cont_ataque<20 && ataque_position==1){
                protaPosition.Y =0;
                if(cont_ataque>10){
                    protaPosition.X -= 2;
                }else
                    protaPosition.X += 2;
            }else if(cont_ataque<20 && ataque_position==2){
                protaPosition.Y =10;
                if(cont_ataque>10){
                    protaPosition.X -= 2;
                }else
                    protaPosition.X += 2;
            }else if(cont_ataque<20 && ataque_position==0){
                protaPosition.Y =-10;
                if(cont_ataque>10){
                    protaPosition.X -= 2;
                }else
                    protaPosition.X += 2;
            }
                
        }else if(ataca==true && direccion==0){
            if(cont_ataque<20 && ataque_position==1){
                protaPosition.Y =0;
                if(cont_ataque>10){
                    protaPosition.X += 2;
                }else
                    protaPosition.X -= 2;
            }else if(cont_ataque<20 && ataque_position==2){
                protaPosition.Y =10;
                if(cont_ataque>10){
                    protaPosition.X += 2;
                }else
                    protaPosition.X -= 2;
            }else if(cont_ataque<20 && ataque_position==0){
                protaPosition.Y =-10;
                if(cont_ataque>10){
                    protaPosition.X += 2;
                }else
                    protaPosition.X -= 2;
            }
    } 
        
    cont_ataque++;  
    }
    else if(cont_ataque>=20){
        protaPosition.Y =0;
        cont_ataque=0;
        ataca=false;
    }

}
/**
FUNCION PARA CONTROLAR LA DEFENSA DEL PROTA
**/
void Protagonista::defender(const f32 Time)
{
    //std::cout<<cont_ataque<<"\n";
    
    
    if(cont_defensa>0 && cont_defensa<20){
        
        if(defensa==true && direccion==1){
            if(cont_defensa<20 && defensa_position==1){
                protaPosition.Y =0;
                if(cont_defensa>10){
                    protaPosition.X += 0.5;
                }else
                    protaPosition.X -= 0.5;
            }else if(cont_defensa<20 && defensa_position==2){
                protaPosition.Y =10;
                if(cont_defensa>10){
                    protaPosition.X += 0.5;
                }else
                    protaPosition.X -= 0.5;
            }else if(cont_defensa<20 && defensa_position==0){
                protaPosition.Y =-10;
                if(cont_defensa>10){
                    protaPosition.X += 0.5;
                }else
                    protaPosition.X -= 0.5;
            }
                
        }else if(defensa==true && direccion==0){
            if(cont_defensa<20 && defensa_position==1){
                protaPosition.Y =0;
                if(cont_defensa>10){
                    protaPosition.X -= 0.5;
                }else
                    protaPosition.X += 0.5;
            }else if(cont_defensa<20 && defensa_position==2){
                protaPosition.Y =10;
                if(cont_defensa>10){
                    protaPosition.X -= 0.5;
                }else
                    protaPosition.X += 0.5;
            }else if(cont_defensa<20 && defensa_position==0){
                protaPosition.Y =-10;
                if(cont_defensa>10){
                    protaPosition.X -= 0.5;
                }else
                    protaPosition.X += 0.5;
            }
    } 
        
    cont_defensa++;  
    }
    else if(cont_defensa>=20){
        protaPosition.Y =0;
        cont_defensa=0;
        defensa=false;
    }

}

/**
FUNCION PARA CONTROLAR EL MOVIMIENTO DEL PROTA
**/

void Protagonista::movimiento(const f32 Time)
{
    if(direccion==0) // MOVIMIENTO HACIA LA IZQUIERDA
    {

        if(sigilo==true)
        {
            protaPosition.X -= VELOCIDAD_MOVIMIENTO * Time*0.5;
        }else if(correr==true && energia>10.1)
        {
                protaPosition.X -= VELOCIDAD_MOVIMIENTO * Time*3;

                if(energia>10)
                {
                    //vitalidad -=0.3f;
                }else
                    correr=false;
        }else
        {
            protaPosition.X -= VELOCIDAD_MOVIMIENTO * Time*1.5;
        }

    }
    else        //MOVIMIENTO HACIA LA DERECHA
    {
         if(sigilo==true)
          {
                protaPosition.X += VELOCIDAD_MOVIMIENTO * Time*0.5;
            }else if(correr==true && energia>10.1){
                protaPosition.X += VELOCIDAD_MOVIMIENTO * Time*3;
                if(energia>10){
                    //vitalidad -=0.3f;
                }else
                    correr=false;
            }else
                protaPosition.X += VELOCIDAD_MOVIMIENTO * Time*1.5;
    }
    

}
/**
FUNCION PARA COMPROBAR LAS COLISIONES
**/
void Protagonista::comprobarColision(Enemigo *enemigo)
{
    enemigoPosition=enemigo->getNode()->getPosition();
    if((enemigoPosition.X-(protaPosition.X+15))<=0 
        && (enemigoPosition.X-(protaPosition.X+15))>-25
        && vida<=100 && vida>0 && protaPosition.Y==0){
        if(ataca)
        {
            enemigo->getNode()->setVisible(false);
        }else if(enemigo->getNode()->isVisible())
        {
           vida-=5; 
        }   
    }
    cont_recarga_enemigo++;
    if(cont_recarga_enemigo>20){
        enemigo->getNode()->setVisible(true);
        cont_recarga_enemigo=0;
    }
}
/**
FUNCION PARA COMPROBAR LA VIDA DEL PROTA
**/
bool Protagonista::checkVida()
{
    if(vida<=0)
    {
        return false;
    }else
    {
        return true;
    }
}
/**
FUNCION PARA RECUPERAR LA VIDA DEL PROTA
**/
void Protagonista::recuperarVida(const f32 Time)
{
    if(vida<100)
        vida+=5* Time;
    if(vida>100){
        vida=100;
    }
}

void Protagonista::setVida(f32 cantidad,const f32 Time)
{
    if(vida<100)
        vida+=cantidad* Time;
    if(vida<0){
        vida=0;
    }else if(vida>100){
        vida=100;
    }
}
/**
FUNCION PARA RECUPERAR EL CANSANCIO DEL PROTA
**/
void Protagonista::recuperarEnergia(const f32 Time)
{
    if(energia<100)
        energia+=10* Time;
    if(energia>=100){
        energia=100;
        recuperarVida(Time);
    }
}

void Protagonista::setEnergia(f32 cantidad,const f32 Time)
{
    if(energia>0 || energia<100)
    	energia+=cantidad* Time;
    if(energia<0){
        energia=0;
        setVida(-5,Time);
    }
}

/**
DEVUELVE EL NODO QUE HEMOS CREADO
**/
scene::ISceneNode* Protagonista::getNode()
{
    return rec;
}

/**
ACTUALIZA EL VALOR DEL SALTO (TRUE/FALSE)
**/
void Protagonista::setSalto(bool s)
{
   saltando=s;
}

core::vector3df Protagonista::getPosition()
{
   return protaPosition;
}

/**
ACTUALIZA LA POSICION DEL PROTA
**/
void Protagonista::setPosition(core::vector3df v)
{
   protaPosition=v;
}

f32 Protagonista::getEnergia()
{
    return energia;
}

bool Protagonista::getSigilo()
{
    return sigilo;
}

void Protagonista::setSigilo()
{
    if(sigilo==false)
    {
        sigilo=true;
    }
    else{

        sigilo=false;
    }
}

void Protagonista::setCorrer(bool s)
{
    correr=s;
}

void Protagonista::setDireccion(int d)
{
    direccion=d;
}
void Protagonista::setAtaquePosition(int d)
{
    ataque_position=d;
}
void Protagonista::setAtaque(bool d)
{

    ataca=d;
    if(cont_ataque==0 && !saltando)
        cont_ataque=1;
}
void Protagonista::setDefensaPosition(int d)
{
    defensa_position=d;
}
void Protagonista::setDefensa(bool d)
{

    defensa=d;
    if(cont_defensa==0 && !saltando)
        cont_defensa=1;
}
Protagonista::~Protagonista()
{
    //dtor
}
