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
		virtual ~BuscarComida();


	private:

		vector<Objeto*> c;
		Blackboard *board;
		glm::f32 frameDeltaTime;		  // Tiempo
		void* enemigoNode;
		void* comidaNode;
		sf::Clock reloj; 		  			// Reloj para controlar el tiempo que tarda en comer
	    int contador; 			  			// Para reiniciar el reloj cuando toca
		
	    //DATOS DE LA COMIDA
	    Posicion* comidaPosition;
	    float comidaX;
	    int distanciaComida;
	    int distanciaCaux;

};

#endif // BUSCARCOMIDA_H
