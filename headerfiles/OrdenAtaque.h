#ifndef ORDENATAQUE_H
#define ORDENATAQUE_H

#include "../headerfiles/Task.h"

// Tarea (Accion) para que el enemigo Elite ordene a un basico que ataque al prota
class OrdenAtaque : public Task
{
	public:
		
		virtual Status run(Enemigo *e) override;   
		virtual void onInitialize(Blackboard *b) override;
		virtual ~OrdenAtaque();


	private:
		
		Blackboard *board;
	    EnemigoBasico *enemBActual;
	    core::vector3df enemBPosition;
	    
	
		
};

#endif // ORDENATAQUE_H