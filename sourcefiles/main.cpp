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

	

	// BUCLE PRINCIPAL DEL JUEGO 

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
		// ACTUALIZAMOS EL MUNDO 
		mundo->update();
		
		//ventana.display();

	}

	


	delete fachada;

}

