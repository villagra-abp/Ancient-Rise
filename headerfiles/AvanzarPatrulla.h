#ifndef AVANZARPATRULLA_H
#define AVANZARPATRULLA_H

#include "../headerfiles/Task.h"



// Tarea (Accion) para realizar la accion de patrullar del enemigo
class AvanzarPatrulla : public Task
{
	public:
		
		virtual Status run(Enemigo *e) override;   			// Hasta que no ponga el override y se declare los metodos abstractos, la clase no deja de ser abstracta al igual que la de su padre
		virtual void onInitialize(Blackboard *b) override;
		void startClock();
		virtual ~AvanzarPatrulla();


	private:

		int contadorPatrulla;     // PARA SABER LA POSICION EN LA QUE SE ENCUENTRA EN LA PATRULLA
		vector<Posicion*> pos;	  // Vector con las posiciones de la patrulla
		float protaPosition;	  
		Blackboard *board;		  // Blackboard con los datos necesarios
		sf::Clock reloj; 		  			// Reloj para controlar el tiempo que esta parado el enemigo en una posicion de la patrulla
	    int contadorReloj; 			  			// Para reiniciar el reloj cuando toca

	
		
};

#endif // AVANZARPATRULLA_H