#include "../headerfiles/Protagonista.h"
#include "../headerfiles/Blackboard.h"
#define SCALE 30.0f

static Protagonista* instance = NULL;


Protagonista::Protagonista():energy(nullptr), life(nullptr), Body(nullptr), rec(nullptr), flecha0(nullptr), flecha1(nullptr), sonido(nullptr),
protaPosition(nullptr), enemigoPosition(nullptr), comidaPosition(nullptr), trampaPosition(nullptr)
{
    
    GameObject::setTipo(PROTA);

    FObjeto* protaObjeto = fachada->addAnimacion(0, 0, 30, "resources/Animaciones/Prueba/prueba");
    rec = protaObjeto;
    
    Posicion escala(2.f,2.f,2.f);
    fachada->setScala((void*)protaObjeto,&escala);
		
    fachada->rotObj(protaObjeto, 0, 1, 0, -90);
        
    flecha1=fachada->addMalla(-160,8,0,"resources/flecha.obj");
    flecha0=fachada->addMalla(-170,8,0,"resources/flecha.obj");
    Posicion escalar(0.f,0.f,.0f);
    fachada->setScala(flecha1,&escalar);
    fachada->rotObj(flecha1, 1, 0, 0, -45);
    fachada->setScala(flecha0,&escalar);
    fachada->rotObj(flecha0, 1, 0, 0, -45);
    fachada->rotObj(flecha0, 0, 1, 0, -3);

    /* Estadisticas del prota */
    energia=ENERGIA_MAXIMA;
    vida=VIDA_MAXIMA;
    saltando=false;
    sigilo=false;
    correr=false;
    estaEnSuelo=false;
    estaCayendo=true;
    direccion=1;

    combate = false;
    pos_combate = 2; 

    sonido = GestorSonido::getInstance();

    nani = sonido->create2DSound(sonido->SOUND_BOSS3_NANI);
    omae = sonido->create2DSound(sonido->SOUND_BOSS3_OMAE);
    grito = sonido->create2DSound(sonido->SOUND_BOSS3_GRITO1);
    risa = sonido->create3DSound(sonido->SOUND_BOSS3_RISA);
    
    protaPosition=fachada->getPosicion(rec);
    
}



//Con esto hacemos que sea singleton. Solo se puede crear el motorgrafico llamando a getInstance. Esta devuelve el motor si ya estaba creado, y sino lo crea
//Parametros: h-> Alto de la ventana, w-> Ancho de la ventana, fullscreen-> si será pantalla completa o no
Protagonista* Protagonista::getInstance() 
{
    if (instance == NULL) instance = new Protagonista();
    return (instance);
}


/* Funcion para hacer el update del protagonista */
void Protagonista::update(Blackboard* b)
{   
    timeAtq = relojAtq.getElapsedTime().asSeconds();
    if( ataca == true && timeAtq>=0.5)       // PROTA EN COMBATE Y ATACANDO
    {   
        relojAtq.restart();
        enemB = b->getEnemB();

        for(int i=0; i<enemB.size();i++)
        {   
            if(enemB[i]!=nullptr)
            {
                comprobarColision(enemB[i]);
            }
        }
    }
}

/**
FUNCION PARA crear el objeto dinamico
**/
void Protagonista::CreateBox(b2World& world, float X, float Y)
{
    BodyDef.position = b2Vec2(X+4, Y+4);
    BodyDef.type = b2_dynamicBody;
    Body = world.CreateBody(&BodyDef);
    Shape.SetAsBox((8.f/2), (10.f/2));
    b2FixtureDef FixtureDef;
    FixtureDef.density = 0.5f;
    FixtureDef.friction = 0.2f;
    FixtureDef.shape = &Shape;
    FixtureDef.isSensor = false;
    FixtureDef.filter.groupIndex = GROUP_PLAYER;
    Body->CreateFixture(&FixtureDef);
    Body->SetUserData( rec );
}

