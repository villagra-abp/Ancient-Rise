
#include <irrlicht/irrlicht.h>
#include "../headerfiles/Protagonista.h"
#include "../headerfiles/Enemigo.h"
#include "../headerfiles/Posicion.h"
#include "../headerfiles/MyEventReceiver.h"
#include <iostream>
#include <unistd.h>


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

/*
To be able to use the Irrlicht.DLL file, we need to link with the Irrlicht.lib.
We could set this option in the project settings, but to make it easy, we use a
pragma comment lib for VisualStudio. On Windows platforms, we have to get rid
of the console window, which pops up when starting a program with main(). This
is done by the second pragma. We could also use the WinMain method, though
losing platform independence then.
*/
#ifdef _IRR_WINDOWS_
#pragma comment(lib, "Irrlicht.lib")
#pragma comment(linker, "/subsystem:windows /ENTRY:mainCRTStartup")
#endif


void timeWait(){
	static long t=clock();
	const float fps = 60.f;

	long toWait = t + CLOCKS_PER_SEC / fps - clock();
	if(toWait > 0)
		usleep(toWait);

	t = clock();
}

/*
This is the main method. We can now use main() on every platform.
*/
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


    MyEventReceiver receiver;

	IrrlichtDevice *device =
		createDevice( video::EDT_OPENGL, dimension2d<u32>(800, 600),16, false, false, false, &receiver);

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
  
  //vector <Posicion> pos;
	//pos.resize(1);

    Posicion *posiciones[5];

        posiciones[0]=new Posicion(40.f,0.f,30.f);
        posiciones[1]=new Posicion(20.f,0.f,30.f);
        posiciones[2]=new Posicion(0.f,0.f,30.f);
        posiciones[3]=new Posicion(-20.f,0.f,30.f);
        posiciones[4]=new Posicion(-40.f,0.f,30.f);


	//CREAMOS ENEMIGO BASICO
	EnemigoBasico *enem = new EnemigoBasico(device, smgr, posiciones);  // dinamico

	//EnemigoBasico ene(device, smgr, posiciones);  No dinamico


	// Fuente

	scene::ISceneNode *fuente=smgr->addCubeSceneNode();

    if (fuente) /** SI HEMOS CREADO EL CUBO **/
	{
		fuente->setPosition(core::vector3df(-200,0,30));
		//rec->setMaterialTexture(0, driver->getTexture(mediaPath + "wall.bmp"));
		fuente->setMaterialFlag(video::EMF_LIGHTING, true);
	}

	// COMIDA

	scene::ISceneNode *comida=smgr->addCubeSceneNode();

    if (comida) /** SI HEMOS CREADO EL CUBO **/
	{
		comida->setPosition(core::vector3df(200,0,30));
		//rec->setMaterialTexture(0, driver->getTexture(mediaPath + "wall.bmp"));
		comida->setMaterialFlag(video::EMF_LIGHTING, true);
	}

	// ALARMA

	scene::ISceneNode *alarma=smgr->addCubeSceneNode();

    if (alarma) /** SI HEMOS CREADO EL CUBO **/
	{
		alarma->setPosition(core::vector3df(220,0,30));
		//rec->setMaterialTexture(0, driver->getTexture(mediaPath + "wall.bmp"));
		alarma->setMaterialFlag(video::EMF_LIGHTING, false);
	}


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

		/* funciones del prota que realizo en todas las iteraciones*/
        prota->salto(frameDeltaTime);
        prota->defender(frameDeltaTime);
        prota->ataque(frameDeltaTime);
        prota->pintarInterfaz();
        prota->recuperarEnergia(frameDeltaTime);
        if(!prota->checkVida())
        	return 0;



        /* 5 veces por segundo registra si pulsamos s 
        para controlar el modo sigilo y controlar colisiones*/

        if(tiempo>0.2f)
        {
            f32 energia=prota->getEnergia();

            time_input=now;

            receiver.checkSigilo(prota,frameDeltaTime);
            prota->comprobarColision(enem);
            
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
	delete enem;
    //delete [] posiciones;

	return 0;
}

