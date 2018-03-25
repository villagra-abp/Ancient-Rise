#ifndef BUSCARCOMIDA_H
#define BUSCARCOMIDA_H

#include "../headerfiles/Task.h"


// Tarea (Accion) para buscar agua cuando el enemigo tiene hambre
class BuscarComida : public Task
{
	public:

		virtual Status run(Enemigo *e) override;   	
		virtual void onInitialize(Blackboard *b) override;
		void startClock();
		void buscarNodoInicial(Enemigo *e, float posX);
		void recorrerNodos(Enemigo *e, uint8_t v, float posX);
		void buscarComidaCercana(float posEnemX);
		NodoGrafo* calcularNodoMasCercano(NodoGrafo* i, NodoGrafo* i2, float posX);
		void movimientoDireccion(Enemigo *e, bool d);
		virtual ~BuscarComida();


	private:

		vector<Objeto*> c;
		Blackboard *board;
		sf::Clock reloj; 		  			// Reloj para controlar el tiempo que tarda en comer
	    int contador; 			  			// Para reiniciar el reloj cuando toca
	    uint8_t pos;
		
	    //DATOS DE LA COMIDA
	    Posicion* comidaPosition;
	    float comidaX, comidaY;
	    int distanciaComida, distanciaCaux;

	    /* PATHFINDING */
	    vector<NodoGrafo*> nodos;
	    NodoGrafo *inicio1, *inicio2, *inicioBueno, *fin;
	    Posicion* posNodoI, *posNodo;
	    vector <Arista*> caminoCorto; 		// Contiene el camino mas corto calculado hasta el punto donde se queria ir
	    bool llegadoInicio = false;
	    bool llegadoFin = false;
	    Grafo *g; 							// Para poder calcular el camino mas corto
	    int iC;
	    float distNodoF, distNodoFY, distNodoI;
};

#endif // BUSCARCOMIDA_H
