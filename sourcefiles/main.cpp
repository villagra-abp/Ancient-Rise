

//#include "../motorgrafico/headerfiles/Motorgrafico.h"
#include "../motorgrafico/sourcefiles/Motorgrafico.cpp"

#include <iostream>


using namespace std;


/*
This is the main method. We can now use main() on every platform.
*/
int main()
{


	Motorgrafico* grafico = Motorgrafico::getInstance();




	/**

	Para poner texto en el subtitulo de la ventana. Necesita de una 'L' delante del string
	debido a que lo necesita el motor de irrlicht

	**/
	std::string s = "Hola mundo";
	grafico->setNombreVentana(s);


	
	grafico->cursorVisible(true);

	while(grafico->getVentanaEstado()){
		grafico->draw();
	}
   
	
	delete grafico;

	return 0;
}

