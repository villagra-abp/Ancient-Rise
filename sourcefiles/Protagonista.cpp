#include "../headerfiles/Protagonista.h"
#define SCALE 30.0f



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
    estaEnSuelo=false;
    estaCayendo=true;
    direccion=1;
    cont_ataque=0;
    cont_defensa=0;
    cont_salto=0;
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
FUNCION PARA crear el objeto dinamico
**/
void Protagonista::CreateBox(b2World& world, float X, float Y)
{

    BodyDef.position = b2Vec2(X/SCALE, Y/SCALE);
    BodyDef.type = b2_dynamicBody;
    Body = world.CreateBody(&BodyDef);
    Shape.SetAsBox((20.f/2)/SCALE, (20.f/2)/SCALE);
    b2FixtureDef FixtureDef;
    FixtureDef.density = 1.f;
    FixtureDef.friction = 0.7f;
    FixtureDef.shape = &Shape;
    Body->CreateFixture(&FixtureDef);

  
}
/**
FUNCION PARA crear el objeto estatico
**/
void Protagonista::CreateGround(b2World& world, float X, float Y,int largo)
{
    b2BodyDef BodyDef;
    BodyDef.position = b2Vec2(X/SCALE, Y/SCALE);
    BodyDef.type = b2_staticBody;
    b2Body* Ground = world.CreateBody(&BodyDef);
    b2PolygonShape Shape;
    Shape.SetAsBox((largo/2)/SCALE, (300.f/2)/SCALE);
    b2FixtureDef FixtureDef;
    FixtureDef.density = 0.f;
    FixtureDef.shape = &Shape;
    Ground->CreateFixture(&FixtureDef);

}
/**
FUNCION PARA actualizar el cuerpo
**/
void Protagonista::updateBody(b2World& world)
{
    
    
    protaPosition.X=Body->GetPosition().x*1;
    protaPosition.Y=Body->GetPosition().y*1;


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
    //std::cout<<estaCayendo<<"\n";
}
/**
FUNCION PARA CONTROLAR LA GRAVEDAD
**/
void Protagonista::gravedad(const f32 Time)
{
    // SIMULA LA GRAVEDAD
    if(protaPosition.Y>0 && saltando==false && estaEnSuelo==false)
    {
        protaPosition.Y -= VELOCIDAD_MOVIMIENTO * Time*1.5;
        estaCayendo=true;
    }else if(estaEnSuelo && protaPosition.Y>=35 && saltando==false)
    {
        protaPosition.Y -= VELOCIDAD_MOVIMIENTO * Time*1.5;
        estaCayendo=true;    
    }else
        estaCayendo=false;

    if(protaPosition.Y<0)
    {
        protaPosition.Y=0;
    }

}
/**
FUNCION PARA CONTROLAR EL SALTO DEL PROTA
**/
void Protagonista::salto(const f32 Time)
{

    if(cont_salto>0 && cont_salto<20){
        //Body->SetLinearVelocity(b2Vec2(0.f,2000000.f));
        //protaPosition.Y+=2;
        cont_salto++;  
    }
    else{
        //protaPosition.Y =0;
        cont_salto=0;
        saltando=false;
    }
    std::cout<<correr<<"\n";
}
/**
FUNCION PARA CONTROLAR EL ATAQUE DEL PROTA
**/
void Protagonista::ataque(const f32 Time)
{
    //std::cout<<cont_ataque<<"\n";
    int pos_actual;
    if(estaEnSuelo){
        pos_actual=34;
    }else
        pos_actual=0;
    
    if(cont_ataque>0 && cont_ataque<20){
        
        if(ataca==true && direccion==1){
            if(cont_ataque<20 && ataque_position==1){
                protaPosition.Y =pos_actual;
                if(cont_ataque>10){
                    protaPosition.X -= 2;
                }else
                    protaPosition.X += 2;
            }else if(cont_ataque<20 && ataque_position==2){
                protaPosition.Y =pos_actual+4;
                if(cont_ataque>10){
                    protaPosition.X -= 2;
                }else
                    protaPosition.X += 2;
            }else if(cont_ataque<20 && ataque_position==0){
                protaPosition.Y =pos_actual-4;
                if(cont_ataque>10){
                    protaPosition.X -= 2;
                }else
                    protaPosition.X += 2;
            }
                
        }else if(ataca==true && direccion==0){
            if(cont_ataque<20 && ataque_position==1){
                protaPosition.Y =pos_actual;
                if(cont_ataque>10){
                    protaPosition.X += 2;
                }else
                    protaPosition.X -= 2;
            }else if(cont_ataque<20 && ataque_position==2){
                protaPosition.Y =pos_actual+4;
                if(cont_ataque>10){
                    protaPosition.X += 2;
                }else
                    protaPosition.X -= 2;
            }else if(cont_ataque<20 && ataque_position==0){
                protaPosition.Y =pos_actual-4;
                if(cont_ataque>10){
                    protaPosition.X += 2;
                }else
                    protaPosition.X -= 2;
            }
    } 
        
    cont_ataque++;  
    }
    else if(cont_ataque>=20){
        protaPosition.Y =pos_actual;
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
    int pos_actual;
    if(estaEnSuelo){
        pos_actual=34;
    }else
        pos_actual=0;

    
    if(cont_defensa>0 && cont_defensa<20){
        
        if(defensa==true && direccion==1){
            if(cont_defensa<20 && defensa_position==1){
                protaPosition.Y =pos_actual;
                if(cont_defensa>10){
                    protaPosition.X += 0.1;
                }else
                    protaPosition.X -= 0.1;
            }else if(cont_defensa<20 && defensa_position==2){
                protaPosition.Y =pos_actual+4;
                if(cont_defensa>10){
                    protaPosition.X += 0.1;
                }else
                    protaPosition.X -= 0.1;
            }else if(cont_defensa<20 && defensa_position==0){
                protaPosition.Y =pos_actual-4;
                if(cont_defensa>10){
                    protaPosition.X += 0.1;
                }else
                    protaPosition.X -= 0.1;
            }
                
        }else if(defensa==true && direccion==0){
            if(cont_defensa<20 && defensa_position==1){
                protaPosition.Y =pos_actual;
                if(cont_defensa>10){
                    protaPosition.X -= 0.1;
                }else
                    protaPosition.X += 0.1;
            }else if(cont_defensa<20 && defensa_position==2){
                protaPosition.Y =pos_actual+4;
                if(cont_defensa>10){
                    protaPosition.X -= 0.1;
                }else
                    protaPosition.X += 0.1;
            }else if(cont_defensa<20 && defensa_position==0){
                protaPosition.Y =pos_actual-4;
                if(cont_defensa>10){
                    protaPosition.X -= 0.1;
                }else
                    protaPosition.X += 0.1;
            }
    } 
        
    cont_defensa++;  
    }
    else if(cont_defensa>=20){
        protaPosition.Y =pos_actual;
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
            Body->ApplyForceToCenter(b2Vec2(-10.f,0.f),true);
            //Body->SetLinearVelocity(b2Vec2(-10.f,0.f));
            //protaPosition.X -= VELOCIDAD_MOVIMIENTO * Time*0.5;
        }else if(correr==true && energia>10.1)
        {
                Body->ApplyForceToCenter(b2Vec2(-10000.f,0.f),true);
                Body->SetLinearVelocity(b2Vec2(-10000.f,0.f));
                //protaPosition.X -= VELOCIDAD_MOVIMIENTO * Time*3;

                if(energia>10)
                {
                    //vitalidad -=0.3f;
                }else
                    correr=false;
        }else
        {
            Body->ApplyForceToCenter(b2Vec2(-100.f,0.f),true);
            //Body->SetLinearVelocity(b2Vec2(-100.f,0.f));
            //protaPosition.X -= VELOCIDAD_MOVIMIENTO * Time*1.5;
        }

    }
    else        //MOVIMIENTO HACIA LA DERECHA
    {
         if(sigilo==true)
            {
                Body->ApplyForceToCenter(b2Vec2(10.f,0.f),true);
               //Body->SetLinearVelocity(b2Vec2(10.f,0.f));
            }else if(correr==true && energia>10.1){
                Body->ApplyForceToCenter(b2Vec2(10000.f,0.f),true);
                Body->SetLinearVelocity(b2Vec2(10000.f,0.f));
                if(energia>10){
                    //vitalidad -=0.3f;
                }else
                    correr=false;
            }else
                Body->ApplyForceToCenter(b2Vec2(100.f,0.f),true);
               // Body->SetLinearVelocity(b2Vec2(100.f,0.f));
    }

    

}
/**
FUNCION PARA COMPROBAR LAS COLISIONES CON ENEMIGOS
**/
void Protagonista::comprobarColision(Enemigo *enemigo)
{
    enemigoPosition=enemigo->getNode()->getPosition();
    if((enemigoPosition.X-(protaPosition.X+15))<=0 
        && (enemigoPosition.X-(protaPosition.X+15))>-25
        && vida<=100 && vida>0 && protaPosition.Y<10){
        if(ataca)
        {
            enemigo->getNode()->setVisible(false);
        }else if(enemigo->getNode()->isVisible() && defensa==false)
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
FUNCION PARA COMPROBAR LAS COLISIONES CON COMIDA
**/

void Protagonista::comprobarColision(Comida *comida)
{
    comidaPosition=comida->getNode()->getPosition();
    if((comidaPosition.X-(protaPosition.X+15))<=0 
        && (comidaPosition.X-(protaPosition.X+15))>-20){
        if(comida->getNode()->isVisible()&& protaPosition.Y<10)
        {
           vida+=10;
            if(vida>100)
                vida=100;

            int i=rand();
            while(i>1000)
            {
                i=rand();
            }
            
            comidaPosition.X+=i;
            comida->getNode()->setPosition(bebidaPosition);

        }
       
    }
    //else
        //comida->getNode()->setVisible(true);
    
}

void Protagonista::comprobarColision(Bebida *bebida)
{
    bebidaPosition=bebida->getNode()->getPosition();
    if((bebidaPosition.X-(protaPosition.X+15))<=0 
        && (bebidaPosition.X-(protaPosition.X+15))>-20){
        if(bebida->getNode()->isVisible()&& protaPosition.Y<10)
        {
           energia+=10;
            if(energia>100)
                energia=100;

            //bebida->getNode()->setVisible(false);
            int i=rand();
            while(i>1000)
            {
                i=rand();
            }
            
            bebidaPosition.X+=i;
            bebida->getNode()->setPosition(bebidaPosition);

        }
       
    }
    //else
        //bebida->getNode()->setVisible(true);
    
}

void Protagonista::comprobarColision(Trampa *trampa)
{
    trampaPosition=trampa->getNode()->getPosition();
    if((trampaPosition.X-(protaPosition.X+15))<=-5 
        && (trampaPosition.X-(protaPosition.X+15))>-30
        && protaPosition.Y<10){
        
           vida-=3;
           //protaPosition.X-=15; //+=15 animacion, rebote de la trampa 
       
    }
    
    
}



/**
FUNCION PARA COMPROBAR LAS COLISIONES CON LAS PLATAFORMAS
**/
bool Protagonista::comprobarColision(scene::ISceneNode* nodo)
{
    nodoPosition=nodo->getPosition();
    if((nodoPosition.X-(protaPosition.X+15))<=40 
        && (nodoPosition.X-(protaPosition.X+15))>-70
        && protaPosition.Y-nodoPosition.Y>0)
    {
        if((nodoPosition.X-(protaPosition.X+15))<=30 
        && (nodoPosition.X-(protaPosition.X+15))>-60)
        {
            if(protaPosition.Y-nodoPosition.Y<0)
            {
                estaEnSuelo=false;
                return false;
            }
            
        }else
        {
            if(protaPosition.Y<35)
                protaPosition.Y=34;
            estaEnSuelo=true;
            return true;

        }
         
    }else
    {
        estaCayendo=true;
        estaEnSuelo=false;
        return false;
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
        //recuperarVida(Time);
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
   
   if(Body->GetLinearVelocity().y>=0 && Body->GetLinearVelocity().y<2){
    Body->ApplyForceToCenter(b2Vec2(0.f,2500.f),true);
        //cont_salto=1;
        //saltando=s;
        setEnergia(1.f,-15);
   }
   
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
bool Protagonista::getCorrer()
{
    return correr;
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
    if(cont_ataque==0 && !saltando && energia>10)
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
    //delete rec;
    //delete energy;
    //delete life;    
}