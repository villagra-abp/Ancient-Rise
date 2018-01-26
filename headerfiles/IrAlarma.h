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
	    vector<Objeto*> a;
	    scene::ISceneNode* enemigoNode;
		
		//Datos de alarma
	    core::vector3df alarmaPosition;
		float alarmaX;
		int distanciaAlarma;
		
};

#endif // IRALARMA_H