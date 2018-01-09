#ifndef IRALARMA_H
#define IRALARMA_H

#include "../headerfiles/Task.h"

// Tarea (Accion) para saber ir hacia la alarma que esta sonando
class IrAlarma : public Task
{
	public:
		
		virtual Status run(Enemigo *e) override;   
		virtual void onInitialize(Blackboard *b) override;
		virtual ~IrAlarma();


	private:
		
		Blackboard *board;
	    f32 frameDeltaTime;		  // Tiempo
	    Objeto *a;
	
		
};

#endif // IRALARMA_H