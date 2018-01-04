#include "../headerfiles/Mundo.h"


#include <iostream>
#include <unistd.h>
#include <irrlicht/irrlicht.h>

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

/*void timeWait(){
	static long t=clock();
	const float fps = 60.f;

	long toWait = t + CLOCKS_PER_SEC / fps - clock();
	if(toWait > 0)
		usleep(toWait);

	t = clock();
}*/



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


	//IrrXMLReader* xml = createIrrXMLReader("BehaviorTreePatrulla.xml");
	 
    MyEventReceiver receiver;

	/* CREAMOS IRRLICHT DEVICE */

	IrrlichtDevice *device =
		createDevice( video::EDT_OPENGL, dimension2d<u32>(1000, 800),16, false, false, false, &receiver);

	if (!device)
		return 1;

	/* CREAMOS MUNDO DEL JUEGO */

	Mundo* mundo = new Mundo(device, &receiver);

	

	/* BUCLE PRINCIPAL DEL JUEGO */

	while(device->run())
	{
		/* ACTUALIZAMOS EL MUNDO */
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


	device->drop();
}

