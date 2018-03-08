#include "../headerfiles/Mundo.h"



Mundo::Mundo()	//CONSTRUCTOR
{
Fachada* fachada=fachada->getInstance();
/* CREAMOS IRRLICHT DEVICE */	 
	device = fachada->getDevice();
	//receiver = mainReceiver;

/** PUNTEROS 
 A VideoDriver, al SceneManager y al entorno de interfaz de usuario, para no tener que
 estar llamandolos siempre y solo los llamamos una vez
**/

	driver = fachada->getDriver();
	smgr = fachada->getScene();
	guienv = fachada->getGUI();



/*CREAMOS GESTOR DE SONIDO*/
	sonido = GestorSonido::getInstance();
	reverbCueva = sonido->create3DReverb();
	reverbCueva->setAtributos3D(0.0f,0.0f,0.0f, 10.0f, 2000.0f);
	reverbCueva->setTipo(sonido->REVERB_CUEVA);
	musicaBosque = sonido->createMusic(sonido->SOUND_MUSIC_BOSQUE);
/* CREAMOS PROTA */

	prota = prota->getInstance();
    
	addGameObject(prota);

	//creo el suelo, el bounding box del prota y la plataforma
	prota->CreateGround(world, 0.f, -150.f,1000*1000);
    prota->CreateGround(world, 6600.f, 900.f,3200);
    prota->CreateGround(world, 9600.f, 1800.f,3200);
    prota->CreateGround(world, 12600.f, 2700.f,3200);
    prota->CreateBox(world, -5000.f, 0.f);


/* CREAMOS VECTOR DE POSICIONES PARA EL ENEMIGO */

	this->posBuilder();

/* CREAMOS OBJETOS */

	Posicion pC(-220.f, 0.f, 30.f);
	c = new Comida(device, smgr, pC);
	comidas.push_back(c);
	addGameObject(c);

	Posicion pC2(190.f, 0.f, 30.f);
	c2 = new Comida(device, smgr, pC2);
	comidas.push_back(c2);
	addGameObject(c2);

	Posicion pF(-190.f,0.f,40.f);
	f = new Fuente(device, smgr, pF);
	fuentes.push_back(f);
	addGameObject(f);

	Posicion pF2(320.f,0.f,40.f);
	f2 = new Fuente(device, smgr, pF2);
	fuentes.push_back(f2);
	addGameObject(f2);

	Posicion pA(120.f,0.f,40.f);
	a = new Alarma(device, smgr, pA);
	alarmas.push_back(a);
	addGameObject(a);

	Posicion pA2(-160.f,0.f,40.f);
	a2 = new Alarma(device, smgr, pA2);
	alarmas.push_back(a2);
	addGameObject(a2);

	Posicion posbebida(-300,0,30.f);
 	bebida = new Bebida(device, smgr, posbebida);
 	addGameObject(bebida);

	Posicion postrampa(520,0,30.f);
 	t = new Trampa(device, smgr, postrampa);
 	addGameObject(t);


/* CREAMOS LA BLACKBOARD */

	b=new Blackboard();
	 b->setFuente(fuentes);
	 b->setComida(comidas);
	 b->setAlarma(alarmas);

/* CREAMOS ENEMIGOS BASICOS */
	
	enem1 = new EnemigoBasico(device, smgr, pos, 80.0, 0.8, 1, this, b, world);
	enemB.push_back(enem1);
	addGameObject(enem1);

	enem2 = new EnemigoBasico(device, smgr, pos2, 80.0, 0.8, 1, this, b, world);
	enemB.push_back(enem2);
	addGameObject(enem2); 
	
	for(int i=0;i<enemB.size();i++)
	{
		b->setEnemB(enemB[i]);
	} 

	

/* CREAMOS ENEMIGOS ELITES */

	enemE1 = new EnemigoElite(device, smgr, pos3, 120.0, 0.8, 2, this, b, world);
	enemE.push_back(enemE1);

/* CREAMOS PLATAFORMAS */

    Posicion* escala = new Posicion(10.f,1.f,5.f);

	Plataforma = fachada->addCube(220,25,30,false);

	if (Plataforma) /** SI HEMOS CREADO EL CUBO **/
	{
		fachada->setScala(Plataforma,escala);
		Plataforma->setMaterialTexture(0,driver->getTexture("resources/plataf.bmp"));
	}

	Plataforma2= fachada->addCube(320,55,30,false);

	if (Plataforma2) /** SI HEMOS CREADO EL CUBO **/
	{
		fachada->setScala(Plataforma2,escala);
		Plataforma2->setMaterialTexture(0,driver->getTexture("resources/plataf.bmp"));
	}

	Plataforma3= fachada->addCube(420,85,30,false);

	if (Plataforma3) /** SI HEMOS CREADO EL CUBO **/
	{
		fachada->setScala(Plataforma3,escala);
		Plataforma3->setMaterialTexture(0,driver->getTexture("resources/plataf.bmp"));
	}

/** ESTABLECEMOS LA CAMARA
 Aqui indicamos la posicion de la camara en el espacio 3d. En este caso,
 esta mirando desde la posicion (0, 30, -40) a la (0, 5, 0) donde es
 aproximadamente donde esta el objeto.
**/

	cam = smgr->addCameraSceneNode(0, vector3df(prota->getPosition()->getPosX(),50,-140), vector3df(0,5,0));
	device->getCursorControl()->setVisible(true);

/* CREAMOS EL TERRENO Y COLISIONES DE CAMARA */

	this->terrainBuilder();

/** TIME AND FRAMES
 Para poder hacer un movimiento independiente del framerate, tenemos que saber
 cuanto ha pasado desde el ultimo frame
**/
	lastFPS = -1;

	then = fachada->getTime();
	time_input = fachada->getTime();

//////////////////////////////////////

	
}	

