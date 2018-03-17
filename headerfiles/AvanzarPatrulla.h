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
		void recorrerAristas(int num);
		virtual ~AvanzarPatrulla();


	private:

			  
	    uint8_t contadorPatrulla;     					// PARA SABER LA POSICION EN LA QUE SE ENCUENTRA EN LA PATRULLA
		float protaPosition;	  
		Blackboard *board;		  						// Blackboard con los datos necesarios
		sf::Clock reloj; 		  						// Reloj para controlar el tiempo que esta parado el enemigo en una posicion de la patrulla
	    uint8_t contadorReloj; 			  				// Para reiniciar el reloj cuando toca

	    /* GRAFO PATHFINDING */
		vector<NodoGrafo*> pos;	  							// Contiene los nodos que va a reccorer el enemigo para la patrulla
		vector<Arista*> aristSal;	  					// Todas las aristas salientes del nodo en el que se encuentra el enemigo
		Posicion* nodoPosition;
		Comportamiento tipoComp;

	
		
};

#endif // AVANZARPATRULLA_H
