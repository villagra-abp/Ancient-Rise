#ifndef DETECTARPROTA_H
#define DETECTARPROTA_H

#include "../headerfiles/Task.h"

// Tarea (Condicion) para saber si hemos visto al protagonista
class DetectarProta : public Task
{
	public:
		
		virtual Status run(Enemigo *e) override;   			// Hasta que no ponga el override y se declare los metodos abstractos, la clase no deja de ser abstracta al igual que la de su padre
		virtual void onInitialize(Blackboard *b) override;
		virtual ~DetectarProta();


	private:
		
		Blackboard *board;
	    float protaPosition;

	
		
};

#endif // DETECTARPROTA_H