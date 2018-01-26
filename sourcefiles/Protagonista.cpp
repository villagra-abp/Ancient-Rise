#include "../headerfiles/Protagonista.h"
#define SCALE 30.0f

/**
 Constructor: CREA UN NODO PASANDOLE POR PARAMETRO EL DEVICE Y EL PUNTERO PARA GESTIONAR LA ESCENA
**/
Protagonista::Protagonista(IrrlichtDevice *dev, ISceneManager* smgr)
{

    GameObject::setTipo(PROTA);

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
        rec->setMaterialFlag(video::EMF_LIGHTING, false);
    }
    
    life->setMaterialFlag(video::EMF_LIGHTING,false);

    
    protaPosition=rec->getPosition();
    energyScale=energy->getScale();
    energyScale.Z=0.1f;
    lifeScale=life->getScale();
    lifeScale.Z=0.1f;
    energy->setScale(energyScale);
    life->setScale(lifeScale);

    combate = false;
    pos_combate = 2; 

    sonido = GestorSonido::getInstance();

    nani = sonido->create2DSound(sonido->SOUND_BOSS3_NANI);
    omae = sonido->create2DSound(sonido->SOUND_BOSS3_OMAE);
    grito = sonido->create2DSound(sonido->SOUND_BOSS3_GRITO1);
    risa = sonido->create3DSound(sonido->SOUND_BOSS3_RISA);

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
    FixtureDef.density = 1.2f;
    FixtureDef.friction = 0.35f;
    FixtureDef.shape = &Shape;
    FixtureDef.isSensor = false;
    Body->CreateFixture(&FixtureDef);
    Body->SetUserData( rec );
    //std::cout<<Body->GetMass()<<"\n";

  
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
    FixtureDef.friction = 0.65f;
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
    energyPosition.X-=110;    // CAMBIO DESDE 80
    energyPosition.Y+=100;   // CAMBIO DESDE 120
    energyPosition.Z-=30;
    energy->setPosition(energyPosition);
    lifePosition=protaPosition;
    lifePosition.X-=110;      // CAMBIO DESDE 80
    lifePosition.Y+=110;     // CAMBIO DESDE 140
    lifePosition.Z-=30;
    life->setPosition(lifePosition);
    energyScale.X=energia/10;
    energy->setScale(energyScale);
    lifeScale.X=vida/10;
    life->setScale(lifeScale);
    //scene::ISceneNode * rct=static_cast<scene::ISceneNode *>(Body->GetUserData());
    //std::cout<<rct->getPosition().X<<"\n";
}

/**
FUNCION PARA CONTROLAR EL ATAQUE DEL PROTA
**/
void Protagonista::ataque(const f32 Time)
{
    //std::cout<<ataque_position<<"\n";
    b2Vec2 pos=Body->GetPosition();
    if(ataca == true && cont_ataque<20){
        energia-=0.5f;
       //rec->setScale(core::vector3df(1.f,.3f,1.f));
        //rec->setRotation(core::vector3df(1.f,ataque_position*100,1.f));
        if(ataque_position!=0){
            Body->SetTransform(b2Vec2(pos.x,pos.y+(ataque_position+2)/3), 0.f);
        }else
            Body->SetTransform(b2Vec2(pos.x,pos.y-0.8f), 0.f);
        if(direccion==1)
        {
            Body->ApplyForceToCenter(b2Vec2(100.f,0.f),true);
            
        }else if(direccion==0){
            Body->ApplyForceToCenter(b2Vec2(-100.f,0.f),true);
            
        } 
        
        cont_ataque++;  
    }
    else if(cont_ataque>=20){
        //Body->ApplyForceToCenter(b2Vec2(0.f,(-ataque_position+1)*10),true);
        //rec->setScale(core::vector3df(1.f,1.f,1.f));
        //rec->setRotation(core::vector3df(1.f,-ataque_position*100,1.f));
        cont_ataque=0;
        ataca=false;
    }
    
}
/**
FUNCION PARA CONTROLAR LA DEFENSA DEL PROTA
**/
void Protagonista::defender(const f32 Time)
{
     //std::cout<<ataque_position<<"\n";
    b2Vec2 pos=Body->GetPosition();
    if(cont_defensa>0){
        //Body->SetTransform(b2Vec2(pos.x,pos.y+(ataque_position/30)), 0.f);
        //Body->ApplyForceToCenter(b2Vec2(0.f,ataque_position*20),true);
        rec->setScale(core::vector3df(.3f,defensa_position+1,1.f));
        
        
    }
    else {
        //Body->ApplyForceToCenter(b2Vec2(0.f,-ataque_position*10),true);
        rec->setScale(core::vector3df(1.f,1.f,1.f));
        cont_defensa=0;
        defensa=false;
    }

}

/**
FUNCION PARA CONTROLAR EL MOVIMIENTO DEL PROTA
**/

