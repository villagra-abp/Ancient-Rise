
#include <irrlicht.h>
#include <Box2D/Box2D.h>
#include <Box2D/Common/b2Math.h>
#include <GL/gl.h>
#include "../headerfiles/Protagonista.h"
#include "../headerfiles/Enemigo.h"
#include "../headerfiles/Posicion.h"
#include "../headerfiles/MyEventReceiver.h"
#include "../headerfiles/EnemigoBasico.h"
#include "../headerfiles/Comida.h"
#include "../headerfiles/Trampa.h"
#include <iostream>
#include <unistd.h>
#include "../headerfiles/BehaviorTree.h"
#include "../headerfiles/Blackboard.h"


using namespace irr; // Para poder usar cualquier clase del motor Irrlicht se utiliza el namespace irr
using namespace std;

/*
Estos son los 5 sub namespace del motor de Irrlicht

1º irr::core--> En este podemos encontrar las clases basicas como vectores, planos, arrays, listas y demas
2º irr::gui--> Contiene clases utiles para la facil creacion de una interfaz grafica de usuario
3º irr::io-->  Proporciona interfaces para la entrada/salida. Lectura y escritura de ficheros, acceso a ficheros zip, ficheros xml..
4º irr::scene--> Se encuentra toda la gestion de la escena
5º irr::video--> Contiene clases para acceder al driver del video. Todo el rendererizado 3d o 2d se realiza aqui
*/

using namespace core;
using namespace scene;
using namespace video;
using namespace io;
using namespace gui;

// FUNCION PARA FIJAR LOS FPS A 60
void timeWait(){
	static long t=clock();
	const float fps = 60.f;

	long toWait = t + CLOCKS_PER_SEC / fps - clock();
	if(toWait > 0)
		usleep(toWait);

	t = clock();
}



