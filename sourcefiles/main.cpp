//<<<<<<< HEAD
#include <fmod.hpp>
#include <fmod_studio.hpp>
#include <fmod_errors.h>
#include <cstddef>
/*
#include "../motorgrafico/headerfiles/Motorgrafico.h"
#include "../motorgrafico/headerfiles/ObjetoF.h"
#include "../motorgrafico/headerfiles/Mapa.h"
#include "../motorgrafico/headerfiles/Camara.h"
#include "../motorgrafico/headerfiles/Vector3D.h"
*/
//#include "../motorgrafico/sourcefiles/Motorgrafico.cpp"

#include <cstdio>
#include <Box2D/Box2D.h>

//=======
#include "../headerfiles/Mundo.h"
#include "../headerfiles/Sonido.h"


#include <iostream>
#include <unistd.h>
#include <irrlicht/irrlicht.h>
//>>>>>>> 05cd3d69ce85dd8d26feff530a78ac6bbe0bc3cb

using namespace std;
//<<<<<<< HEAD
using namespace io;

//=======


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

/*void timeWait(){
	static long t=clock();
	const float fps = 60.f;

	long toWait = t + CLOCKS_PER_SEC / fps - clock();
	if(toWait > 0)
		usleep(toWait);

	t = clock();
}*/


//>>>>>>> 05cd3d69ce85dd8d26feff530a78ac6bbe0bc3cb

int main()
{
/*
<<<<<<< HEAD
FMOD_RESULT result;
FMOD::Studio::System* system = NULL;
=======
	
	El irrlicht device es el objeto nucleo que necesitamos para interactuar con el motor de irrlicht
	Por eso la funcion createDevice es la mas importante puesto que es necesario crear el device para
	poder dibujar cualquier cosa en pantalla

	Tiene 7 parametros:

	-deviceType --> Tipo del device (Null-device, uno de los 2 software renders, OpenGL

    - WindowSize --> Tamaño de la ventana

    - Bits --> Cantidad de bits de colores por pixeles. Puede ser 16 o 32.
>>>>>>> 05cd3d69ce85dd8d26feff530a78ac6bbe0bc3cb

result = FMOD::Studio::System::create(&system);
if(result != FMOD_OK){
	printf("FMOD error! (%d) %s\n", result, FMOD_ErrorString(result));
    exit(-1);
} 

result = system->initialize(512, FMOD_STUDIO_INIT_NORMAL, FMOD_INIT_NORMAL, 0);
if(result != FMOD_OK){
	printf("FMOD error! (%d) %s\n", result, FMOD_ErrorString(result));
    exit(-1);
} 

FMOD::System *lowLevelSystem;
result = system->getLowLevelSystem(&lowLevelSystem);
if(result != FMOD_OK){
	printf("FMOD error! (%d) %s\n", result, FMOD_ErrorString(result));
    exit(-1);
} 

FMOD::Channel *channel = NULL;

FMOD::Sound *sound;

<<<<<<< HEAD
const char* name = "resources/sonido/boss3/boss3_NANI.wav";

result = lowLevelSystem->createSound(name,FMOD_DEFAULT,0,&sound);

if(result != FMOD_OK){
	printf("FMOD error! (%d) %s\n", result, FMOD_ErrorString(result));
    exit(-1);
}


	const path mapa = "resources/media/map-20kdm2.pk3";


	Motorgrafico* grafico = Motorgrafico::getInstance();


	string s = "Mapas";
	grafico->setNombreVentana(s);


	grafico->cursorVisible(false);

	Mapa* mapita = new Mapa(mapa);
	mapita->setPosicion(-1300,-144,-1249);

	Camara* camara = new Camara(1);

	Objeto* cubo = new Objeto(0);
	Objeto* esfera = new Objeto(1);

	Vector3D v(0,0,30);

	cubo->setPosicion(v);
	v.Z = 60;
	esfera->setPosicion(v);

	cubo->setMaterial("resources/media/wall.bmp");
	esfera->setMaterial("resources/media/wall.bmp");

	cubo->setLuz(false);
	esfera->setLuz(false);

	int lastFPS = -1;
	u32 then = grafico->getTime();

	const f32 MOVEMENT_SPEED= 100.f;

	while(grafico->getVentanaEstado()){
		if (grafico->getVentanaActiva()){
			system->update();
			const u32 now = grafico->getTime();
			const f32 frameDeltaTime = (f32)(now-then) / 1000.f; //Time in seconds
			then = now; 
			
			Vector3D nodePosicion = camara->getPosicion();
			Vector3D nodeRotation = camara->getRotation();

			Eventlistener receiver = grafico->getListener();
			if(receiver.IsKeyDown('w')){
				nodePosicion.Z += MOVEMENT_SPEED * frameDeltaTime;
				
			}
			else if(receiver.IsKeyDown('s')){
				nodePosicion.Z -= MOVEMENT_SPEED * frameDeltaTime;
			}

			if(receiver.IsKeyDown('a')){
				nodeRotation.Y -= MOVEMENT_SPEED*frameDeltaTime;
			}
			else if(receiver.IsKeyDown('d'))
				nodeRotation.Y += MOVEMENT_SPEED*frameDeltaTime;
			if(receiver.IsKeyDown(3)){
				grafico->cerrar();
			}
			camara->setPosicion(nodePosicion);
			camara->setRotation(nodeRotation);
			
			grafico->draw(255,200,200,200);

			int fps = grafico->getFPS();

			if(lastFPS != fps){
				string str = "Irrlicht Engine - Quake 3 Map example FPS:";
				str += to_string(fps);
	
				grafico->setNombreVentana(str);
				lastFPS = fps;
			}
		} else{
			grafico->suspension();
		}
		
	}
   
	
	delete grafico;
	delete mapita;
	delete camara;
	system->release();
	return 0;
=======
	//IrrXMLReader* xml = createIrrXMLReader("BehaviorTreePatrulla.xml");
	 

	/* CREAMOS IRRLICHT DEVICE */
    MyEventReceiver receiver;

	IrrlichtDevice *device =
		createDevice( video::EDT_OPENGL, dimension2d<u32>(1400, 900),16, false, false, false, &receiver);

	if (!device)
		return 1;

	/*FMOD Inicializar*/
	
	Sonido* sonido = Sonido::getInstance();



	/* CREAMOS MUNDO DEL JUEGO */

	Mundo* mundo = new Mundo(device, &receiver);

	

	/* BUCLE PRINCIPAL DEL JUEGO */

	while(device->run())
	{
		/* ACTUALIZAMOS EL MUNDO */
		sonido->update();
		mundo->update();

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

	delete sonido;
	device->drop();
}