void Protagonista::movimiento(const f32 Time)
{
    b2Vec2 velo=Body->GetLinearVelocity();
    if(direccion==0) // MOVIMIENTO HACIA LA IZQUIERDA
    {

        if(sigilo==true)
        {
            velo.x=-10.f;
            //Body->ApplyForceToCenter(b2Vec2(-35.f,0.f),true);
            Body->SetLinearVelocity(velo);
            //protaPosition.X -= VELOCIDAD_MOVIMIENTO * Time*0.5;
        }else if(correr==true && energia>10.1)
        {
            velo.x=-90.f;
            Body->ApplyForceToCenter(b2Vec2(-150.f,0.f),true);
             //Body->SetLinearVelocity(velo);
            //protaPosition.X -= VELOCIDAD_MOVIMIENTO * Time*3;

            if(energia<10)
                correr=false;
        }else
        {
            velo.x=-40.f;
            //Body->ApplyForceToCenter(b2Vec2(-60.f,0.f),true);
            Body->SetLinearVelocity(velo);
            //protaPosition.X -= VELOCIDAD_MOVIMIENTO * Time*1.5;
        }

    }
    else        //MOVIMIENTO HACIA LA DERECHA
    {
         if(sigilo==true)
            {
                velo.x=10.f;
                //Body->ApplyForceToCenter(b2Vec2(35.f,0.f),true);
               Body->SetLinearVelocity(velo);
            }else if(correr==true && energia>10.1){
                velo.x=90.f;
                Body->ApplyForceToCenter(b2Vec2(150.f,0.f),true);
                //Body->SetLinearVelocity(velo);
                if(energia<10)
                    correr=false;
            }else{
                velo.x=40.f;
                //Body->ApplyForceToCenter(b2Vec2(60.f,0.f),true);
                Body->SetLinearVelocity(velo);
            }
                
    }  

}
/**
FUNCION PARA COMPROBAR LAS COLISIONES CON ENEMIGOS
**/
void Protagonista::comprobarColision(Enemigo *enemigo)
{/*
    enemigoPosition=enemigo->getNode()->getPosition();
    int defensaEnemigo=enemigo->getDefensaPosition();
    int ataqueEnemigo=enemigo->getAtaquePosition();
    bool medefiende=enemigo->getDefiende();
    bool meataca=enemigo->getAtaca();
    if((enemigoPosition.X-(protaPosition.X+10))<0 
        && (enemigoPosition.X-(protaPosition.X+10))>-20
        && vida<=100 && vida>0 && protaPosition.Y<10){
        if(ataca)
        {
            if(medefiende && (int)ataque_position!=defensaEnemigo)
                enemigo->getNode()->setVisible(false);
        }else if(enemigo->getNode()->isVisible() && defensa==false)
        {
            if(meataca && (int)defensa_position!=ataqueEnemigo)
                vida-=5; 
        }   
    }
    cont_recarga_enemigo++;
    if(cont_recarga_enemigo>20){
        enemigo->getNode()->setVisible(true);
        cont_recarga_enemigo=0;
    }
    */

    enemigoPosition=enemigo->getNode()->getPosition();

    if((enemigoPosition.X-(protaPosition.X+10))<0 
        && (enemigoPosition.X-(protaPosition.X+10))>-20
        && vida<=100 && vida>0 && protaPosition.Y<10){

        if(enemigo->getPosCombate() != pos_combate)
        {
            vida-=5; 
        }
    }

}

/**
FUNCION PARA COMPROBAR LAS COLISIONES CON COMIDA
**/

void Protagonista::comprobarColision(Comida *comida)
{
    comidaPosition=comida->getNode()->getPosition();
    if((comidaPosition.X-(protaPosition.X+10))<-5 
        && (comidaPosition.X-(protaPosition.X+10))>-15){
        if(comida->getNode()->isVisible()&& protaPosition.Y<10)
        {
           vida+=10;
            if(vida>100)
                vida=100;
            
            comidaPosition.X+=500;
        if(comidaPosition.X>2500)
            comidaPosition.X=-1900;
            comida->getNode()->setPosition(comidaPosition);

        }
       
    }
    //else
        //comida->getNode()->setVisible(true);
    
}

void Protagonista::comprobarColision(Bebida *bebida)
{
    bebidaPosition=bebida->getNode()->getPosition();
    if((bebidaPosition.X-(protaPosition.X+10))<=-5 
        && (bebidaPosition.X-(protaPosition.X+10))>-15){
        if(bebida->getNode()->isVisible()&& protaPosition.Y<10)
        {
           energia+=10;
            if(energia>100)
                energia=100;

            //bebida->getNode()->setVisible(false);
            
            bebidaPosition.X+=400;
        if(bebidaPosition.X>2200)
            bebidaPosition.X=-1800;
            bebida->getNode()->setPosition(bebidaPosition);

        }
       
    }
    //else
        //bebida->getNode()->setVisible(true);
    
}

