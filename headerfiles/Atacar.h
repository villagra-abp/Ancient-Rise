#ifndef ATACAR_H
#define ATACAR_H

#include "../headerfiles/Task.h"
#include "../headerfiles/Protagonista.h"

// Tarea (Accion) para atacar al protagonista
class Atacar : public Task
{
	public:
		
		virtual Status run(Enemigo *e) override;   
		virtual void onInitialize(Blackboard *b) override;
		void startClock(int t);
		void buscarNodoInicial(Enemigo *e, float posX);
		void recorrerNodos(Enemigo *e, uint8_t v, float posX);
		NodoGrafo* calcularNodoMasCercano(NodoGrafo* i, NodoGrafo* i2, float posX);
		void movimientoDireccion(Enemigo *e, bool d);
		void checkComportamiento(Enemigo *e);
		void checkVelocidad(Enemigo *e);
		void reset();
		virtual ~Atacar();


	private:

		Blackboard *board;
	    Protagonista* p;
	    float enemigoY, enemigoX, protaX, protaY;
	    int pos_combate;

	    uint8_t separacionAtaque; 			// Separacion que tiene que haber entre el enemigo y el prota en funcion de si utiliza un arma 
	    									// a distancia o cuerpo a cuerpo
	
		sf::Clock relojPos; 		  		// Reloj para controlar el tiempo que tarda en cambiar la pos de ataque
		sf::Clock relojRec; 				// Reloj para controlar el tiempo que tarda en recargar el proyectil  	
		sf::Clock relojAtq; 				// Reloj para controlar el tiempo que tarda en recargar el proyectil  			
	    int contPos; 			  			// Para reiniciar el reloj cuando toca
	    int contRec;
	    int contAtq;


	    /* PATHFINDING */
	    vector<NodoGrafo*> nodos;
	    NodoGrafo *inicio1, *inicio2, *inicioBueno, *fin;
	    Posicion* posNodoI, *posNodo;
	    vector <Arista*> caminoCorto; 		// Contiene el camino mas corto calculado hasta el punto donde se queria ir	
	    bool llegadoInicio = false;
	    bool llegadoFin = false;
	    Grafo *g; 							// Para poder calcular el camino mas corto
	    int iC; 													// COntador para el recorrido del pathfinding
	    float distNodoF, distNodoFY; 								// Valores para las distancias de los nodos en x e y

	    uint8_t contador;
	    Comportamiento tipo;
	    bool bajada;
		bool primera;

		Fachada* fachada=fachada->getInstance();
};

#endif // ATACAR_H
