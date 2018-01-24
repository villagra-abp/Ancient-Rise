#include "../headerfiles/Mundo.h"


Mundo::Mundo(IrrlichtDevice* mainDevice, MyEventReceiver* mainReceiver)	//CONSTRUCTOR
{

/* CREAMOS IRRLICHT DEVICE */	 
	device = mainDevice;
	receiver = mainReceiver;

/** PUNTEROS 
 A VideoDriver, al SceneManager y al entorno de interfaz de usuario, para no tener que
 estar llamandolos siempre y solo los llamamos una vez
**/

	driver = device->getVideoDriver();
	smgr = device->getSceneManager();
	guienv = device->getGUIEnvironment();

/** SUBTITULO DE VENTANA
 Para poner texto en el subtitulo de la ventana. Necesita de una 'L' delante del string
 debido a que lo necesita el motor de irrlicht
**/

	device->setWindowCaption(L"Ancient Rise");

	

/* CREAMOS PROTA */

	prota = new Protagonista(device, smgr);
	addGameObject(prota);

	rec = prota->getNode();

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
	addGameObject(c);

	Posicion pC2(190.f, 0.f, 30.f);
	c2 = new Comida(device, smgr, pC2);
	addGameObject(c2);

	Posicion pF(-190.f,0.f,40.f);
	f = new Fuente(device, smgr, pF);
	addGameObject(f);

	Posicion pF2(320.f,0.f,40.f);
	f2 = new Fuente(device, smgr, pF2);
	addGameObject(f2);

	Posicion pA(120.f,0.f,40.f);
	a = new Alarma(device, smgr, pA);
	addGameObject(a);

	Posicion pA2(-160.f,0.f,40.f);
	a2 = new Alarma(device, smgr, pA2);
	addGameObject(a2);

	Posicion posbebida(-300,0,30.f);
 	bebida = new Bebida(device, smgr, posbebida);
 	addGameObject(bebida);

	Posicion postrampa(520,0,30.f);
 	t = new Trampa(device, smgr, postrampa);
 	addGameObject(t);

/* CREAMOS LA BLACKBOARD */

	b=new Blackboard();
	 b->setFuente(f);
	 b->setFuente(f2);
	 b->setComida(c);
	 b->setComida(c2);
	 b->setAlarma(a);
	 b->setAlarma(a2);

/* CREAMOS ENEMIGOS BASICOS */
	
	enem1 = new EnemigoBasico(device, smgr, pos, 80.0, 0.8, 2, this, b, world);
	enemB.push_back(enem1);
	addGameObject(enem1);

	enem2 = new EnemigoBasico(device, smgr, pos2, 80.0, 0.8, 2, this, b, world);
	enemB.push_back(enem2);
	addGameObject(enem2); 

	

/* CREAMOS ENEMIGOS ELITES */

	//enemE1 = new EnemigoElite(device, smgr, pos3, 100.0, 0.36, 2, b, world);
	//enemE.push_back(enemE1);

/* CREAMOS PLATAFORMAS */

	Plataforma = smgr->addCubeSceneNode();

	if (Plataforma) /** SI HEMOS CREADO EL CUBO **/
	{
		Plataforma->setPosition(core::vector3df(220,25,30));
		Plataforma->setScale(core::vector3df(10.f,1.f,5.f));
		Plataforma->setMaterialFlag(video::EMF_LIGHTING, false);
		Plataforma->setMaterialTexture(0,driver->getTexture("resources/plataf.bmp"));
	}

	Plataforma2= smgr->addCubeSceneNode();

	if (Plataforma2) /** SI HEMOS CREADO EL CUBO **/
	{
		Plataforma2->setPosition(core::vector3df(320,55,30));
		Plataforma2->setScale(core::vector3df(10.f,1.f,5.f));
		Plataforma2->setMaterialFlag(video::EMF_LIGHTING, false);
		Plataforma2->setMaterialTexture(0,driver->getTexture("resources/plataf.bmp"));
	}

	Plataforma3= smgr->addCubeSceneNode();

	if (Plataforma3) /** SI HEMOS CREADO EL CUBO **/
	{
		Plataforma3->setPosition(core::vector3df(420,85,30));
		Plataforma3->setScale(core::vector3df(10.f,1.f,5.f));
		Plataforma3->setMaterialFlag(video::EMF_LIGHTING, false);
		Plataforma3->setMaterialTexture(0,driver->getTexture("resources/plataf.bmp"));
	}

/** ESTABLECEMOS LA CAMARA
 Aqui indicamos la posicion de la camara en el espacio 3d. En este caso,
 esta mirando desde la posicion (0, 30, -40) a la (0, 5, 0) donde es
 aproximadamente donde esta el objeto.
**/

	cam = smgr->addCameraSceneNode(0, vector3df(rec->getPosition().X,50,-140), vector3df(0,5,0));
	device->getCursorControl()->setVisible(true);

/* CREAMOS EL TERRENO Y COLISIONES DE CAMARA */

	this->terrainBuilder();

/** TIME AND FRAMES
 Para poder hacer un movimiento independiente del framerate, tenemos que saber
 cuanto ha pasado desde el ultimo frame
**/
	lastFPS = -1;

	then = device->getTimer()->getTime();
	time_input = device->getTimer()->getTime();

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

	terrain = smgr->addTerrainSceneNode(

        "resources/terrain-heightmap.bmp",

        0,                  					// parent node

        -1,                 					// node id

        core::vector3df(-5000, -177, -250),		// position

        core::vector3df(0.f, 0.f, 0.f),     	// rotation

        core::vector3df(40.f, 4.4f, 40.f),  	// scale

        video::SColor ( 255, 255, 255, 255 ),   // vertexColor

        5,                 						// maxLOD

        scene::ETPS_17,             			// patchSize

        4                   					// smoothFactor

        );

    //LE APLICAMOS TEXTURA AL TERRENO

    terrain->setMaterialFlag(video::EMF_LIGHTING, false);
    terrain->setMaterialTexture(0, driver->getTexture("resources/terrain-texture.jpg"));

    //LE APLICAMOS RELIEVE

    terrain->setMaterialTexture(1, driver->getTexture("resources/detailmap3.jpg"));
	terrain->setMaterialType(video::EMT_DETAIL_MAP);
    terrain->scaleTexture(1.0f, 20.0f);

    /** COLISIONES 

    (Aplicado solo a la camara) extraer a clase y aplicar a prota etc 
	create triangle selector for the terrain 

	

    selector = smgr->createTerrainTriangleSelector(terrain, 0);
    terrain->setTriangleSelector(selector);

    // create collision response animator and attach it to the camera

    anim = smgr->createCollisionResponseAnimator(

        selector, cam, core::vector3df(60,100,60),

        core::vector3df(0,0,0),

        core::vector3df(0,50,0));

    selector->drop();
    cam->addAnimator(anim);
    anim->drop();
**/
}

