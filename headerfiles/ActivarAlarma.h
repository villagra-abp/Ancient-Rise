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
	    Objeto *a;
	    scene::ISceneNode* enemigoNode;
	    sf::Clock reloj; 		  			// Reloj para controlar el tiempo que se tarda en activar la alarma
	    int contador;
	
		
};

#endif // ACTIVARALARMA_H