#include "Protagonista.h"
#include "Mundo.h"

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

    rec=smgr->addCubeSceneNode();

    if (rec) /** SI HEMOS CREADO EL CUBO **/
	{
		rec->setPosition(core::vector3df(50,0,30));
		//rec->setMaterialTexture(0, driver->getTexture(mediaPath + "wall.bmp"));
		rec->setMaterialFlag(video::EMF_LIGHTING, true);
	}


    saltando=false;
    correr=false;
    sigilo=false;
    direccion=1;
    energia = 100.f;
    protaPosition=rec->getPosition();

}

/**
FUNCION PARA CONTROLAR EL SALTO DEL PROTA
**/
void Protagonista::salto(const f32 Time)
{

    if(protaPosition.Y<30 && saltando==true){
            protaPosition.Y += VELOCIDAD_MOVIMIENTO * Time*1.5;
            if(energia>1)
                this->setEnergia(-0.5f, Time);
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

void Protagonista::setEnergia(f32 cantidad, const f32 Time)
{
    energia+=cantidad*Time;
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
Protagonista::~Protagonista()
{
    //dtor
}