void Mundo::posBuilder(){	//CONSTRUCTOR DE POSICIONES DE ENEMIGOS

	Posicion *p0 = new Posicion(40.f,0.f,30.f);
  	pos.push_back(p0);
  	Posicion *p1 = new Posicion(0.f,0.f,30.f);
  	pos.push_back(p1);
  	Posicion *p2 = new Posicion(-40.f,0.f,30.f);
  	pos.push_back(p2);
  	Posicion *p3 = new Posicion(-60.f,0.f,30.f);
  	pos.push_back(p3);
  	Posicion *p4 = new Posicion(-80.f,0.f,30.f);
	pos.push_back(p4);

	Posicion *p5 = new Posicion(160.f,0.f,30.f);
  	pos2.push_back(p5);
  	Posicion *p6 = new Posicion(180.f,0.f,30.f);
  	pos2.push_back(p6);
  	Posicion *p7 = new Posicion(200.f,0.f,30.f);
	pos2.push_back(p7);


	Posicion *p8 = new Posicion(200.f,0.f,30.f);
  	pos3.push_back(p8);
  	Posicion *p9 = new Posicion(150.f,0.f,30.f);
  	pos3.push_back(p9);
  	Posicion *p10 = new Posicion(60.f,0.f,30.f);
  	pos3.push_back(p10);
  	Posicion *p11 = new Posicion(0.f,0.f,30.f);
  	pos3.push_back(p11);

}

void Mundo::terrainBuilder(){	//CONSTRUCTOR DEL TERRENOS Y COLISIONES DE CAMARA

    fachada->drawTerreno();

}

