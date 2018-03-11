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
		virtual ~ActivarAlarma();


	private:
		
		Blackboard *board;
	    f32 frameDeltaTime;		  // Tiempo
	    vector<Objeto*> a;
	    void* enemigoNode;
	    sf::Clock reloj; 		  			// Reloj para controlar el tiempo que se tarda en activar la alarma
	    int contador;

	    //Datos de alarma
	    Posicion* alarmaPosition;
		float alarmaX;
		int distanciaAlarma;
		int pos;
		
};

#endif // ACTIVARALARMA_H
