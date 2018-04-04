#include "../headerfiles/Mundo.h"
#include "../headerfiles/Fachada.h"
#include "../headerfiles/Protagonista.h"

int main()
{

    //Creo la fachada 
    Fachada* fachada = fachada->getInstance(800,600,false);
    //Protagonista* prota = prota->getInstance();
	/* CREAMOS IRRLICHT DEVICE */

	//IrrlichtDevice *device = fachada->getDevice();
    sf::RenderWindow* ventana = fachada->getVentana();

	//if (!device)
		//return 1;
	

	/* CREAMOS MUNDO DEL JUEGO */

	Mundo* mundo = new Mundo();
    TMotorTAG* motorgrafico = TMotorTAG::getInstance();
	

	// BUCLE PRINCIPAL DEL JUEGO 

	while(ventana->isOpen())
	{
		char inputKey;
		bool keyPressed;
        
        glClearColor(0.0f,0.2f,0.5f,0.0f);
		glClearDepth(1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		//Evento
		sf::Event* evento = new sf::Event; 
		//Obtener eventos
		while (ventana->pollEvent(*evento))
		{
		    switch (evento-> type)
		    {
		        case sf::Event::Closed:
		       

		            ventana->close();
		            //device->closeDevice();

		        break;
		    }
		    
		    
		}

        //ventana->clear();
        
		//
		//ventana.draw(rectangle);
		// ACTUALIZAMOS EL MUNDO 
		mundo->update();
		
    motorgrafico->draw();
    ventana->display();

	}

	cout<<"1"<<endl;
    delete mundo;
    cout<<"2"<<endl;
    delete motorgrafico;
    cout<<"3"<<endl;
	delete fachada;
	cout<<"4"<<endl;

}

