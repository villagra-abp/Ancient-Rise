#ifndef HUIR_H
#define HUIR_H

#include "../headerfiles/Task.h"

// Tarea (Accion) para que el enemigo huya durante un tiempo determinado al lado contrario de donde ha visto al protagonista
class Huir : public Task
{
	public:
		
		virtual Status run(Enemigo *e) override;   
		virtual void onInitialize(Blackboard *b) override;
		virtual ~Huir();
		void startClock();


	private:
		
		Blackboard *board;
	    sf::Clock reloj; 		  			// Reloj para controlar el tiempo que tiene que estar huyendo
	    int contador; 			  			// Para reiniciar el reloj cuando toca
	    void* enemigoNode;
	
		
};

#endif // HUIR_H