void Mundo::update(){

	//pasos de las fisicas en el mundo
	world.Step(1/60.f, 8, 3);
	//reinicio las fuerzas en el mundo
	world.ClearForces();

	/* Creamos el framedeltatime y el tiempo */

	const u32 now = device->getTimer()->getTime();
	const f32 frameDeltaTime = (f32)(now - then) / 1000.f; // Time in seconds
	then = now;
	f32 tiempo=(f32)(now - time_input)/1000.f;

	core::vector3df protaPosition = prota->getPosition();
	core::vector3df camPosition = cam->getPosition();

	/* PROTA UPDATE */

	this->protaUpdate(now, frameDeltaTime, tiempo);

	/* CAM UPDATE*/

    this->camUpdate(frameDeltaTime);

    b->setTime(frameDeltaTime);
    b->setProta(protaPosition.X);

    /* ALARMA UPDATE*/
    a->update();
    a2->update();


    /* UPDATE DE LOS ENEMIGOS */
    
    for(int i=0; i<enemB.size();i++)
    {
       	enemB[i]->updateTiempo(frameDeltaTime);
     	enemB[i]->Update(prota->getPosition());
    }

    for(int i2=0; i2<enemE.size();i2++)
    {
    	enemE[i2]->updateTiempo(frameDeltaTime);
     	enemE[i2]->Update(prota->getPosition());
    }

    /* DRAW SCENE */

    this->draw();

    /* CONTROL DE FRAMES POR SEGUNDO */

    this->fpsControl();

}

void Mundo::protaUpdate(const u32 now, const f32 frameDeltaTime, f32 tiempo){
	core::vector3df protaPosition = prota->getPosition();

	
	energiaAnterior = prota->getEnergia();
	//prota->gravedad(frameDeltaTime);
    //prota->salto(frameDeltaTime);
    //prota->defender(frameDeltaTime);
    prota->ataque(frameDeltaTime);
    prota->pintarInterfaz();
    //prota->comprobarColision(Plataforma);
    //prota->comprobarColision(Plataforma2);
	prota->comprobarColision(c);
    prota->comprobarColision(bebida);
    prota->comprobarColision(t);

    prota->updateBody(world);

    if(!prota->checkVida())
		device->closeDevice();

    if(tiempo>0.2f) 	// EVITAMOS QUE LO HAYA DENTRO SE HAGA MENOS VECES POR SEGUNDO
    {
        f32 energia=prota->getEnergia();

        time_input=now;

        receiver->checkSigilo(prota,frameDeltaTime);
        receiver->checkCombate(prota);

        for(int i2=0; i2<enemB.size();i2++)
        {
           	prota->comprobarColision(enemB[i2]);
        }
            
    }

    if(prota->getCombate())
    {
    	prota->checkPosCombate();
    }
    receiver->checkInput(prota,frameDeltaTime);

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

void Mundo::camUpdate(const f32 frameDeltaTime){
	core::vector3df protaPosition = prota->getPosition();
	core::vector3df camPosition = cam->getPosition();

	rec->setPosition(protaPosition);
    cam->setPosition(vector3df(protaPosition.X,protaPosition.Y+30,-140)); // cambio 5O A ProtaPosition.Y
    camPosition=rec->getPosition();
    camPosition.Y=protaPosition.Y+30;
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
}
