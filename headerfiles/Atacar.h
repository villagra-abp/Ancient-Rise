#ifndef ATACAR_H
#define ATACAR_H

#include "../headerfiles/Task.h"
#include "../headerfiles/Protagonista.h"

// Tarea (Accion) para atacar al protagonista
class Atacar : public Task
{
	public:
		
		virtual Status run(Enemigo *e) override;   
		virtual void onInitialize(Blackboard *b) override;
		void startClock(int t);
		virtual ~Atacar();


	private:

		Blackboard *board;
	    void* enemigoNode;
	    Protagonista* p;

	    int separacionAtaque; 				// Separacion que tiene que haber entre el enemigo y el prota en funcion de si utiliza un arma 
	    									// a distancia o cuerpo a cuerpo
	
		sf::Clock relojPos; 		  		// Reloj para controlar el tiempo que tarda en cambiar la pos de ataque
		sf::Clock relojRec; 				// Reloj para controlar el tiempo que tarda en recargar el proyectil  	
		sf::Clock relojAtq; 				// Reloj para controlar el tiempo que tarda en recargar el proyectil  			
	    int contPos; 			  			// Para reiniciar el reloj cuando toca
	    int contRec;
	    int contAtq;
		
};

#endif // ATACAR_H
