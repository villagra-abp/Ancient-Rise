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



	private:
		IVideoDriver* 		driver;
		sf::Clock reloj; 		  			// Reloj para controlar el tiempo que tiene que estar activada la alarma
	    int contador; 			  			// Para reiniciar el reloj cuando toca




};

#endif