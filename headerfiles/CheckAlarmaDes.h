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
	    f32 frameDeltaTime;		  // Tiempo
	    vector<Objeto*> a;
	    scene::ISceneNode* enemigoNode;
	
		
};

#endif // CHECKALARMADES_H