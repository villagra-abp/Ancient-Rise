#ifndef CHECKORDEN
#define CHECKORDEN

#include "../headerfiles/Task.h"

// Tarea (Condicion) para que el enemigo basico compruebe si ha recibido una orden de un superior
class CheckOrden : public Task
{
	public:
		
		virtual Status run(Enemigo *e) override;   
		virtual void onInitialize(Blackboard *b) override;
		virtual ~CheckOrden();


	private:
		
	    Blackboard *board;
	
		
};

#endif // CHECKORDEN