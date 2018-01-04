#include "../headerfiles/EnemigoBasico.h"


/**
CONSTRUCTOR DE ENEMIGO BASICO
Parametros : Irrlicht objetos, vector con posiciones para la patrulla, entero para indicar si melee/distancia, Blackboard con datos necesarios para el arbol
**/
EnemigoBasico::EnemigoBasico(IrrlichtDevice *dev, ISceneManager *smgr, vector<Posicion*> pos, float xlength, float pendValue, int t, Blackboard *b):Enemigo(dev, smgr, pos, xlength, pendValue), black(nullptr)
{

    //ESTABLECEMOS LAS ESTADISTICAS ENEMIGO BASICO

    this->setEnergia(ENERGIA_MAX);
    this->setHambre(100.f);
    this->setSalud(29.f);
    this->setSed(100.f);
    this->setVelocidad(VELOCIDAD_NORMAL);

    tipo = t;

    black = b;                                             // Guardamos la blackboard 

    /* CREAMOS EL ARBOL DE COMPORTAMIENTO DE EL ENEMIGO BASICO PASANDOLE LA BLACKBOARD */

    comportamiento = new BehaviorTree(1, b);              
    

     /* Velocidad a la que bajan las estadisticas del enemigo */
    this->setVelHambre(-0.3);
    this->setVelSed(-0.5);

}

/**
PARA COMPROBAR EN QUE COMPORTAMIENTO ESTA EL ENEMIGO
**/
void EnemigoBasico::Update(core::vector3df prota, Objeto* alarma)
{
	this->update(prota);                                     // Llamamos tambien al update de la clase general del enemigo y actualizamos los valores de sed - hambre del mismo
  this->comprobarEnergia();

  comportamiento->update(this);                           // Empezamos a ejecutar el arbol de comportamiento del enemigo

  /*
	if(this->getAvistadoProta() == true)
	{
		this->AvistadoProta(prota, alarma);
	}
	*/
}


/*
FUNCION PARA COMPROBAR LA VELOCIDAD DEL ENEMIGOBASICO Y REDUCIR/AUMENTAR LA ENERGIA
*/
void EnemigoBasico::comprobarEnergia()
{
    if(VELOCIDAD_ENEMIGO >VELOCIDAD_NORMAL)  // Si su velcidad es mayor que la velocidad normal de moviemiento, empieza a bajar la energia
    {
        if(energia >0)
        {
            energia+= -20.f * frameDeltaTime;
        }
    }
    else{                       // Si no la supera, entonces la energia se recupera hasta su maximo
            if(energia<=ENERGIA_MAX)
            {
              energia += 10.f * frameDeltaTime;
            }
    }

}

/**
FUNCION PARA VER QUE HACE EL ENEMIGO BASICO CUANDO VE AL PROTAGONISTA
**/
void EnemigoBasico::AvistadoProta(core::vector3df prota, Objeto* alarma)
{
  
    // HUIR - ATACAR - ACTIVAR ALARMA
   
   if(this->getSalud() <=30)     // HUIR
   {
      
      this->setVelocidad(25.f);  // La velocidad del enemigo aumenta


      core::vector3df posicionE = enemigo->getPosition();

      if(prota.X <= posicionE.X)  // Si el protagonista esta a la izquierda, el enemigo huye hacia la derecha 
      {
          posicionE.X += VELOCIDAD_ENEMIGO * frameDeltaTime*3;

          enemigo->setPosition(posicionE);
      }
      else               
      {
          posicionE.X -= VELOCIDAD_ENEMIGO * frameDeltaTime*3;

          enemigo->setPosition(posicionE);
      }

   }
   else
   {
    /*
      this->setVelocidad(25.f);

      core::vector3df alarmaPosition = alarma->getVector3df();

      float distanciaAlarma = alarmaPosition.X - EnemigoPosition.X;

       if (distanciaAlarma<0) // AVANZAMOS HACIA LA IZQUIERDA
            {
                EnemigoPosition.X-= VELOCIDAD_ENEMIGO * frameDeltaTime*3;

                enemigo->setPosition(EnemigoPosition); // CAMBIAMOS LA POSICION

            }
            else{
                if(distanciaAlarma>0) // AVANZAMOS HACIA LA DERECHA
                {

                    EnemigoPosition.X+= VELOCIDAD_ENEMIGO * frameDeltaTime*3;

                    enemigo->setPosition(EnemigoPosition);
                }
               }
      */
   }


}


/**
FUNCION PARA VER QUE HACE EL ENEMIGO BASICO CUANDO SUENA LA ALARMA
**/
void EnemigoBasico::AlarmaSonando(scene::ISceneNode *alarma)
{

   

}



EnemigoBasico::~EnemigoBasico()
{
    //dtor

  delete comportamiento;
}
