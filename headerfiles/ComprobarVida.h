#ifndef COMPROBARVIDA_H
#define COMPROBARVIDA_H

#include "../headerfiles/Task.h"

// Tarea (Condicion) para comprobar la vida del enemigo de tal manera que si es baja devolvera SUCCESS y tendra que huir
class ComprobarVida : public Task
{
	public:
		
		virtual Status run(Enemigo *e) override;   
		virtual void onInitialize(Blackboard *b) override;
		virtual ~ComprobarVida();


	private:
		
		Blackboard *board;

	
		
};

#endif // COMPROBARVIDA_H