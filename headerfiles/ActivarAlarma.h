#ifndef ACTIVARALARMA_H
#define ACTIVARALARMA_H

#include "../headerfiles/Task.h"

// Tarea (Accion) para activar una alarma cercana
class ActivarAlarma : public Task
{
	public:
		
		virtual Status run(Enemigo *e) override;   
		virtual void onInitialize(Blackboard *b) override;
		void startClock();
		void buscarNodoInicial(Enemigo *e, float posX);
		void recorrerNodos(Enemigo *e, uint8_t v, float posX);
		void movimientoDireccion(Enemigo *e, bool d);
		NodoGrafo* calcularNodoMasCercano(NodoGrafo* i, NodoGrafo* i2, float posX);
		virtual ~ActivarAlarma();


	private:
		
		Blackboard *board;
	    vector<Objeto*> a;
	    sf::Clock reloj; 		  			// Reloj para controlar el tiempo que se tarda en activar la alarma
	    int contador;

	    //Datos de alarma
		float alarmaX, alarmaY;
		int distanciaAlarma;
		uint8_t pos;

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

#endif // ACTIVARALARMA_H

