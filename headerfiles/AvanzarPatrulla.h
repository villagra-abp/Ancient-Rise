#ifndef AVANZARPATRULLA_H
#define AVANZARPATRULLA_H

#include "../headerfiles/Task.h"



// Tarea (Accion) para realizar la accion de patrullar del enemigo
class AvanzarPatrulla : public Task
{
	public:
		
		virtual Status run(Enemigo *e) override;   			// Hasta que no ponga el override y se declare los metodos abstractos, la clase no deja de ser abstracta al igual que la de su padre
		virtual void onInitialize(Blackboard *b) override;
		void reset(Enemigo *e);
		void startClock();
		void buscarNodoInicial(Enemigo *e, float posX);
		void buscarNodoFinal(Enemigo *e);
		void recorrerNodos(Enemigo *e, uint8_t v, float posX);
		void movimientoDireccion(Enemigo *e, bool d);
		NodoGrafo* calcularNodoMasCercano(NodoGrafo* i, NodoGrafo* i2, float posX);
		virtual ~AvanzarPatrulla();


	private:

		int contadorPatrulla;     // PARA SABER LA POSICION EN LA QUE SE ENCUENTRA EN LA PATRULLA
		vector<Posicion*> pos;	  // Vector con las posiciones de la patrulla
		float protaPosition;	  
		Blackboard *board;		  // Blackboard con los datos necesarios
		sf::Clock reloj; 		  			// Reloj para controlar el tiempo que esta parado el enemigo en una posicion de la patrulla
	    int contadorReloj; 			  			// Para reiniciar el reloj cuando toca

	    bool bajada;

	    /* PATHFINDING */
	    vector<NodoGrafo*> nodos;
	    NodoGrafo *inicioBuenoAux, *finAux;
	    vector <Arista*> caminoCortoAux;
	    NodoGrafo *inicio1, *inicio2, *inicioBueno; 				// Posible nodos iniciales y el nodo definitivo para el pathfinding
	    NodoGrafo *fin; 											// Para almacenar el nodo final del camino
	   	Posicion* posNodo, *posNodoI;
	    Grafo *g; 													// Para poder calcular el camino mas corto
	    vector <Arista*> caminoCorto; 								// Contiene el camino mas corto calculado hasta el punto donde se queria ir
	    bool llegadoInicio=false; 									// Para saber si hemos llegado al nodo inicio
	    bool llegadoFin=false;
	    int iC;
	    float distNodoF, distNodoFY;

	
		
};

#endif // AVANZARPATRULLA_H