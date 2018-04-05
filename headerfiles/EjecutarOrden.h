#ifndef EJECUTARORDEN
#define EJECUTARORDEN

//#include "../headerfiles/Task.h"
#include "../headerfiles/Atacar.h"

// Tarea (Accion) para que que el enemigo basico ejecute la orden que ha recibido
class EjecutarOrden : public Task
{
	public:
		
		virtual Status run(Enemigo *e) override;   
		virtual void onInitialize(Blackboard *b) override;
		virtual ~EjecutarOrden();


	private:
		
		Blackboard *board;
	    EnemigoBasico *enemBActual;
	    
	    Atacar *at = new Atacar();
	    
	
		
};

#endif // EJECUTARORDEN