void Protagonista::comprobarColision(Trampa *trampa)
{
    trampaPosition=trampa->getNode()->getPosition();
    if((trampaPosition.X-(protaPosition.X+10))<8 
        && (trampaPosition.X-(protaPosition.X+10))>-28
        && protaPosition.Y<10){
        
           vida-=0.4f;
           //protaPosition.X-=15; //+=15 animacion, rebote de la trampa 
       
    }
    
    
}
/*
FUNCION PARA COMPROBAR LA POSICION DE COMBATE DEL PROTA Y CAMBIAR LA POS EN Y 
DEL PROTA 
*/
void Protagonista::checkPosCombate()
{
    
    if(pos_combate == 1)    // ARRIBA
    {
        protaPosition.Y = 10.f;
        rec->setPosition (protaPosition);
    }
    else
    {
        if(pos_combate == 3) // ABAJO
        {
            protaPosition.Y = 0.f;
            rec->setPosition (protaPosition);
        }
        else        // CENTRO
        {
            protaPosition.Y = 5.f;
            rec->setPosition (protaPosition);
        }
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

/*
FUNCION PARA CAMBIAR LA POS DE COMBATE DEL PROTA
*/
void Protagonista::setPosCombate(int n)
{
    pos_combate = n;
    //cout<<pos_combate<<endl;
}
/**
FUNCION PARA RECUPERAR LA VIDA DEL PROTA
**/
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
METODO PARA GESTIONAR LA ENERGIA
**/
void Protagonista::setEnergia(f32 cantidad,const f32 Time)
{
    if(energia>0 || energia<100)
        energia+=cantidad* Time;
    if(energia<0){
        energia=0;
        //setVida(-5,Time);
    }else if(energia>100)
        energia=100;

}
/**
METODO PARA GESTIONAR EL SALTO
**/
void Protagonista::setSalto(bool s)
{
    bool flag;
    //sonido->playSound(risa);
    b2Vec2 velocidad=Body->GetLinearVelocity();
    //std::cout<<velocidad.y<<"\n";
    if(velocidad.y>=-5 && velocidad.y<5 && s && !saltando && !sigilo){
        if(correr && energia>10)
        {   
            flag = sonido->playSound(omae);
            if(flag){
                DSP* dsp = sonido->createDSP("echo");
                omae->getCanal()->addDSP(dsp);
                omae->getCanal()->setGrupoCanales(sonido->getGrupoVoces());
            }
            Body->ApplyForceToCenter(b2Vec2(0.f,10000.f),true);
        }else if(energia<10)
        {
            sonido->playSound(grito);
            grito->getCanal()->setGrupoCanales(sonido->getGrupoVoces());
            Body->ApplyForceToCenter(b2Vec2(0.f,2500.f),true);
        }
        else{
            flag = sonido->playSound(nani);
            if(flag){
                nani->getCanal()->setGrupoCanales(sonido->getGrupoVoces());
                DSP* dsp = sonido->createDSP("echo");
                nani->getCanal()->addDSP(dsp);
            }
            Body->ApplyForceToCenter(b2Vec2(0.f,6000.f),true);    
        }
        //cont_salto=1;
        //saltando=s;
        setEnergia(1.f,-15);
    }
    saltando=s;
}
/**
ACTUALIZA LA POSICION DEL PROTA
**/
void Protagonista::setPosition(core::vector3df v)
{
   protaPosition=v;
}

/*
FUNCION PARA ACTIVAR O DESACTIVAR EL SIGILO
*/
void Protagonista::setSigilo()
{
    if(sigilo==false)
    {
        sigilo=true;
        //rec->setMaterialFlag(video::EMF_LIGHTING, true);
    }
    else{
        //rec->setMaterialFlag(video::EMF_LIGHTING, false);
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
    //ataca=d;
    /*
    if(cont_ataque==0 && !saltando && energia>10){
        cont_ataque=1;
    }
    */

    ataca = d;
    if(ataca == true)
    {
        if(cont_ataque==0 && energia>10)        // CONTADOR PARA LA ANIMACION DE ATAQUE
        {
            cont_ataque=1;
        }
    }

}
void Protagonista::setDefensaPosition(int d)
{
    defensa_position=d;
}
void Protagonista::setDefensa(bool d)
{

    defensa=d;
    if(defensa && !saltando)
    {
        cont_defensa=1;
    }else
    {
        cont_defensa=0;
    }
}

void Protagonista::setCombate()
{
    if(combate == true)
    {
        combate = false;        // DESACTIVAMOS MODO COMBATE
        rec->setMaterialFlag(video::EMF_LIGHTING, false);

    }
    else
    {
        combate = true;         // MODO COMBATE ACTIVADO
        rec->setMaterialFlag(video::EMF_LIGHTING, true);
    }
}
/**
DEVUELVE EL NODO QUE HEMOS CREADO
**/
scene::ISceneNode* Protagonista::getNode()
{
    return rec;
}

bool Protagonista::getCombate()
{
    return combate;
}

/*core::vector3df Protagonista::getPosition()
{
   return protaPosition;
}*/

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

int Protagonista::getPosCombate()
{
    return pos_combate;
}


Protagonista::~Protagonista()
{
    //dtor
    //delete rec;
    //delete energy;
    //delete life;    
}
