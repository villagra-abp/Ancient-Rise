#ifndef BUSCARAGUA_H
#define BUSCARAGUA_H

#include "../headerfiles/Task.h"


// Tarea (Accion) para buscar agua cuando el enemigo tiene sed
class BuscarAgua : public Task
{
	public:

		virtual Status run(Enemigo *e) override;   	
		virtual void onInitialize(Blackboard *b) override;
		virtual ~BuscarAgua();
		void startClock();
		void buscarNodoInicial(Enemigo *e, float posX);
		void recorrerNodos(Enemigo *e, uint8_t v, float posX);
		void buscarFuenteCercana(float posEnemX);
		void movimientoDireccion(Enemigo *e, bool d);
		void checkComportamiento(Enemigo *e);
		void reset();
		NodoGrafo* calcularNodoMasCercano(NodoGrafo* i, NodoGrafo* i2, float posX);

	private:

		vector<Objeto*> f;
		Blackboard *board;
		sf::Clock reloj; 		  			// Reloj para controlar el tiempo que tarda en beber
	    int contador; 			  			// Para reiniciar el reloj cuando toca

	    float enemigoY, enemigoX;
		
	    /* DATOS DE LA FUENTE */
	    Posicion* fuentePosition;
	    float fuenteX, fuenteY;
	    int distanciaFuente, distanciaFaux, pos;

	    /* PATHFINDING */
	    vector<NodoGrafo*> nodos;
	    NodoGrafo *inicio1, *inicio2, *inicioBueno; 				// Posible nodos iniciales y el nodo definitivo para el pathfinding
	    NodoGrafo *fin; 											// Para almacenar el nodo final del camino
	   	Posicion* posNodo, *posNodoI;
	    Grafo *g; 													// Para poder calcular el camino mas corto
	    vector <Arista*> caminoCorto; 								// Contiene el camino mas corto calculado hasta el punto donde se queria ir
	    bool llegadoInicio=false; 									// Para saber si hemos llegado al nodo inicio
	    bool llegadoFin=false;
	    int iC; 													// COntador para el recorrido del pathfinding
	    float distNodoF, distNodoFY; 								// Valores para las distancias de los nodos en x e y
	    Comportamiento tipo;
	    bool bajada;


};


#endif // BUSCARAGUA_H
