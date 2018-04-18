#ifndef CHECKALARMADES_H
#define CHECKALARMADES_H

#include "../headerfiles/Task.h"

// Tarea (Condicion) para comprobar si hay una alarma cerca y desactivada
class CheckAlarmaDes : public Task
{
	public:
		
		virtual Status run(Enemigo *e) override;   
		virtual void onInitialize(Blackboard *b) override;
		virtual ~CheckAlarmaDes();


	private:
		
		Blackboard *board;
	    glm::f32 frameDeltaTime;		  // Tiempo
	    vector<Alarma*> a;
	
		
};

#endif // CHECKALARMADES_H