/**
FUNCION PARA actualizar el cuerpo
**/
void Protagonista::updateBody(b2World& world)
{
    
    protaPosition->setPosX(Body->GetPosition().x);
    protaPosition->setPosY(Body->GetPosition().y);
    
    //FObjeto* objeto=(FObjeto*)rec;
    //vec3 position=vec3(Body->GetPosition().x,Body->GetPosition().y,0);
    //cout<<position.x<<" "<<position.y<<" "<<position.z<<endl;
    //objeto->setPosicion(position);
    fachada->setPosicion(rec,protaPosition);
    
    
    protaPosition->setPosX(protaPosition->getPosX()+5);
    if(pos_combate==2){
        protaPosition->setPosY(protaPosition->getPosY()+5);
    }
        
    if(pos_combate==1){
        protaPosition->setPosY(protaPosition->getPosY()+10);
    }
        
    if(pos_combate==3){
        protaPosition->setPosY(protaPosition->getPosY());
    }
    fachada->setPosicion(flecha1,protaPosition);
    protaPosition->setPosX(protaPosition->getPosX()-10);
    fachada->setPosicion(flecha0,protaPosition);
    if(pos_combate==1){
        protaPosition->setPosY(protaPosition->getPosY()-5);
    }
        
    if(pos_combate==3){
        protaPosition->setPosY(protaPosition->getPosY()+5);
    }
    
    Posicion escalaFlechaCorta(0,0.f,0.f);
    Posicion escalaFlechaLarga(0.1,.1f,0.1f);
    Posicion escalaFlechaLarga2(0.2,.1f,0.1f);
    
    if(direccion==1&&combate){
        fachada->setScala(flecha0,&escalaFlechaCorta);
        if(!ataca){
            fachada->setScala(flecha1,&escalaFlechaLarga);
        }else
            fachada->setScala(flecha1,&escalaFlechaLarga2);
        
    }
    if(direccion==0&&combate){
        fachada->setScala(flecha1,&escalaFlechaCorta);
        if(!ataca){
            fachada->setScala(flecha0,&escalaFlechaLarga);
        }else
            fachada->setScala(flecha0,&escalaFlechaLarga2);
    }
    if(!combate){
        fachada->setScala(flecha1,&escalaFlechaCorta);
        fachada->setScala(flecha0,&escalaFlechaCorta);
        
    }
    
}

/**
FUNCION PARA CONTROLAR EL ATAQUE DEL PROTA
**/
void Protagonista::ataque(EnemigoBasico* e)
{

    if(pos_combate != e->getPosCombate() || e->getCombate()!=true)
    {
        e->setSalud(-20.f);
    }
    
}

b2Body* Protagonista::getBody(){
    
    return Body;
}

/**
FUNCION PARA CONTROLAR EL MOVIMIENTO DEL PROTA
**/
void Protagonista::movimiento(const glm::f32 Time)
{
    b2Vec2 velo=Body->GetLinearVelocity();
    if(direccion==0) // MOVIMIENTO HACIA LA IZQUIERDA
    {
        if(sigilo==true)
        {
            velo.x=-10.f;
            Body->SetLinearVelocity(velo);
        }else if(correr==true && velo.y>=-4 && velo.y<4)
        {
            setEnergia(-1.f,0.2f);
            Body->ApplyForceToCenter(b2Vec2(-3500.f,0.f),true);

            if(velo.x<-80.f){
                velo.x=-80.f; 
                Body->SetLinearVelocity(velo);
            }
            
        }else
        {
            velo.x=-30.f;
            Body->SetLinearVelocity(velo);
        }

    }
    else        //MOVIMIENTO HACIA LA DERECHA
    {
         if(sigilo==true)
            {
                velo.x=10.f;
                //Body->ApplyForceToCenter(b2Vec2(35.f,0.f),true);
               Body->SetLinearVelocity(velo);
            }else if(correr==true && velo.y>=-4 && velo.y<4){
                setEnergia(-1.f,0.2f);
                Body->ApplyForceToCenter(b2Vec2(3500.f,0.f),true);
                if(velo.x>80.f){
                    velo.x=80.f;  
                    Body->SetLinearVelocity(velo);
                    //std::cout<<"velocidad +90"<<endl;
                }
                
            }else{
                velo.x=30.f;
                //Body->ApplyForceToCenter(b2Vec2(60.f,0.f),true);
                Body->SetLinearVelocity(velo);
            }
                
    }  

}
/**
FUNCION PARA COMPROBAR LAS COLISIONES CON ENEMIGOS
**/
void Protagonista::comprobarColision(EnemigoBasico *e)
{   
    enemigoPosition=e->getPosition();
    int distanciaEnemigo = protaPosition->getPosX() - enemigoPosition->getPosX();

    float enemigoPosY = enemigoPosition->getPosY();

      /* Posicion del prota en y */
    float protaPosY=protaPosition->getPosY();

    if(abs(distanciaEnemigo)<20 && protaPosY>enemigoPosY-10  && protaPosY<enemigoPosY+10 )   // Distancia para poder atacar
    {   
        ataque(e);
    }
    
}

