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
	    glm::f32 frameDeltaTime;		  // Tiempo
	    vector<Alarma*> a;
	    void* enemigoNode;
	
		//Datos de alarma
	    Posicion* alarmaPosition;
		float alarmaX;
		int distanciaAlarma;
		
};

#endif // ALARMASONANDO_H
