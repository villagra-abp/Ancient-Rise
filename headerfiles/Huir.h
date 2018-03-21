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
		void buscarNodoInicial(Enemigo *e, float posX);
		void recorrerNodos(Enemigo *e, uint8_t v, float posX);
		NodoGrafo* calcularNodoMasCercano(NodoGrafo* i, NodoGrafo* i2, float posX);


	private:
		
		Blackboard *board;
	    sf::Clock reloj; 		  			// Reloj para controlar el tiempo que tiene que estar huyendo
	    int contador; 			  			// Para reiniciar el reloj cuando toca

	    /* Pathfinding */
	    vector<NodoGrafo*> nodos;
	    NodoGrafo *inicio1, *inicio2, *fin; 
	    Posicion *posNodo, *posNodoI;
	
		
};

#endif // HUIR_H