/**
ESTA FUNCION ES PARA QUE NO PETE EL CONTACTLISTENER PREGUNTAR RUBEN
**/
void Protagonista::comprobarColision(Enemigo *e)
{   /*
    enemigoPosition=e->getNode()->getPosition();
    int distanciaEnemigo = protaPosition.X - enemigoPosition.X;

    if(abs(distanciaEnemigo)<25)   // Distancia para poder atacar
    {   
        ataque(e);
    }
    */
}

/**
FUNCION PARA COMPROBAR LAS COLISIONES CON COMIDA
**/
void Protagonista::comprobarColision(Objeto *comida)
{
    /* Posicion del prota */
    float protaPosX=protaPosition->getPosX();
    float protaPosY=protaPosition->getPosY();
    
    /* Posicion de la comida */
    float comidaPosX=comida->getPosition()->getPosX();
    float comidaPosY=comida->getPosition()->getPosY();
    
    if(protaPosY<comidaPosY+10 && protaPosY>comidaPosY-10)
    {
        if(protaPosX>comidaPosX-5 && protaPosX<comidaPosX+5)
        {
            if(vida<VIDA_MAXIMA) // Solo lo recogemos si nos falta vida
            {
                vida+=20;
                if(vida>VIDA_MAXIMA)
                {
                    vida=VIDA_MAXIMA;
                }

                comida->setRecogido(true);
            }
        }
    }
    
}

void Protagonista::comprobarColision(Bebida *bebida)
{
 /* Posicion bebida */
    float bebidaPosX=bebida->getPosition()->getPosX();
    float bebidaPosY=bebida->getPosition()->getPosY();

    /* Posicion prota*/
    float protaPosX=protaPosition->getPosX();
    float protaPosY=protaPosition->getPosY();

    if(protaPosY<bebidaPosY+10 && protaPosY>bebidaPosY-10)
    {
        if(protaPosX>bebidaPosX-5 && protaPosX<bebidaPosX+5)
        {
            if(energia<ENERGIA_MAXIMA)
            {
                energia+=40;
                if(energia>ENERGIA_MAXIMA)
                {
                    energia=ENERGIA_MAXIMA;
                }

                bebida->setRecogido(true);
            }
        }
    }

    
}

