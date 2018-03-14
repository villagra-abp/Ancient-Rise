#include "../headerfiles/Mundo.h"
#include "../headerfiles/Fachada.h"
#include "../headerfiles/Protagonista.h"

int main()
{

    //Creo la fachada 
    Fachada* fachada = fachada->getInstance(800,600,false);
    //Protagonista* prota = prota->getInstance();
	/* CREAMOS IRRLICHT DEVICE */
	IrrlichtDevice *device = fachada->getDevice();
    sf::RenderWindow* ventana = fachada->getVentana();

	if (!device)
		return 1;
	

	/* CREAMOS MUNDO DEL JUEGO */
	Mundo* mundo = new Mundo();

	

	/* BUCLE PRINCIPAL DEL JUEGO */

	while(device->run())
	{
		char inputKey;
		bool keyPressed;
		//Evento
		sf::Event* evento = new sf::Event; 
		//Obtener eventos
		while (ventana->pollEvent(*evento))
		{
		    switch (evento-> type)
		    {
		        case sf::Event::Closed:
		       
		            //ventana.close();
		            device->closeDevice();
		        break;

		        case sf::Event::KeyPressed:
		        {    
		            inputKey = evento->key.code;
		            //std::cout<<evento->key.code<<"\n";
		            keyPressed = true;
		           
		        }   
		        break;
		    }
		    
		    
		}
        ventana->clear();
        
		//
		//ventana.draw(rectangle);
		/* ACTUALIZAMOS EL MUNDO */
		mundo->update();
		
		//ventana.display();

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

	delete fachada;
}