void Mundo::update(){
    //Comprueba las entradas del teclado
	checkInput();
	//pasos de las fisicas en el mundo
	world.Step(1/60.f, 8, 3);
	//reinicio las fuerzas en el mundo
	world.ClearForces();

	/* Creamos el framedeltatime y el tiempo */

	const u32 now = device->getTimer()->getTime();
	const f32 frameDeltaTime = (f32)(now - then) / 1000.f; // Time in seconds
	then = now;
	f32 tiempo=(f32)(now - time_input)/1000.f;

	Posicion* protaPosition = prota->getPosition();
	core::vector3df camPosition = cam->getPosition();

	/* PROTA UPDATE */

	this->protaUpdate(now, frameDeltaTime, tiempo);

	/* CAM UPDATE*/

    this->camUpdate(frameDeltaTime);

    b->setTime(frameDeltaTime);
    b->setProta(protaPosition->getPosX());

    /* ALARMA UPDATE*/
    a->update();
    a2->update();


    /* UPDATE DE LOS ENEMIGOS */
    
    for(int i=0; i<enemB.size();i++)
    {
       	enemB[i]->updateTiempo(frameDeltaTime);/////////////////////////////////////////////////////////////////////////////////////
     	enemB[i]->Update(prota->getPosition());
    }

    for(int i2=0; i2<enemE.size();i2++)
    {
    	enemE[i2]->updateTiempo(frameDeltaTime);////////////////////////////////////////////////////////////////////////////////////
     	enemE[i2]->Update(prota->getPosition());
    }

    /* DRAW SCENE */

    this->draw();

    /* CONTROL DE FRAMES POR SEGUNDO */

    this->fpsControl();

    /*UPDATE DE SONIDO*/
    sonido->playSound(musicaBosque);
    sonido->update();
	sonido->setListener(prota->getPosition()->getPosX(), prota->getPosition()->getPosY(), prota->getPosition()->getPosZ());

}

void Mundo::protaUpdate(const u32 now, const f32 frameDeltaTime, f32 tiempo){
	scene::ISceneNode* pro = (scene::ISceneNode*)prota->getNode();
    core::vector3df protaPosition = pro->getPosition();

	energiaAnterior = prota->getEnergia();

    prota->ataque(frameDeltaTime);
    
    prota->pintarInterfaz();

	prota->comprobarColision(c);

    prota->comprobarColision(bebida);

    prota->comprobarColision(t);

    prota->updateBody(world);

    if(!prota->checkVida())
		device->closeDevice();

    if(tiempo>0.2f) 	// HACEMOS QUE LO QUE HAYA DENTRO SE HAGA MENOS VECES POR SEGUNDO
    {
        f32 energia=prota->getEnergia();

        time_input=now;

        //receiver->checkCombate(prota); 						// Comprobamos si hemos pulsado la tecla de combate (K)

        for(int i2=0; i2<enemB.size();i2++)
        {
           	prota->comprobarColision(enemB[i2]);
        }
            
    }

    if(prota->getCombate())  // Si combate activado entonces comprobamos las posiciones de combate
    {
    	prota->checkPosCombate();
    }
    else
    {
    	//receiver->checkSigilo(prota);  						// Comprobamos si hemos pulsado la tecla de sigilo (C)
    }

    //receiver->checkInput(prota,frameDeltaTime);

    /* Velocidad Barra de Energia */
    energiaActual = prota->getEnergia();
    energiaDelta = energiaActual - energiaAnterior;

    if(energiaDelta < 0){
    	relojDescanso.restart();
    }

    tiempoTrans = relojDescanso.getElapsedTime().asSeconds();
    
    if(tiempoTrans > 0.8f)	
    	prota->setEnergia(25,frameDeltaTime);  //CAMBIO 5 a 15
    else
    	prota->setEnergia(2, frameDeltaTime);


}
void Mundo::checkInput(){

	if(sf::Joystick::isConnected(0)){
		JoyY=sf::Joystick::getAxisPosition(0, sf::Joystick::Y);
		JoyX=sf::Joystick::getAxisPosition(0, sf::Joystick::X);
		//std::cout<<JoyX<<"\n";
	}
	/*
	if (sf::Joystick::isButtonPressed(0, 2))
	{
	    std::cout<<"x=2"<<"\n";
	}
	if (sf::Joystick::isButtonPressed(0, 4))
	{
	    std::cout<<"l=4"<<"\n";
	}
	if (sf::Joystick::isButtonPressed(0, 0))
	{
	    std::cout<<"a=0"<<"\n";
	}
	if (sf::Joystick::isButtonPressed(0, 5))
	{
	    std::cout<<"r=5"<<"\n";
	}
	*/

/* hacemos un set de ataque a 2 que es arriba 
        if(inputkey==22)//w
        {
           pos_pelea(prota,2);
           pos_defensa(prota,2);
        }
        else if(inputkey==18)//s
        {
            pos_pelea(prota,0);
            pos_defensa(prota,0);
        }
        else
        {
            pos_pelea(prota,1);
            pos_defensa(prota,1);
        }
*/
        /* control de ataque*/
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::P)||sf::Joystick::isButtonPressed(0, 2))//p
        {  
            prota->setAtaque(true);
        }
        
        /* control de defensa*/
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::K)||sf::Joystick::isButtonPressed(0, 4))//k
        {
            prota->setCombate();

        }

        /* movimiento hacia los lados y control de la velocidad en funcion de
        las variables de correr, sigilo y vitalidad */

        if(sf::Keyboard::isKeyPressed(sf::Keyboard::A)||JoyX<=-50)//A
        {
            prota->setDireccion(0);
	    prota->movimiento(0.1f);
    		if(sf::Keyboard::isKeyPressed(sf::Keyboard::LShift)||sf::Joystick::isButtonPressed(0, 5))
    		{
                prota->setCorrer(true);
      		    prota->setEnergia(-5.0f,1.1f);
    		}else
		  prota->setCorrer(false);
        }

        else if(sf::Keyboard::isKeyPressed(sf::Keyboard::D)||JoyX>=50){//D

            prota->setDireccion(1);
            prota->movimiento(0.1f);
    		if(sf::Keyboard::isKeyPressed(sf::Keyboard::LShift)||sf::Joystick::isButtonPressed(0, 5))
    		{
		  prota->setCorrer(true);
      		  prota->setEnergia(-5.0f,0.2f);
    		}else
		  prota->setCorrer(false);
        }
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Space)||sf::Joystick::isButtonPressed(0, 0)){
        	prota->setSalto(true);
    	}else
		prota->setSalto(false);
       	
	       
}
void Mundo::camUpdate(const f32 frameDeltaTime){
	Posicion* protaPosition = prota->getPosition();
	core::vector3df camPosition = cam->getPosition();

	//rec->setPosition(protaPosition);
    cam->setPosition(vector3df(protaPosition->getPosX(),protaPosition->getPosY()+30,-140)); // cambio 5O A ProtaPosition.Y
    camPosition=core::vector3df(protaPosition->getPosX(),protaPosition->getPosY(),protaPosition->getPosZ());
    camPosition.Y=protaPosition->getPosY()+30;
    cam->setTarget(camPosition);
}