int main()
{

	/**
	El irrlicht device es el objeto nucleo que necesitamos para interactuar con el motor de irrlicht
	Por eso la funcion createDevice es la mas importante puesto que es necesario crear el device para
	poder dibujar cualquier cosa en pantalla

	Tiene 7 parametros:

	-deviceType --> Tipo del device (Null-device, uno de los 2 software renders, OpenGL

    - WindowSize --> Tamaño de la ventana

    - Bits --> Cantidad de bits de colores por pixeles. Puede ser 16 o 32.

    - FUllScreen --> Especifica si queremos que el device se ejecute en pantalla completa o no

    - stencilbuffer --> Especifica si queremos usar el stencil buffer ( para dibujar sombras )

    - vsync --> Especificamos si queremos tener vsync activado, solo es util en pantalla completa

    - eventReceiver --> Un objeto para recibir eventos
	**/

	//Creo la gravedad y el mundo 
	b2Vec2 gravedad(0.f, -9.8f*20);
    b2World world(gravedad);
    


    MyEventReceiver receiver;

	IrrlichtDevice *device =
		createDevice( video::EDT_OPENGL, dimension2d<u32>(1000, 800),16, false, false, false, &receiver);

	if (!device)
		return 1;

    /**
	PUNTEROS AL VideoDriver, al SceneManager y al entorno de interfaz de usuario, para no tener que
	estar llamandolos siempre y solo los llamamos una vez
	*/

	IVideoDriver* driver = device->getVideoDriver();
	ISceneManager* smgr = device->getSceneManager();
	IGUIEnvironment* guienv = device->getGUIEnvironment();

    // CREAMOS PROTA
	Protagonista *prota = new Protagonista(device, smgr);
	scene::ISceneNode  *rec = prota->getNode();
	scene::ISceneNode* Terrain;

	//crea los cuerpos para las fisicas
   
    
  
  	// CREAMOS VECTOR DE POSICIONES PARA EL ENEMIGO
  	typedef vector<Posicion*> patrulla;
	patrulla pos; 
  	Posicion *p0 = new Posicion(40.f,0.f,30.f);
  	pos.push_back(p0);
  	Posicion *p1 = new Posicion(20.f,0.f,30.f);
  	pos.push_back(p1);
  	Posicion *p2 = new Posicion(0.f,0.f,30.f);
  	pos.push_back(p2);
  	Posicion *p3 = new Posicion(-20.f,0.f,30.f);
  	pos.push_back(p3);
  	Posicion *p4 = new Posicion(-40.f,0.f,30.f);
  	pos.push_back(p4);

	patrulla pos2; 
  	Posicion *p5 = new Posicion(60.f,0.f,30.f);
  	pos2.push_back(p5);
  	Posicion *p6 = new Posicion(80.f,0.f,30.f);
  	pos2.push_back(p6);
  	Posicion *p7 = new Posicion(100.f,0.f,30.f);
  	pos2.push_back(p7);


  
	
 
	//CREAMOS ENEMIGO BASICO
	EnemigoBasico *enem1 = new EnemigoBasico(device, smgr, pos);  // dinamico

	//EnemigoBasico ene(device, smgr, posiciones);  No dinamico

	EnemigoBasico *enem2 = new EnemigoBasico(device, smgr, pos2); 

	// CREAMOS EL OBJETO COMIDA
	Posicion p(-150.f, 0.f, 30.f);
	
	Comida *comi = new Comida(smgr, p);

	//CREAMOS EL OBJETO BEBIDA

	Posicion posbebida(-300,0,30.f);
 	Bebida *bebi = new Bebida(smgr, posbebida);
	



	//CREAMOS EL OBJETO TRAMPA

	Posicion postrampa(330,0,30.f);
 	Trampa *tram = new Trampa(smgr, postrampa);
	


	// CREAMOS LA BLACKBOARD
	 Blackboard *b=new Blackboard();
	 b->setEnemigo(enem1);
	 b->setPos(pos);
	 b->setVel(enem1->getVelocidad());

	 // CREAMOS EL ARBOL DE COMPORTAMIENTO PASANDOLE LA BLACKBOARD
	  BehaviorTree beh(1, b);
	

	// Fuente

	scene::ISceneNode *fuente=smgr->addCubeSceneNode();

    if (fuente) /** SI HEMOS CREADO EL CUBO **/
	{
		fuente->setPosition(core::vector3df(-200,0,30));
		//rec->setMaterialTexture(0, driver->getTexture(mediaPath + "wall.bmp"));
		fuente->setMaterialFlag(video::EMF_LIGHTING, true);
		fuente ->setScale(core::vector3df(3.f,1.f,1.f));
	}

	// ALARMA

	scene::ISceneNode *alarma=smgr->addCubeSceneNode();

    if (alarma) /** SI HEMOS CREADO EL CUBO **/
	{
		alarma->setPosition(core::vector3df(220,0,30));
		//rec->setMaterialTexture(0, driver->getTexture(mediaPath + "wall.bmp"));
		alarma->setMaterialFlag(video::EMF_LIGHTING, false);
		alarma ->setScale(core::vector3df(2.f,3.f,1.f));
	}


	scene::ISceneNode* Plataforma= smgr->addCubeSceneNode();

	if (Plataforma) /** SI HEMOS CREADO EL CUBO **/
	{
		Plataforma->setPosition(core::vector3df(220,25,30));
		Plataforma->setScale(core::vector3df(10.f,1.f,5.f));
		Plataforma->setMaterialFlag(video::EMF_LIGHTING, false);
	}

	//creo el suelo, el bounding box del prota y la plataforma
	prota->CreateGround(world, 0.f, -150.f,1000*1000);
    prota->CreateGround(world, 6600.f, 900.f,3200);
    prota->CreateBox(world, 0.f, 200.f);

	/**

	Para poner texto en el subtitulo de la ventana. Necesita de una 'L' delante del string
	debido a que lo necesita el motor de irrlicht

	**/

	device->setWindowCaption(L"Mecanicas Basicas: Movimiento");


	/**

	Etiqueta de texto utilizando el entorno de GUI. Indicamos en que posicion queremos
	colocarla (10,10) y (260,20) es la esquina derecha mas baja

	guienv->addStaticText(L"Hello World! This is the Irrlicht Software renderer!",
		rect<s32>(10,10,260,22), true);
	**/


    /**

	Aqui indicamos la posicion de la camara en el espacio 3d. En este caso,
	esta mirando desde la posicion (0, 30, -40) a la (0, 5, 0) donde es
	aproximadamente donde esta el objeto.

	**/

	scene::ICameraSceneNode* cam =smgr->addCameraSceneNode(0, vector3df(rec->getPosition().X,50,-140), vector3df(0,5,0));
	device->getCursorControl()->setVisible(true);


    /**
	Vamos a dibujar la escena y escribir los fps

	*/

	/*TERRENO*/
	 // add terrain scene node

    //EL TERRENO SE FORMA A PARTIR DE UN MAPA DE ALTURAS

    scene::ITerrainSceneNode* terrain = smgr->addTerrainSceneNode(

        "../resources/terrain-heightmap.bmp",

        0,                  // parent node

        -1,                 // node id

        core::vector3df(-5000, -177, -250),     // position

        core::vector3df(0.f, 0.f, 0.f),     // rotation

        core::vector3df(40.f, 4.4f, 40.f),  // scale

        video::SColor ( 255, 255, 255, 255 ),   // vertexColor

        5,                  // maxLOD

        scene::ETPS_17,             // patchSize

        4                   // smoothFactor

        );



    	//LE APLICAMOS TEXTURA AL TERRENO

    	terrain->setMaterialFlag(video::EMF_LIGHTING, false);



    	terrain->setMaterialTexture(0,

            driver->getTexture("../resources/terrain-texture.jpg"));



    	//LE APLICAMOS RELIEVE

    terrain->setMaterialTexture(1,

            driver->getTexture("../resources/detailmap3.jpg"));

	

	terrain->setMaterialType(video::EMT_DETAIL_MAP);



    terrain->scaleTexture(1.0f, 20.0f);





    //COLISIONES (Aplicado solo a la camara) extraer a clase y aplicar a prota etc 

    // create triangle selector for the terrain
/*
    scene::ITriangleSelector* selector

        = smgr->createTerrainTriangleSelector(terrain, 0);

    terrain->setTriangleSelector(selector);



     // create collision response animator and attach it to the camera

    scene::ISceneNodeAnimator* anim = smgr->createCollisionResponseAnimator(

        selector, cam, core::vector3df(60,100,60),

        core::vector3df(0,0,0),

        core::vector3df(0,50,0));

    selector->drop();

    cam->addAnimator(anim);

    anim->drop();
    */

/*TERRENO*/


	int lastFPS = -1;

	/**
	  Para poder hacer un movimiento independiente del framerate, tenemos que saber
	  cuanto ha pasado desde el ultimo frame
	*/
	u32 then = device->getTimer()->getTime();
	u32 time_input = device->getTimer()->getTime();

	/*bucle del juego*/
	while(device->run())
	{
		// recojo el frame delta time y el tiempo.
		const u32 now = device->getTimer()->getTime();
		const f32 frameDeltaTime = (f32)(now - then) / 1000.f; // Time in seconds
		then = now;
		f32 tiempo=(f32)(now - time_input)/1000.f;


		core::vector3df protaPosition = prota->getPosition();
		core::vector3df camPosition = cam->getPosition();

		//pasos de las fisicas en el mundo
		world.Step(1/60.f, 8, 3);
		//reinicio las fuerzas en el mundo
		world.ClearForces();

		/* funciones del prota que realizo en todas las iteraciones*/
		//prota->gravedad(frameDeltaTime);
        //prota->salto(frameDeltaTime);
        prota->defender(frameDeltaTime);
        prota->ataque(frameDeltaTime);
        prota->pintarInterfaz();
        prota->recuperarEnergia(frameDeltaTime);
        //prota->comprobarColision(Plataforma);

        prota->comprobarColision(comi);
        prota->comprobarColision(bebi);
        prota->comprobarColision(tram);


        prota->updateBody(world);


        if(!prota->checkVida())
        	return 0;




        /* 5 veces por segundo registra si pulsamos s 
        para controlar el modo sigilo y controlar colisiones*/

        if(tiempo>0.2f)
        {
            f32 energia=prota->getEnergia();

            time_input=now;

            receiver.checkSigilo(prota,frameDeltaTime);
            prota->comprobarColision(enem1);
            prota->comprobarColision(enem2);
            
        }

        /* comprueba el resto de inputs*/
        receiver.checkInput(prota,frameDeltaTime);

		/* ajuste de la posicion de la camara y su foco en funcion de la posicion de
		nuestro protagonita */

		rec->setPosition(protaPosition);
        cam->setPosition(vector3df(protaPosition.X,50,-140));
        camPosition=rec->getPosition();
        camPosition.Y=50;
        cam->setTarget(camPosition);

        /*CONTROL DE LA PATRULLA*/

        //enem->update(frameDeltaTime, pos, protaPosition.X, fuente, c.getObjeto());  //INICIAMOS LA PATRULLA DEL ENEMIGO
        //enem->Update(alarma);
        b->setTime(frameDeltaTime);
        b->setProta(protaPosition.X);

       	beh.update();

		/*
		Anything can be drawn between a beginScene() and an endScene()
		call. The beginScene() call clears the screen with a color and
		the depth buffer, if desired. Then we let the Scene Manager and
		the GUI Environment draw their content. With the endScene()
		call everything is presented on the screen.
		*/

		driver->beginScene(true, true, SColor(255,100,101,140));

		smgr->drawAll(); // draw the 3d scene
		device->getGUIEnvironment()->drawAll(); // draw the gui environment (the logo)

		driver->endScene();

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

		timeWait();

	}

	/*
	After we are done with the render loop, we have to delete the Irrlicht
	Device created before with createDevice(). In the Irrlicht Engine, you
	have to delete all objects you created with a method or function which
	starts with 'create'. The object is simply deleted by calling ->drop().
	See the documentation at irr::IReferenceCounted::drop() for more
	information.
	*/

	/**

	Hay que eliminar el objete device que creamos anteriormente antes de terminar con el bucle de render
	En el motor de irrlicht todos los objetos que se han creado mediante una funcion que empieza por
	'create' deben ser eliminados y esto se hace simplemente llamanado a '->drop()'

	**/
	device->drop();
	delete prota;
	delete enem1;
	delete enem2;
    delete b;

	return 0;
}

