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
	    glm::f32 frameDeltaTime;		  // Tiempo
	    vector<Objeto*> a;
	    void* enemigoNode;
		
		//Datos de alarma
	    Posicion* alarmaPosition;
		float alarmaX;
		int distanciaAlarma;
		
};

#endif // IRALARMA_H