void Mundo::fpsControl(){
	
	int fps = driver->getFPS();

	if (lastFPS != fps)
	{
		core::stringw tmp(L"Movement Example - Irrlicht Engine [");
		tmp += driver->getName();
		tmp += L"] fps: ";
		tmp += fps;

		device->setWindowCaption(tmp.c_str());
		lastFPS = fps;
	}

	this->timeWait();
}

void Mundo::timeWait(){
	static long t=clock();
	const float fps = 60.f;

	long toWait = t + CLOCKS_PER_SEC / fps - clock();
	
	if(toWait > 0)
		usleep(toWait);

	t = clock();
}

void Mundo::draw(){
	/*
	Anything can be drawn between a beginScene() and an endScene()
	call. The beginScene() call clears the screen with a color and
	the depth buffer, if desired. Then we let the Scene Manager and
	the GUI Environment draw their content. With the endScene()
	call everything is presented on the screen.
	*/

	driver->beginScene(true, true, SColor(255,100,101,140));

	smgr->drawAll(); 							// draw the 3d scene
	device->getGUIEnvironment()->drawAll(); 	// draw the gui environment (the logo)

	driver->endScene();
}

void Mundo::addGameObject (GameObject* o){
	gos.push_back(o);
}

GameObject* Mundo::getGameObject(uint8_t pos) const{
	GameObject* o = nullptr;

	if(pos < gos.size() && gos[pos] != nullptr){
		o = gos[pos];
	}

	return o;
}

Mundo::~Mundo()	//DESTRUCTOR
{
	delete prota;
	
	for(int cont=0; cont<enemB.size();cont++)
	{
		delete enemB[cont];
	}
	for(int cont2=0; cont2<enemE.size();cont2++)
	{
		delete enemE[cont2];
	}

	enemB.clear();
	enemE.clear();

	pos.clear();
	pos2.clear();
	pos3.clear();

    delete b;
    delete c;
    delete f;
    delete a;
    delete a2;
    delete bebida;
    delete t;
    delete sonido;
}
