#ifndef ALARMASONANDO_H
#define ALARMASONANDO_H

#include "../headerfiles/Task.h"

// Tarea (Condicion) para saber si hay una alarma cerca sonando
class AlarmaSonando : public Task
{
	public:
		
		virtual Status run(Enemigo *e) override;   
		virtual void onInitialize(Blackboard *b) override;
		virtual ~AlarmaSonando();


	private:
		
		Blackboard *board;
	    f32 frameDeltaTime;		  // Tiempo
	    Objeto *a;
	    scene::ISceneNode* enemigoNode;
	
		
};

#endif // ALARMASONANDO_H