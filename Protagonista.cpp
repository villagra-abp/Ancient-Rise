#include "Protagonista.h"

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
    saltando=false;
    correr=false;
    sigilo=false;
    direccion=1;
    cont_ataque=0;
    ataque_position=0;
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

}
/**
FUNCION PARA CONTROLAR EL SALTO DEL PROTA
**/
void Protagonista::salto(const f32 Time)
{

    if(protaPosition.Y<30 && saltando==true){
            protaPosition.Y += VELOCIDAD_MOVIMIENTO * Time*1.5;
	   if(energia>0)
	    energia-=30*Time;
            if(direccion==1){
                protaPosition.X += VELOCIDAD_MOVIMIENTO * Time*0.2;
            }
            else
                protaPosition.X -= VELOCIDAD_MOVIMIENTO * Time*0.2;

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

    
}
/**
FUNCION PARA CONTROLAR EL ATAQUE DEL PROTA
**/
void Protagonista::ataque(const f32 Time)
{
    //std::cout<<cont_ataque<<"\n";
    
    
    if(cont_ataque>0 && cont_ataque<20){
        
        if(ataca==true && direccion==1){
            if(cont_ataque<20 && ataque_position==0){
                protaPosition.Y =-10;
                if(cont_ataque>10){
                    protaPosition.X -= 2;
                }else
                    protaPosition.X += 2;
            }else if(cont_ataque<20 && ataque_position==1){
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
            }
                
        }else if(ataca==true && direccion==0){
            if(cont_ataque<20 && ataque_position==0){
                protaPosition.Y =-10;
                if(cont_ataque>10){
                    protaPosition.X += 2;
                }else
                    protaPosition.X -= 2;
            }else if(cont_ataque<20 && ataque_position==1){
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
            }
    } 
        
    cont_ataque++;  
    }
    else if(cont_ataque>=20){
        cont_ataque=0;
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
FUNCION PARA RECUPERAR EL CANSANCIO DEL PROTA
**/

void Protagonista::setEnergia(f32 cantidad,const f32 Time)
{
    if(energia>0 || energia<100)
    	energia+=cantidad* Time;
    if(energia<0){
        energia=0;
    }else if(energia>100){
        energia=100;
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
Protagonista::~Protagonista()
{
    //dtor
}
