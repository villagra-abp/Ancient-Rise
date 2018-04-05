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
		NodoGrafo* calcularNodoMasCercano(NodoGrafo* i, NodoGrafo* i2, float posX);

	private:

		vector<Objeto*> f;
		Blackboard *board;
		glm::f32 frameDeltaTime;		  // Tiempo
		void* fuenteNode;
		sf::Clock reloj; 		  			// Reloj para controlar el tiempo que tarda en beber
	    int contador; 			  			// Para reiniciar el reloj cuando toca
		
	    //DATOS DE LA FUENTE
	    Posicion* fuentePosition;
	    float fuenteX, fuenteY;;
	    int distanciaFuente, distanciaFaux, pos;
	    Objeto* fuenteCercana;

	    /* PATHFINDING */
	    vector<NodoGrafo*> nodos;
	    NodoGrafo *inicio1; 				// Posible nodo inicial para el pathfinding
	    NodoGrafo *inicio2;
	    NodoGrafo *fin; 					// Para almacenar el nodo final del camino
	    NodoGrafo *inicioBueno; 			// Nodo inicial definitivo para el camino
	   	Posicion* posNodo;
	   	Posicion* posNodoI;
	   	Posicion* prueba;
	    Grafo *g; 							// Para poder calcular el camino mas corto
	    vector <Arista*> caminoCorto; 		// Contiene el camino mas corto calculado hasta el punto donde se queria ir
	    bool llegadoInicio=false; 				// Para saber si hemos llegado al nodo inicio
	    bool llegadoFin=false;


};


#endif // BUSCARAGUA_H
