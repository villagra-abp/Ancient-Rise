#ifndef GRAFO_H
#define GRAFO_H

#include "../headerfiles/NodoGrafo.h"
#include "../headerfiles/Arista.h"

#include <list>

class Grafo
{
	public:
		
		Grafo();
		vector<Arista*> pathfindDijkstra(NodoGrafo *inicio, NodoGrafo *fin);
		void smallestElement();
		void reset();
		virtual ~Grafo();


	private:

		NodoGrafo *current; 					// Nodo en el que nos encontramos en este momento
		NodoGrafo *nodoFinal; 					// Nodo final de la arista
		double nodoFinalCoste;
		std::list<NodoGrafo*> abierta;			// Contiene todos los nodos que han sido vistos pero no han tenido su propia iteracion
		std::list<NodoGrafo*> cerrada;			// Contiene todos los nodos que ya han sido procesados
		std::list<NodoGrafo*>::iterator itA;
		std::list<NodoGrafo*>::iterator itC; 		

		vector<Arista*> aristas; 			
		vector<Arista*> path; 					// Vector con todas las aristas necesarias para encontrar el camino mas corto

		NodoGrafo *startRecord; 				// Para poder tener un seguimiento de la informacion del nodo Inicial
		NodoGrafo *endNodeRecord; 				// Para poder tener un seguimiento de la informacion del nodo final de la arista

		bool encontrado;
		
		
};

#endif // GRAFO_H