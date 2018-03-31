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
    //TMotorTAG* motorgrafico = TMotorTAG::getInstance();
	
    sf::RectangleShape rectangle;
    rectangle.setPosition(400.f,300.f);
    rectangle.setSize(sf::Vector2f(300,300));
    rectangle.setFillColor(sf::Color(255, 255, 255));
    
    sf::View fixed = ventana->getView(); // The 'fixed' view will never change

    sf::View standard = fixed; // The 'standard' view will be the one that gets always displayed

    unsigned int size = 200; // The 'minimap' view will show a smaller picture of the map
    sf::View minimap(sf::FloatRect(standard.getCenter().x, standard.getCenter().y, static_cast<float>(size), static_cast<float>(ventana->getSize().y*size/ventana->getSize().x)));
    minimap.setViewport(sf::FloatRect(1.f-static_cast<float>(minimap.getSize().x)/ventana->getSize().x-0.02f, 1.f-static_cast<float>(minimap.getSize().y)/ventana->getSize().y-0.02f, static_cast<float>(minimap.getSize().x)/ventana->getSize().x, static_cast<float>(minimap.getSize().y)/ventana->getSize().y));
    minimap.zoom(4.f);

    
    

	// BUCLE PRINCIPAL DEL JUEGO 

	while(ventana->isOpen())
	{
		char inputKey;
		bool keyPressed;
        
        ventana->clear();
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
		//
		// ACTUALIZAMOS EL MUNDO 
		mundo->update();
		
    mundo->draw();
    //ventana->pushGLStates();
    //ventana->setView(view);
	//ventana->setActive(false);
    //ventana->draw(rectangle);
    //ventana->popGLStates();
    ventana->setView(minimap);
    mundo->draw();
    ventana->display();

	}

	
    delete mundo;
    std::cout<<"mundo"<<endl;
    //delete motorgrafico;
    std::cout<<"motor"<<endl;
	delete fachada;
    std::cout<<"fachada"<<endl;

}

