#ifndef ALARMA_H
#define ALARMA_H


#include "../headerfiles/Objeto.h"


class Alarma : public Objeto
{

	public:
		Alarma(IrrlichtDevice *dev, ISceneManager* smgr, Posicion pos);
		void update();
		void checkActivada();
		void startClock();
		virtual ~Alarma();

		int getContador();

	private:
		IVideoDriver* 		driver;
		sf::Clock reloj; 		  			// Reloj para controlar el tiempo que tiene que estar activada la alarma
	    int contador; 			  			// Para reiniciar el reloj cuando toca
	    core::vector3df alarmaPosition;		// Posicion de la alarma en el mapa



};

#endif