void Protagonista::comprobarColision(Trampa *trampa)
{
    /* Posicion del prota */
    float protaPosX=protaPosition->getPosX();
    float protaPosY=protaPosition->getPosY();
    
    /* Posicion de la trampa */
    float tramPosX=trampa->getPosition()->getPosX();
    float tramPosY=trampa->getPosition()->getPosY();

    if(protaPosY<tramPosY+10 && protaPosY>tramPosY-10)
    {
        if(protaPosX>tramPosX-5 && protaPosX<tramPosX+5)
        {
            vida-=0.4f;
        }
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
        protaPosition->setPosY(protaPosition->getPosY()+5);
        //fachada->setPosicion(flecha1,protaPosition);
        //fachada->setPosicion(flecha0,protaPosition);
        protaPosition->setPosY(protaPosition->getPosY()-5);
    }
    else
    {
        if(pos_combate == 3) // ABAJO
        {
            protaPosition->setPosY(protaPosition->getPosY()-5);
            //fachada->setPosicion(flecha1,protaPosition);
            //fachada->setPosicion(flecha0,protaPosition);
            protaPosition->setPosY(protaPosition->getPosY()+5);
        }
        else        // CENTRO
        {
            protaPosition->setPosY(protaPosition->getPosY());
            //fachada->setPosicion(flecha1,protaPosition);
            //fachada->setPosicion(flecha0,protaPosition);
        }
    }
  //std::cout<<pos_combate<<endl;
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

void Protagonista::startClock()
{
    if(contAtq == 0)
    {
        relojAtq.restart();
        contAtq = contAtq+1;
    }
}

/*
FUNCION PARA CAMBIAR LA POS DE COMBATE DEL PROTA
*/
void Protagonista::setPosCombate(int n)
{
    pos_combate = n;
}
/**
FUNCION PARA RECUPERAR LA VIDA DEL PROTA
**/
void Protagonista::setVida(glm::f32 cantidad,const glm::f32 Time)
{
    //std::cout<<Time<<endl;
    if(vida>0 || vida<100)
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
void Protagonista::setEnergia(glm::f32 cantidad,const glm::f32 Time)
{
    if(energia>0 || energia<100)
        energia+=cantidad* Time;
    if(energia<0){
        energia=0;
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
        flag = sonido->playSound(omae);
        if(flag){
            DSP* dsp = sonido->createDSP("echo");
            omae->getCanal()->addDSP(dsp);
            omae->getCanal()->setGrupoCanales(sonido->getGrupoVoces());
        }
        if(correr && energia>20)
        {   
            Body->ApplyForceToCenter(b2Vec2(0.f,10000000.f),true);
        }else if(energia<20)
        {
           /* sonido->playSound(grito);
            grito->getCanal()->setGrupoCanales(sonido->getGrupoVoces());*/
            Body->ApplyForceToCenter(b2Vec2(0.f,350000.f),true);
        }
        else{
            Body->ApplyForceToCenter(b2Vec2(0.f,6000000.f),true);    
        }
        //cont_salto=1;
        //saltando=s;
        setEnergia(1.5f,-10);
    }
    saltando=s;
}

/**
ACTUALIZA LA POSICION DEL PROTA
**/
void Protagonista::setPosition(Posicion* v)
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
    if(energia>10){
        correr=s;
    }else
        correr=false;
    
}

void Protagonista::setDireccion(int d)
{
    direccion=d;
}

void Protagonista::setAtaque(bool d)
{
    ataca = d;

}

void Protagonista::setCombate()
{
    if(combate == true)
    {
        combate = false;        // DESACTIVAMOS MODO COMBATE
        
    }
    else
    {
        combate = true;         // MODO COMBATE ACTIVADO
        
    }
    //std::cout<<combate<<endl;
}

void Protagonista::quitarVida(glm::f32 cantidad)
{
    vida -=cantidad; 
}

/**
DEVUELVE EL NODO QUE HEMOS CREADO
**/
void* Protagonista::getNode()
{
    return rec;
}

bool Protagonista::getCombate()
{
    return combate;
}

Posicion* Protagonista::getPosition()
{
   return protaPosition;
}

glm::f32 Protagonista::getEnergia()
{
    return energia;
}
glm::f32 Protagonista::getVida()
{
    return vida;
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

int Protagonista::getTiempoAtaque()
{
    return timeAtq;
}



Protagonista::~Protagonista()
{
    //dtor
    //std::cout<<"peta peta"<<endl;
    rec = nullptr;
    energy = nullptr;
    life = nullptr;  
    
    //delete energyPosition;
    //delete lifePosition;
}
